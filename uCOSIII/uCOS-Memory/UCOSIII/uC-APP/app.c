#include "app.h"

extern OS_TCB TaskStartTCB;

OS_TCB  TaskMemTCB;
CPU_STK TaskMemStk[TASK_Mem_STK_SIZE];

void TaskStart(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;

    // create task Mem
    OSTaskCreate((OS_TCB    * )&TaskMemTCB,
                 (CPU_CHAR  * )"TaskMem",
                 (OS_TASK_PTR )TaskMem,
                 (void      * )0,
                 (OS_PRIO     )TASK_Mem_PRIO,
                 (CPU_STK   * )&TaskMemStk[0],
                 (CPU_STK_SIZE)TASK_Mem_STK_SIZE / 8,
                 (CPU_STK_SIZE)TASK_Mem_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void      * )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR    * )&err);

    OSTaskDel(&TaskStartTCB, &err);
}

void TaskMem(void *p_arg)
{
    OS_ERR err;
    (void)p_arg;
    u8 *pbuf;
    u8 size = 12;

    while (1)
    {
        printf("Alloc %u B memory...\r\n", size);
        pbuf = mymalloc(SRAMIN, size);
        if (pbuf)
        {
            printf("Alloc successful! Now writing...\r\n");
            sprintf((char *)pbuf, "hello world!");

            printf("Show data: \"%s\"\r\n", pbuf);

            printf("Now free...\r\n");
            myfree(SRAMIN, pbuf);

            printf("After free: \"%s\"\r\n", pbuf);

            pbuf = NULL;
            printf("After set null: \"%s\"\r\n", pbuf);

            printf("\r\n\r\n");

            OSTimeDlyHMSM(0, 0, 5, 0, OS_OPT_TIME_DLY, &err);
        }
    }
}
