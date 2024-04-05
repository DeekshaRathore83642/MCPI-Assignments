/*
 * timer.h
 *
 *  Created on: Apr 4, 2024
 *      Author: Deeksha Rathore
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define TCLK		16000000
#define TIM_PR		16000

void TimerInit(uint32_t ms);

extern int exti0_flag;

#endif /* TIMER_H_ */
