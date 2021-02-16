/*
 * EventInit.cpp
 *
 *  Created on: Dec 7, 2020
 *      Author: ans0l
 */

#include "ScreenEvents.h"

std::string ListEvent[100] = {};

void EventInit(void) {
	ListEvent[NumberCrash::PanelOn] = "Панель включена";
	ListEvent[10] = "Обрыв связи: ";
	ListEvent[11] = "Связь востановленна: ";
	ListEvent[12] = "Неисправность: ";
	ListEvent[21] = "Неисправность батареи";
}
