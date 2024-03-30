

#ifndef LCD_H_
#define LCD_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define LCD_DATA_GPIO	GPIOD
#define LCD_DATA_GPIO_EN	3
#define LCD_D7			3
#define LCD_D6			2
#define LCD_D5			1
#define LCD_D4			0
#define LCD_BF			LCD_D7
#define LCD_D7_CLR		(LCD_D7+16)
#define LCD_D6_CLR		(LCD_D6+16)
#define LCD_D5_CLR		(LCD_D5+16)
#define LCD_D4_CLR		(LCD_D4+16)

#define LCD_CTRL_GPIO	GPIOD
#define LCD_CTRL_GPIO_EN	3
#define LCD_RS			5
#define LCD_RW			6
#define LCD_EN			7
#define LCD_RS_CLR		(LCD_RS+16)
#define LCD_RW_CLR		(LCD_RW+16)
#define LCD_EN_CLR		(LCD_EN+16)

#define LCD_CLEAR		0x01
#define LCD_FN_SET		0x28
#define LCD_DISP_ON		0x0F
#define LCD_ENTRY_MODE	0x06
#define LCD_LINE1		0x80
#define LCD_LINE2		0xC0

#define LCD_CMD			0
#define LCD_DATA		1

void LcdBusyWait(void);
void LcdWriteNibble(uint8_t rs, uint8_t val);
void LcdWrite(uint8_t rs, uint8_t val);

void LcdInit(void);
void LcdPuts(uint8_t line, char str[]);

#endif /* LCD_H_ */




