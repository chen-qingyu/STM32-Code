#include "at24cxx.h"

// 在AT24CXX指定地址读出一个数据
static u8 AT24CXX_ReadOneByte(u16 addr)
{
    u8 data = 0;
    IIC_Start();
    if (EEPROM_TYPE > AT24C16)
    {
        IIC_SendByte(0XA0); // 发送写命令
        IIC_WaitAck();
        IIC_SendByte(addr >> 8); // 发送高地址
        IIC_WaitAck();
    }
    else
    {
        IIC_SendByte(0XA0 + ((addr / 256) << 1)); // 发送器件地址0XA0,写数据
    }
    IIC_WaitAck();
    IIC_SendByte(addr % 256); // 发送低地址
    IIC_WaitAck();
    IIC_Start();
    IIC_SendByte(0XA1); // 进入接收模式
    IIC_WaitAck();
    data = IIC_ReadByte(0);
    IIC_Stop(); // 产生一个停止条件
    return data;
}

// 在AT24CXX指定地址写入一个数据
static void AT24CXX_WriteOneByte(u16 addr, u8 data)
{
    IIC_Start();
    if (EEPROM_TYPE > AT24C16)
    {
        IIC_SendByte(0XA0); // 发送写命令
        IIC_WaitAck();
        IIC_SendByte(addr >> 8); // 发送高地址
    }
    else
    {
        IIC_SendByte(0XA0 + ((addr / 256) << 1)); // 发送器件地址0XA0,写数据
    }
    IIC_WaitAck();
    IIC_SendByte(addr % 256); // 发送低地址
    IIC_WaitAck();
    IIC_SendByte(data); // 发送字节
    IIC_WaitAck();
    IIC_Stop(); // 产生一个停止条件
    delay_ms(10);
}

// 初始化IIC
void AT24CXX_Init(void)
{
    IIC_Init();
}

// 在AT24CXX里面的指定地址开始读出指定个数的数据
// buffer: 数据数组首地址
// addr: 开始读出的地址，对AT24C02为0~255
// len: 要读出数据的字节数
void AT24CXX_Read(u8 *buffer, u16 addr, u16 len)
{
    while (len--)
    {
        *buffer++ = AT24CXX_ReadOneByte(addr++);
    }
}

// 在AT24CXX里面的指定地址开始写入指定个数的数据
// buffer: 数据数组首地址
// addr: 开始写入的地址，对AT24C02为0~255
// len: 要写入数据的字节数
void AT24CXX_Write(u8 *buffer, u16 addr, u16 len)
{
    while (len--)
    {
        AT24CXX_WriteOneByte(addr++, *buffer++);
    }
}
