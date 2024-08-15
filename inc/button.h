//**************************************************
// Файл                 : button.h

#ifndef BUTTON_H
#define BUTTON_H
#include <stdint.h>
#include "stm32f4xx.h"
typedef struct
{
    GPIO_TypeDef *Port_B;
    uint16_t Pin_B;
} buttons_t;
#define BUTTON 1

extern struct process button_process;
extern volatile uint16_t rez_butt;
extern volatile uint8_t a_h;



#endif //BUTTON_H




