#include "app.h"

extern OS_TCB TaskStartTCB;

OS_TCB  TaskLED0TCB;
CPU_STK TaskLED0Stk[TASK_LED0_STK_SIZE];

OS_TCB  TaskDelayTCB;
CPU_STK TaskDelayStk[TASK_DELAY_STK_SIZE];

// define MyFlags
OS_FLAG_GRP MyFlags;

void TaskStart(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;

    // create MyFlags
    OSFlagCreate(&MyFlags, "MyFlags", 0, &err);

    // create task Delay
    OSTaskCreate((OS_TCB    * )&TaskDelayTCB,
                 (CPU_CHAR  * )"TaskDelay",
                 (OS_TASK_PTR )TaskDelay,
                 (void      * )0,
                 (OS_PRIO     )TASK_Delay_PRIO,
                 (CPU_STK   * )&TaskDelayStk[0],
                 (CPU_STK_SIZE)TASK_DELAY_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_DELAY_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);

    // create task LED0
    OSTaskCreate((OS_TCB    * )&TaskLED0TCB,
                 (CPU_CHAR  * )"TaskLED0",
                 (OS_TASK_PTR )TaskLED0,
                 (void      * )0,
                 (OS_PRIO     )TASK_LED0_PRIO,
                 (CPU_STK   * )&TaskLED0Stk[0],
                 (CPU_STK_SIZE)TASK_LED0_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_LED0_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);

    OSTaskDel(&TaskStartTCB, &err);
}

void TaskDelay(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;

    while (1)
    {
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_PERIODIC, &err);
        OSFlagPost(&MyFlags, DLY_FLAG, OS_OPT_POST_FLAG_SET, &err);
    }
}

void TaskLED0(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;

    while (1)
    {
        OSFlagPend(&MyFlags,
                   (DLY_FLAG | KEY_FLAG),
                   0,
                   OS_OPT_PEND_FLAG_SET_ANY | OS_OPT_PEND_FLAG_CONSUME | OS_OPT_PEND_BLOCKING,
                   0,
                   &err);
        LED0 = 0;
        OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_DLY, &err);
        LED0 = 1;
    }
}
