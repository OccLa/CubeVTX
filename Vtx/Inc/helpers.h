#pragma once

#include <stdint.h>
#include <stddef.h>
#include "stm32f0xx_hal.h"
#include "main.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

uint32_t millis(void);
void delay(uint32_t const ms);

/*
uint8_t serial_available(void);
uint8_t serial_read(void);
void serial_flush(void);
*/

//void Serial_write_len(uint8_t *data, uint32_t size);

// TODO
typedef struct
{
    uint32_t regs;
    uint32_t bit;
} gpio_in_t;
typedef struct
{
    uint32_t regs;
    uint32_t bit;
} gpio_out_t;

gpio_in_t gpio_in_setup(uint32_t pin, int32_t pull_up);
gpio_out_t gpio_out_setup(uint32_t pin, uint32_t val);

#define BUTTON 0

uint8_t gpio_in_read(gpio_in_t g);
void gpio_out_write(gpio_out_t g, uint32_t val);

#define MAX_POWER                   400 // mW
#define SA_NUM_POWER_LEVELS         5 // Max 5 for INAV.
#define POWER_LEVEL_LABEL_LENGTH    3
extern uint8_t saPowerLevelsLut[SA_NUM_POWER_LEVELS];
extern uint8_t saPowerLevelsLabel[SA_NUM_POWER_LEVELS * POWER_LEVEL_LABEL_LENGTH];

#include "modeIndicator.h"

void delayMicroseconds(uint32_t us);

void serial_begin(uint32_t baud, uint32_t tx_pin, uint32_t rx_pin, uint8_t stopbits);

#define UART_RX 0
#define UART_TX 0

#define SPI_SS 0
#define SPI_CLOCK 0
#define SPI_MOSI 0

#define LED_INDICATION_OF_VTX_MODE 1
