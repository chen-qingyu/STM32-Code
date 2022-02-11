#ifndef KEY_H
#define KEY_H

#include "includes.h"

// Î»´ø²Ù×÷
#define KEY0  PEin(4)
#define KEY1  PEin(3)
#define KEYUP PAin(0)

#define KEY0_PRESS  1
#define KEY1_PRESS  2
#define KEYUP_PRESS 3

#define EDGE_TRI 0
#define LEVEL_TRI 1

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif
