//**************************************************
// Файл                 : exe.c
//**************************************************
#include "main.h"
#include "stm32f4xx.h"

mavlink_message_t message;
volatile  mavlink_message_t message_read;
volatile mavlink_status_t status_read;
mavlink_status_t status;

mavlink_gps_raw_int_t gps_raw;

uint8_t buffer_sbus[256];

void fnSendBinUart1(const uint8_t *s, int16_t len);
void USART1_Init(uint32_t bt);
volatile uint8_t satellite = 0;
static union
{
    uint16_t arr[2];
    uint32_t i;
} un;

static uint32_t  rez;
//------------------------------------
PROCESS(exe_process, "T_exe");
PROCESS_THREAD(exe_process, ev, data)
{
    PROCESS_BEGIN();
    USART1_Init(57600);
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
    USART_ITConfig(USART1, USART_IT_RXNE,  ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------
void USART1_IRQHandler(void)
{
    static uint8_t m_Byte;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        m_Byte = USART_ReceiveData(USART1);
        if (mavlink_parse_char(MAVLINK_COMM_1, m_Byte, &message_read, &status_read))
        {
            if (message_read.msgid == MAVLINK_MSG_ID_GPS_RAW_INT)
            {
                USART_ITConfig(USART1, USART_IT_RXNE,  DISABLE);
                mavlink_msg_gps_raw_int_decode(&message_read, &gps_raw);
                satellite = gps_raw.satellites_visible;
							  if(satellite <= 10)
								{
									rez = 2000;
								}
								else if(satellite >= 12)
								{
									rez = 1000;
								}
                process_post(&satellite_process, event_decode, &rez);
                USART_ClearFlag(USART1, USART_FLAG_CTS);
                USART_ITConfig(USART1, USART_IT_RXNE,  ENABLE);
            }//(message.msgid == MAVLINK_MSG_ID_GPS_RAW_INT)
        }
    }// end     if( USART_GetITStatus(USART2, USART_IT_RXNE) )
    if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
    {
        (void)USART_ReceiveData(USART1);
    }
}
//---------------------------------------------------





