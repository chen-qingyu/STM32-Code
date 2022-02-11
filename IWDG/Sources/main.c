#include "stm32f10x.h"

#include "delay.h"

#include "iwdg.h"
#include "key.h"
#include "led.h"

int main(void)
{
    delay_init();

    LED_Init();
    KEY_Init();
    IWDG_Init(2, 0XFFF); // ¥Û∏≈1.6√Î
    delay_ms(500);
    LED0 = 0;

    while (1)
    {
        if (KEY_Scan(0) == KEYUP_PRESS)
        {
            IWDG_ReloadCounter(); // Œππ∑
        }
    }
}
