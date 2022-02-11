#include "app.h"

extern OS_TCB TaskStartTCB;

OS_TCB  TaskLED0TCB;
CPU_STK TaskLED0STK[TASK_LED0_STK_SIZE];

OS_TCB  TaskLED1TCB;
CPU_STK TaskLED1STK[TASK_LED1_STK_SIZE];

void TaskStart(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;
    
    // 根据配置使能时间片轮转调度
#if OS_CFG_SCHED_ROUND_ROBIN_EN
    OSSchedRoundRobinCfg(DEF_ENABLED, 1, &err); // 1 * 5 = 5ms
#endif

    // 创建LED0任务
    OSTaskCreate((OS_TCB    * )&TaskLED0TCB,
                 (CPU_CHAR  * )"TaskLED0",
                 (OS_TASK_PTR )TaskLED0,
                 (void      * )0,
                 (OS_PRIO     )TASK_LED0_PRIO,
                 (CPU_STK   * )&TaskLED0STK[0],
                 (CPU_STK_SIZE)TASK_LED0_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_LED0_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )2, // 2 * 5 = 10ms
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);
                 
    // 创建LED1任务
    OSTaskCreate((OS_TCB    * )&TaskLED1TCB,
                 (CPU_CHAR  * )"TaskLED1",
                 (OS_TASK_PTR )TaskLED1,
                 (void      * )0,
                 (OS_PRIO     )TASK_LED1_PRIO,
                 (CPU_STK   * )&TaskLED1STK[0],
                 (CPU_STK_SIZE)TASK_LED1_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_LED1_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )2, // 2 * 5 = 10ms
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);
                 
    OSTaskDel(&TaskStartTCB, &err);
}

void TaskLED0(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;
    
    while (1)
    {
        LED0 = ~LED0;
        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err); // delay 500ms
    }
}

void TaskLED1(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;
    
    while (1)
    {
        LED1 = ~LED1;
        OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err); // delay 1s
    }
}
