#ifndef KEY_H
#define KEY_H

#include "stm32f10x.h"

#include "delay.h"
#include "sys.h"

#define KEY0  PEin(4)
#define KEY1  PEin(3)
#define KEYUP PAin(0)

#define KEY0_PRESS  1
#define KEY1_PRESS  2
#define KEYUP_PRESS 3

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif
