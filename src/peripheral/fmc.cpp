/**
 * @file fmc.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include <stm32f7xx_hal.h>

#include "pinit.hpp"

namespace Peripheral::VA_FMC
{

SRAM_HandleTypeDef hsram1;

static uint32_t FMC_Initialized   = 0;
static uint32_t FMC_DeInitialized = 0;

/* FMC initialization function */
void Init(void)
{
  FMC_NORSRAM_TimingTypeDef Timing = { 0 };

  /** Perform the SRAM1 memory initialization sequence
   */
  hsram1.Instance = FMC_NORSRAM_DEVICE;
  hsram1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank             = FMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType         = FMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode    = FMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal         = FMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst         = FMC_WRITE_BURST_DISABLE;
  hsram1.Init.ContinuousClock    = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hsram1.Init.WriteFifo          = FMC_WRITE_FIFO_DISABLE;
  hsram1.Init.PageSize           = FMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime      = 0;
  Timing.AddressHoldTime       = 1;
  Timing.DataSetupTime         = 4;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision           = 2;
  Timing.DataLatency           = 2;
  Timing.AccessMode            = FMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK) { Error_Handler(); }
}

static void MspInit(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  if (FMC_Initialized) { return; }
  FMC_Initialized = 1;

  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_ENABLE();

  /** FMC GPIO Configuration
  PE7   ------> FMC_D4
  PE8   ------> FMC_D5
  PE9   ------> FMC_D6
  PE10   ------> FMC_D7
  PE11   ------> FMC_D8
  PE12   ------> FMC_D9
  PE13   ------> FMC_D10
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PD10   ------> FMC_D15
  PD11   ------> FMC_A16
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PD0   ------> FMC_D2
  PD1   ------> FMC_D3
  PD4   ------> FMC_NOE
  PD5   ------> FMC_NWE
  PD7   ------> FMC_NE1
  */
  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                        GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
                        GPIO_PIN_15;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                        GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1 |
                        GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

static void MspDeInit(void)
{
  if (FMC_DeInitialized) { return; }
  FMC_DeInitialized = 1;
  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_DISABLE();

  /** FMC GPIO Configuration
  PE7   ------> FMC_D4
  PE8   ------> FMC_D5
  PE9   ------> FMC_D6
  PE10   ------> FMC_D7
  PE11   ------> FMC_D8
  PE12   ------> FMC_D9
  PE13   ------> FMC_D10
  PE14   ------> FMC_D11
  PE15   ------> FMC_D12
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PD10   ------> FMC_D15
  PD11   ------> FMC_A16
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PD0   ------> FMC_D2
  PD1   ------> FMC_D3
  PD4   ------> FMC_NOE
  PD5   ------> FMC_NWE
  PD7   ------> FMC_NE1
  */

  HAL_GPIO_DeInit(GPIOE,
                  GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                    GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

  HAL_GPIO_DeInit(GPIOD,
                  GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_14 |
                    GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
                    GPIO_PIN_7);
}

} // namespace Peripheral::VA_FMC

void HAL_SRAM_MspInit(SRAM_HandleTypeDef * sramHandle)
{
  Peripheral::VA_FMC::MspInit();
}

void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef * sramHandle)
{
  Peripheral::VA_FMC::MspDeInit();
}