#include "iic.h"

// SDA����ģʽ
static void IIC_SDAIn(void)
{
    GPIOB->CRL &= 0X0FFFFFFF;
    GPIOB->CRL |= (u32)8 << 28;
}

// SDA���ģʽ
static void IIC_SDAOut(void)
{
    GPIOB->CRL &= 0X0FFFFFFF;
    GPIOB->CRL |= (u32)3 << 28;
}

// ����ACKӦ��
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

// ������ACKӦ��
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

// ��ʼ��IIC
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

// ����IIC��ʼ�ź�
void IIC_Start(void)
{
    IIC_SDAOut();
    SDA_OUT = 1;
    SCL = 1;
    delay_us(4);
    SDA_OUT = 0; // START: when SCL is high, SDA change form high to low
    delay_us(4);
    SCL = 0; // ǯסI2C���ߣ�׼�����ͻ��������
}

// ����IICֹͣ�ź�
void IIC_Stop(void)
{
    IIC_SDAOut();
    SCL = 0;
    SDA_OUT = 0; // STOP: when SCL is high SDA change form low to high
    delay_us(4);
    SCL = 1;
    SDA_OUT = 1; // ����I2C���߽����ź�
    delay_us(4);
}

// �ȴ�Ӧ���źŵ���
// ����ֵ��0������Ӧ��ɹ���1������Ӧ��ʧ��
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

// IIC����һ���ֽ�
// ���شӻ�����Ӧ��:
// 1����Ӧ��
// 0����Ӧ��
void IIC_SendByte(u8 txd)
{
    IIC_SDAOut();
    SCL = 0; //����ʱ�ӿ�ʼ���ݴ���
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

// ��һ���ֽڣ�ack=1ʱ������ACK��ack=0������NACK
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
