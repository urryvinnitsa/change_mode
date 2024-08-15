//**************************************************
// Файл                     : main.h
//**************************************************

#ifndef MAIN_H
#define MAIN_H

#define BIT_SET(var,bitno)  ((var) |= 1 << (bitno))
#define BIT_CLR(var,bitno)  ((var) &= ~(1 << (bitno)))
#define BIT_TST1(var,bitno) ((var) & (1 << (bitno)))

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stdbool.h"
#include "mavlink.h"
#include "contiki.h"
#include "hard_config.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_spi.h"
#include "button.h"
#include "exe.h"


extern process_event_t event_button;
extern process_event_t event_1ms;
extern process_event_t event_kill;

//#define DEBUG_MY 1


#endif // MAIN_H

