/*
 * rtc.h
 *
 *  Created on: Apr 4, 2024
 *      Author: rucha
 */

#ifndef RTC_H_
#define RTC_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"


typedef struct {
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
} RTC_Time;

typedef struct {
	uint8_t Month;
	uint8_t Date;
	uint8_t Year;
	uint8_t WeekDay; // 1 (Mon) to 7 (Sun)
} RTC_Date;

void RTC_Init(RTC_Date *dt, RTC_Time *tm);
void RTC_SetDate(RTC_Date *dt);
void RTC_SetTime(RTC_Time *tm);
void RTC_GetDate(RTC_Date *dt);
void RTC_GetTime(RTC_Time *tm);

#endif /* RTC_H_ */
