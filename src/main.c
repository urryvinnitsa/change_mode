//**************************************************
// Файл                     : main.c
//**************************************************
//
#include "main.h"


uint32_t idle_count = 0;

process_event_t event_button;
process_event_t event_1ms;
process_event_t event_decode;

void IWDG_Configuration(void);
// for debug ------------
static char pair = 0;
mavlink_message_t message1;
static uint8_t buffer_sbus[20];
//-----------------------
//--------------------------------------------------
PROCESS(led_process, "Led");
PROCESS_THREAD(led_process, ev, data)
{
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
                mavlink_msg_set_mode_pack(0xff, 158, &message1, 1, 209, 0);
            }
            else
            {
                pair = 0;
                mavlink_msg_set_mode_pack(0xff, 158, &message1, 1, 209, 10);
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
    RCC_HSEConfig(RCC_HSE_ON);
    SystemInit();
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
    clock_init();
    rtimer_init();
    process_init();
    //
    event_button = process_alloc_event();
    event_1ms = process_alloc_event();
    event_decode = process_alloc_event();
    process_start(&etimer_process, NULL);
    process_start(&led_process, NULL);
    process_start(&button_process, NULL);
    process_start(&exe_process, NULL);
    process_start(&satellite_process, NULL);
    //
    IWDG_Configuration();
    for (;;)
    {
        do {}
        while (process_run() > 0);
        idle_count++;
    }
}
//--------------------------------------------------
void IWDG_Configuration(void)
{
    /* IWDG timeout equal to 280 ms (the timeout may varies due to LSI frequency
    dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    //  IWDG_WriteAccessCmd(
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    /* IWDG counter clock: 40KHz(LSI) / 256 = 156 Hz */
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    /* Set counter reload value to 349 */
    IWDG_SetReload(156 * 5); // 5 sec
    /* Reload IWDG counter */
    IWDG_ReloadCounter();       //4,42 sec
    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
}
//--------------------------------------------------


