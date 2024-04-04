#include "targets.h"

void target_set_power_dB(float power) {
  uint32_t pwr = power + 0xF;
  TIM2->CCR1 = pwr & 0x3FF;
}
void checkPowerOutput(void){
}

void mcu_reboot(void) {
  HAL_NVIC_SystemReset();
}
