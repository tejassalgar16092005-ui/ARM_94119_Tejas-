
#ifndef LCD16X2_I2C_H_
#define LCD16X2_I2C_H_

#include "main.h"
#include <stdbool.h>
#include <stdint.h>

/* LCD commands */
#define LCD_CLEARDISPLAY    0x01
#define LCD_ENTRYMODESET    0x04
#define LCD_DISPLAYCONTROL  0x08
#define LCD_FUNCTIONSET     0x20
#define LCD_SETDDRAMADDR    0x80

/* Entry mode & display control */
#define LCD_ENTRY_ID        0x02
#define LCD_DISPLAY_D       0x04
#define LCD_FUNCTION_N      0x08

/* PCF8574 control bits */
#define LCD_RS              (1 << 0)
#define LCD_EN              (1 << 2)
#define LCD_BK_LIGHT        (1 << 3)

/* I2C slave addresses */
#define LCD_I2C_SLAVE_ADDRESS_0  0x4E
#define LCD_I2C_SLAVE_ADDRESS_1  0x7E

/* LCD API */
HAL_StatusTypeDef lcd_i2c_send_nibble(uint8_t nibble_with_flags);
bool lcd16x2_i2c_init(I2C_HandleTypeDef *pI2cHandle);

void lcd16x2_i2c_setCursor(uint8_t row, uint8_t col);
void lcd16x2_i2c_clear(void);
void lcd16x2_i2c_1stLine(void);

void lcd16x2_i2c_printf(const char* str);


#endif /* LCD16X2_I2C_H_ */
