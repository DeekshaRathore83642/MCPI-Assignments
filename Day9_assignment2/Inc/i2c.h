

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define I2C1_SCL	6
#define I2C1_SDA	7

void I2CStart();
void I2CRepeatStart();
void I2CStop();
void I2CSendSlaveAddress(uint8_t slaveaddr);
void I2CSendData(uint8_t val);
uint8_t I2CRecvDataAck(void);
uint8_t I2CRecvDataNAck(void);
int I2CIsDeviceReady(uint8_t slaveaddr);
void I2CInit();

#endif /* I2C_H_ */
