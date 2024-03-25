/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

#include "stm32f0xx_ll_usart.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_PWR1_Pin LL_GPIO_PIN_1
#define LED_PWR1_GPIO_Port GPIOA
#define LED_PWR2_Pin LL_GPIO_PIN_2
#define LED_PWR2_GPIO_Port GPIOA
#define LED_CH0_Pin LL_GPIO_PIN_3
#define LED_CH0_GPIO_Port GPIOA
#define LED_CH1_Pin LL_GPIO_PIN_4
#define LED_CH1_GPIO_Port GPIOA
#define LED_CH2_Pin LL_GPIO_PIN_5
#define LED_CH2_GPIO_Port GPIOA
#define LED_CH3_Pin LL_GPIO_PIN_6
#define LED_CH3_GPIO_Port GPIOA
#define LED_CH4_Pin LL_GPIO_PIN_7
#define LED_CH4_GPIO_Port GPIOA
#define LED_FR2_Pin LL_GPIO_PIN_0
#define LED_FR2_GPIO_Port GPIOB
#define LED_FR0_Pin LL_GPIO_PIN_1
#define LED_FR0_GPIO_Port GPIOB
#define LED_FR1_Pin LL_GPIO_PIN_2
#define LED_FR1_GPIO_Port GPIOB
#define LED_FR3_Pin LL_GPIO_PIN_9
#define LED_FR3_GPIO_Port GPIOA
#define LED_FR4_Pin LL_GPIO_PIN_10
#define LED_FR4_GPIO_Port GPIOA
#define LED_FR5_Pin LL_GPIO_PIN_11
#define LED_FR5_GPIO_Port GPIOA
#define LED_FR6_Pin LL_GPIO_PIN_12
#define LED_FR6_GPIO_Port GPIOA
#define LED_FR7_Pin LL_GPIO_PIN_15
#define LED_FR7_GPIO_Port GPIOA
#define SC_SPI1_Pin LL_GPIO_PIN_4
#define SC_SPI1_GPIO_Port GPIOB
#define LED_PWR0_Pin LL_GPIO_PIN_8
#define LED_PWR0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
