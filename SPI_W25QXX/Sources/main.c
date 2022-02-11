#include "stm32f10x.h"

#include "delay.h"
#include "sys.h"
#include "usart.h"

#include "led.h"
#include "key.h"
#include "spi.h"
#include "w25qxx.h"

int main(void)
{
    delay_init();
    uart_init(115200);
    
    LED_Init();
    KEY_Init();
    W25QXX_Init();

    const u8 text[] = "Hello World~";
    int size = sizeof(text);
    int addr = 100;
    int key;
    u8 data[size];

    while (1)
    {
        key = KEY_Scan(0);
        if (key == KEY1_PRESS)
        {
            printf("Start write W25Q128 @0x%x(%d bytes)...\r\n", addr, size);
            W25QXX_Write((u8 *)text, addr, size);
            printf("W25Q128 write finished!\r\n\r\n");
        }
        if (key == KEY0_PRESS)
        {
            printf("Start read W25Q128 @0x%x(%d bytes)...\r\n", addr, size);
            W25QXX_Read(data, addr, size);
            printf("The data readed is: %s\r\n\r\n", data);
        }
    }
}
