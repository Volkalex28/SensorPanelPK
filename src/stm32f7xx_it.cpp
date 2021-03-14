/**
 * @file stm32f7xx_it.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include <stm32f7xx_hal.h>

#include "freertos.hpp"

#include "peripheral/pinit.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

  /******************************************************************************/
  /*           Cortex-M7 Processor Interruption and Exception Handlers          */
  /******************************************************************************/
  /**
   * @brief This function handles Non maskable interrupt.
   */
  void NMI_Handler(void) {}

  /**
   * @brief This function handles Hard fault interrupt.
   */
  void HardFault_Handler(void)
  {
    while (1) continue;
  }

  /**
   * @brief This function handles Memory management fault.
   */
  void MemManage_Handler(void)
  {
    while (1) continue;
  }

  /**
   * @brief This function handles Pre-fetch fault, memory access fault.
   */
  void BusFault_Handler(void)
  {
    while (1) continue;
  }

  /**
   * @brief This function handles Undefined instruction or illegal state.
   */
  void UsageFault_Handler(void)
  {
    while (1) continue;
  }

  /**
   * @brief This function handles Debug monitor.
   */
  void DebugMon_Handler(void) {}

  /**
   * @brief This function handles System tick timer.
   */
  void SysTick_Handler(void)
  {
    using namespace OS::FreeRTOS;

    HAL_IncTick();

#if (INCLUDE_xTaskGetSchedulerState == 1)
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
#endif /* INCLUDE_xTaskGetSchedulerState */
      xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1)
    }
#endif /* INCLUDE_xTaskGetSchedulerState */
  }

  /**
   * @brief This function handles DMA1 stream2 global interrupt.
   */
  void DMA1_Stream2_IRQHandler(void)
  {
    HAL_DMA_IRQHandler(&Peripheral::VA_UART::hdma_uart4_rx);
  }

  /**
   * @brief This function handles DMA1 stream4 global interrupt.
   */
  void DMA1_Stream4_IRQHandler(void)
  {
    HAL_DMA_IRQHandler(&Peripheral::VA_UART::hdma_uart4_tx);
  }

  /**
   * @brief This function handles USART1 global interrupt.
   */
  void USART1_IRQHandler(void)
  {
    HAL_UART_IRQHandler(&Peripheral::VA_UART::huart1);

    // VA_USART_IRQHandler(&huart1);
  }

  /**
   * @brief This function handles UART4 global interrupt.
   */
  void UART4_IRQHandler(void)
  {
    HAL_UART_IRQHandler(&Peripheral::VA_UART::huart4);

    // VA_USART_IRQHandler(&Peripheral::VA_UART::huart4);
  }

  /**
   * @brief This function handles TIM7 global interrupt.
   */
  void TIM7_IRQHandler(void) { HAL_TIM_IRQHandler(&Peripheral::VA_TIM::htim7); }

  /**
   * @brief This function handles DMA2 stream2 global interrupt.
   */
  void DMA2_Stream2_IRQHandler(void)
  {
    HAL_DMA_IRQHandler(&Peripheral::VA_UART::hdma_usart1_rx);
  }

  /**
   * @brief This function handles DMA2 stream7 global interrupt.
   */
  void DMA2_Stream7_IRQHandler(void)
  {
    HAL_DMA_IRQHandler(&Peripheral::VA_UART::hdma_usart1_tx);
  }

  /**
   * @brief This function handles EXTI line[15:10] interrupts.
   */
  void EXTI15_10_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10); }

#ifdef __cplusplus
}
#endif
