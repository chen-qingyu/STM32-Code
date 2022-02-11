#ifndef APP_H
#define APP_H

#include "includes.h"

#define DLY_FLAG (1<<0)
#define KEY_FLAG (1<<1)

/******************* 设置任务优先级 *******************/
#define TASK_START_PRIO         3
#define TASK_Delay_PRIO         4
#define TASK_LED0_PRIO          5


/******************* 设置任务栈大小 *******************/
#define TASK_START_STK_SIZE     64
#define TASK_DELAY_STK_SIZE     64
#define TASK_LED0_STK_SIZE      64


/******************** 声明用户任务 ********************/
void TaskStart(void *p_arg);
void TaskDelay(void *p_arg);
void TaskLED0(void *p_arg);


#endif
