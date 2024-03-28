#include "vtx_gpio.h"

uint8_t getButtonState(void){
  uint8_t pinOutState = LL_GPIO_IsOutputPinSet(LED_FR2_GPIO_Port, LED_FR2_Pin);
  LL_GPIO_SetOutputPin(LED_FR2_GPIO_Port, LED_FR2_Pin);
  //LL_GPIO_ResetOutputPin(LED_FR2_GPIO_Port, LED_FR2_Pin);
  LL_GPIO_SetPinMode(LED_FR2_GPIO_Port, LED_FR2_Pin, LL_GPIO_MODE_INPUT);
  HAL_Delay(0);
  uint8_t pinInState = LL_GPIO_IsInputPinSet(LED_FR2_GPIO_Port, LED_FR2_Pin);
  LL_GPIO_SetPinMode(LED_FR2_GPIO_Port, LED_FR2_Pin, LL_GPIO_MODE_OUTPUT);
  if (!pinOutState)
    LL_GPIO_ResetOutputPin(LED_FR2_GPIO_Port, LED_FR2_Pin);
  return pinInState;
}
