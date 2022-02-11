#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

#define GPIO_Pin_0123 (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3)
#define GPIO_Pin_4567 (GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7)

void Motor_Init(u16 arr, u16 psc);
void Motor_TurnPositive(char motor);
void Motor_TurnNegative(char motor);
void Motor_Halt(char motor);

#endif
