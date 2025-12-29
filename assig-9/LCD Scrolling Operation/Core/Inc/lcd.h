/*
 * LCD.h
 *
 *  Created on: Dec 26, 2025
 *  Author: Omkar
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

uint8_t lcd16x2_i2c_init(I2C_HandleTypeDef *hi2c);
void lcd16x2_i2c_clear(void);
void lcd16x2_i2c_setCursor(uint8_t row, uint8_t col);
void lcd16x2_i2c_printf(char *str);

/* Scroll functions */
void lcd16x2_i2c_scrollLeft(void);
void lcd16x2_i2c_scrollRight(void);

#endif /* INC_LCD_H_ */
