/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
//#include "adc.h"
#include "dma.h"
//#include "eth.h"
#include "rtc.h"
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
//#include "usb_otg.h"
#include "gpio.h"
#include "fmc.h"

#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "math.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct {
	uint8_t Adress;
	uint8_t Func;
	uint16_t AdrReg;
	uint16_t Value;
} WriteBuf_t;

typedef struct {
	uint16_t Adress;
	uint16_t Value;
} EEPBuf_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern osMessageQueueId_t WriteBufHandle;
extern osMessageQueueId_t EEPBufHandle;

extern osTimerId_t sleepTimerHandle;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void Setup(void);
void ShowDefault(void *argument);
void LoopTask(void *argument);
void ExchangeTask(void *argument);
void EEPROMTask(void *argument);
void SleepTFT(void *argument);

void SPI_SetPol_LOW(SPI_HandleTypeDef* hspi);
void SPI_SetPol_HIGH(SPI_HandleTypeDef* hspi);

void VA_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void VA_USART_IRQHandler(UART_HandleTypeDef *huart);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Q0_Pin GPIO_PIN_2
#define Q0_GPIO_Port GPIOE
#define Q1_Pin GPIO_PIN_3
#define Q1_GPIO_Port GPIOE
#define Q2_Pin GPIO_PIN_4
#define Q2_GPIO_Port GPIOE
#define Q3_Pin GPIO_PIN_5
#define Q3_GPIO_Port GPIOE
#define Q4_Pin GPIO_PIN_6
#define Q4_GPIO_Port GPIOE
#define Q5_Pin GPIO_PIN_13
#define Q5_GPIO_Port GPIOC
#define Q6_Pin GPIO_PIN_0
#define Q6_GPIO_Port GPIOF
#define Q7_Pin GPIO_PIN_1
#define Q7_GPIO_Port GPIOF
#define OUT1_Pin GPIO_PIN_0
#define OUT1_GPIO_Port GPIOA
#define OUT2_Pin GPIO_PIN_3
#define OUT2_GPIO_Port GPIOA
#define DIR1_Pin GPIO_PIN_8
#define DIR1_GPIO_Port GPIOA
#define DIR4_Pin GPIO_PIN_15
#define DIR4_GPIO_Port GPIOA
#define I7_Pin GPIO_PIN_11
#define I7_GPIO_Port GPIOG
#define I6_Pin GPIO_PIN_12
#define I6_GPIO_Port GPIOG
#define I5_Pin GPIO_PIN_13
#define I5_GPIO_Port GPIOG
#define I4_Pin GPIO_PIN_14
#define I4_GPIO_Port GPIOG
#define NSS1_Pin GPIO_PIN_15
#define NSS1_GPIO_Port GPIOG
#define L1_Pin GPIO_PIN_6
#define L1_GPIO_Port GPIOB
#define L2_Pin GPIO_PIN_7
#define L2_GPIO_Port GPIOB
#define I3_Pin GPIO_PIN_8
#define I3_GPIO_Port GPIOB
#define I2_Pin GPIO_PIN_9
#define I2_GPIO_Port GPIOB
#define I1_Pin GPIO_PIN_0
#define I1_GPIO_Port GPIOE
#define I0_Pin GPIO_PIN_1
#define I0_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
