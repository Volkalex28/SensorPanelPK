/**
 * @file main.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include <stm32f7xx_hal.h>

#include "peripheral/pinit.hpp"
#include "peripheral/pins.hpp"

int main(void)
{
  SCB_EnableICache();

  HAL_Init();

  Peripheral::VA_Clock::Init();
  Peripheral::VA_GPIO::Init();
  // Peripheral::VA_DMA::Init();
  // Peripheral::VA_FMC::Init();
  // Peripheral::VA_SPI::Init_SPI1();
  // Peripheral::VA_UART::Init_UART1();
  // Peripheral::VA_UART::Init_UART4();
  // Peripheral::VA_TIM::Init_TIM7();
  // Peripheral::VA_RTC::Init();
  // Peripheral::VA_IWDG::Init();

  
  while (true)
  {
    HAL_GPIO_TogglePin(OUT1_GPIO_Port, OUT1_Pin);
    uint32_t t = 16000000;
    while(t--) {};
    HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, GPIO_PIN_SET);
  }
}
