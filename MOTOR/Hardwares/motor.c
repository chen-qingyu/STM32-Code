/*
**简介**
两相混合式步进电机（35HB）驱动程序。

**接线**
GPIOC.0 和 GPIOC.2 是步进电机1的A相，GPIOC.1 和 GPIOC.3 是步进电机1的B相。
GPIOC.4 和 GPIOC.6 是步进电机2的A相，GPIOC.5 和 GPIOC.7 是步进电机2的B相。

**特性**
- 采用查表方式，程序结构简洁精炼
- 使用八拍驱动，电机旋转强劲有力

By 陈青羽
*/

#include "motor.h"

uint16_t positive[8] = {0x0001, 0x0003, 0x0002, 0x0006, 0x0004, 0x000c, 0x0008, 0x0009};
uint16_t negative[8] = {0x0009, 0x0008, 0x000c, 0x0004, 0x0006, 0x0002, 0x0003, 0x0001};

void Motor_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    // Init GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0123 | GPIO_Pin_4567;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_ResetBits(GPIOC, GPIO_Pin_0123 | GPIO_Pin_4567);
    
    // Init TIM2, TIM3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period        = arr;
    TIM_TimeBaseInitStruct.TIM_Prescaler     = psc;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    
    // Init NVIC for TIM2 & TIM3
    NVIC_InitStruct.NVIC_IRQChannel                   = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 2;
    NVIC_Init(&NVIC_InitStruct);
    NVIC_InitStruct.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_Init(&NVIC_InitStruct);
    
    // Enable TIM2 & TIM3's update interrupt
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    
    // Enable TIM2, TIM3
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

void Motor_TurnPositive(char motor)
{
    static int i = 0;

    if (motor == 'A')
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_0123);
        GPIO_SetBits(GPIOC, positive[i]);
    }
    else if (motor == 'B')
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_4567);
        GPIO_SetBits(GPIOC, positive[i] << 4);
    }
    i = (i + 1) % 8;
}

void Motor_TurnNegative(char motor)
{
    static int i = 0;

    if (motor == 'A')
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_0123);
        GPIO_SetBits(GPIOC, negative[i]);
    }
    else if (motor == 'B')
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_4567);
        GPIO_SetBits(GPIOC, negative[i] << 4);
    }
    i = (i + 1) % 8;
}

void Motor_Halt(char motor)
{
    if (motor == 'A')
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_0123);
    }
    else if (motor == 'B')
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_4567);
    }
}
