#ifndef HCSR04_H
#define HCSR04_H

#include "delay.h"
#include "sys.h"

#define TRIG_Send PBout(0)
#define ECHO_Reci PBin(1)

#define HCSR04_TRIG_RCC RCC_APB2Periph_GPIOB
#define HCSR04_TRIG_PORT GPIOB
#define HCSR04_TRIG_PIN GPIO_Pin_0
#define HCSR04_ECHO_RCC RCC_APB2Periph_GPIOB
#define HCSR04_ECHO_PORT GPIOB
#define HCSR04_ECHO_PIN GPIO_Pin_1

void HCSR04_Init(void);
void TIM6_IRQHandler(void);
double HCSR04_GetDistance(void);

#endif
