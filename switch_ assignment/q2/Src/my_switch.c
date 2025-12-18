/*
 * my_switch.c
 *
 *  Created on: Dec 17, 2025
 *      Author: kiran_z6dopa8
 */

#include <stdint.h>
#include <stdio.h>
#include"stm32f407xx.h"
#include"my_switch.h"


void switch_init(void)
{
	//0. enable clock for GPIOA in AHB1
	RCC->AHB1ENR |= BV(0);
	//1. select mode as Input
	GPIOA->MODER &= ~(BV(0) | BV(1) );


	//2. select type as push pull
	//GPIOA->OTYPER &= ~(BV(0) );
	//3. select speed as low
	GPIOA->OSPEEDR &= ~(BV(0) | BV(1));

	//4. select pull up/down as no
	GPIOA->PUPDR &= ~(BV(0) | BV(1));

}
int switch_status(void)
{
	if ((GPIOA->IDR) & BV(0) )
	{
		return 1 ; // switch is press
	}
	else
	{
		return 0 ; // switch is nor press
	}
}
