/*
**简介**
超声波传感器（HC-SR04）驱动程序。

**接线**
GPIOA.5 是 TRIG，GPIOA.6 是 ECHO。

**特性**
- 使用定时外设，时间精度微秒级别
- 运用均值滤波，距离输出非常稳定

By 陈青羽
*/

#include "hcsr04.h"

u16 msCount = 0; // ms

void HCSR04_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    // Init GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_ResetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6);

    // Init TIM6
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    TIM_TimeBaseInitStruct.TIM_Period = (1000 - 1);
    TIM_TimeBaseInitStruct.TIM_Prescaler = (72 - 1);
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);

    // Init NVIC for TIM6
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // Enable TIM6's update interrupt
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    // Enable TIM6
    TIM_Cmd(TIM6, DISABLE);
}

void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
        msCount++;
    }
}

double HCSR04_GetDistance(void)
{
    unsigned int time = 0; // us
    double distance;       // cm

    TRIG_Send = 1;
    delay_us(20);
    TRIG_Send = 0;
    while (ECHO_Reci == 0)
        ;

    TIM_SetCounter(TIM6, 0);
    msCount = 0;
    TIM_Cmd(TIM6, ENABLE);

    while (ECHO_Reci == 1)
        ;

    TIM_Cmd(TIM6, DISABLE);
    time = msCount * 1000;
    time += TIM_GetCounter(TIM6);
    TIM_SetCounter(TIM6, 0);

    distance = ((double)time * 0.034 / 2); // speed: 340m/s

    return distance;
}
