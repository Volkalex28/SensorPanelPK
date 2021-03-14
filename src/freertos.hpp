/**
 * @file freertos.hpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

namespace OS
{

namespace FreeRTOS
{

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>

extern xTimerHandle timerScroll;

void Init(void);

} // namespace FreeRTOS

} // namespace OS
