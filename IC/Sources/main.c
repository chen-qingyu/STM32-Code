#include "stm32f10x.h"
#include "stdbool.h"

#include "delay.h"
#include "sys.h"
#include "usart.h"

#include "key.h"
#include "tim.h"

extern bool IC_CaptureOK;
extern bool IC_HighFlag;
extern u8 IC_OverflowCount;
extern u16 IC_CounterValue;

int main(void)
{
    delay_init();
    uart_init(115200);
    TIM5_Cap_Init(0x10000 - 1, 72 - 1); // 1Mhz
    KEY_Init();

    u32 time_us = 0;

    while (1)
    {
        if (IC_CaptureOK)
        {
            time_us = IC_OverflowCount * 0x10000 + IC_CounterValue;
            printf("Press KEY_UP: %.2f s (%d us)\r\n", (float)time_us / 1e6, time_us);

            IC_CaptureOK = 0;
            IC_HighFlag = 0;
            IC_OverflowCount = 0;
        }
    }
}
