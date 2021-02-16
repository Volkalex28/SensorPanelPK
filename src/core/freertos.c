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
const osThreadAttr_t showTask_attributes = {
  .name = "showTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 2048 * 4
};
/* Definitions for loopTask */
osThreadId_t loopTaskHandle;
const osThreadAttr_t loopTask_attributes = {
  .name = "loopTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 1024 * 4
};
/* Definitions for exchangeTask */
osThreadId_t exchangeTaskHandle;
const osThreadAttr_t exchangeTask_attributes = {
  .name = "exchangeTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 512 * 4
};
/* Definitions for eepromTask */
osThreadId_t eepromTaskHandle;
const osThreadAttr_t eepromTask_attributes = {
  .name = "eepromTask",
  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 512 * 4
};
/* Definitions for WriteBuf */
osMessageQueueId_t WriteBufHandle;
const osMessageQueueAttr_t WriteBuf_attributes = {
  .name = "WriteBuf"
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
