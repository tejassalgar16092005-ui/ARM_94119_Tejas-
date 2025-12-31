/*
 * dht11.h
 *
 *  Created on: Dec 22, 2025
 *      Author: Administrator
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "stm32f407xx.h"   // change family if needed

#define DHT11_PORT GPIOA
#define DHT11_PIN  GPIO_PIN_0

void DHT11_Init(void);
uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity);
void delay_us(uint32_t us);

#endif /* INC_DHT11_H_ */
