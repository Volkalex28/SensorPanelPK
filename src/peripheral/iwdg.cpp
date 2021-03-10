/**
 * @file iwdg.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include <stm32f7xx_hal.h>

#include "pinit.hpp"

namespace Peripheral::VA_IWDG
{

IWDG_HandleTypeDef hiwdg;

/* IWDG init function */
void Init(void)
{
  hiwdg.Instance       = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
  hiwdg.Init.Window    = 4095;
  hiwdg.Init.Reload    = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK) { Error_Handler(); }
}

} // namespace Peripheral::VA_IWDG
