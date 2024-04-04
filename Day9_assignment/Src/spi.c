/*
 * spi.c
 *
 *  Created on: Apr 3, 2024
 *      Author: Nilesh
 */

#include "spi.h"

void SPI_Init(void) {
	// SPI GPIO CS pin config
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	GPIOE->MODER &= ~BV(SPI_CS_PIN*2+1); // GPIO mode=OUTPUT(0b01)
	GPIOE->MODER |= BV(SPI_CS_PIN*2);
	GPIOE->OSPEEDR &= ~BV(SPI_CS_PIN*2+1); // GPIO speed=Medium(0b01)
	GPIOE->OSPEEDR |= BV(SPI_CS_PIN*2);
	GPIOE->PUPDR &= ~(BV(SPI_CS_PIN*2+1) | BV(SPI_CS_PIN*2)); // GPIO No Pull-up/down (0b00)
	GPIOE->OTYPER &= ~BV(SPI_CS_PIN);	// GPIO push-pull
	// Disable slave initially
	SPI_CS_Disable();

	// SPI GPIO MOSI, MISO, SCLK pin config
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~(BV(SPI_MOSI_PIN*2)|BV(SPI_MISO_PIN*2)|BV(SPI_SCLK_PIN*2)); // GPIO mode=AltFn(0b10)
	GPIOA->MODER |= (BV(SPI_MOSI_PIN*2+1)|BV(SPI_MISO_PIN*2+1)|BV(SPI_SCLK_PIN*2+1));
	GPIOA->OSPEEDR &= ~(BV(SPI_MOSI_PIN*2+1)|BV(SPI_MISO_PIN*2+1)|BV(SPI_SCLK_PIN*2+1)); // GPIO speed=Medium(0b01)
	GPIOA->OSPEEDR |= (BV(SPI_MOSI_PIN*2)|BV(SPI_MISO_PIN*2)|BV(SPI_SCLK_PIN*2));
	GPIOA->PUPDR &= ~(BV(SPI_MOSI_PIN*2)|BV(SPI_MISO_PIN*2)|BV(SPI_SCLK_PIN*2)); // GPIO Pull-Down (0b10)
	GPIOA->PUPDR |= (BV(SPI_MOSI_PIN*2+1)|BV(SPI_MISO_PIN*2+1)|BV(SPI_SCLK_PIN*2+1));
	GPIOA->OTYPER &= ~(BV(SPI_MOSI_PIN)|BV(SPI_MISO_PIN)|BV(SPI_SCLK_PIN));	// GPIO push-pull
	GPIOA->AFR[0] |= (SPI_ALT_FN << GPIO_AFRL_AFSEL5_Pos) | (SPI_ALT_FN << GPIO_AFRL_AFSEL6_Pos) | (SPI_ALT_FN << GPIO_AFRL_AFSEL7_Pos); /* BUG FIXED |= */

	// SPI bus config
	// Enable SPI clock
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	// CR1: Master=1, BR=0x02(010), LSBF=0, DFF=0 (8-bit), CRCEN=0,
	//		SSM=1 & SSI=1 (Soft Slave Manage), BIDI=0 and RXONLY=0 for Full Duplex,
	//		CPOL=0 and CPHA=0 for LIS3DSH
	SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | (0x02 << SPI_CR1_BR_Pos);

	// CR2 = Motorola Frame, No intr enabled, No dma enabled, No SS output
	SPI1->CR2 = 0x0000;
	// Enable SPI
	SPI1->CR1 |= SPI_CR1_SPE; /*bug fixed |= */
}

uint16_t SPI_Transmit(uint8_t dataW) {
	// wait while tx regr is not empty
	while(!(SPI1->SR & SPI_SR_TXE))
		;
	// write given data into spi data regr
	uint32_t frame = dataW;
	SPI1->DR = frame;
	// wait while rx regr is empty
	while(!(SPI1->SR & SPI_SR_RXNE))
		;
	// read data from spi data regr
	frame = SPI1->DR;
	return frame;
}

uint16_t SPI_Receive(void) {
	// send dummy data (0x00) and receive data from slave
	uint32_t val = SPI_Transmit(0x00);
	// return received data
	return val;
}

void SPI_CS_Enable(void) {
	// PE.3 = 0 (active low)
	GPIOE->BSRR = BV(SPI_CS_CLR_BIT);
}

void SPI_CS_Disable(void) {
	// PE.3 = 1 (active low)
	GPIOE->BSRR = BV(SPI_CS_SET_BIT);
}

