#ifndef __UART_H
#define __UART_H

#include "debug.h"

void PIOC_INIT(void);

void PIOC_UART_INIT(uint32_t baudrate,uint8_t parity,uint8_t stopbits,uint8_t lenth);

void PIOC_UART_SEND(uint8_t *p_source_addr,uint16_t total_bytes);

#endif