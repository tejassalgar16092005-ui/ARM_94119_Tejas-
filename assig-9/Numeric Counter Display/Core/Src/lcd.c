/*
 * LCD.c
 *
 *  Created on: Dec 26, 2025
 *  Author: Omkar
 */

#include "LCD.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR       (0x27 << 1)
#define LCD_BACKLIGHT  0x08
#define LCD_EN         0x04
#define LCD_RS         0x01

void lcd_send_nibble(uint8_t nibble)
{
  uint8_t data = nibble | LCD_BACKLIGHT;

  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, 100);

  data |= LCD_EN;
  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, 100);
  HAL_Delay(1);

  data &= ~LCD_EN;
  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, 100);
}

void lcd_send_cmd(uint8_t cmd)
{
  lcd_send_nibble(cmd & 0xF0);
  lcd_send_nibble((cmd << 4) & 0xF0);
  HAL_Delay(2);
}

void lcd_send_data(uint8_t data)
{
  lcd_send_nibble((data & 0xF0) | LCD_RS);
  lcd_send_nibble(((data << 4) & 0xF0) | LCD_RS);
}

void lcd_init(void)
{
  HAL_Delay(50);
  lcd_send_cmd(0x33);
  lcd_send_cmd(0x32);
  lcd_send_cmd(0x28);
  lcd_send_cmd(0x0C);
  lcd_send_cmd(0x06);
  lcd_send_cmd(0x01);
}

void lcd_print(char *str)
{
  while (*str)
  {
    lcd_send_data(*str++);
  }
}
