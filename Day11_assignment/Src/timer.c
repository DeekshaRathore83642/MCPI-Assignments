/*
 * timer.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Deeksha Rathore
 */
#include "timer.h"


// Refer user manual 17.3.10: PWM mode.
/*
1. Setup PWM clock (10 KHz to 100 KHz). Program the period and the duty cycle respectively in ARR and CCRx registers.
	* PCLK = 16MHz, PSC = 16 --> TCLK = 1MHz
	* ARR = 100 => PWM output freq = TCLK / ARR = 1 MHz / 100 = 10 KHz
	* CCR = 50 => 50% Duty Cycle
2. Configure the output pin:
    * Select the output mode by writing CCS bits (00 = output) in CCMRx register.
    * Select the polarity by writing the CCxP bit (0 = active high) in CCER register.
3. Select the PWM mode (PWM11 or PWM2) by writing OCxM bits in CCMRx register.
    * The PWM mode can be selected independently on each channel (one PWM per OCx output) by writing 110 (PWM mode 1) or 111 (PWM mode 2) in the TIMx_CCMRx register.
4. Set the preload bit in CCMRx register and the ARPE bit in the CR1 register.
5. Select the counting mode in CR1:
    * PWM edge-aligned mode (00): the counter must be configured up-counting or down-counting.
    * PWM center aligned mode: the counter mode must be center aligned counting mode (CMS bits different from '00').
6. Enable the capture compare in CCER.
7. Enable main output in BDTR and Enable the counter.
*/

void TimerInit(void) {
    // Enable GPIO clock for port C.6
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    // Configure PC6 as alternate function mode
    GPIOC->MODER |= (2 << 6*2);
    // Set alternate function as Timer8 output (AF3)
    GPIOC->AFR[0] |= (3 << GPIO_AFRL_AFSEL6_Pos);

    // Enable Timer8 clock
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;

    // Set prescaler value
    TIM8->PSC = (TIM_PSC-1);  // Prescaler value
    // Set ARR value to 100 for 10KHz PWM output freq
    TIM8->ARR = (100-1);
    // Set CCR value i.e. Duty Cycle (must be less than ARR value)
    TIM8->CCR1 = 1-1;

    // Configure Timer8 channels as output channel
    //TIM8->CCMR1 &= ~TIM_CCMR1_CC1S;	// default
    // Configure Timer8 channel polarity as active high
    //TIM8->CCER &= ~TIM_CCER_CC1P;		// default
    // Configure Timer8 for output compare mode
    TIM8->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; // PWM Mode 1 => 110

    // Set the preload bit in CCMRx register
    TIM8->CCMR1 |= TIM_CCMR1_OC1PE;
    // Set the ARPE bit in the CR1 register.
    TIM8->CR1 |= TIM_CR1_ARPE;
    // Set the PWM edge align mode in the CR1 register.
    //TIM8->CR1 &= ~TIM_CR1_CMS;	// default

    // Configure Timer8 output OCx signal to output pin
    TIM8->CCER |= TIM_CCER_CC1E;

    // Enable Timer 8 Main output and Timer8 peripheral
    TIM8->BDTR |= TIM_BDTR_MOE;
    TIM8->CR1 |= TIM_CR1_CEN;
}

