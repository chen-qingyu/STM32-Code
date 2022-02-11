#include "exti.h"

void EI_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);

    EXTI_InitStruct.EXTI_Line    = EXTI_Line4;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel                   = EXTI4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 2;
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI4_IRQHandler(void)
{
    delay_ms(10);
    if (KEY0 == 0)
    {
        LED0 = !LED0;
        LED1 = !LED1;
    }
    EXTI_ClearITPendingBit(EXTI_Line4);
}
