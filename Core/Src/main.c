/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "helpers.h"
#include "openVTxEEPROM.h"
#include "common.h"
#include "rtc6705.h"
#include "smartAudio.h"
#include "tramp.h"
#include "mspVtx.h"
#include "button.h"
#include "targets.h"
#include "errorCodes.h"
#include "vtx_gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void start_serial(uint8_t type)
{
  uint32_t baud, stopbits;
  switch (type) {
    case TRAMP:
      baud = TRAMP_BAUD;
      stopbits = LL_USART_STOPBITS_1;
      trampReset();
      break;
    case SMARTAUDIO:
      baud = SMARTAUDIO_BAUD;
      stopbits = LL_USART_STOPBITS_2;
      smartaudioReset();
      break;
    case MSP:
      baud = MSP_BAUD;
      stopbits = LL_USART_STOPBITS_1;
      mspReset();
      break;
    default:
      baud = 115200;
      stopbits = LL_USART_STOPBITS_1;
      break;
  }
  //serial_begin(baud, UART_TX, UART_RX, stopbits);
  customSerialSet(baud, stopbits);
  myEEPROM.vtxMode = type;
}

void checkRTC6705isAlive()
{
  if (!rtc6705CheckFrequency())
  {
    rtc6705WriteFrequency(myEEPROM.currFreq); // Tries and set the correct freq to the RTC6705

    if (currentErrorMode == NO_ERROR)
    {
      currentErrorMode = RTC6705_NOT_DETECTED;
    }
  } else {
    if (currentErrorMode == RTC6705_NOT_DETECTED)
      {
        currentErrorMode = NO_ERROR;
      }
  }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  // target_rfPowerAmpPinSetup();
  // rtc6705spiPinSetup();

  readEEPROM();

  pitMode = myEEPROM.pitmodeInRange;

  rtc6705ResetState(); // During testing registers got messed up. So now it gets reset on boot!
  rtc6705WriteFrequency(myEEPROM.currFreq);

  start_serial(myEEPROM.vtxMode);

  status_leds_init();
  //button_init(); -- replaced by MX_GPIO_Init()

  resetModeIndication();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    uint32_t now = millis();

    // ToDo -- protocol detect

    /* Process uart data */
    switch (myEEPROM.vtxMode) {
      case TRAMP:
        trampProcessSerial();
        break;
      case SMARTAUDIO:
        smartaudioProcessSerial();
        break;
      case MSP:
        mspUpdate(now);
        break;
      default:
        break;
    }

    checkButton();

    rtc6705PowerUpAfterPLLSettleTime();

    checkPowerOutput();

    checkRTC6705isAlive();

    errorCheck();

    writeEEPROM();

    //target_loop(); todo

    if (LED_INDICATION_OF_VTX_MODE && !(vtxModeLocked && myEEPROM.vtxMode == TRAMP)) // TRAMP doesnt use VTx Tables so LED indication of band/channel doesnt really work.
      modeIndicationLoop();
    else
      status_led2(vtxModeLocked);

    //LL_GPIO_TogglePin(LED_PWR0_GPIO_Port, LED_PWR0_Pin);
    //HAL_Delay(100);
    //LL_GPIO_TogglePin(LED_CH0_GPIO_Port, LED_CH0_Pin);
    //HAL_Delay(100);
    //LL_GPIO_TogglePin(LED_FR2_GPIO_Port, LED_FR2_Pin);
    if (getButtonState())
      LL_GPIO_SetOutputPin(LED_PWR1_GPIO_Port, LED_PWR1_Pin);
    else
      LL_GPIO_ResetOutputPin(LED_PWR1_GPIO_Port, LED_PWR1_Pin);
    //HAL_Delay(500);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
