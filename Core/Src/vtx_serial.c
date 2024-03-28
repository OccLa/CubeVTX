#include "vtx_serial.h"

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

void customSerialSet(uint32_t baud, uint8_t stopbits) {
  LL_USART_InitTypeDef USART_InitStruct = {0};
  USART_InitStruct.BaudRate = baud;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = stopbits;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_DisableIT_CTS(USART1);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);
}

void fillRxBuffer(void) {
  if(LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1)) {
    uint8_t next = rx_head;
    uint8_t data = LL_USART_ReceiveData8(USART1);
    if (((next + 1) % sizeof(rx_buffer)) != rx_tail) {
      rx_buffer[next] = data;
      rx_head = (next + 1) % sizeof(rx_buffer);
    }
  }
}
