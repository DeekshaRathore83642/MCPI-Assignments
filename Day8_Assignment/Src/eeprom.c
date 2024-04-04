


#include "eeprom.h"

void EEPROM_Init(void) {
	int ret;
	I2CInit();
	// optional -- check if eeprom is present
	I2CStart();
	ret = I2CIsDeviceReady(EEPROM_W);
	// if ret=0, eeprom not avail; otherwise, eeprom is avail.
	I2CStop();
}

void EEPROM_Write(uint16_t addr, uint8_t byte[], uint8_t n) {
	uint8_t high = addr >> 8, low = addr & 0xFF;
	I2CStart();
	I2CSendSlaveAddress(EEPROM_W);
	I2CSendData(high);
	I2CSendData(low);
	for(int i=0; i<n; i++)
		I2CSendData(byte[i]);
	I2CStop();
}

void EEPROM_Read(uint16_t addr, uint8_t byte[], uint8_t n) {
	int i;
	uint8_t high = addr >> 8, low = addr & 0xFF;
	I2CStart();
	I2CSendSlaveAddress(EEPROM_W);
	I2CSendData(high);
	I2CSendData(low);
	I2CRepeatStart();
	I2CSendSlaveAddress(EEPROM_R);
	for(i=0; i<n-1; i++)
		byte[i] = I2CRecvDataAck();
	byte[i] = I2CRecvDataNAck();
	I2CStop();
}

















