

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "lcd.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	SystemInit();
	LcdInit();
	LcdPuts(LCD_LINE1, "DESD @ SUNBEAM");
	LcdPuts(LCD_LINE2, "GOD BLESS YOU!");
	while(1)
	{
	for(int i=0;i<16;i++)
	{
		LcdWrite(LCD_CMD,LCD_LINE_SHIFT);
		DelayMs(1000);
	}
	}
	return 0;
}







