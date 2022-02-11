#include "stm32f10x.h"
#include "uart.h"

int main(void)
{
    UART_Init();
    while (1)
        ;
}

void USART1_IRQHandler(void)
{
    u16 data;
    if (USART_GetITStatus(USART1, USART_IT_RXNE))
    {
        data = USART_ReceiveData(USART1) + 1;
        USART_SendData(USART1, data);
    }
}
