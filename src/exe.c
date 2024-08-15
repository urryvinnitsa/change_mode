//**************************************************
// Файл                 : exe.c
//**************************************************
#include "main.h"
#if 0

FLTMODE6 :
Flight Mode 6¶
Flight mode when pwm of Flightmode channel(FLTMODE_CH) is >= 1750

0 Stabilize
1 Acro
2 AltHold
3 Auto
4 Guided
5 Loiter
6 RTL
7 Circle
9 Land
11 Drift
13 Sport
14 Flip
15 AutoTune
16 PosHold
17 Brake
18 Throw
19 Avoid_ADSB
20 Guided_NoGPS
21 Smart_RTL
22 FlowHold
23 Follow
24 ZigZag
25 SystemID
26 Heli_Autorotate
27 Auto RTL

#endif
mavlink_message_t message;
#define CODE_LOITER 5
#define CODE_AUTO 3

uint8_t buffer_sbus[256];
void fnSendBinUart1(const uint8_t *s, int16_t len);
int len;

static union
{
    uint16_t arr[2];
    uint32_t i;
} un;


//------------------------------------
PROCESS(exe_process, "T_exe");
PROCESS_THREAD(exe_process, ev, data)
{
    PROCESS_BEGIN();
    USART1_Init(115200);
    while (1)
    {
        PROCESS_WAIT_EVENT_UNTIL(ev == event_1ms || ev == event_button);
        un.i = (*(uint32_t *)data);
        if (ev == event_1ms)
        {
        }
        if (ev == event_button)
        {
            uint16_t butt = un.arr[0];
            uint16_t press = un.arr[1];
            if (butt == 0)
            {
                if (press == 1)
                {
                    mavlink_msg_set_mode_pack(0xff, 158, &message, 1, 209, 2);
                }
                else
                {
                    mavlink_msg_set_mode_pack(0xff, 158, &message, 1, 209, 12);
                }
                message.magic = 0xFD;//
                len = mavlink_msg_to_send_buffer((uint8_t *)buffer_sbus, &message);
                fnSendBinUart1((const uint8_t *)buffer_sbus, len);
            }
        }
    }
    PROCESS_END();
}
//------------------------------------
void fnSendBinUart1(const uint8_t *s, int16_t len)
{
    while (len--)
    {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}
        USART_SendData(USART1, *s++);
    }
}
//------------------------------------




