#include "stm32f10x.h"

#include "delay.h"
#include "malloc.h"
#include "sys.h"
#include "usart.h"

#include "led.h"

int main(void)
{
    delay_init();

    LED_Init();

    while (1)
    {
        LED0 = !LED0;
        LED1 = !LED1;
        delay_ms(500);
    }
}
