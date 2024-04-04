

#include "i2c_lcd.h"

void LcdWriteByte(uint8_t val) {
	I2CStart();
	I2CSendSlaveAddress(LCD_SLAVE_ADDR_W);
	I2CSendData(val);
	I2CStop();
}

void LcdWrite(uint8_t rs, uint8_t val) {
	uint8_t high = val & 0xF0, low = (val << 4) & 0xF0;
	uint8_t bvrs = (rs == LCD_CMD) ? 0 : BV(LCD_RS);
	LcdWriteByte(high | bvrs | BV(LCD_EN) | BV(LCD_BL));
	DelayMs(1);
	LcdWriteByte(high | bvrs | BV(LCD_BL));

	LcdWriteByte(low | bvrs | BV(LCD_EN) | BV(LCD_BL));
	DelayMs(1);
	LcdWriteByte(low | bvrs | BV(LCD_BL));
}

// As per 4-bit initialization sequence mentioned HD44780 datasheet fig 24 (page 46)
int LcdInit() {
	// wait for min 15 ms (for 5V)
	DelayMs(20);
	I2CInit();
	// check if lcd is ready
	I2CStart();
	int ret = I2CIsDeviceReady(LCD_SLAVE_ADDR_W);
	I2CStop();
	if(!ret)
		return 0;

	// attention sequence
	LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	LcdWriteByte(LCD_FN_SET_8BIT);
	DelayMs(5);

	LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	LcdWriteByte(LCD_FN_SET_8BIT);
	DelayMs(1);

	LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	LcdWriteByte(LCD_FN_SET_8BIT);
	DelayMs(3);

	LcdWriteByte(LCD_FN_SET_4BIT | BV(LCD_EN));
	__NOP();
	LcdWriteByte(LCD_FN_SET_4BIT);
	DelayMs(3);

	// lcd initialization
	LcdWriteByte(LCD_FN_SET_4BIT_2LINES);
	DelayMs(1);
	LcdWrite(LCD_CMD, LCD_DISP_CTRL);
	DelayMs(1);
	LcdWrite(LCD_CMD, LCD_CLEAR);
	DelayMs(1);
	LcdWrite(LCD_CMD, LCD_ENTRY_MODE);
	DelayMs(1);
	LcdWrite(LCD_CMD, LCD_DISP_ON);
	DelayMs(1);
	return ret;
}

void LcdPuts(uint8_t line, char str[]) {
	int i;
	LcdWrite(LCD_CMD, line); // line address
	DelayMs(1);
	for(i=0; str[i]!='\0'; i++)
		LcdWrite(LCD_DATA, str[i]);
}
