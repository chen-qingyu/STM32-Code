#include "stm32f10x.h"

#include "delay.h"
#include "sys.h"

#include "tim.h"

int main(void)
{
    delay_init();

    TIM3_PWM_Init(900 - 1, 1 - 1);

    u16 threshold = 0;
    u8 dir = 1;

    while (1)
    {
        delay_ms(1);
        if (dir)
        {
            threshold++;
        }
        else
        {
            threshold--;
        }

        if (threshold >= 900)
        {
            dir = 0;
        }
        if (threshold == 0)
        {
            dir = 1;
        }
        TIM_SetCompare2(TIM3, threshold);
    }
}
