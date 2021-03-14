/**
 * @file main.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include <math.h>

#include <stm32f7xx_hal.h>

#include "freertos.hpp"

#include "peripheral/pinit.hpp"
#include "peripheral/pins.hpp"

#include "drivers/VA_RA8875/VA_RA8875.hpp"

#include "VA_GUI/Elements/VAGraphics.hpp"

using namespace VA;

Graphics<Triangle> temp({ { 80, 400 }, { 99, 200 }, { 61, 200 }, Colors::MAGENTA }, false, true);
Graphics<RoundRect> rr({ { 100, 0 }, 200, 2, 20, VA::Colors::BLUE });

RA8875 disp(RA8875::displaySizes::_800x480, HAL_Delay);

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

  disp.init();
  disp.setLayer(VA::LCD::layers::LAYER1);
  disp.fillScreen(VA::Colors::BLACK);
  disp.setLayer(VA::LCD::layers::LAYER2);
  disp.fillScreen(VA::Colors::BLACK);
  HAL_Delay(50);
  disp.setBrightness(50);

  OS::FreeRTOS::Init();

  while (true)
    continue;
}

float count = 0;
bool state = false;

void taskShow(void * pvParametres)
{
  using namespace OS::FreeRTOS;

  portTickType xLastWakeTime = xTaskGetTickCount();

  while (true)
  {
    static Graphics<Ellipse> elp({ { 100, 100 }, 20, 20, Colors::WHITE });
    const Point touchPoint = disp.getTouchPoint();

    if (touchPoint != Point())
    {

      if (!elp.isMe(touchPoint))
      {
        elp.setCenter(touchPoint);
      }
      else
      {
        elp.show(true); // place for call the touthed function
      }

      state = !rr.isMe(elp.getCenter());
    }
    else
    {
      elp.show(false);
      state = true;
    }

    rr.setHeight(count);

    // ==================================== show ==============================
    disp.setLayer(disp.getLayer() + 1);
    disp.fillScreen(VA::Colors::BACKGROUND);
    if (temp.isMe(Point(temp.getCenterW(), rr.getNullPoint().getY() + rr.getHeight())))
    {
      temp.draw(disp);
    }

    rr.draw(disp);
    elp.draw(disp);

    disp.showLayer(disp.getLayer());

    HAL_IWDG_Refresh(&Peripheral::VA_IWDG::hiwdg);
    taskYIELD();

    vTaskDelayUntil(&xLastWakeTime, (40 / portTICK_RATE_MS));
  }
}

void taskBlink(void * pvParametres)
{
  while (true)
  {
    HAL_GPIO_TogglePin(OUT1_GPIO_Port, OUT1_Pin);

    taskYIELD();
    OS::FreeRTOS::vTaskDelay(500);
  }
}

void timerCallbackScroll(OS::FreeRTOS::xTimerHandle xTimer)
{
  if (state)
  {
    count = fmodf(count + 4.8f / 1, 480);
  }
  taskYIELD();
}