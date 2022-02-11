#include "stm32f10x.h"
#include "delay.h"

#include "led.h"
#include "bee.h"
#include "key.h"

int main(void)
{
    delay_init();
    
    LED_Init();
    BEE_Init();
    KEY_Init();
    
    int key;
    while (1)
    {
        key = KEY_Scan(0);
        if (key)
        {
            switch (key)
            {
                case KEYUP_PRESS:
                    BEE = !BEE;
                    break;
                case KEY1_PRESS:
                    LED1 = !LED1;
                    break;
                case KEY0_PRESS:
                    LED0 = !LED0;
                    break;
            }
        }
    }
}
