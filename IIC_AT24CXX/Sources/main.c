#include "stm32f10x.h"

#include "delay.h"
#include "sys.h"
#include "usart.h"

#include "led.h"
#include "key.h"
#include "iic.h"
#include "at24cxx.h"

int main(void)
{
    delay_init();
    uart_init(115200);
    
    LED_Init();
    KEY_Init();
    AT24CXX_Init();

    const u8 text[] = {"Hello World~"};
    int size = sizeof(text);
    int addr = 0;
    int key;
    u8 data[size];

    while (1)
    {
        key = KEY_Scan(0);
        if (key == KEY1_PRESS)
        {
            printf("Start write AT24C02 @0x%x(%d bytes)...\r\n", addr, size);
            AT24CXX_Write((u8 *)text, addr, size);
            printf("AT24C02 write finished!\r\n\r\n");
        }
        if (key == KEY0_PRESS)
        {
            printf("Start read AT24C02 @0x%x(%d bytes)...\r\n", addr, size);
            AT24CXX_Read(data, addr, size);
            printf("The data readed is: %s\r\n\r\n", data);
        }
    }
}
