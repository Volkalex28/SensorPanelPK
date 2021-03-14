/**
 * @file main.h
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#pragma once

void taskShow(void * pvParametres);
void taskBlink(void * pvParametres);
void timerCallbackScroll(OS::FreeRTOS::xTimerHandle xTimer);
