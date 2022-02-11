#include "stm32f10x.h"

#include "sys.h"

#include "led.h"
#include "tim.h"

int main(void)
{
    LED_Init();
    TIM2_IT_Init(5000 - 1, 7200 - 1); // 5000 x 0.1ms = 500ms

    while (1)
    {
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        LED1 = !LED1;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
