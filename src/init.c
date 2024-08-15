//**************************************************
// Файл                     : init.c
//**************************************************
#include "main.h"
//--------------------------------------------------
volatile send_free_ send_free;
//--------------------------------------------------
void USART1_Init(uint32_t bt)//, uint8_t *arr_send, uint16_t max_size)
{
    /**USART1 GPIO Configuration
    PA9   ------> USART1_TX
    PA10   ------> USART1_RX
    */
    //    DMA_InitTypeDef DMA_InitStructureRX;
    USART_InitTypeDef USART_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    //
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    //    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
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
#if 0
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //
    DMA_DeInit(DMA2_Stream7);
    DMA_Cmd(DMA2_Stream7, DISABLE);
    //
    DMA_StructInit(&DMA_InitStructureRX);
    DMA_InitStructureRX.DMA_PeripheralBaseAddr = (uint32_t) & (USART1->DR);
    DMA_InitStructureRX.DMA_Memory0BaseAddr = (uint32_t)(&arr_send[0]);
    DMA_InitStructureRX.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructureRX.DMA_BufferSize = max_size;
    DMA_InitStructureRX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructureRX.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructureRX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructureRX.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructureRX.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructureRX.DMA_Priority = DMA_Priority_High;
    DMA_InitStructureRX.DMA_Channel = DMA_Channel_4;
    DMA_Init(DMA2_Stream7, &DMA_InitStructureRX);
    //
    DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    //
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //
    NVIC_EnableIRQ(DMA2_Stream7_IRQn);
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    DMA_Cmd(DMA2_Stream7, ENABLE); // RUN
#endif
}
//--------------------------------------------------

//--------------------------------------------------
void USART2_Init(uint32_t bt, uint8_t *arr_send, uint16_t max_size)
{
    /**USART2 GPIO Configuration
    PA2   ------> USART2_TX
    PA3   ------> USART2_RX
    */
    USART_InitTypeDef USART_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    DMA_InitTypeDef DMA_InitStructureRX;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    //
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    USART_DeInit(USART2);
    USART_InitStructure.USART_BaudRate = bt;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);
    USART_ClearFlag(USART2, USART_FLAG_CTS);
    USART_Cmd(USART2, ENABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //
    DMA_DeInit(DMA1_Stream6);
    DMA_Cmd(DMA1_Stream6, DISABLE);
    //
    DMA_StructInit(&DMA_InitStructureRX);
    DMA_InitStructureRX.DMA_PeripheralBaseAddr = (uint32_t) & (USART2->DR);
    DMA_InitStructureRX.DMA_Memory0BaseAddr = (uint32_t)(&arr_send[0]);
    DMA_InitStructureRX.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructureRX.DMA_BufferSize = max_size;
    DMA_InitStructureRX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructureRX.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructureRX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructureRX.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructureRX.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructureRX.DMA_Priority = DMA_Priority_High;
    DMA_InitStructureRX.DMA_Channel = DMA_Channel_4;
    DMA_Init(DMA1_Stream6, &DMA_InitStructureRX);
    //
    DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);
    USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
    //
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //
    NVIC_EnableIRQ(DMA1_Stream6_IRQn);
    USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
    DMA_Cmd(DMA1_Stream6, ENABLE); // RUN
}
//--------------------------------------------------
void DMA1_Stream6_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6))
    {
        DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
        DMA_Cmd(DMA1_Stream6, DISABLE);
        send_free.u2 = 0;
    }
}
//--------------------------------------------------
void USART2SendDMA(uint16_t len)
{
    /* Restart DMA Channel*/
    DMA_Cmd(DMA1_Stream6, DISABLE);
    DMA1_Stream6->NDTR = len;
    DMA_Cmd(DMA1_Stream6, ENABLE);
    send_free.u2 = 1;
}
//--------------------------------------------------
void USART6_Init(uint32_t bt)//, uint8_t *arr_send, uint16_t max_size)
{
    /**USART6 GPIO Configuration
    PA11   ------> USART6_TX
    PA12   ------> USART6_RX
    */
    USART_InitTypeDef USART_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    DMA_InitTypeDef DMA_InitStructureRX;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    //
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_USART6);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    USART_DeInit(USART6);
    USART_InitStructure.USART_BaudRate = bt;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART6, &USART_InitStructure);
    USART_ClearFlag(USART6, USART_FLAG_CTS);
    USART_Cmd(USART6, ENABLE);
#if 0
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    //    USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //
    DMA_DeInit(DMA2_Stream6);
    DMA_Cmd(DMA2_Stream6, DISABLE);
    //
    DMA_StructInit(&DMA_InitStructureRX);
    DMA_InitStructureRX.DMA_PeripheralBaseAddr = (uint32_t) & (USART6->DR);
    DMA_InitStructureRX.DMA_Memory0BaseAddr = (uint32_t)(&arr_send[0]);
    DMA_InitStructureRX.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructureRX.DMA_BufferSize = max_size;
    DMA_InitStructureRX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructureRX.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructureRX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructureRX.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructureRX.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructureRX.DMA_Priority = DMA_Priority_High;
    DMA_InitStructureRX.DMA_Channel = DMA_Channel_5;
    DMA_Init(DMA2_Stream6, &DMA_InitStructureRX);
    //
    DMA_ITConfig(DMA2_Stream6, DMA_IT_TC, ENABLE);
    USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);
    //
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_EnableIRQ(DMA2_Stream6_IRQn);
    USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);
    DMA_Cmd(DMA2_Stream6, ENABLE); // RUN
#endif
}
//--------------------------------------------------
void DMA2_Stream6_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA2_Stream6, DMA_IT_TCIF6))
    {
        DMA_ClearITPendingBit(DMA2_Stream6, DMA_IT_TCIF6);
        DMA_Cmd(DMA2_Stream6, DISABLE);
        send_free.u6 = 0;
    }
}
//--------------------------------------------------
void USART6SendDMA(uint16_t len)
{
    /* Restart DMA Channel*/
    DMA_Cmd(DMA2_Stream6, DISABLE);
    DMA2_Stream6->NDTR = len;
    DMA_Cmd(DMA2_Stream6, ENABLE);
    send_free.u6 = 1;
}
//--------------------------------------------------
#pragma inline
void delay_us(uint16_t delay)
{
    uint16_t summa;
    summa = delay * 16;
    do
    {
        __NOP();
    }
    while (--summa);
}
//--------------------------------------------------
void delay_ms(uint16_t delay)
{
    do
    {
        delay_us(1000);
    }
    while (--delay);
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


//TIM1

//--------------------------------------------------
void TIM1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    TIM_DeInit(TIM1);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 4000); //
    TIM_TimeBaseStructure.TIM_Period = (2 - 1);                //  (1/2K) * 2K = 1s
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;          //
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM1, ENABLE); //
}
//--------------------------------------------------

//--------------------------------------------------
void TIM2_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 200000); // -> 200KHz
    TIM_TimeBaseStructure.TIM_Period = 50 - 1; // 0.25 ms
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM2, ENABLE);
}
//--------------------------------------------------
/**********************************************
 *
 * TIM3 Timer
 *
 */
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        //   tst = 10;
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
//--------------------------------------------------
void TIM3_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_DeInit(TIM3);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 2000); // -> 2KHz
    TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // 2KHz -> 1/2K -> 1/2K * 1500 = 0.5s
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM3, ENABLE);
}
//--------------------------------------------------
void CS_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    // SPI-CS (PA0)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
}
//--------------------------------------------------
void RST_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    // SPI-RES (PA1)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}
//--------------------------------------------------
void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    // SCK:PA5, MISO:PA6, MOSI:PA7 or PB3, PB4, PB5
    //    // SCK:PA5, MISO:PA6, MOSI:PA7 or PB3, PB4, PB5
#ifndef PROG_SPI
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE); // reset SPI1
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);// stop reset SPI1
    SPI_InitTypeDef SPI_InitStructure;
    SPI_StructInit(&SPI_InitStructure); // set default settings
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;// SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // data sampled at first edge
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   // clock is low when idle
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // data is transmitted MSB first
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // transmit in master mode, NSS pin has to be always high
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // set the NSS management to internal and pull internal NSS high
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
#else
#define MOSI1(x) x ? GPIO_SetBits(GPIOB,GPIO_Pin_5) : GPIO_ResetBits(GPIOB,GPIO_Pin_5);
#define SCK1(x) x ? GPIO_SetBits(GPIOB,GPIO_Pin_3) : GPIO_ResetBits(GPIOB,GPIO_Pin_3);
#define MISO1() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)
    //    // SCK:PA5, MISO:PA6, MOSI:PA7 or PB3, PB4, PB5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 |  GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
}
//--------------------------------------------------
//void SPI2_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
//    // SCK:PA5, MISO:PA6, MOSI:PA7 or PB3, PB4, PB5
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI2);
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI2);
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI2);
//    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE); // reset SPI2
//    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);// stop reset SPI1
//    SPI_InitTypeDef SPI_InitStructure;
//    SPI_StructInit(&SPI_InitStructure); // set default settings
//    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;// SPI_BaudRatePrescaler_8;
//    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // data sampled at first edge
//    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   // clock is low when idle
//    SPI_InitStructure.SPI_CRCPolynomial = 7;
//    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
//    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
//    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // data is transmitted MSB first
//    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // transmit in master mode, NSS pin has to be always high
//    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // set the NSS management to internal and pull internal NSS high
//    SPI_Init(SPI2, &SPI_InitStructure);
//    SPI_Cmd(SPI2, ENABLE);
//}
//--------------------------------------------------
//void SPI1_transfer(uint8_t *arr, uint16_t size, uint8_t *arr_in)
//{
//    if (size == 0)
//    {
//        return;
//    }
//    for (int i = 0; i < size; i++)
//    {
//        arr_in[i] = SPI_Write_Then_Read(arr[i]);
//    }
//}
//--------------------------------------------------
//uint8_t SPI_Write_Then_Read(uint8_t data)
//{
//    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//    SPI_I2S_SendData(SPI1, data);
//    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//    return SPI_I2S_ReceiveData(SPI1);
//}
//
//--------------------------------------------------
#ifndef PROG_SPI
void SPI1_WriteByte(uint8_t TxData)
{
    while (SPI_I2S_GetFlagStatus(SPI1,  SPI_I2S_FLAG_TXE) == 0);
    SPI1->DR = TxData;
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == 0);
    SPI1->DR;
}
//--------------------------------------------------
uint8_t SPI1_ReadByte(void)
{
    while ((SPI1->SR & SPI_I2S_FLAG_TXE) == 0); //
    SPI1->DR = 0xFF;
    while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == 0); //
    return SPI1->DR;
}
////--------------------------------------------------
#else
uint8_t SPI1_ReadByte(void)
{
    unsigned char miso = 0;
    unsigned char data = 0xFF;
    unsigned char mask = 0x80;
    for (; mask; mask >>= 1)
    {
        if (data & mask)
        {
            MOSI1(1);
        }
        else
        {
            MOSI1(0);
        }
        //delay_us(1);
        SCK1(1);
        delay_us(1);
        if (MISO1())
        {
            miso |= mask;
        }
        SCK1(0);
        //delay_us(1);
    }
    return miso;
}
//--------------------------------------------------
void SPI1_WriteByte(uint8_t TxData)
{
    //    unsigned char miso = 0;
    unsigned char mask = 0x80;
    for (; mask; mask >>= 1)
    {
        if (TxData & mask)
        {
            MOSI1(1);
        }
        else
        {
            MOSI1(0);
        }
        //delay_us(1);
        SCK1(1);
        // delay_us(1);
        SCK1(0);
    }
}
//--------------------------------------------------
#endif
//#endif
//void SPI2_WriteByte(uint8_t TxData)
//{
//    while (SPI_I2S_GetFlagStatus(SPI2,  SPI_I2S_FLAG_TXE) == 0);
//    SPI2->DR = TxData;
//    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == 0);
//    SPI2->DR;
//}
////--------------------------------------------------
//uint8_t SPI2_ReadByte(void)
//{
//    while ((SPI2->SR & SPI_I2S_FLAG_TXE) == 0); //
//    SPI2->DR = 0xFF;
//    while ((SPI2->SR & SPI_I2S_FLAG_RXNE) == 0); //
//    return SPI2->DR;
//}
//--------------------------------------------------
#if 0
void NRF24L01_SPI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if (NRF24L01_SPIx == SPI1)
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
        // SCK:PA5, MISO:PA6, MOSI:PA7 or PB3, PB4, PB5
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE); // reset SPI1
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);// stop reset SPI1
    }
    else if (NRF24L01_SPIx == SPI2)
    {
        // B13, B14, B15
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    }
    else     // SPI3,4,5,6
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
    }
    SPI_InitTypeDef SPI_InitStructure;
    SPI_StructInit(&SPI_InitStructure); // set default settings
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // data sampled at first edge
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   // clock is low when idle
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // data is transmitted MSB first
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // transmit in master mode, NSS pin has to be always high
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // set the NSS management to internal and pull internal NSS high
    SPI_Init(NRF24L01_SPIx, &SPI_InitStructure);
    SPI_Cmd(NRF24L01_SPIx, ENABLE);
}

void NRF24L01_EXTILine_Config(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    GPIO_InitTypeDef   GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* Connect EXTI Line13 to PG13 pin */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource13);
    EXTI_InitTypeDef   EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line    = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    NVIC_InitTypeDef   NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
* Basic SPI operation: Write to SPIx and read
*/
static u8 SPI_Write_Then_Read(u8 data)
{
    while (SPI_I2S_GetFlagStatus(NRF24L01_SPIx, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(NRF24L01_SPIx, data);
    while (SPI_I2S_GetFlagStatus(NRF24L01_SPIx, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(NRF24L01_SPIx);
}
/**
* Read a multi-byte register
*  reg  - register to read
*  buf  - pointer to the buffer to write
*  len  - number of bytes to read
*/
u8 NRF24L01_Read_To_Buf(u8 reg, u8 *buf, u8 len)
{
    CSN(0);
    u8 status = SPI_Write_Then_Read(reg);
    while (len--)
    {
        *buf++ = SPI_Write_Then_Read(NRF24L01_CMD_NOP);
    }
    CSN(1);
    return status;
}

/**
* Write a multi-byte register
*  reg - register to write
*  buf - pointer to the buffer with data
*  len - number of bytes to write
*/
u8 NRF24L01_Write_From_Buf(u8 reg, u8 *buf, u8 len)
{
    CSN(0);
    u8 status = SPI_Write_Then_Read(reg);
    while (len--)
    {
        SPI_Write_Then_Read(*buf++);
    }
    CSN(1);
    return status;
}

#endif














