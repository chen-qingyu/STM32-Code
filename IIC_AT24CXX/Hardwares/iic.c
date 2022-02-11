#include "iic.h"

// SDA输入模式
static void IIC_SDAIn(void)
{
    GPIOB->CRL &= 0X0FFFFFFF;
    GPIOB->CRL |= (u32)8 << 28;
}

// SDA输出模式
static void IIC_SDAOut(void)
{
    GPIOB->CRL &= 0X0FFFFFFF;
    GPIOB->CRL |= (u32)3 << 28;
}

// 产生ACK应答
static void IIC_Ack(void)
{
    SCL = 0;
    IIC_SDAOut();
    SDA_OUT = 0;
    delay_us(2);
    SCL = 1;
    delay_us(2);
    SCL = 0;
}

// 不产生ACK应答
static void IIC_NAck(void)
{
    SCL = 0;
    IIC_SDAOut();
    SDA_OUT = 1;
    delay_us(2);
    SCL = 1;
    delay_us(2);
    SCL = 0;
}

// 初始化IIC
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7);
}

// 产生IIC起始信号
void IIC_Start(void)
{
    IIC_SDAOut();
    SDA_OUT = 1;
    SCL = 1;
    delay_us(4);
    SDA_OUT = 0; // START: when SCL is high, SDA change form high to low
    delay_us(4);
    SCL = 0; // 钳住I2C总线，准备发送或接收数据
}

// 产生IIC停止信号
void IIC_Stop(void)
{
    IIC_SDAOut();
    SCL = 0;
    SDA_OUT = 0; // STOP: when SCL is high SDA change form low to high
    delay_us(4);
    SCL = 1;
    SDA_OUT = 1; // 发送I2C总线结束信号
    delay_us(4);
}

// 等待应答信号到来
// 返回值：0，接收应答成功；1，接收应答失败
u8 IIC_WaitAck(void)
{
    u8 errCnt = 0;
    IIC_SDAIn();
    SDA_OUT = 1;
    delay_us(1);
    SCL = 1;
    delay_us(1);
    while (SDA_IN)
    {
        errCnt++;
        if (errCnt > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    SCL = 0;
    return 0;
}

// IIC发送一个字节
// 返回从机有无应答:
// 1，有应答
// 0，无应答
void IIC_SendByte(u8 txd)
{
    IIC_SDAOut();
    SCL = 0; //拉低时钟开始数据传输
    for (int i = 0; i < 8; i++)
    {
        SDA_OUT = (txd & 0x80) >> 7;
        txd <<= 1;
        delay_us(2);
        SCL = 1;
        delay_us(2);
        SCL = 0;
        delay_us(2);
    }
}

// 读一个字节，ack=1时，发送ACK，ack=0，发送NACK
u8 IIC_ReadByte(u8 ack)
{
    u8 receive = 0;
    IIC_SDAIn();
    for (int i = 0; i < 8; i++)
    {
        SCL = 0;
        delay_us(2);
        SCL = 1;
        receive <<= 1;
        if (SDA_IN)
        {
            receive++;
        }
        delay_us(1);
    }
    if (!ack)
    {
        IIC_NAck();
    }
    else
    {
        IIC_Ack();
    }
    return receive;
}
