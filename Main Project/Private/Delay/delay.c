/*
 * delay.c
 *
 *  Created on: 07-Jun-2019
 *      Author: poe
 */


/* using TIM 1 to create a delay in microseconds
 * TIM2 Running at 72 MHz
 * therefore prescalar is set to 72-1 to reduce it to 1 MHz
 * ARR is set to MAX i.e. 0xffff
 * rest is unchanged
 */


#include "delay.h"
#include "stm32f1xx.h"

//extern TIM_HandleTypeDef handler_timer1;
extern TIM_HandleTypeDef htim2;


void delay_init ()
{
	HAL_TIM_Base_Start(&htim2);  // change this according to ur setup
}

void delay_us (u16 delay)
{
	__HAL_TIM_SET_COUNTER(&htim2, 0);  // reset the counter
	while ((__HAL_TIM_GET_COUNTER(&htim2))<delay);  // wait for the delay to complete
}

void delay_ms(u16 delay)
{
	HAL_Delay (delay);  // better use HAL_DElay in millis
}
