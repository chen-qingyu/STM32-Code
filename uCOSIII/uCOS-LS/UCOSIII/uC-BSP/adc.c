#include "adc.h"

void ADC3_Init(void)
{
    ADC_InitTypeDef ADC_InitStruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);
    
    ADC_DeInit(ADC3);
    
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_Init(ADC3, &ADC_InitStruct);
    
    ADC_Cmd(ADC3, ENABLE);
    
    ADC_ResetCalibration(ADC3);
    while (ADC_GetResetCalibrationStatus(ADC3))
        ;
    ADC_StartCalibration(ADC3);
    while (ADC_GetCalibrationStatus(ADC3))
        ;
}

u16 ADC3_GetValue(u8 channel)
{
    ADC_RegularChannelConfig(ADC3, channel, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADC3, ENABLE);
    
    while (ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC) != SET)
        ;
    
    return ADC_GetConversionValue(ADC3);
}
