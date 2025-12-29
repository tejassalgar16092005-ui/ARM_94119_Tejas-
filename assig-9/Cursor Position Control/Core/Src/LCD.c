/*
 * LCD.c
 *
 *  Created on: Dec 26, 2025
 *  Author: Omkar
 */

#include "LCD.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_I2C_ADDR   (0x27 << 1)
#define LCD_BACKLIGHT  0x08
#define LCD_EN         0x04
#define LCD_RS         0x01

static void lcd_i2c_write(uint8_t data)
{
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &data, 1, 100);
}

static void lcd_send_nibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data = nibble | rs | LCD_BACKLIGHT;
    lcd_i2c_write(data | LCD_EN);
    HAL_Delay(1);
    lcd_i2c_write(data & ~LCD_EN);
}

static void lcd_send_cmd(uint8_t cmd)
{
    lcd_send_nibble(cmd & 0xF0, 0);
    lcd_send_nibble((cmd << 4) & 0xF0, 0);
    HAL_Delay(2);
}

static void lcd_send_data(uint8_t data)
{
    lcd_send_nibble(data & 0xF0, LCD_RS);
    lcd_send_nibble((data << 4) & 0xF0, LCD_RS);
}

uint8_t lcd16x2_i2c_init(I2C_HandleTypeDef *hi2c)
{
    HAL_Delay(50);
    lcd_send_cmd(0x33);
    lcd_send_cmd(0x32);
    lcd_send_cmd(0x28);
    lcd_send_cmd(0x0C);
    lcd_send_cmd(0x06);
    lcd_send_cmd(0x01);
    return 1;
}

void lcd16x2_i2c_clear(void)
{
    lcd_send_cmd(0x01);
}

void lcd16x2_i2c_setCursor(uint8_t row, uint8_t col)
{
    uint8_t address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(address);
}

void lcd16x2_i2c_printf(char *str)
{
    while (*str)
    {
        lcd_send_data(*str++);
    }
}
