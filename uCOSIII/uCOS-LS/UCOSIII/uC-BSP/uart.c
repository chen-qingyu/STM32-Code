#include "uart.h"

void UART_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate            = bound;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity              = USART_Parity_No;
    USART_InitStruct.USART_StopBits            = USART_StopBits_1;
    USART_InitStruct.USART_WordLength          = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStruct.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 1;
    NVIC_Init(&NVIC_InitStruct);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}


/* Remote sample 远程采集 */

extern OS_FLAG_GRP SampleFlag;

void USART1_IRQHandler(void)
{
    OS_ERR err;
    u8 recv_data;
    static int state = 0; // 如果没有static就无法运行，不知道为什么
    
    OSIntEnter();

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        recv_data = USART_ReceiveData(USART1);
        switch (state)
        {
            case 0:
            {
                if (recv_data == 'r')
                    state = 'r';
                else
                    state = 0;
                break;
            }
            case 'r':
            {
                if (recv_data == 'e')
                    state = 'e';
                else
                    state = 0;
                break;
            }
            case 'e':
            {
                if (recv_data == 'a')
                    state = 'a';
                else
                    state = 0;
                break;
            }
            case 'a':
            {
                if (recv_data == 'd')
                {
                    OSFlagPost(&SampleFlag, CMD_FLAG, OS_OPT_POST_FLAG_SET, &err);
                }
                state = 0;
                break;
            }
        }
    }
    OSIntExit();
}
