#include "helpers.h"

uint32_t millis(void){
  return HAL_GetTick();
}

void delay(uint32_t const ms) {
  HAL_Delay(ms);
}

/*
uint8_t serial_available(void) {
  return (uint32_t)(sizeof(rx_buffer) + rx_head - rx_tail) % sizeof(rx_buffer);
}

uint8_t serial_read(void){
  uint8_t data = rx_buffer[rx_tail++];
  rx_tail %= sizeof(rx_buffer);
  return data;
}

void serial_flush(void){
  rx_tail = rx_head;
}
*/

uint8_t saPowerLevelsLut[SA_NUM_POWER_LEVELS] = { 1, RACE_MODE, 14, 20, 26 };
uint8_t saPowerLevelsLabel[SA_NUM_POWER_LEVELS * POWER_LEVEL_LABEL_LENGTH] = {
        '0', ' ', ' ',
        'R', 'C', 'E',
        '2', '5', ' ',
        '1', '0', '0',
        '4', '0', '0'};

// ToDo
void Serial_write_len(uint8_t *data, uint32_t size) {
}
