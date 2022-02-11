#ifndef  INCLUDES_H
#define  INCLUDES_H


// 优先级0：中断服务服务管理任务 OS_IntQTask()
// 优先级1：时钟节拍任务 OS_TickTask()
// 优先级2：定时任务 OS_TmrTask()
// 优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
// 优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()


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
