#include "includes.h"

OS_TCB TaskStartTCB;
CPU_STK TaskStartStk[TASK_START_STK_SIZE];

int main(void)
{
    OS_ERR err;

    BSP_Init();
    OSInit(&err);

    OSTaskCreate((OS_TCB      *)&TaskStartTCB,                             // ���ƿ�ָ��
                 (CPU_CHAR    *)"TaskStart",                               // ����
                 (OS_TASK_PTR  )TaskStart,                                 // ����ָ��
                 (void        *)0,                                         // ���ݸ�����Ĳ���
                 (OS_PRIO      )TASK_START_PRIO,                           // ���ȼ�
                 (CPU_STK     *)&TaskStartStk[0],                          // ջ����ַ
                 (CPU_STK_SIZE )TASK_START_STK_SIZE / 8,                   // ջ�����λ
                 (CPU_STK_SIZE )TASK_START_STK_SIZE,                       // ջ��С
                 (OS_MSG_QTY   )0,                                         // �ɽ��յ������Ϣ������
                 (OS_TICK      )0,                                         // ʱ��Ƭ��תʱ��
                 (void        *)0,                                         // ���ƿ���չ��Ϣ
                 (OS_OPT       )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, // ѡ��
                 (OS_ERR      *)&err);                                     // ����ֵ
                 
    OSStart(&err);
}
