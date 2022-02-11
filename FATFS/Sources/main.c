#include "stm32f10x.h"

#include "delay.h"
#include "malloc.h"
#include "sys.h"
#include "usart.h"

#include "spi.h"
#include "w25qxx.h"

#include "exfuns.h"
#include "ff.h"

int main(void)
{
    u8 res = 0;
    FIL fp;
    u8 readData[1024];
    UINT br;

    delay_init();
    uart_init(115200);
    my_mem_init(SRAMIN);
    exfuns_init();

    W25QXX_Init();

    res = f_mount(fs[1], "1:", 1); // ����FLASH.
    printf("Mount res = %d.\r\n", res);

    res = f_open(&fp, "1:BadApple.bin", FA_READ); // ���ļ�
    printf("Open res = %d.\r\n", res);

    res = f_read(&fp, readData, 1, &br); // ��ȡһ���ֽ�
    printf("Read res = %d.\r\n", res);

    f_close(&fp);

    while (1)
    {
    }
}
