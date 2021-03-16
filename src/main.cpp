/**
 * @file main.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include <math.h>
#include <stm32f7xx_hal.h>

#include "VA_GUI/Elements/VAIndicator.hpp"
#include "VA_GUI/Elements/VALabel.hpp"
#include "drivers/VA_RA8875/VA_RA8875.hpp"
#include "freertos.hpp"
#include "peripheral/pinit.hpp"
#include "peripheral/pins.hpp"

using namespace VA;

Elements::Graphics<Triangle> temp({ { 80, 400 }, { 99, 200 }, { 61, 200 }, Colors::MAGENTA }, false);
Elements::Graphics<RoundRect> rr({ { 100, 0 }, 200, 2, 20, VA::Colors::BLUE });

Elements::IndicatorCircular ind(Point(500, 240), 100, 100);
Elements::IndicatorCircular ind2(Point(620, 240), 100, 100,
  Elements::IndicatorCircular::Property{ .colorTrue = Colors::WHITE, .colorFalse = Colors::BLACK });

Elements::BaseElement * arrInd[] = { &ind, &ind2 };

Elements::Label lb({ 400, 0 }, 300, 200,
  Elements::Label::Property{
    .fontForm = Font::FontForms::Bold,
    .scale = Elements::Label::Scale::S3,
    .alignX = Elements::Label::AlignX::Center,
    .alignY = Elements::Label::AlignY::Center,
  });

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

  // portTickType xLastWakeTime = xTaskGetTickCount();

  while (true)
  {
    static Elements::Graphics<Ellipse> elp({ { 100, 100 }, 20, 20, Colors::WHITE });
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
    ind.state(ind2.isMe(elp.getCenter()) && elp.isShowed());
    ind2.state(ind.isMe(elp.getCenter()) && elp.isShowed());
    lb.setText(std::to_string(elp.getCenterW()) + "\n" + std::to_string(elp.getCenterH()));

    rr.draw(disp);
    lb.draw(disp);

    for (size_t i = 0; i < 2; i++)
    {
      arrInd[i]->draw(disp);
    }

    elp.draw(disp);
    disp.showLayer(disp.getLayer());

    HAL_IWDG_Refresh(&Peripheral::VA_IWDG::hiwdg);
    taskYIELD();

    // vTaskDelayUntil(&xLastWakeTime, 40 / portTICK_RATE_MS);
    vTaskDelay(5);
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