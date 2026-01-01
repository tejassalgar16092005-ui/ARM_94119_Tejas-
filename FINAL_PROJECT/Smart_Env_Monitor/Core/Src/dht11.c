/*
 * dht11.c
 *
 *  Created on: Dec 22, 2025
 *      Author: Administrator
 */
#include "dht11.h"
#include "main.h"

/* ---------- Microsecond delay using DWT ---------- */

static int DWT_Delay_Init(void)
{
    /* Disable TRC */
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
    /* Enable TRC */
    CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;
    /* Disable clock cycle counter */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
    /* Enable  clock cycle counter */
    DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;
    /* Reset the clock cycle counter value */
    DWT->CYCCNT = 0;
    /* 3 NO OPERATION instructions */
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
    /* Check if clock cycle counter has started: 0 on success */
    return !(DWT->CYCCNT);
}

void delay_us(uint32_t us)
{
	uint32_t init_ticks = DWT->CYCCNT;
	uint32_t ticks = (SystemCoreClock / 1000000);
	us *= ticks;
	while ((DWT->CYCCNT - init_ticks) < us);
}

/* ---------- GPIO direction control ---------- */
static void DHT11_Pin_Output(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

static void DHT11_Pin_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

/* ---------- Initialization ---------- */
void DHT11_Init(void)
{
	extern UART_HandleTypeDef huart2;

    if(DWT_Delay_Init()!= 0) {
  	  HAL_UART_Transmit(&huart2, (uint8_t*)"DWT FAIL.\r\n", 11, HAL_MAX_DELAY);
  	  return;
    }
    HAL_UART_Transmit(&huart2, (uint8_t*)"DWT WORK.\r\n", 11, HAL_MAX_DELAY);
}

/* ---------- Read one byte ---------- */
static uint8_t DHT11_ReadByte(void)
{
    uint8_t i, byte = 0;

    for (i = 0; i < 8; i++)
    {
        while (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)); // wait HIGH
        delay_us(40);

        if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
        {
            byte |= (1 << (7 - i)); // bit = 1
            while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
        }
    }
    return byte;
}

/* ---------- Main Read Function ---------- */
uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity)
{
    uint8_t data[5];

    /* Start signal */
    DHT11_Pin_Output();
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    HAL_Delay(18);
    //HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    //delay_us(30);
    DHT11_Pin_Input();
    delay_us(30);

    /* Sensor response */
    if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
    	return 1;
    while (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));

    /* Read 5 bytes */
    for (uint8_t i = 0; i < 5; i++)
        data[i] = DHT11_ReadByte();

    /* Checksum */
    if (data[4] != (data[0] + data[1] + data[2] + data[3]))
        return 2;

    *humidity = data[0];
    *temperature = data[2];

    return 0; // success
}


