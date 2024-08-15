//**************************************************
// Файл                     : init.h
//**************************************************

#ifndef INIT_H
#define INIT_H
#include <stdint.h>
#include <stdbool.h>
void USART1_Init(uint32_t bt);//, uint8_t *arr_send, uint16_t max_size);
//void USART1SendDMA(uint8_t *arr, uint16_t len);
//
void USART2_Init(uint32_t bt, uint8_t *arr_send, uint16_t max_size);
void USART2SendDMA(uint16_t len);
//
void USART6_Init(uint32_t bt);//, uint8_t *arr_send, uint16_t max_size);
void USART6SendDMA(uint16_t len);
//
typedef struct
{
    bool u1;
    bool u2;
    bool u6;
} send_free_;

extern volatile send_free_ send_free;


void TIM1_Init(void);
void TIM3_Init(void);
void TIM2_Init(void);
//
void delay_us(uint16_t delay);
void delay_ms(uint16_t delay);
void IWDG_Configuration(void);
//--------------------------------------------------
void SPI1_Init(void);
void SPI2_Init(void);
//--------------------------------------------------
void SPI1_WriteByte(uint8_t TxData);
uint8_t SPI1_ReadByte(void);
//--------------------------------------------------
void SPI2_WriteByte(uint8_t TxData);
uint8_t SPI2_ReadByte(void);
//--------------------------------------------------

#endif // INIT_H

