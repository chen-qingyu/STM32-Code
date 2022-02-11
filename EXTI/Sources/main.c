#include "stm32f10x.h"

#include "delay.h"
#include "sys.h"

#include "exti.h"
#include "key.h"
#include "led.h"

int main(void)
{
    delay_init();

    LED_Init();
    KEY_Init();
    EI_Init();

    LED0 = 0;
    while (1)
        ;
}
