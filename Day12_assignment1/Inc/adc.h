/*
 * adc.h
 *
 *  Created on: Apr 6, 2024
 *      Author: Deeksha Rathore
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

void ADC_Init(void);
uint16_t ADC_GetValue(void);

#endif /* ADC_H_ */
