#ifndef KEY_H
#define KEY_H

#include "delay.h"

#define KEY0  PEin(4)
#define KEY1  PEin(3)
#define KEYUP PAin(0)

#define KEY0_PRESS  1
#define KEY1_PRESS  2
#define KEYUP_PRESS 3

void KEY_Init(void);
int KEY_Scan(int mode);

#endif
