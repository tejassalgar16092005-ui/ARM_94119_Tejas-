/*
 * lcd.c
 *
 *  Created on: Dec 30, 2025
 *      Author: RITESH
 */
/* LCD header file (contains macros & prototypes) */
#include "lcd.h"

/* Standard C libraries */
#include <stdio.h>      // for
#include <string.h>     // for string handling
#include <stdarg.h>     // for variable arguments

/* STM32 HAL library */
#include "stm32f4xx_hal.h"

/* -------------------------------------------------------------
 * Global Variables
 * ------------------------------------------------------------- */

/* Pointer to I2C handle used by LCD */
I2C_HandleTypeDef* lcd16x2_i2cHandle = NULL;

/* Stores detected LCD I2C address */
uint8_t LCD_I2C_SLAVE_ADDRESS = 0;

/* -------------------------------------------------------------
 * Function: lcd_i2c_send_nibble
 * -------------------------------------------------------------
 * Purpose:
 * Send 4-bit data (nibble) to LCD through I2C.
 *
 * LCD reads data when EN pin changes
 * from HIGH â†’ LOW (falling edge).
 * ------------------------------------------------------------- */
HAL_StatusTypeDef lcd_i2c_send_nibble(uint8_t nibble_with_flags)
{
    uint8_t i2cData[2];

    /* Step 1: EN = HIGH (prepare LCD to read data) */
    i2cData[0] = nibble_with_flags + LCD_EN;

    /* Step 2: EN = LOW (LCD latches data here) */
    i2cData[1] = nibble_with_flags;

    /* Step 3: Send both bytes through I2C */
    return HAL_I2C_Master_Transmit(lcd16x2_i2cHandle,LCD_I2C_SLAVE_ADDRESS,i2cData, 2,  200);
//                lcd16x2_i2cHandle,     -> I2C handle
//                LCD_I2C_SLAVE_ADDRESS, -> LCD I2C address
//                i2cData,               -> data buffer
//                2,                     -> number of bytes
//                200                    -> timeout (ms)
}

/* -------------------------------------------------------------
 * Function: lcd16x2_i2c_sendCommand
 * -------------------------------------------------------------
 * Purpose:
 * Send an 8-bit COMMAND to LCD in 4-bit mode.
 *
 * RS = 0 â†’ Command mode
 * ------------------------------------------------------------- */
void lcd16x2_i2c_sendCommand(uint8_t command)
{
    uint8_t high_nibble;
    uint8_t low_nibble;

    /* Extract upper 4 bits (D7â€“D4) */
    high_nibble = command & 0xF0;

    /* Extract lower 4 bits and shift them to upper position */
    low_nibble = (command << 4);
    low_nibble = low_nibble & 0xF0;

    /* Send upper nibble first */
    lcd_i2c_send_nibble(high_nibble + LCD_BK_LIGHT);

    /* Then send lower nibble */
    lcd_i2c_send_nibble(low_nibble + LCD_BK_LIGHT);
}

/* -------------------------------------------------------------
 * Function: lcd16x2_i2c_sendData
 * -------------------------------------------------------------
 * Purpose:
 * Send one CHARACTER to LCD.
 *
 * RS = 1 â†’ Data mode
 * ------------------------------------------------------------- */
void lcd16x2_i2c_sendData(uint8_t data)
{
    uint8_t high_nibble;
    uint8_t low_nibble;

    /* Upper 4 bits */
    high_nibble = data & 0xF0;

    /* Lower 4 bits shifted to upper position */
    low_nibble = (data << 4);
    low_nibble = low_nibble & 0xF0;

    /* Send upper nibble with RS = 1 */
    lcd_i2c_send_nibble(high_nibble + LCD_BK_LIGHT + LCD_RS);

    /* Send lower nibble with RS = 1 */
    lcd_i2c_send_nibble(low_nibble + LCD_BK_LIGHT + LCD_RS);
}

/* -------------------------------------------------------------
 * Function: lcd16x2_i2c_init
 * -------------------------------------------------------------
 * Purpose:
 * Initialize LCD in 4-bit mode using I2C.
 *
 * Returns:
 * true  â†’ LCD found and initialized
 * false â†’ LCD not detected
 * ------------------------------------------------------------- */
bool lcd16x2_i2c_init(I2C_HandleTypeDef *pI2cHandle)
{
    /* Store I2C handle */
    lcd16x2_i2cHandle = pI2cHandle;

    /* Give time for LCD power-up */
    HAL_Delay(100);

    /* Check first possible I2C address */
    if (HAL_I2C_IsDeviceReady( lcd16x2_i2cHandle,LCD_I2C_SLAVE_ADDRESS_0, 3,100) == HAL_OK)
    {
        LCD_I2C_SLAVE_ADDRESS = LCD_I2C_SLAVE_ADDRESS_0;
    }
    /* Check second possible I2C address */
    else if (HAL_I2C_IsDeviceReady(lcd16x2_i2cHandle,LCD_I2C_SLAVE_ADDRESS_1, 3,100) == HAL_OK)
    {
        LCD_I2C_SLAVE_ADDRESS = LCD_I2C_SLAVE_ADDRESS_1;
    }
    else
    {
        /* LCD not detected */
        return false;
    }

    /* LCD initialization delay */
    HAL_Delay(45);

    /* Force LCD into 8-bit mode (as per datasheet) */
    lcd16x2_i2c_sendCommand(0x30);
    HAL_Delay(5);

    lcd16x2_i2c_sendCommand(0x30);
    HAL_Delay(1);

    lcd16x2_i2c_sendCommand(0x30);
    HAL_Delay(1);

    /* Switch LCD to 4-bit mode */
    lcd16x2_i2c_sendCommand(0x20);
    HAL_Delay(1);

    /* Function set: 4-bit, 2-line display */
    lcd16x2_i2c_sendCommand(LCD_FUNCTIONSET + LCD_FUNCTION_N);

    /* Display OFF */
    lcd16x2_i2c_sendCommand(LCD_DISPLAYCONTROL);

    /* Clear display */
    lcd16x2_i2c_sendCommand(LCD_CLEARDISPLAY);
    HAL_Delay(2);

    /* Entry mode: cursor moves right */
    lcd16x2_i2c_sendCommand(LCD_ENTRYMODESET + LCD_ENTRY_ID);

    /* Display ON, cursor OFF */
    lcd16x2_i2c_sendCommand(LCD_DISPLAYCONTROL + LCD_DISPLAY_D);

    return true;
}

/* -------------------------------------------------------------
 * Function: lcd16x2_i2c_setCursor
 * -------------------------------------------------------------
 * Purpose:
 * Move cursor to specified row and column.
 * ------------------------------------------------------------- */
void lcd16x2_i2c_setCursor(uint8_t row, uint8_t col)
{
    uint8_t address;

    /* Limit column to 0â€“15 */
    if (col > 15)
        col = 15;

    /* Calculate DDRAM address */
    if (row == 0)
        address = 0x80 + col;   // First line
    else
        address = 0xC0 + col;   // Second line

    lcd16x2_i2c_sendCommand(address);
}

/* -------------------------------------------------------------
 * LCD Utility Functions
 * ------------------------------------------------------------- */

void lcd16x2_i2c_clear(void)
{
    lcd16x2_i2c_sendCommand(LCD_CLEARDISPLAY);
    HAL_Delay(3);
}
void lcd16x2_i2c_1stLine(void)
{
    lcd16x2_i2c_setCursor(0, 0);
}

/* -------------------------------------------------------------
 * Function: lcd16x2_i2c_printf
 * -------------------------------------------------------------
 * Purpose:
 * Print formatted text on LCD (like printf)
 * ------------------------------------------------------------- */
void lcd16x2_i2c_printf(const char* str)
{
	    uint8_t i = 0;

	    while (str[i] != '\0')
	    {
	        lcd16x2_i2c_sendData(str[i]);
	        i++;
	    }
}


void lcd_print_number(uint8_t num)
{
    if (num >= 10)
    {
        lcd16x2_i2c_sendData((num / 10) + '0');
    }
    lcd16x2_i2c_sendData((num % 10) + '0');
}

