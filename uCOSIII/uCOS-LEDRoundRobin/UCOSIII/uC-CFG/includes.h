#ifndef  INCLUDES_H
#define  INCLUDES_H


// ���ȼ�0���жϷ������������� OS_IntQTask()
// ���ȼ�1��ʱ�ӽ������� OS_TickTask()
// ���ȼ�2����ʱ���� OS_TmrTask()
// ���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
// ���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()


// STANDARD LIBRARIES
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// uCOS-III LIBRARIES
#include <cpu.h>
#include <lib_def.h>
#include <lib_ascii.h>
#include <lib_math.h>
#include <lib_mem.h>
#include <lib_str.h>


// APP / BSP
#include "app.h"
#include "bsp.h"
#include "led.h"


// OS
#include <os.h>
#include <os_type.h>


// ST
#include <stm32f10x.h>


// ALIENTEK
#include "delay.h"
#include "sys.h"
#include "usart.h"


#endif
