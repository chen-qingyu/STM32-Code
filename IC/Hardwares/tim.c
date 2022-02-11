#include "tim.h"

void TIM5_Cap_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    TIM_ICInitTypeDef TIM_ICInitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    // Init TIM5
    TIM_TimeBaseInitStruct.TIM_Period = arr;
    TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);

    // Init Input Capture for TIM5
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICFilter = 0x00;
    TIM_ICInit(TIM5, &TIM_ICInitStruct);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // Init NVIC for TIM5
    NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // Enable TIM5's update interrupt and input capture interrupt
    TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);

    // Enable TIM5
    TIM_Cmd(TIM5, ENABLE);
}

bool IC_CaptureOK = 0;
bool IC_HighFlag = 0;
u8 IC_OverflowCount = 0;
u16 IC_CounterValue = 0;

void TIM5_IRQHandler(void)
{
    if (IC_CaptureOK == 0)
    {
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET) // 定时中断
        {
            if (IC_HighFlag) // 已捕获上升沿，则开始计时
            {
                if (IC_OverflowCount == 0xFF)
                {
                    IC_CaptureOK = 1;
                    IC_CounterValue = 0xFFFF;
                }
                else
                {
                    IC_OverflowCount++;
                }
            }
        }

        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) == SET) // 捕获中断
        {
            if (IC_HighFlag) // 已捕获上升沿，这次捕获的是下降沿，即完成一次输入捕获
            {
                IC_CaptureOK = 1;
                IC_CounterValue = TIM_GetCapture1(TIM5);
                TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);
            }
            else // 这次捕获的是上升沿，即开始一次输入捕获
            {
                IC_CaptureOK = 0;
                IC_OverflowCount = 0;
                IC_CounterValue = 0;
                TIM_SetCounter(TIM5, 0);
                IC_HighFlag = 1;
                TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);
            }
        }
    }

    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update);
}
