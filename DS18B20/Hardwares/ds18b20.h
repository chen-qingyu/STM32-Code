#ifndef DS18B20_H
#define DS18B20_H

#include "sys.h"

// IO��������
#define DS18B20_IO_IN()           \
    {                             \
        GPIOG->CRH &= 0XFFFF0FFF; \
        GPIOG->CRH |= 8 << 12;    \
    }
#define DS18B20_IO_OUT()          \
    {                             \
        GPIOG->CRH &= 0XFFFF0FFF; \
        GPIOG->CRH |= 3 << 12;    \
    }

// IO��������
#define DS18B20_DQ_OUT PGout(11)
#define DS18B20_DQ_IN PGin(11)

void DS18B20_Init(void);         // ��ʼ��
u8 DS18B20_Check(void);          // ���ģ���Ƿ����
s16 DS18B20_GetTemp(void);       // ��ȡ�¶�ֵ
void DS18B20_Reset(void);        // ��λ
u8 DS18B20_ReadByte(void);       // ��ȡһ���ֽ�
void DS18B20_WriteByte(u8 data); // д��һ���ֽ�

#endif
