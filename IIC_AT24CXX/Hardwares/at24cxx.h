#ifndef AT24CXX_H
#define AT24CXX_H

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "iic.h"

#define AT24C01 127
#define AT24C02 255
#define AT24C04 511
#define AT24C08 1023
#define AT24C16 2047
#define AT24C32 4095
#define AT24C64 8191
#define AT24C128 16383
#define AT24C256 32767

// STM32F103开发板使用的是AT24C02，所以定义EEPROM_TYPE为AT24C02
#define EEPROM_TYPE AT24C02

void AT24CXX_Init(void);
void AT24CXX_Write(u8 *buffer, u16 addr, u16 len);
void AT24CXX_Read(u8 *buffer, u16 addr, u16 len);

#endif
