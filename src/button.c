//**************************************************
// Файл                 : button.c
//**************************************************
#include "main.h"


const buttons_t buttons[BUTTON] = {\
                                   [0].Port_B = B0_PORT, [0].Pin_B = B0_PIN, \
                                  };

typedef struct
{
    bool blok;
    bool naj;
    bool otj; //
    signed char st;//
} but_t ;
static  but_t but[BUTTON];

#define BUT_TIME_MAX 10
#define kn_ot(x) {but[x].otj=1;but[x].st =0;but[x].blok=0; but[x].naj=0;}
#define kn_nj(x)  {but[x].naj=1;but[x].st =BUT_TIME_MAX;but[x].otj=0;}
volatile  uint8_t new_button;

void fnButtonInit(void);
static void fnButtRead(void);
static void fnSetRegButt(void);
volatile uint16_t rez_butt;
static uint16_t rez_butt_old = 0xFFFF;

static union
{
    uint16_t arr[2];
    uint32_t i;
} un;

//--------------------------------------------------
////--------------------------------------------------
////--------------------------------------------------
PROCESS(button_process, "Button");
//---------------------------------------------------
PROCESS_THREAD(button_process, ev, data)
{
    PROCESS_BEGIN();
    fnButtonInit();
    while (1)
    {
        static struct etimer et;
        etimer_set(&et, 1);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        fnButtRead();
        fnSetRegButt();
    }
    PROCESS_END();
}
//---------------------------------------------------
void fnButtonInit(void)
{
    uint8_t i;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    for (i = 0; i < BUTTON; i++)
    {
        GPIO_InitStruct.GPIO_Pin = buttons[i].Pin_B ;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_Init(buttons[i].Port_B, &GPIO_InitStruct);
    }
}
//---------------------------------------------------
static void fnButtRead(void)
{
    uint8_t i;
    for (i = 0; i < BUTTON; i++)
    {
        if ((!GPIO_ReadInputDataBit(buttons[i].Port_B, buttons[i].Pin_B)))
        {
            but[i].st++;
            if (but[i].st >= BUT_TIME_MAX)
            {
                kn_nj(i);
            }
        }
        else
        {
            but[i].st--;
            if (but[i].st <= 0)
            {
                kn_ot(i);
            }
        }
    }
}
//---------------------------------------------------
static void fnSetRegButt(void)
{
    for (int i = 0; i < BUTTON; i++)
    {
        if (but[i].naj)
        {
            BIT_SET(rez_butt, i);
        }
        else
        {
            BIT_CLR(rez_butt, i);
        }
    }
    //
    uint16_t rez = rez_butt_old ^ rez_butt;
    if (rez)
    {
        for (int i = 0; i < BUTTON; i++)
        {
            if (BIT_TST1(rez, i))
            {
                un.arr[0] = i;//
                if ((BIT_TST1(rez_butt, i))) //
                {
                    un.arr[1] = 1; // press
                }
                else
                {
                    un.arr[1] = 0; //unpress
                }
                break;
            }
        }
        //-------------------------------------------------
        process_post(&exe_process, event_button, &un.i);
        rez_butt_old = rez_butt;
        new_button = 1;
    }
}
//---------------------------------------------------



