/*
**简介**
柔性叩击按摩机器人主函数。 

**模块**
两相混合式步进电机（35HB）两个
超声波传感器（HC-SR04）一个
限位开关两个。

By 白宇洁、陈青羽
*/

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

#include "motor.h"
#include "hcsr04.h"
#include "switch.h"

#define POSITIVE 1
#define NEGATIVE (-1)

double distance; // cm
int dir = POSITIVE;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init();
    Motor_Init(5000 - 1, 72 - 1); // 5ms -> 200Hz
    HCSR04_Init();
    Switch_Init();

    while (1)
    {
        distance = HCSR04_GetDistance();
        delay_ms(200);
    }
}

// control motor A
void TIM2_IRQHandler(void) 
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        if (distance > 10)
        {
            Motor_TurnPositive('A');
        }
        else if (distance < 5)
        {
            Motor_TurnNegative('A');
        }
        else
        {
            Motor_Halt('A');
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

// control motor B
void TIM3_IRQHandler(void) 
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        if (dir == POSITIVE)
        {
            Motor_TurnPositive('B');
        }
        else if (dir == NEGATIVE)
        {
            Motor_TurnNegative('B');
        }
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

// detect limit switch for motor B
void EXTI9_5_IRQHandler(void) 
{
    dir = -dir;
    Motor_Halt('B');
    EXTI_ClearITPendingBit(EXTI_Line7);
    EXTI_ClearITPendingBit(EXTI_Line8);
}
