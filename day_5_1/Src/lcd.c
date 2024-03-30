

#include "lcd.h"

void LcdBusyWait(void) {
	uint32_t state;
	// make D7/BF pin as input
	LCD_DATA_GPIO->MODER &= ~(BV(LCD_BF*2)|BV(LCD_BF*2+1));
	// set RS=0, RW=1, EN=1
	LCD_CTRL_GPIO->BSRR = BV(LCD_RS_CLR) | BV(LCD_RW) | BV(LCD_EN);
	// read data
	do {
		state = LCD_DATA_GPIO->IDR;
	} while((state & BV(LCD_BF)) != 0); // repeat if BF=1
	// set RW=0, EN=0
	LCD_CTRL_GPIO->BSRR = BV(LCD_RW_CLR) | BV(LCD_EN_CLR);
	// make D7/BF pin as output
	LCD_DATA_GPIO->MODER |= BV(LCD_BF*2);
}

void LcdWriteNibble(uint8_t rs, uint8_t val) {
	// set RS, RW = 0
	if(rs == LCD_CMD) // RS = 0
		LCD_CTRL_GPIO->BSRR = BV(LCD_RS_CLR) | BV(LCD_RW_CLR);
	else // RS = 1
		LCD_CTRL_GPIO->BSRR = BV(LCD_RS) | BV(LCD_RW_CLR);
	// write data (4-bits)
	LCD_DATA_GPIO->ODR &= ~(BV(LCD_D7) | BV(LCD_D6) | BV(LCD_D5) | BV(LCD_D4));
	LCD_DATA_GPIO->ODR |= val << LCD_D4;
	// falling edge on EN
	LCD_CTRL_GPIO->BSRR = BV(LCD_EN);
	DelayMs(1);
	LCD_CTRL_GPIO->BSRR = BV(LCD_EN_CLR);
}

void LcdWrite(uint8_t rs, uint8_t val) {
	uint8_t high = val >> 4, low = val & 0x0F;
	// write high nibble
	LcdWriteNibble(rs, high);
	// write low nibble
	LcdWriteNibble(rs, low);
	// wait for busy flag
	LcdBusyWait();
	DelayMs(3);
}

void LcdInit(void) {
	DelayMs(50);
	// enable lcd data port and ctrl port
	RCC->AHB1ENR |= BV(LCD_DATA_GPIO_EN);
	RCC->AHB1ENR |= BV(LCD_CTRL_GPIO_EN);

	//initialize lcd data pins (mode=output, speed=low, type=push-pull, no pull up/down)
	LCD_DATA_GPIO->MODER &= ~(BV(LCD_D7*2+1) | BV(LCD_D6*2+1) | BV(LCD_D5*2+1) | BV(LCD_D4*2+1));
	LCD_DATA_GPIO->MODER |= BV(LCD_D7*2) | BV(LCD_D6*2) | BV(LCD_D5*2) | BV(LCD_D4*2);
	LCD_DATA_GPIO->OSPEEDR &= ~(BV(LCD_D7*2+1) | BV(LCD_D7*2) | BV(LCD_D6*2+1) | BV(LCD_D6*2) | BV(LCD_D5*2+1) | BV(LCD_D5*2) | BV(LCD_D4*2+1) | BV(LCD_D4*2));
	LCD_DATA_GPIO->PUPDR &= ~(BV(LCD_D7*2+1) | BV(LCD_D7*2) | BV(LCD_D6*2+1) | BV(LCD_D6*2) | BV(LCD_D5*2+1) | BV(LCD_D5*2) | BV(LCD_D4*2+1) | BV(LCD_D4*2));
	LCD_DATA_GPIO->OTYPER &= ~(BV(LCD_D7) | BV(LCD_D6) | BV(LCD_D5) | BV(LCD_D4));
	//clear lcd data pins
	LCD_DATA_GPIO->BSRR = (BV(LCD_D7_CLR) | BV(LCD_D6_CLR) | BV(LCD_D5_CLR) | BV(LCD_D4_CLR));

	//initialize lcd ctrl pins (mode=output, speed=low, type=push-pull, no pull up/down)
	LCD_CTRL_GPIO->MODER &= ~(BV(LCD_RS*2+1) | BV(LCD_RW*2+1) | BV(LCD_EN*2+1));
	LCD_CTRL_GPIO->MODER |= BV(LCD_RS*2) | BV(LCD_RW*2) | BV(LCD_EN*2);
	LCD_CTRL_GPIO->OSPEEDR &= ~(BV(LCD_RS*2+1) | BV(LCD_RS*2) | BV(LCD_RW*2+1) | BV(LCD_RW*2) | BV(LCD_EN*2+1) | BV(LCD_EN*2));
	LCD_CTRL_GPIO->PUPDR &= ~(BV(LCD_RS*2+1) | BV(LCD_RS*2) | BV(LCD_RW*2+1) | BV(LCD_RW*2) | BV(LCD_EN*2+1) | BV(LCD_EN*2));
	LCD_CTRL_GPIO->OTYPER &= ~(BV(LCD_RS) | BV(LCD_RW) | BV(LCD_EN));

	//clear lcd ctrl pins
	LCD_CTRL_GPIO->BSRR = (BV(LCD_RS_CLR) | BV(LCD_RW_CLR) | BV(LCD_EN_CLR));

	DelayMs(200);
	// lcd initialization
	// 4-bit mode, 2-line, 5x8 font
	LcdWrite(LCD_CMD, LCD_FN_SET);
	// display on, cursor on, blink on
	LcdWrite(LCD_CMD, LCD_DISP_ON);
	// entry mode -- increment address
	LcdWrite(LCD_CMD, LCD_ENTRY_MODE);
	// clear display
	LcdWrite(LCD_CMD, LCD_CLEAR);

	DelayMs(200);
}

void LcdPuts(uint8_t line, char str[]) {
	int i;
	// set lcd line address
	LcdWrite(LCD_CMD, line);
	// send chars to lcd one by one
	for(i=0; str[i]!='\0'; i++)
		LcdWrite(LCD_DATA, str[i]);
}

