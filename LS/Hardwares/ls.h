#ifndef LS_H
#define LS_H

#include "stm32f10x.h"
#include "delay.h"
#include "adc.h"

void LS_Init(void);
u8 LS_GetValue(void);

#endif
