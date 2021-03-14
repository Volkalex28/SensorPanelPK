/**
 * @file freertos.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include "freertos.hpp"
#include "main.h"

namespace OS::FreeRTOS
{

xTimerHandle timerScroll;

void Init(void)
{
  xTaskCreate(&taskShow, (const char *)"RA8878", 2048, NULL, 3, NULL);
  xTaskCreate(&taskBlink, "Blink", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

  timerScroll = xTimerCreate("Scroll", pdTRUE, 10, 0, timerCallbackScroll);

  xTimerChangePeriod(timerScroll, 10, 0);
  xTimerReset(timerScroll, 0);

  vTaskStartScheduler();
}

} // namespace OS::FreeRTOS

using namespace OS::FreeRTOS;

#ifdef __cplusplus
extern "C"
{
#endif

  /* Idle task control block and stack */
  static StaticTask_t Idle_TCB;
  static StackType_t Idle_Stack[configMINIMAL_STACK_SIZE];

  /* Timer task control block and stack */
  static StaticTask_t Timer_TCB;
  static StackType_t Timer_Stack[configTIMER_TASK_STACK_DEPTH];

  /*
    vApplicationGetIdleTaskMemory gets called when configSUPPORT_STATIC_ALLOCATION
    equals to 1 and is required for static memory allocation support.
  */
  void vApplicationGetIdleTaskMemory(
    StaticTask_t ** ppxIdleTaskTCBBuffer, StackType_t ** ppxIdleTaskStackBuffer, uint32_t * pulIdleTaskStackSize)
  {
    *ppxIdleTaskTCBBuffer = &Idle_TCB;
    *ppxIdleTaskStackBuffer = &Idle_Stack[0];
    *pulIdleTaskStackSize = (uint32_t)configMINIMAL_STACK_SIZE;
  }

  /*
    vApplicationGetTimerTaskMemory gets called when configSUPPORT_STATIC_ALLOCATION
    equals to 1 and is required for static memory allocation support.
  */
  void vApplicationGetTimerTaskMemory(
    StaticTask_t ** ppxTimerTaskTCBBuffer, StackType_t ** ppxTimerTaskStackBuffer, uint32_t * pulTimerTaskStackSize)
  {
    *ppxTimerTaskTCBBuffer = &Timer_TCB;
    *ppxTimerTaskStackBuffer = &Timer_Stack[0];
    *pulTimerTaskStackSize = (uint32_t)configTIMER_TASK_STACK_DEPTH;
  }

#ifdef __cplusplus
}
#endif
