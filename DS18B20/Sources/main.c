#include "stm32f10x.h"

#include "delay.h"
#include "sys.h"
#include "usart.h"

#include "ds18b20.h"

int main(void)
{
    delay_init();
    uart_init(115200);

    DS18B20_Init();

    while (!DS18B20_Check())
    {
        printf("Error.\r\n");
    }

    s16 temp;

    while (1)
    {
        temp = DS18B20_GetTemp();
        printf("temperature: %.1f.\r\n", (float)temp / 10);
        delay_ms(1000);
    }
}
