#include "app.h"

extern OS_TCB TaskStartTCB;

OS_TCB  TaskCycleTCB;
CPU_STK TaskCycleStk[TASK_CYCLE_STK_SIZE];

OS_TCB  TaskFieldTCB;
CPU_STK TaskFieldStk[TASK_FIELD_STK_SIZE];

OS_TCB  TaskSampleTCB;
CPU_STK TaskSampleStk[TASK_SAMPLE_STK_SIZE];

OS_FLAG_GRP SampleFlag;

void TaskStart(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;

    // create sample flag
    OSFlagCreate(&SampleFlag, "SampleFlag", 0, &err);
    
    // create task cycle sample
    OSTaskCreate((OS_TCB    * )&TaskCycleTCB,
                 (CPU_CHAR  * )"TaskCycle",
                 (OS_TASK_PTR )TaskCycle,
                 (void      * )0,
                 (OS_PRIO     )TASK_CYCLE_PRIO,
                 (CPU_STK   * )&TaskCycleStk[0],
                 (CPU_STK_SIZE)TASK_CYCLE_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_CYCLE_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);
                 
    // create task field sample
    OSTaskCreate((OS_TCB    * )&TaskFieldTCB,
                 (CPU_CHAR  * )"TaskField",
                 (OS_TASK_PTR )TaskField,
                 (void      * )0,
                 (OS_PRIO     )TASK_FIELD_PRIO,
                 (CPU_STK   * )&TaskFieldStk[0],
                 (CPU_STK_SIZE)TASK_FIELD_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_FIELD_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);
                 
    // create task sample upload
    OSTaskCreate((OS_TCB    * )&TaskSampleTCB,
                 (CPU_CHAR  * )"TaskSample",
                 (OS_TASK_PTR )TaskSample,
                 (void      * )0,
                 (OS_PRIO     )TASK_SAMPLE_PRIO,
                 (CPU_STK   * )&TaskSampleStk[0],
                 (CPU_STK_SIZE)TASK_SAMPLE_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_SAMPLE_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);
                 
    OSTaskDel(&TaskStartTCB, &err);
}

void TaskCycle(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;
    
    while (1)
    {
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_PERIODIC, &err);
        OSFlagPost(&SampleFlag, DLY_FLAG, OS_OPT_POST_FLAG_SET, &err);
    }
}

void TaskField(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;
    
    while (1)
    {
        OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_DLY, &err);
        if (KEY_Scan(EDGE_TRI) == KEY0_PRESS)
        {
            OSFlagPost(&SampleFlag, KEY_FLAG, OS_OPT_POST_FLAG_SET, &err);
        }
    }
}

void TaskSample(void *p_arg)
{
    OS_ERR err;
    u8 value;
    OS_TICK ts;
    (void)p_arg;
    
    while (1)
    {
        OSFlagPend(&SampleFlag,
                   DLY_FLAG | KEY_FLAG | CMD_FLAG,
                   0,
                   OS_OPT_PEND_FLAG_SET_ANY | OS_OPT_PEND_FLAG_CONSUME | OS_OPT_PEND_BLOCKING,
                   0,
                   &err);
        ts = OSTimeGet(&err);
        value = LS_GetValue();
        GPRS_Send(value, ts);
    }
}
