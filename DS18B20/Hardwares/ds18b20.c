#include "ds18b20.h"
#include "delay.h"

// ��ʼ�¶�ת��
static void DS18B20_Convert(void)
{
    DS18B20_Reset();
    DS18B20_Check();
    DS18B20_WriteByte(0xcc); //  skip rom
    DS18B20_WriteByte(0x44); //  convert
}

// ��ʼ��DS18B20��IO��
void DS18B20_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    GPIO_SetBits(GPIOG, GPIO_Pin_11);

    DS18B20_Reset();
}

// ���DS18B20�Ĵ���
// ����0:δ��⵽DS18B20����
// ����1:��⵽DS18B20����
u8 DS18B20_Check(void)
{
    DS18B20_IO_IN();

    u8 retry = 0;
    while (DS18B20_DQ_IN && retry < 200)
    {
        retry++;
        delay_us(1);
    }
    if (retry >= 200)
    {
        return 0;
    }

    retry = 0;
    while (!DS18B20_DQ_IN && retry < 240)
    {
        retry++;
        delay_us(1);
    }
    if (retry >= 240)
    {
        return 0;
    }

    return 1;
}

// ��DS18B20�õ��¶�ֵ
// ����ֵ���¶�ֵ��-550~1250������λ��0.1���϶�
s16 DS18B20_GetTemp(void)
{
    u8 sign;
    u8 tl, th;
    s16 temp;

    DS18B20_Convert();
    DS18B20_Reset();
    DS18B20_Check();
    DS18B20_WriteByte(0xcc); //  skip rom
    DS18B20_WriteByte(0xbe); //  convert
    tl = DS18B20_ReadByte(); //  LSB
    th = DS18B20_ReadByte(); //  MSB

    if (th > 7) // �¶�Ϊ��
    {
        th = ~th;
        tl = ~tl;
        sign = 0;
    }
    else // �¶�Ϊ��
    {
        sign = 1;
    }
    temp = th;
    temp <<= 8;
    temp += tl;
    temp = (float)temp * 0.625; // ת��

    return sign ? temp : -temp;
}

// ��λDS18B20
void DS18B20_Reset(void)
{
    DS18B20_IO_OUT();   // SET PG11 OUTPUT
    DS18B20_DQ_OUT = 0; // ����DQ
    delay_us(750);      // ����750us
    DS18B20_DQ_OUT = 1; // ����DQ
    delay_us(15);       // ����15us
}

// ��DS18B20��ȡһ���ֽ�
u8 DS18B20_ReadByte(void)
{
    u8 data = 0;
    u8 bit = 0;
    for (u8 i = 0; i < 8; i++)
    {
        DS18B20_IO_OUT();
        DS18B20_DQ_OUT = 0;
        delay_us(2);
        DS18B20_DQ_OUT = 1;
        DS18B20_IO_IN();
        delay_us(12);
        bit = DS18B20_DQ_IN ? 1 : 0;
        delay_us(50);
        data = (bit << 7) | (data >> 1);
    }
    return data;
}

// д��һ���ֽڵ�DS18B20
void DS18B20_WriteByte(u8 data)
{
    u8 bit;
    DS18B20_IO_OUT();
    for (u8 i = 0; i < 8; i++)
    {
        bit = data & 0x01;
        data >>= 1;
        if (bit)
        {
            DS18B20_DQ_OUT = 0; //  Write 1
            delay_us(2);
            DS18B20_DQ_OUT = 1;
            delay_us(60);
        }
        else
        {
            DS18B20_DQ_OUT = 0; //  Write 0
            delay_us(60);
            DS18B20_DQ_OUT = 1;
            delay_us(2);
        }
    }
}
