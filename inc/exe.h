//**************************************************
// Файл                 : exe.h

#ifndef _EXE_H
#define _EXE_H
#include <stdint.h>
#include "stm32f4xx.h"


extern struct process exe_process;
void fnSendBinUart1(const uint8_t *s, int16_t len);

extern volatile  mavlink_message_t message_read;
extern volatile mavlink_status_t status_read;


#endif //_EXE_H


