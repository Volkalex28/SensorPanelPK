/**
 * @file tim.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include <stm32f7xx_hal.h>

#include "pinit.hpp"

namespace Peripheral::VA_TIM
{

TIM_HandleTypeDef htim7;

/* TIM7 init function */
void Init_TIM7(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = { 0 };

  htim7.Instance               = TIM7;
  htim7.Init.Prescaler         = 10799;
  htim7.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim7.Init.Period            = 49999;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK) { Error_Handler(); }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

} // namespace Peripheral::TIM

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef * tim_baseHandle)
{

  if (tim_baseHandle->Instance == TIM7)
  {
    /* TIM7 clock enable */
    __HAL_RCC_TIM7_CLK_ENABLE();

    /* TIM7 interrupt Init */
    HAL_NVIC_SetPriority(TIM7_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef * tim_baseHandle)
{

  if (tim_baseHandle->Instance == TIM7)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM7_CLK_DISABLE();

    /* TIM7 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM7_IRQn);
  }
}
