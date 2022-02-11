#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

#include "led.h"
#include "adc.h"
#include "ls.h"

int main(void)
{
    delay_init();
    uart_init(115200);
    
    LED_Init();
    ADC3_Init();
    LS_Init();

    u8 value;
    u8 i = 0;
    while (1)
    {
        value = LS_GetValue();
        printf("@%3us: Now the brightness is %u.\r\n", i, value);
        LED0 = !LED0;
        delay_ms(1000);
        i++;
    }
}
