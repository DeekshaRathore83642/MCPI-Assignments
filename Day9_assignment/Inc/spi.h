

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define SPI_SCLK_PIN			5
#define SPI_MISO_PIN			6
#define SPI_MOSI_PIN			7

#define SPI_CS_PIN			3
#define SPI_CS_SET_BIT		SPI_CS_PIN
#define SPI_CS_CLR_BIT		(16+SPI_CS_PIN)

#define SPI_ALT_FN			5

void SPI_Init(void);
uint16_t SPI_Transmit(uint8_t dataW);
uint16_t SPI_Receive(void);
void SPI_CS_Enable(void);
void SPI_CS_Disable(void);

#endif /* SPI_H_ */
