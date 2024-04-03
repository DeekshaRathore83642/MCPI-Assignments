/*
 * uart.c
 *
 *  Created on: Apr 1, 2024
 *      Author: rucha
 */

#include "uart.h"

#define TX_PIN 		 2
#define RX_PIN 		 3
#define USART_ALT_FN 7

void UartInit(uint32_t baud)
{
	//UART GPIO Initialization----
	//PA.2 (Tx) and PA.3 (Rx)

	//enable clock

	RCC->AHB1ENR |= BV(RCC_AHB1ENR_GPIOAEN_Pos);

	//Alternate Function = 0111(7)
	//alternate function chya 7th pin vr apn
	//UART as receiver and transmitter work karnaar

	GPIOA->AFR[0] |= ((USART_ALT_FN << GPIO_AFRL_AFSEL3_Pos) | (USART_ALT_FN << GPIO_AFRL_AFSEL2_Pos));
//							0111(7)													0111(7)

	//MODER set karnaar

	GPIOA->MODER |= (BV(TX_PIN * 2 + 1) | BV(RX_PIN * 2 + 1));

	GPIOA->MODER &= ~(BV(TX_PIN * 2) | BV(RX_PIN * 2));

	//OSPEER, speed set karnar

	GPIOA->OSPEEDR &= ~(BV(TX_PIN * 2) | BV(TX_PIN *2 + 1) | BV(RX_PIN * 2) | BV(RX_PIN *2 +1));

	//Pull-Up,Pull-Down Select karnar
	GPIOA->PUPDR &= ~(BV(TX_PIN * 2) | BV(TX_PIN *2 + 1) | BV(RX_PIN * 2) | BV(RX_PIN *2 +1));

	//Push-Pull, OR Open-Drain Mode
	GPIOA->OTYPER &= ~(BV(TX_PIN) | BV(RX_PIN));

	//**UART Config**
	//enable clock

	RCC->APB1ENR |= BV(RCC_APB1ENR_USART2EN_Pos);

	USART2->CR1 = BV(USART_CR1_TE_Pos) | BV(USART_CR1_RE_Pos);

	USART2->CR2 = 0x00000000;

	USART2->CR3 = 0x00000000;

	switch(baud)
	{
	case BAUD_9600:
				USART2->BRR = BAUD_BRR_9600;
				break;
	case BAUD_38400:
				USART2->BRR = BAUD_BRR_38400;
				break;
	case BAUD_115200:
				USART2->BRR = BAUD_BRR_115200;
				break;
	}

	USART2->CR1 |= BV(USART_CR1_UE_Pos);
}

void UartPutch(uint8_t ch)
{
	//wait until TDR is empty

	while((USART2->SR & BV(USART_SR_TXE_Pos)) == 0);

	USART2->DR = ch;

}

uint8_t UartGetch(void)
{
	//wait intil RDR is not empty

	while((USART2->SR & BV(USART_SR_RXNE_Pos)) == 0);

	char ch = USART2->DR;
	return ch;
}

void UartPuts(char str[])
{
	int i;
	for(i=0; str[i] != '\0'; i++)
			UartPutch(str[i]);
}

void UartGets(char str[])
{
	int i=0;
	char ch;
	do
	{
		ch = UartGetch();
		str[i] = ch;
		i++;
	}
	while(ch != '\r');
	str[i] = '\n';
	i++;
	str[i] = '\0';
}






































