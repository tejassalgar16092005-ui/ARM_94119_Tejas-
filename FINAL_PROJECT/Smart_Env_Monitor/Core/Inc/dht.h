/*
 * dht.h
 *
 *  Created on: Dec 31, 2025
 *      Author: tejas
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_
#include "stm32f4xx_hal.h"   // change if needed

/* ===== PIN DEFINITIONS ===== */
#define DHT11_PORT GPIOA
#define DHT11_PIN  GPIO_PIN_1   // <-- CHANGE PIN NUMBER HERE

/* ===== VARIABLES ===== */
extern uint8_t DHT11_Temperature;
extern uint8_t DHT11_Humidity;

/* ===== FUNCTIONS ===== */
void DHT11_Init(void);
uint8_t DHT11_Read(void);



#endif /* INC_DHT_H_ */
