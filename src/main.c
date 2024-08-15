//**************************************************
// Файл                     : main.c
//**************************************************
//
#include "main.h"

#if 0
0 manual
1 circle
2 stabilize
3 trening
4 acro
5 fbwa
6 fbwb
7 cruise
8 autotune
9 trening
10 rtl
11 rtl
12 loiter
13 takeoff
14 AVOID_A
15 Guided
16 trening
17 xz
18 xz
19
#endif
uint32_t idle_count = 0;
uint32_t cl;
process_event_t event_button;
process_event_t event_1ms;
process_event_t event_kill;
static char pair = 0;
mavlink_message_t message1;
#define CODE_LOITER 5
#define CODE_AUTO 3
static uint8_t buffer_sbus[32];
//--------------------------------------------------
PROCESS(led_process, "Led");
PROCESS_THREAD(led_process, ev, data)
{
    static int rez = 0;
    static int cnt = 0;
    PROCESS_BEGIN();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = LED_PIN ; //
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(LED_PORT, &GPIO_InitStruct);
    while (1)
    {
        static struct etimer et;
        etimer_set(&et, 1);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        cnt++;
        if (cnt >= 500)
        {
            cnt = 0;
            IWDG_ReloadCounter();
            GPIO_ToggleBits(LED_PORT, LED_PIN);
#ifdef DEBUG_MY
            if (!pair)
            {
                pair = 1;
                mavlink_msg_set_mode_pack(0xff, 158, &message1, 1, 209, 12);
            }
            else
            {
                pair = 0;
                mavlink_msg_set_mode_pack(0xff, 158, &message1, 1, 209, 2);
            }
            message1.magic = 0xFD;//
            int    len = mavlink_msg_to_send_buffer((uint8_t *)buffer_sbus, &message1);
            fnSendBinUart1((const uint8_t *)buffer_sbus, len);
#endif
        }
    }
    PROCESS_END();
}
//--------------------------------------------------
int main(void)
{
    static int rez = 0;
    RCC_HSEConfig(RCC_HSE_ON);
    SystemInit();
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
    USART6_Init(115200);
    printf("\r\nstart version  %.1f\r\n", 1.0);
    clock_init();
    rtimer_init();
    process_init();
    //
    event_button = process_alloc_event();
    event_1ms = process_alloc_event();
    event_kill = process_alloc_event();
    process_start(&etimer_process, NULL);
    process_start(&led_process, NULL);
    process_start(&button_process, NULL);
    process_start(&exe_process, NULL);
    process_post(&exe_process, event_button, &rez);
    IWDG_Configuration();
    for (;;)
    {
        do {}
        while (process_run() > 0);
        idle_count++;
    }
}
//--------------------------------------------------
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#pragma import(__use_no_semihosting)
struct __FILE
{
    int handle;
};
FILE __stdout;
void _sys_exit(int x)
{
    x = x;
}
PUTCHAR_PROTOTYPE
{
    USART_SendData(USART6, (uint8_t) ch);
    while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)
    {}
    return ch;
}
//--------------------------------------------------



