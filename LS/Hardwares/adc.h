#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"

void ADC3_Init(void);
u16 ADC3_GetValue(u8 channel);

#endif
