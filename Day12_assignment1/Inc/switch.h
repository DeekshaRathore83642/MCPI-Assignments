/*
 * switch.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Deeksha Rathore
 */

#ifndef SWITCH_H_
#define SWITCH_H_


#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define SWITCH_GPIO		GPIOA
#define SWITCH_GPIO_EN	0

#define SWITCH			0

void SwitchInit(uint32_t pin);
int SwitchGetState(uint32_t pin);

extern int exti0_flag;

#endif /* SWITCH_H_ */
