#pragma once

#include "usart.h"

static volatile uint8_t rx_buffer[64];
static volatile uint8_t rx_head, rx_tail;

uint8_t serial_available(void);
uint8_t serial_read(void);
void serial_flush(void);

void customSerialSet(uint32_t baud, uint8_t stopbits);

void fillRxBuffer(void);
