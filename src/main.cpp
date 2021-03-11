/**
 * @file main.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include <stm32f7xx_hal.h>

#include "peripheral/pinit.hpp"
#include "peripheral/pins.hpp"

#include "drivers/RA8875/RA8875.hpp"

static RA8875 disp(RA8875::displaySizes::_800x480, HAL_Delay);

int main(void)
{
  SCB_EnableICache();

  HAL_Init();

  Peripheral::VA_Clock::Init();
  Peripheral::VA_GPIO::Init();
  Peripheral::VA_DMA::Init();
  Peripheral::VA_FMC::Init();
  Peripheral::VA_SPI::Init_SPI1();
  Peripheral::VA_UART::Init_UART1();
  Peripheral::VA_UART::Init_UART4();
  Peripheral::VA_TIM::Init_TIM7();
  Peripheral::VA_RTC::Init();
  Peripheral::VA_IWDG::Init();

  HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, (GPIO_PinState)disp.init());
  ;
  disp.setBrightness(50);

  // disp.fillScreen(disp.Colour565To332(VA::Colors::GREEN));

  // disp.draw(
  //   VA::RoundRect({ 100, 50 }, 200, 200, 20,
  //   disp.Colour565To332(VA::Colors::BLUE)), true);
  // disp.draw(VA::Triangle({ { 500, 20 }, { 300, 300 }, { 700, 250 } },
  //             disp.Colour565To332(VA::Colors::RED)),
  //   true);

  // disp.draw(VA::Ellipse(VA::Rectangle({650, 0}, 150, 240)), true);
  // disp.draw(VA::Rectangle({650, 20}, 70, 70,
  // disp.Colour565To332(VA::Colors::WHITE)), true);

  VA::RoundRect rr({ 100, 0 }, 200, 0, 20, disp.Colour565To332(VA::Colors::BLUE));

  uint32_t count = 0, cl = 0;

  while (true)
  {
    HAL_GPIO_TogglePin(OUT1_GPIO_Port, OUT1_Pin);
    HAL_Delay(3);
    HAL_IWDG_Refresh(&Peripheral::VA_IWDG::hiwdg);

    disp.setLayer((VA::LCD::layers)(cl % 2));

    disp.fillScreen(disp.Colour565To332(VA::Colors::GREEN));
    disp.draw(rr, true);

    disp.showLayer((VA::LCD::layers)(cl % 2));

    if (disp.touched()) {
      disp.touchRead();
      count++;
    }
    rr.setHeight(count % 480);

    cl++;
  }
}
