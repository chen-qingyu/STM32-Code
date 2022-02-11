/*
**���**
��λ������������

**����**
GPIOA.7 �ǿ���1��1�ţ�GPIOA.8 �ǿ���2��1�š�
2�Ž�GND��3�Ž�VCC��

By �����
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // �������루�͵�ƽ������
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
