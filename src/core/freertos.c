/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticTimer_t osStaticTimerDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for showTask */
osThreadId_t showTaskHandle;
uint32_t showTaskBuffer[ 2048 ];
osStaticThreadDef_t showTaskControlBlock;
const osThreadAttr_t showTask_attributes = {
  .name = "showTask",
  .cb_mem = &showTaskControlBlock,
  .cb_size = sizeof(showTaskControlBlock),
  .stack_mem = &showTaskBuffer[0],
  .stack_size = sizeof(showTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for loopTask */
osThreadId_t loopTaskHandle;
uint32_t loopTaskBuffer[ 1024 ];
osStaticThreadDef_t loopTaskControlBlock;
const osThreadAttr_t loopTask_attributes = {
  .name = "loopTask",
  .cb_mem = &loopTaskControlBlock,
  .cb_size = sizeof(loopTaskControlBlock),
  .stack_mem = &loopTaskBuffer[0],
  .stack_size = sizeof(loopTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for exchangeTask */
osThreadId_t exchangeTaskHandle;
uint32_t exchangeTaskBuffer[ 256 ];
osStaticThreadDef_t exchangeTaskControlBlock;
const osThreadAttr_t exchangeTask_attributes = {
  .name = "exchangeTask",
  .cb_mem = &exchangeTaskControlBlock,
  .cb_size = sizeof(exchangeTaskControlBlock),
  .stack_mem = &exchangeTaskBuffer[0],
  .stack_size = sizeof(exchangeTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for eepromTask */
osThreadId_t eepromTaskHandle;
uint32_t eepromTaskBuffer[ 256 ];
osStaticThreadDef_t eepromTaskControlBlock;
const osThreadAttr_t eepromTask_attributes = {
  .name = "eepromTask",
  .cb_mem = &eepromTaskControlBlock,
  .cb_size = sizeof(eepromTaskControlBlock),
  .stack_mem = &eepromTaskBuffer[0],
  .stack_size = sizeof(eepromTaskBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for WriteBuf */
osMessageQueueId_t WriteBufHandle;
uint8_t WriteBufBuffer[ 30 * sizeof( WriteBuf_t ) ];
osStaticMessageQDef_t WriteBufControlBlock;
const osMessageQueueAttr_t WriteBuf_attributes = {
  .name = "WriteBuf",
  .cb_mem = &WriteBufControlBlock,
  .cb_size = sizeof(WriteBufControlBlock),
  .mq_mem = &WriteBufBuffer,
  .mq_size = sizeof(WriteBufBuffer)
};
/* Definitions for EEPBuf */
osMessageQueueId_t EEPBufHandle;
uint8_t EEPBufBuffer[ 5000 * sizeof( EEPBuf_t ) ];
osStaticMessageQDef_t EEPBufControlBlock;
const osMessageQueueAttr_t EEPBuf_attributes = {
  .name = "EEPBuf",
  .cb_mem = &EEPBufControlBlock,
  .cb_size = sizeof(EEPBufControlBlock),
  .mq_mem = &EEPBufBuffer,
  .mq_size = sizeof(EEPBufBuffer)
};
/* Definitions for sleepTimer */
osTimerId_t sleepTimerHandle;
osStaticTimerDef_t sleepTimerControlBlock;
const osTimerAttr_t sleepTimer_attributes = {
  .name = "sleepTimer",
  .cb_mem = &sleepTimerControlBlock,
  .cb_size = sizeof(sleepTimerControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void ShowDefault(void *argument);
void LoopTask(void *argument);
void ExchangeTask(void *argument);
void EEPROMTask(void *argument);
void SleepTFT(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of sleepTimer */
  sleepTimerHandle = osTimerNew(SleepTFT, osTimerOnce, NULL, &sleepTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of WriteBuf */
  WriteBufHandle = osMessageQueueNew (30, sizeof(WriteBuf_t), &WriteBuf_attributes);

  /* creation of EEPBuf */
  EEPBufHandle = osMessageQueueNew (5000, sizeof(EEPBuf_t), &EEPBuf_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of showTask */
  showTaskHandle = osThreadNew(ShowDefault, NULL, &showTask_attributes);

  /* creation of loopTask */
  loopTaskHandle = osThreadNew(LoopTask, NULL, &loopTask_attributes);

  /* creation of exchangeTask */
  exchangeTaskHandle = osThreadNew(ExchangeTask, NULL, &exchangeTask_attributes);

  /* creation of eepromTask */
  eepromTaskHandle = osThreadNew(EEPROMTask, NULL, &eepromTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_ShowDefault */
/**
  * @brief  Function implementing the showTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_ShowDefault */
__weak void ShowDefault(void *argument)
{
  /* USER CODE BEGIN ShowDefault */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }
  /* USER CODE END ShowDefault */
}

/* USER CODE BEGIN Header_LoopTask */
/**
* @brief Function implementing the loopTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LoopTask */
__weak void LoopTask(void *argument)
{
  /* USER CODE BEGIN LoopTask */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }
  /* USER CODE END LoopTask */
}

/* USER CODE BEGIN Header_ExchangeTask */
/**
* @brief Function implementing the exchangeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ExchangeTask */
__weak void ExchangeTask(void *argument)
{
  /* USER CODE BEGIN ExchangeTask */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }
  /* USER CODE END ExchangeTask */
}

/* USER CODE BEGIN Header_EEPROMTask */
/**
* @brief Function implementing the eepromTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_EEPROMTask */
__weak void EEPROMTask(void *argument)
{
  /* USER CODE BEGIN EEPROMTask */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }
  /* USER CODE END EEPROMTask */
}

/* SleepTFT function */
__weak void SleepTFT(void *argument)
{
  /* USER CODE BEGIN SleepTFT */

  /* USER CODE END SleepTFT */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
