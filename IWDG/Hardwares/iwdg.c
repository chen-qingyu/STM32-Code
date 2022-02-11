#include "iwdg.h"

void IWDG_Init(u8 pre, u16 reload)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(pre);
    IWDG_SetReload(reload);
    IWDG_ReloadCounter();
    IWDG_Enable();
}
