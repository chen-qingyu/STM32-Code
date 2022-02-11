#ifndef APP_H
#define APP_H

#include "includes.h"


/******************* 设置任务优先级 *******************/
#define TASK_START_PRIO         3
#define TASK_Mem_PRIO          4


/******************* 设置任务栈大小 *******************/
#define TASK_START_STK_SIZE     64
#define TASK_Mem_STK_SIZE      64


/******************** 声明用户任务 ********************/
void TaskStart(void *p_arg);
void TaskMem(void *p_arg);


#endif
