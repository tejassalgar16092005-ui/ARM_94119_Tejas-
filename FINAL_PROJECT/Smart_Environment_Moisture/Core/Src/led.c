/*
 * led.c
 *
 *  Created on: Dec 30, 2025
 *      Author: RITESH
 */
#include "led.h"
/* Standard C libraries */
#include <stdio.h>      // for
#include <string.h>     // for string handling
#include <stdarg.h>     // for variable arguments

/* STM32 HAL library */
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;

void Led_Alert(void)
{

    /* Take 10 ADC samples for stability */
    uint32_t sum = 0;
    uint32_t adc_val = 0;
    char lcd_buf[16];
    /* Take 10 ADC samples for stability */
    for (int i = 0; i < 10; i++)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        sum += HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
        HAL_Delay(5);
    }

    adc_val = sum / 10;
    if (adc_val > SMOKE_THRESHOLD)
    {
        /* Alert ON */
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);

    }
    else
    {
        /* Alert OFF */
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);

    }
}

