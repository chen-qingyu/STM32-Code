#ifndef HCSR04_H
#define HCSR04_H

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

#define TRIG_Send  PAout(5)
#define ECHO_Reci  PAin(6)

void HCSR04_Init(void);
double HCSR04_GetDistance(void);

#endif
