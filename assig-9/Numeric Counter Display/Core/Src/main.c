/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Numeric Counter Display on LCD
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "LCD.h"
#include <stdio.h>

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int main(void)
{
  char buffer[16];

  HAL_Init();
  SystemClock_Config();   // ✅ NOW DEFINED
  MX_GPIO_Init();
  MX_I2C1_Init();

  lcd_init();             // Mandatory function

  for (int i = 1; i <= 20; i++)
  {
    sprintf(buffer, "%d", i);

    lcd_send_cmd(0x01);   // Clear display
    lcd_send_cmd(0xC0);   // Line 2 address
    lcd_print(buffer);

    HAL_Delay(500);
  }

  while (1)
  {
  }
}

/* ================= SYSTEM CLOCK CONFIG ================= */
/* Minimal clock config using HSI */

void SystemClock_Config(void)
{
  /* Default HSI clock is sufficient for this assignment */
}

/* ================= I2C INIT ================= */

static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  HAL_I2C_Init(&hi2c1);
}

/* ================= GPIO INIT ================= */

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOB_CLK_ENABLE();
}
