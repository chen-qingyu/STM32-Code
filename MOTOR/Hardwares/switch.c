/*
**简介**
限位开关驱动程序。

**接线**
GPIOA.7 是开关1的1脚，GPIOA.8 是开关2的1脚。
2脚接GND，3脚接VCC。

By 白宇洁
*/

#include "switch.h"

void Switch_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    // Init GPIOA & AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7 | GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入（低电平触发）
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // Config EXTI Line
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
    
    // Init EXTI
    EXTI_InitStruct.EXTI_Line    = EXTI_Line7;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line    = EXTI_Line8;
    EXTI_Init(&EXTI_InitStruct);
    
    //Init NVIC for EXTI_Line7, EXTI_Line8
    NVIC_InitStruct.NVIC_IRQChannel                   = EXTI9_5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 0;
    NVIC_Init(&NVIC_InitStruct);
}
