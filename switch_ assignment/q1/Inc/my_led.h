/*
 * my_led.h
 *
 *  Created on: Dec 17, 2025
 *      Author: kiran_z6dopa8
 */

#ifndef MY_LED_H_
#define MY_LED_H_

#include <stdint.h>
#include <stdio.h>
#include"stm32f407xx.h"

#define BV(n) (1 << (n))

#define GREEN_LED     12
#define ORANGE_LED    13
#define RED_LED       14
#define BLUE_LED      15

#define LED_PORT GPIOD


void led_init(void);
void led_on(void);
void led_off(void);

#endif /* MY_LED_H_ */
