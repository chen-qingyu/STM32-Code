#include "key.h"

void KEY_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPEEN, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
}

u8 KEY_Scan(u8 mode) //mode == 1 -> 电平触发; mode == 0 -> 沿触发;
{
    static u8 keyUp = 1;
    if (mode)
    {
        keyUp = 1;
    }
    if (keyUp && (!KEY0 || !KEY1 || KEYUP))
    {
        delay_ms(10);
        keyUp = 0;
        if (!KEY0)
        {
            return KEY0_PRESS;
        }
        else if (!KEY1)
        {
            return KEY1_PRESS;
        }
        else if (KEYUP)
        {
            return KEYUP_PRESS;
        }
    }
    else if (KEY0 && KEY1 && !KEYUP)
    {
        keyUp = 1;
    }
    return 0;
}
