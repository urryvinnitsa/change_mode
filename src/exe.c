//**************************************************
// Файл                 : exe.c
//**************************************************
#include "main.h"
#include "stm32f4xx.h"
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
void USART1_Init(uint32_t bt);

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
                    mavlink_msg_set_mode_pack(0xff, 158, &message, 1, 209, 0);
                }
                else
                {
                    mavlink_msg_set_mode_pack(0xff, 158, &message, 1, 209, 10);
                }
                message.magic = 0xFD;//
                int len = mavlink_msg_to_send_buffer((uint8_t *)buffer_sbus, &message);
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}
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
void USART1_Init(uint32_t bt)
{
    /**USART1 GPIO Configuration
    PA9   ------> USART1_TX
    PA10   ------> USART1_RX
    */
    USART_InitTypeDef USART_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    //
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    //
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    USART_DeInit(USART1);
    USART_InitStructure.USART_BaudRate = bt;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
    USART_ClearFlag(USART1, USART_FLAG_CTS);
    USART_Cmd(USART1, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);// ENABLE);
}
//------------------------------------


