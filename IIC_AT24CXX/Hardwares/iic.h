#ifndef IIC_H
#define IIC_H

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

#define SCL PBout(6)
#define SDA_OUT PBout(7)
#define SDA_IN PBin(7)

void IIC_Init(void);       //��ʼ��IIC��IO��
void IIC_Start(void);      //����IIC��ʼ�ź�
void IIC_Stop(void);       //����IICֹͣ�ź�
void IIC_SendByte(u8 txd); //IIC����һ���ֽ�
u8 IIC_ReadByte(u8 ack);   //IIC��ȡһ���ֽ�
u8 IIC_WaitAck(void);      //IIC�ȴ�ACK�ź�

#endif
