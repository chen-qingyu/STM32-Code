#include "app.h"

extern OS_TCB TaskStartTCB;

OS_TCB  Task1TCB;
CPU_STK Task1STK[TASK_1_STK_SIZE];

OS_TCB  Task2TCB;
CPU_STK Task2STK[TASK_2_STK_SIZE];

// 定义互斥信号量
OS_MUTEX LED0Mutex;

void TaskStart(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;

    // 创建互斥信号量
    OSMutexCreate(&LED0Mutex, "LED 0 Mutex", &err);
    
    // 创建Task 1任务
    OSTaskCreate((OS_TCB    * )&Task1TCB,
                 (CPU_CHAR  * )"Task 1",
                 (OS_TASK_PTR )Task1,
                 (void      * )0,
                 (OS_PRIO     )TASK_1_PRIO,
                 (CPU_STK   * )&Task1STK[0],
                 (CPU_STK_SIZE)TASK_1_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_1_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);

    // 创建Task 2任务
    OSTaskCreate((OS_TCB    * )&Task2TCB,
                 (CPU_CHAR  * )"Task 2",
                 (OS_TASK_PTR )Task2,
                 (void      * )0,
                 (OS_PRIO     )TASK_2_PRIO,
                 (CPU_STK   * )&Task2STK[0],
                 (CPU_STK_SIZE)TASK_2_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_2_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);
                 
    OSTaskDel(&TaskStartTCB, &err);
}

void Task1(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;
    
    while (1)
    {
        // pend mutex
        OSMutexPend(&LED0Mutex, 0, OS_OPT_PEND_BLOCKING, (CPU_TS *)0, &err);
        
        // using LED0
        LED0 = 0;
        OSTimeDly(50, OS_OPT_TIME_DLY, &err);
        LED0 = 1;
        
        // post mutex
        OSMutexPost(&LED0Mutex, OS_OPT_POST_NONE, &err);
        
        // delay 100 tick
        OSTimeDly(100, OS_OPT_TIME_PERIODIC, &err);
    }
}

void Task2(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;
    
    while (1)
    {
        // pend mutex
        OSMutexPend(&LED0Mutex, 0, OS_OPT_PEND_BLOCKING, (CPU_TS *)0, &err);
        
        // using LED0
        LED0 = 0;
        OSTimeDly(50, OS_OPT_TIME_DLY, &err);
        LED0 = 1;
        
        // post mutex
        OSMutexPost(&LED0Mutex, OS_OPT_POST_NONE, &err);
        
        // delay 300 tick
        OSTimeDly(300, OS_OPT_TIME_PERIODIC, &err);
    }
}
