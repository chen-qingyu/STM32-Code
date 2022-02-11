#include "ls.h"

void LS_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOF, &GPIO_InitStruct);
}

// Get the value of the light sensor.
// Return value: 0(dark) ~ 100(light)
u8 LS_GetValue(void)
{
    u32 value = 0;
    for (int i = 0; i < 5; i++)
    {
        value += ADC3_GetValue(ADC_Channel_6);
        delay_ms(10);
    }
    value /= 5;
    return 100 - ((value * 100) / 4096); // Mapping value from 4096 ~ 0 to 0 ~ 100
}
