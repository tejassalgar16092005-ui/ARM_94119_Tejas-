/*
 * MQ2.c
 *
 *  Created on: Dec 30, 2025
 *      Author: RITESH
 */
#include "MQ2.h"

/* Standard C libraries */
#include <stdio.h>      // for
#include <string.h>     // for string handling
#include <stdarg.h>     // for variable arguments

/* STM32 HAL library */
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

void Smoke_Monitor_Task(void)
{
    uint32_t sum = 0;
    uint32_t adc_val = 0;
    char lcd_buf[16];
	char str[32]="SMOKE DETECTED\t";
	char str2[50]="Air Normal\t";
	char str3[20]="\r\n";
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

    lcd16x2_i2c_clear();

    if (adc_val > SMOKE_THRESHOLD)
    {
        /* Alert ON */
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);

    	    lcd16x2_i2c_setCursor(0, 0);
    	    lcd16x2_i2c_printf("SMOKE DETECTED");
    	    HAL_UART_Transmit(&huart2,(uint8_t*)str,strlen(str),HAL_MAX_DELAY);

    	    sprintf(lcd_buf, "ADC:%lu", adc_val);

    	    HAL_UART_Transmit(&huart2, (uint8_t *)lcd_buf, strlen(lcd_buf), HAL_MAX_DELAY);
    	    HAL_UART_Transmit(&huart2,(uint8_t*)str3,strlen(str3),HAL_MAX_DELAY);
    	    lcd16x2_i2c_setCursor(1, 0);
    	    lcd16x2_i2c_printf(lcd_buf);
    }
    else
    {
        /* Alert OFF */
    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);

    	    lcd16x2_i2c_setCursor(0, 0);
    	    lcd16x2_i2c_printf("Air Normal");
    	    HAL_UART_Transmit(&huart2,(uint8_t*)str2,strlen(str2),HAL_MAX_DELAY);

    	    sprintf(lcd_buf, "ADC:%lu", adc_val);

    	    HAL_UART_Transmit(&huart2, (uint8_t *)lcd_buf, strlen(lcd_buf), HAL_MAX_DELAY);
    	    HAL_UART_Transmit(&huart2,(uint8_t*)str3,strlen(str3),HAL_MAX_DELAY);
    	    lcd16x2_i2c_setCursor(1, 0);
    	    lcd16x2_i2c_printf(lcd_buf);
    }
}

