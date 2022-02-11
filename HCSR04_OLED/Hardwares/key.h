#ifndef KEY_H
#define KEY_H

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define KEY0  PEin(3)
#define KEY1  PEin(4)

#define KEY0_RCC  RCC_APB2Periph_GPIOE
#define KEY0_PORT GPIOE
#define KEY0_PIN  GPIO_Pin_3
#define KEY1_RCC  RCC_APB2Periph_GPIOE
#define KEY1_PORT GPIOE
#define KEY1_PIN  GPIO_Pin_4

#define KEY0_PRESS  1
#define KEY1_PRESS  2

void KEY_Init(void);
int KEY_Scan(void);

#endif
