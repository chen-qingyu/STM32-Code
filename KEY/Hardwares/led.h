#ifndef LED_H
#define LED_H

#include "stm32f10x.h"

#define LED0 PBout(5)
#define LED0_RCC RCC_APB2Periph_GPIOB
#define LED0_PORT GPIOB
#define LED0_PIN GPIO_Pin_5

#define LED1 PEout(5)
#define LED1_RCC RCC_APB2Periph_GPIOE
#define LED1_PORT GPIOE
#define LED1_PIN GPIO_Pin_5

void LED_Init(void);

#endif
