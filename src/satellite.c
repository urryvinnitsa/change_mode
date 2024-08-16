//**************************************************
// Файл                 : satellite.c
//**************************************************
#include "main.h"
#include "stm32f4xx.h"

static mavlink_message_t message_send;

uint16_t sat;
uint8_t buffer_send[64];

static union
{
    uint16_t arr[2];
    uint32_t i;
} un;
//------------------------------------
PROCESS(satellite_process, "T_satellite");
PROCESS_THREAD(satellite_process, ev, data)
{
    PROCESS_BEGIN();
    while (1)
    {
        PROCESS_WAIT_EVENT_UNTIL(ev == event_decode);
        un.i = (*(uint32_t *)data);
        sat = un.i;
        if (ev == event_decode)
        {
            mavlink_msg_rc_channels_override_pack(0xff, 158, &message_send, 1, 1,
                                                  1000, 1000, 1000, 1000,
                                                  1000, 1000, 1000,
                                                  1000, 1000, 1000, 1000,
                                                  1000, 1000, 1000, sat,
                                                  sat,
                                                  1000, 2500);
            message_send.magic = 0xFD;//
            int len_send = mavlink_msg_to_send_buffer((uint8_t *)buffer_send, &message_send);
            while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}
            fnSendBinUart1((const uint8_t *)buffer_send, len_send);
        }
    }
    PROCESS_END();
}
//------------------------------------






