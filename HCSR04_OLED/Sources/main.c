/*
**���**
OLED�ۺ����

**����**
����0���£���ʾ���
����1���£����Ŷ���
���κΰ������£���ʾ�����棬ͬʱ��ʾ�����������

**ģ��**
OLED��SSD1306��һ��
��������������HC-SR04��һ��
������������
*/

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "key.h"
#include "hcsr04.h"

// ASCII1608����߶�
#define HIGHT 16

// ��ʡ�����Counting Stars��
const u8 lyric[14][17] = {
    {"Lately I've been"},
    {"I've been       "},
    {"losing sleep    "},
    {"Dreaming about  "},
    {"the things      "},
    {"that we could be"},
    {"But baby,       "},
    {"I've been,      "},
    {"I've been       "},
    {"praying hard    "},
    {"Said no more    "},
    {"counting dollars"},
    {"We'll be        "},
    {"counting stars  "}
};

int main(void)
{
    delay_init();
    
    // �����ʼ��
    OLED_Init();
    KEY_Init();
    HCSR04_Init();
    
    u8 key;  // ��������
    u8 i, j; // ѭ������
    u8 h;    // �߶ȿ���
    u8 flag = 1; // �������־��������ֹһֱˢ��������

    while (1)
    {
        key = KEY_Scan();

        switch (key)
        {
            // ����0���£���ʾ���
            case KEY0_PRESS:
                OLED_Clear();
                for (i = 0; i < 11; i++)
                {
                    for (j = i, h = 0; j < i + 4; j++, h++)
                    {
                        OLED_ShowString(00, h * HIGHT, lyric[j]);
                    }
                    delay_ms(1000);
                }
                delay_ms(100);
                OLED_Clear();
                flag = 1;
                break;

            // ����1���£����Ŷ���
            case KEY1_PRESS:
                OLED_Clear();
                for (i = 0; i < 10; i++)
                {
                    for (j = 0; j < 32; j++)
                    {
                        OLED_Fill(63 - 2 * j, 31 - j, 64 + 2 * j, 32 + j, i % 2);
                        delay_ms(1);
                    }
                }
                delay_ms(100);
                OLED_Clear();
                flag = 1;
                break;

            // ���κΰ������£���ʾ�����棬ͬʱ��ʾ�����������
            default:
                if (flag)
                {
                    OLED_Clear();
                    OLED_ShowString(00, 0 * HIGHT, "Key 1: Lyric");
                    OLED_ShowString(00, 1 * HIGHT, "Key 2: Animation");
                    OLED_ShowString(00, 2 * HIGHT, "Ultrasonic");
                    OLED_ShowString(00, 3 * HIGHT, "Distance: ");
                    OLED_ShowString(14 * HIGHT / 2, 3 * HIGHT, "cm");
                    flag = 0;
                }
                OLED_ShowNum(10 * HIGHT / 2, 3 * HIGHT, (u32)HCSR04_GetDistance(), 3);
                delay_ms(100);
                break;
        }
    }
}
