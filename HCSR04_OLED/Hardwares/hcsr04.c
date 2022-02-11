#include "hcsr04.h"

u16 msCount = 0; // ms

void HCSR04_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB2PeriphClockCmd(HCSR04_TRIG_RCC | HCSR04_ECHO_RCC, ENABLE);

    GPIO_InitStruct.GPIO_Pin = HCSR04_TRIG_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(HCSR04_TRIG_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = HCSR04_ECHO_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HCSR04_ECHO_PORT, &GPIO_InitStruct);

    GPIO_ResetBits(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN);
    GPIO_ResetBits(HCSR04_ECHO_PORT, HCSR04_ECHO_PIN);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    TIM_DeInit(TIM2);
    TIM_TimeBaseStruct.TIM_Period = (1000 - 1);
    TIM_TimeBaseStruct.TIM_Prescaler = (72 - 1);
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStruct);

    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

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
    double distance = 0;   // cm
    for (int i = 0; i < 5; i++)
    {
        TRIG_Send = 1;
        delay_us(20);
        TRIG_Send = 0;
        while (ECHO_Reci == 0)
            ; // 等待接收

        TIM_SetCounter(TIM6, 0);
        msCount = 0;
        TIM_Cmd(TIM6, ENABLE);

        while (ECHO_Reci == 1)
            ; // 收到反馈

        TIM_Cmd(TIM6, DISABLE);
        time = msCount * 1000;
        time += TIM_GetCounter(TIM6);
        TIM_SetCounter(TIM6, 0);
        delay_ms(50);

        distance += ((double)time * 0.034 / 2); // 音速 = 340 m/s
    }
    distance /= 5.0; // 测五次取均值

    return distance;
}
