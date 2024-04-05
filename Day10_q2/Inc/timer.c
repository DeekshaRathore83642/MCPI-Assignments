/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: rucha
 */

#include "timer.h"

void TimerInit(void)
{
	// enable timer clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	// set prescalar
	TIM7->PSC = TIM_PR-1;
}

void TimerDelayMs(uint32_t ms)
{
	// set number of clocks to count
	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
	TIM7->ARR = cnt - 1;
	// start count from 0
	TIM7->CNT = 0;
	// start timer counter
	TIM7->CR1 |= TIM_CR1_CEN;
	// wait for update interrupt flag
	while(! (TIM7->SR & TIM_SR_UIF));
	// clear the update interrupt flag
	TIM7->SR &= ~TIM_SR_UIF;
	// stop timer counter
	TIM7->CR1 &= ~TIM_CR1_CEN;
}




