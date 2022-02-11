#include "app.h"

extern OS_TCB TaskStartTCB;

OS_TCB  TaskLED0TCB;
CPU_STK TaskLED0Stk[TASK_LED0_STK_SIZE];

void TaskStart(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;

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

void TaskLED0(void *p_arg)
{
    OS_ERR err;
    OS_TICK start, end;
    (void)p_arg;
    
    while (1)
    {
        // get start time value
        start = OSTimeGet(&err);
        
        // using LED0
        LED0 = ~LED0;
        
        // delay 1 s
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        
        // get end time value
        end = OSTimeGet(&err);
        
        // print time cost
        printf("time cost: %u ms.\r\n", (end - start) * (1000 / OSCfg_TickRate_Hz));
    }
}
