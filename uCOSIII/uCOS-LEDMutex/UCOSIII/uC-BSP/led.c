#include "led.h"

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(LED0_RCC | LED1_RCC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = LED0_PIN;
    GPIO_Init(LED0_PORT, &GPIO_InitStruct);
    GPIO_SetBits(LED0_PORT, LED0_PIN);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = LED1_PIN;
    GPIO_Init(LED1_PORT, &GPIO_InitStruct);
    GPIO_SetBits(LED1_PORT, LED1_PIN);
}
