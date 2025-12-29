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

/* Mandatory functions */
void lcd_init(void);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_send_nibble(uint8_t nibble);

/* Helper function */
void lcd_print(char *str);

#endif /* INC_LCD_H_ */
