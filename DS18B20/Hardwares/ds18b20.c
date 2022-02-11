#include "ds18b20.h"
#include "delay.h"

// 开始温度转换
static void DS18B20_Convert(void)
{
    DS18B20_Reset();
    DS18B20_Check();
    DS18B20_WriteByte(0xcc); //  skip rom
    DS18B20_WriteByte(0x44); //  convert
}

// 初始化DS18B20的IO口
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

// 检测DS18B20的存在
// 返回0:未检测到DS18B20存在
// 返回1:检测到DS18B20存在
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

// 从DS18B20得到温度值
// 返回值：温度值（-550~1250），单位：0.1摄氏度
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

    if (th > 7) // 温度为负
    {
        th = ~th;
        tl = ~tl;
        sign = 0;
    }
    else // 温度为正
    {
        sign = 1;
    }
    temp = th;
    temp <<= 8;
    temp += tl;
    temp = (float)temp * 0.625; // 转换

    return sign ? temp : -temp;
}

// 复位DS18B20
void DS18B20_Reset(void)
{
    DS18B20_IO_OUT();   // SET PG11 OUTPUT
    DS18B20_DQ_OUT = 0; // 拉低DQ
    delay_us(750);      // 持续750us
    DS18B20_DQ_OUT = 1; // 拉高DQ
    delay_us(15);       // 持续15us
}

// 从DS18B20读取一个字节
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

// 写入一个字节到DS18B20
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
