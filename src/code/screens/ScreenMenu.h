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
#include "ScreenMain.h"
#include "ScreenBKI.h"

using namespace VA;

extern ScreenCrash sCrash;
extern ScreenEvents sEvents;
extern ScreenSysSett SystemSett;
extern ScreenZVU sZVU;
extern ScreenBattery sBatteryControl;
extern ScreenMain sMain;
extern ScreenBKI sBKI;

class ScreenMenu : public BaseScreen {

public:

	Button lookCrash	 = Button(this, 60, 100, 400, 110, 0x7BEF, "Просмотр аварий", 0);
	Button lookEvent	 = Button(this, 60, 230, 400, 60, 0x7BEF, "Просмотр событий", 0);
	Button systemSetting = Button(this, 60, 305, 400, 60, 0x7BEF, "Системные настройки", 0);


	Button butZVU	 = Button(this, 505, 100, 100, 110, 0x7BEF, "ЗВУ", 0);
	Button butDCXJ	 = Button(this, 615, 100, 160, 110, 0x7BEF, "Контроль  АКБ", 0);
	Button butMain	 = Button(this, 505, 230, 270, 60, 0x7BEF, "Основной экран", 0);
	Button butAnalog = Button(this, 505, 305, 270, 60, 0x7BEF, "БКИ", 0);

	ScreenMenu(void):BaseScreen(&Screens, "Меню") {

		this->systemSetting.addCallBack([]() { Screens.JumpScreen(&SystemSett); });
		this->lookCrash.addCallBack([]() { Screens.JumpScreen(&sCrash); });
		this->lookEvent.addCallBack([]() { Screens.JumpScreen(&sEvents); });
		this->butZVU.addCallBack([]() { Screens.JumpScreen(&sZVU); });
		this->butDCXJ.addCallBack([]() { Screens.JumpScreen(&sBatteryControl); });
		this->butMain.addCallBack([]() { Screens.JumpScreen(&sMain); });
		this->butAnalog.addCallBack([]() { Screens.JumpScreen(&sBKI); });
	}

};

