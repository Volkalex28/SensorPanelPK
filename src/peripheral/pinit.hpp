/**
 * @file clock.hpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#pragma once

namespace Peripheral
{

#define Error_Handler()                                                             \
  while (true) continue

namespace VA_Clock
{
void Init(void);

} // namespace VA_Clock

namespace VA_GPIO
{
void Init(void);
} // namespace VA_GPIO

namespace VA_DMA
{

void Init(void);

} // namespace VA_DMA

namespace VA_FMC
{
extern SRAM_HandleTypeDef hsram1;

void Init(void);

} // namespace VA_FMC

namespace VA_SPI
{
extern SPI_HandleTypeDef hspi1;

void Init_SPI1(void);

} // namespace VA_SPI

namespace VA_UART
{
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;

void Init_UART1(void);
void Init_UART4(void);

} // namespace VA_UART

namespace VA_TIM
{
extern TIM_HandleTypeDef htim7;

void Init_TIM7(void);

} // namespace VA_TIM

namespace VA_RTC
{
extern RTC_HandleTypeDef hrtc;

void Init(void);

} // namespace VA_RTC

namespace VA_IWDG
{
extern IWDG_HandleTypeDef hiwdg;

void Init(void);

} // namespace VA_IWDG

} // namespace Peripheral
