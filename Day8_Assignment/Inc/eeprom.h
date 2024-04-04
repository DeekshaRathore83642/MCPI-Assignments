

#ifndef EEPROM_H_
#define EEPROM_H_

#include "i2c.h"

#define EEPROM_W	0xA0
#define EEPROM_R	0xA1

void EEPROM_Init(void);
void EEPROM_Write(uint16_t addr, uint8_t byte[], uint8_t n);
void EEPROM_Read(uint16_t addr, uint8_t byte[], uint8_t n);

#endif /* EEPROM_H_ */
