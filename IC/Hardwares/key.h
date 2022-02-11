#ifndef KEY_H
#define KEY_H

#include "stm32f10x.h"
#include "delay.h"

#define KEYUP PAin(0)

#define KEYUP_PRESS 1

void KEY_Init(void);
int KEY_Scan(int mode);

#endif
