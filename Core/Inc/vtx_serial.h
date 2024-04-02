#pragma once

#include "usart.h"

static volatile uint8_t rx_buffer[64];
static volatile uint8_t rx_head, rx_tail;

uint8_t serial_available(void);
uint8_t serial_read(void);
void Serial_write_len(uint8_t *data, uint32_t size);
void serial_flush(void);

void customSerialSet(uint32_t baud, uint32_t stopbits);

void fillRxBuffer(void);
