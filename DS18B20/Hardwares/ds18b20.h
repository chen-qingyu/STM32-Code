#ifndef DS18B20_H
#define DS18B20_H

#include "sys.h"

// IO方向设置
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

// IO操作函数
#define DS18B20_DQ_OUT PGout(11)
#define DS18B20_DQ_IN PGin(11)

void DS18B20_Init(void);         // 初始化
u8 DS18B20_Check(void);          // 检测模块是否存在
s16 DS18B20_GetTemp(void);       // 获取温度值
void DS18B20_Reset(void);        // 复位
u8 DS18B20_ReadByte(void);       // 读取一个字节
void DS18B20_WriteByte(u8 data); // 写入一个字节

#endif
