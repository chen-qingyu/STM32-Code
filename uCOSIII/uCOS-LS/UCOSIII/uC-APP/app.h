#ifndef APP_H
#define APP_H

#include "includes.h"

#define DLY_FLAG (1<<0)
#define KEY_FLAG (1<<1)
#define CMD_FLAG (1<<2)

/******************* 设置任务优先级 *******************/
#define TASK_START_PRIO         3
#define TASK_CYCLE_PRIO         5
#define TASK_FIELD_PRIO         4
#define TASK_SAMPLE_PRIO        6


/******************* 设置任务栈大小 *******************/
#define TASK_START_STK_SIZE     64
#define TASK_CYCLE_STK_SIZE     64
#define TASK_FIELD_STK_SIZE     64
#define TASK_SAMPLE_STK_SIZE    64


/******************** 声明用户任务 ********************/
void TaskStart(void *p_arg);
void TaskCycle(void *p_arg);
void TaskField(void *p_arg);
void TaskSample(void *p_arg);

#endif
