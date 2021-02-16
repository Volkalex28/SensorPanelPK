/*
 * ScreenSysSett.h
 *
 *  Created on: Nov 30, 2020
 *      Author: ans0l
 */

#pragma once

#include "Loop.h"

#include "ScreenSetTime.h"
#include "ScreenCOM.h"
#include "ScreenAutorization.h"

using namespace VA;

extern ScreenSetTime SetTime;
extern ScreenCOM COMSett;
extern ScreenAutorization Autorization;

class ScreenSysSett: public BaseScreen {
public:

	Button portCOM 			= Button(this, 35, 130, 425, 60, 0x7BEF, "COM порты", 0);
	Button authorization 	= Button(this, 35, 210, 425, 60, 0x7BEF, "Авторизация", 0);
	Button setTime 			= Button(this, 35, 290, 425, 60, 0x7BEF, "Установка даты и времени", 0);

	Label lBackLight		= Label(this, 500, 130, 150, 100, "Яркость\nподсветки\nдисплея");
	Display dBacklight 		= Display(this, 650, 145, 75, 60, &Memory[eMemory::Backlight].U, 3, 0, 1, 100, &Screens.kbr);
	Label lProcent			= Label(this, 740, 160, 40, 40, "%");

	Label lTimeOut			= Label(this, 500, 270, 150, 100, "Тайм-аут\nподсветки");
	Display dTimeOut		= Display(this, 650, 275, 75, 60, &Memory[eMemory::TimeOut].U, 3, 0, 1, 180, &Screens.kbr);
	Label lMin				= Label(this, 740, 285, 40, 40, "мин.");

	ScreenSysSett(void)
		: BaseScreen(&Screens, "Системные настройки")
	{
		this->setTime.addCallBack([]() { Screens.JumpScreen(&SetTime); });
		this->portCOM.addCallBack([]() { Screens.JumpScreen(&COMSett); });
		this->authorization.addCallBack([]() { Screens.JumpScreen(&Autorization); });

		this->dBacklight.addCallBack([]() {
			Screens.SetBackLight(Memory[eMemory::Backlight].U);
			eeprom.Write(&Memory[eMemory::Backlight].U);
		});
		this->dTimeOut.addCallBack([]() {
			Screens.SetTimeOut(Memory[eMemory::TimeOut].U);
			eeprom.Write(&Memory[eMemory::TimeOut].U);
		});
	}
};

