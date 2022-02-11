#ifndef IIC_H
#define IIC_H

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

#define SCL PBout(6)
#define SDA_OUT PBout(7)
#define SDA_IN PBin(7)

void IIC_Init(void);       //初始化IIC的IO口
void IIC_Start(void);      //发送IIC开始信号
void IIC_Stop(void);       //发送IIC停止信号
void IIC_SendByte(u8 txd); //IIC发送一个字节
u8 IIC_ReadByte(u8 ack);   //IIC读取一个字节
u8 IIC_WaitAck(void);      //IIC等待ACK信号

#endif
