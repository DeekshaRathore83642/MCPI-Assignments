

#ifndef LIS3DSH_H_
#define LIS3DSH_H_

#include "spi.h"

// Registers (used in this program)
#define LIS_CTRL_REG4_ADDR               0x20
#define LIS_STATUS_ADDR                  0x27
#define LIS_OUT_X_L_ADDR                 0x28
#define LIS_OUT_X_H_ADDR                 0x29
#define LIS_OUT_Y_L_ADDR                 0x2A
#define LIS_OUT_Y_H_ADDR                 0x2B
#define LIS_OUT_Z_L_ADDR                 0x2C
#define LIS_OUT_Z_H_ADDR                 0x2D

// Registers (not used in this program)
#define LIS_WHO_AM_I_ADDR                0x0F
#define LIS_OFF_X_ADDR                   0x10
#define LIS_OFF_Y_ADDR                   0x11
#define LIS_OFF_Z_ADDR                   0x12
#define LIS_CTRL_REG1_ADDR               0x21
#define LIS_CTRL_REG2_ADDR               0x22
#define LIS_CTRL_REG3_ADDR               0x23
#define LIS_CTRL_REG5_ADDR               0x24
#define LIS_CTRL_REG6_ADDR               0x25

// Data rate (used in this program)
#define LIS_DATARATE_25                  ((uint8_t)0x40)  /* 25    Hz Normal Mode */

// Data rate (Not used in this program)
#define LIS_DATARATE_POWERDOWN           ((uint8_t)0x00)  /* Power Down Mode*/
#define LIS_DATARATE_3_125               ((uint8_t)0x10)  /* 3.125 Hz Normal Mode */
#define LIS_DATARATE_6_25                ((uint8_t)0x20)  /* 6.25  Hz Normal Mode */
#define LIS_DATARATE_12_5                ((uint8_t)0x30)  /* 12.5  Hz Normal Mode */
#define LIS_DATARATE_50                  ((uint8_t)0x50)  /* 50    Hz Normal Mode */
#define LIS_DATARATE_100                 ((uint8_t)0x60)  /* 100   Hz Normal Mode */
#define LIS_DATARATE_400                 ((uint8_t)0x70)  /* 400   Hz Normal Mode */
#define LIS_DATARATE_800                 ((uint8_t)0x80)  /* 800   Hz Normal Mode */
#define LIS_DATARATE_1600                ((uint8_t)0x90)  /* 1600  Hz Normal Mode */

// Axes Enable
#define LIS_X_ENABLE                     ((uint8_t)BV(0))
#define LIS_Y_ENABLE                     ((uint8_t)BV(1))
#define LIS_Z_ENABLE                     ((uint8_t)BV(2))
#define LIS_XYZ_ENABLE                   (LIS_X_ENABLE | LIS_Y_ENABLE | LIS_Z_ENABLE)
//#define LIS_XY_ENABLE                    (LIS_X_ENABLE | LIS_Y_ENABLE)

// Status register mask (XDA, YDA, ZDA)
#define LIS_STATUS_XYZ_Msk					(BV(0) | BV(1) | BV(2))

// Accel raw data
typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
}LIS_Data;

// Accel IO Functions
void LIS_WriteIO(uint8_t reg, uint8_t data[], uint8_t size);
void LIS_ReadIO(uint8_t reg, uint8_t data[], uint8_t size);

// Accel Init
void LIS_Init(void);
// Accel Get Raw Data
LIS_Data LIS_GetData(void);
// Accel Poll if Ready
int LIS_DRdy(void);

#endif /* LIS3DSH_H_ */
