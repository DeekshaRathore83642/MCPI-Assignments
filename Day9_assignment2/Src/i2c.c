

#include "i2c.h"

void I2CStart() {
    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));
}

void I2CRepeatStart() {
	I2CStart();
}

void I2CStop() {
    I2C1->CR1 |= I2C_CR1_STOP;
    while(!(I2C1->SR2 & I2C_SR2_BUSY));
}

void I2CSendSlaveAddress(uint8_t slaveaddr) {
    // send slaveaddr
    // wait until address is sent
    I2C1->DR = slaveaddr;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    // dummy read to clear flags
    (void)I2C1->SR1;
    (void)I2C1->SR2; // clear addr condition
}

void I2CSendData(uint8_t val) {
    // send data in write mode
    // wait until address is sent
    while (!(I2C1->SR1 & I2C_SR1_TXE));
    // write dr and clear flags
    I2C1->DR = val;
    // wait until data byte is transferred
    while (!(I2C1->SR1 & I2C_SR1_BTF));
}

uint8_t I2CRecvDataAck(void) {
	uint8_t val;
	I2C1->CR1 |= I2C_CR1_ACK | I2C_CR1_POS;
	// wait until receive buffer is not empty
	while (!(I2C1->SR1 & I2C_SR1_RXNE));
	// read content and clear flags
	val = (uint8_t)I2C1->DR;
	return val;
}

uint8_t I2CRecvDataNAck(void) {
	uint8_t val;
	I2C1->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
	// wait until receive buffer is not empty
	while (!(I2C1->SR1 & I2C_SR1_RXNE));
	// read content and clear flags
	val = I2C1->DR;
	return val;
}

int I2CIsDeviceReady(uint8_t slaveaddr) {
    // send slaveaddr of write
	slaveaddr &= ~BV(0);
    // wait until address is sent
    I2C1->DR = slaveaddr;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    // dummy read to clear flags
    (void)I2C1->SR2; // clear addr condition
	return 1;
}

void I2CInit() {
    // enable GPIOB clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	DelayMs(50);

    // setup I2C pins
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER &= ~(3U << I2C1_SCL*2); // PB6
    GPIOB->MODER |=  (2 << I2C1_SCL*2); // AF
    GPIOB->OTYPER |= (1 << I2C1_SCL);   // open-drain
    GPIOB->PUPDR &= ~(3U << I2C1_SCL*2); // no pull-up/down
    GPIOB->MODER &= ~(3U << I2C1_SDA*2); // PB7
    GPIOB->MODER |=  (2 << I2C1_SDA*2); // AF
    GPIOB->OTYPER |= (1 << I2C1_SDA);   // open-drain
    GPIOB->PUPDR &= ~(3U << I2C1_SDA*2); // no pull-up/down

    // choose AF4 for I2C1 in Alternate Function registers
    GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFSEL6_Pos); // for pin 6
    GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFSEL7_Pos); // for pin 7

    // enable I2C clock
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	DelayMs(50);
    // reset and clear reg
    I2C1->CR1 = I2C_CR1_SWRST;
    I2C1->CR1 = 0;

    I2C1->CR2 &= ~(I2C_CR2_ITERREN); // disable error interrupt
    I2C1->CCR &= ~(1 << I2C_CCR_FS_Pos); // standard mode (100 khz)
    // Enable Ack
    I2C1->CR1 |= (1<<I2C_CR1_ACK_Pos);

    // fPCLK1 must be at least 2 Mhz for SM mode (100 kHz)
    // For SM Mode:
    //    Thigh = CCR * TPCLK1
    //    Tlow  = CCR * TPCLK1
    // So to generate 100 kHz SCL frequency
    // we need 1/100kz = 10us clock speed
    // Thigh and Tlow needs to be 5us each

    // Let's pick fPCLK1 = 16Mhz, TPCLK1 = 1/16Mhz = 62.5ns
    // Thigh = CCR * TPCLK1 => 5us = CCR * 62.5ns
    // CCR = 80
    I2C1->CR2 |= (16 << I2C_CR2_FREQ_Pos); // 16Mhz PCLK
    I2C1->CCR |= (80 << I2C_CCR_CCR_Pos);
    // Maximum rise time.
    // Calculation is (maximum_rise_time / Tpclk) + 1
    // In SM mode maximum allowed SCL rise time is 1000ns
    // For TPCLK1 = 62.5ns => (1000ns / 62.5ns) + 1 = 16 + 1 = 17
    I2C1->TRISE |= (17 << I2C_TRISE_TRISE_Pos); // program Trise to 17 for 100khz
    // Enable I2C
    I2C1->CR1 |= I2C_CR1_PE;
}
