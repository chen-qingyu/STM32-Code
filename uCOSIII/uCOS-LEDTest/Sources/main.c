#include "includes.h"

OS_TCB TaskStartTCB;
CPU_STK TaskStartStk[TASK_START_STK_SIZE];

int main(void)
{
    OS_ERR err;

    BSP_Init();
    OSInit(&err);

    OSTaskCreate((OS_TCB      *)&TaskStartTCB,                             // 控制块指针
                 (CPU_CHAR    *)"TaskStart",                               // 名称
                 (OS_TASK_PTR  )TaskStart,                                 // 代码指针
                 (void        *)0,                                         // 传递给任务的参数
                 (OS_PRIO      )TASK_START_PRIO,                           // 优先级
                 (CPU_STK     *)&TaskStartStk[0],                          // 栈基地址
                 (CPU_STK_SIZE )TASK_START_STK_SIZE / 8,                   // 栈深度限位
                 (CPU_STK_SIZE )TASK_START_STK_SIZE,                       // 栈大小
                 (OS_MSG_QTY   )0,                                         // 可接收的最大消息队列数
                 (OS_TICK      )0,                                         // 时间片轮转时间
                 (void        *)0,                                         // 控制块扩展信息
                 (OS_OPT       )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, // 选项
                 (OS_ERR      *)&err);                                     // 返回值
                 
    OSStart(&err);
}
