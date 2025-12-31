/*shree ganeshaiy namahaa
 * dht.c
 *
 *  Created on: Dec 31, 2025
 *      Author: tejas
 */
#include "dht.h"

/* Standard C libraries */
#include <stdio.h>      // for
#include <string.h>     // for string handling
#include <stdarg.h>     // for variable arguments

/* STM32 HAL library */
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

/* Global variables */
uint8_t DHT11_Temperature = 0;
uint8_t DHT11_Humidity    = 0;

/* -------- GPIO MODE -------- */
static void DHT11_Pin_Output(void)
{
    GPIO_InitTypeDef gpio = {0};
    gpio.Pin = DHT11_PIN;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT11_PORT, &gpio);
}

static void DHT11_Pin_Input(void)
{
    GPIO_InitTypeDef gpio = {0};
    gpio.Pin = DHT11_PIN;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;     // IMPORTANT
    HAL_GPIO_Init(DHT11_PORT, &gpio);
}

/* -------- MICROSECOND DELAY -------- */
static void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT - start) < ticks);
}

/* -------- INIT -------- */
void DHT11_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
}

/* -------- READ SENSOR -------- */
uint8_t DHT11_Read(void)
{
    uint8_t data[5] = {0};
    uint8_t i, j;

    /* START SIGNAL */
    DHT11_Pin_Output();
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    HAL_Delay(18);
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    delay_us(30);
    DHT11_Pin_Input();

    /* RESPONSE */
    delay_us(40);
    if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
        return 1;

    delay_us(80);
    if (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
        return 2;

    delay_us(80);

    /* READ 40 BITS */
    for (j = 0; j < 5; j++)
    {
        for (i = 0; i < 8; i++)
        {
            while (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
            delay_us(40);

            if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
            {
                data[j] |= (1 << (7 - i));
                while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
            }
        }
    }

    /* CHECKSUM */
    if (data[4] != (data[0] + data[1] + data[2] + data[3]))
        return 3;

    /* STORE VALUES */
    DHT11_Humidity    = data[0];
    DHT11_Temperature = data[2];

    return 0;   // SUCCESS
}


