#include "at24cxx.h"

// ��AT24CXXָ����ַ����һ������
static u8 AT24CXX_ReadOneByte(u16 addr)
{
    u8 data = 0;
    IIC_Start();
    if (EEPROM_TYPE > AT24C16)
    {
        IIC_SendByte(0XA0); // ����д����
        IIC_WaitAck();
        IIC_SendByte(addr >> 8); // ���͸ߵ�ַ
        IIC_WaitAck();
    }
    else
    {
        IIC_SendByte(0XA0 + ((addr / 256) << 1)); // ����������ַ0XA0,д����
    }
    IIC_WaitAck();
    IIC_SendByte(addr % 256); // ���͵͵�ַ
    IIC_WaitAck();
    IIC_Start();
    IIC_SendByte(0XA1); // �������ģʽ
    IIC_WaitAck();
    data = IIC_ReadByte(0);
    IIC_Stop(); // ����һ��ֹͣ����
    return data;
}

// ��AT24CXXָ����ַд��һ������
static void AT24CXX_WriteOneByte(u16 addr, u8 data)
{
    IIC_Start();
    if (EEPROM_TYPE > AT24C16)
    {
        IIC_SendByte(0XA0); // ����д����
        IIC_WaitAck();
        IIC_SendByte(addr >> 8); // ���͸ߵ�ַ
    }
    else
    {
        IIC_SendByte(0XA0 + ((addr / 256) << 1)); // ����������ַ0XA0,д����
    }
    IIC_WaitAck();
    IIC_SendByte(addr % 256); // ���͵͵�ַ
    IIC_WaitAck();
    IIC_SendByte(data); // �����ֽ�
    IIC_WaitAck();
    IIC_Stop(); // ����һ��ֹͣ����
    delay_ms(10);
}

// ��ʼ��IIC
void AT24CXX_Init(void)
{
    IIC_Init();
}

// ��AT24CXX�����ָ����ַ��ʼ����ָ������������
// buffer: ���������׵�ַ
// addr: ��ʼ�����ĵ�ַ����AT24C02Ϊ0~255
// len: Ҫ�������ݵ��ֽ���
void AT24CXX_Read(u8 *buffer, u16 addr, u16 len)
{
    while (len--)
    {
        *buffer++ = AT24CXX_ReadOneByte(addr++);
    }
}

// ��AT24CXX�����ָ����ַ��ʼд��ָ������������
// buffer: ���������׵�ַ
// addr: ��ʼд��ĵ�ַ����AT24C02Ϊ0~255
// len: Ҫд�����ݵ��ֽ���
void AT24CXX_Write(u8 *buffer, u16 addr, u16 len)
{
    while (len--)
    {
        AT24CXX_WriteOneByte(addr++, *buffer++);
    }
}
