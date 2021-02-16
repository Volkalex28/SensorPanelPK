/*
 * Screen1.h
 *
 *  Created on: 11 нояб. 2020 г.
 *      Author: anan2
 */

#pragma once

#include "Loop.h"
#include "ScreenEvents.h"
#include "ScreenCrash.h"
#include "ScreenSysSett.h"
#include "ScreenZVU.h"
#include "ScreenBattery.h"

using namespace VA;

extern ScreenCrash sCrash;
extern ScreenEvents sEvents;
extern ScreenSysSett SystemSett;
extern ScreenZVU sZVU;
extern ScreenBattery sBatteryControl;

class ScreenMenu : public BaseScreen {

public:

	Button lookCrash = Button(this, 60, 100, 410, 110, 0x7BEF, "Просмотр аварий", 0);
	Button lookEvent = Button(this, 60, 230, 410, 60, 0x7BEF, "Просмотр событий", 0);
	Button systemSetting = Button(this, 60, 305, 410, 60, 0x7BEF, "Системные настройки", 0);

	Button butZVU = Button(this, 530, 100, 220, 120, 0x7BEF, "ЗВУ", 0);
	Button butDCXJ = Button(this, 530, 250, 220, 120, 0x7BEF, "Контроль  АКБ", 0);


	ScreenMenu(void) : BaseScreen(&Screens, "Меню") {

		this->systemSetting.addCallBack([]() { Screens.JumpScreen(&SystemSett); });
		this->lookCrash.addCallBack([]() { Screens.JumpScreen(&sCrash); });
		this->lookEvent.addCallBack([]() { Screens.JumpScreen(&sEvents); });
		this->butZVU.addCallBack([]() { Screens.JumpScreen(&sZVU); });
		this->butDCXJ.addCallBack([]() { Screens.JumpScreen(&sBatteryControl); });
	}
};

