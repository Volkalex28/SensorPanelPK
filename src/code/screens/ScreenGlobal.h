/*
 * Screen.h
 *
 *  Created on: 11 нояб. 2020 г.
 *      Author: anan2
 */

#pragma once

#include "Loop.h"

#include "ScreenMenu.h"
#include "ScreenSysSett.h"
#include "ScreenSetTime.h"
#include "ScreenCOM.h"
#include "ScreenAutorization.h"
#include "ScreenCrash.h"
#include "ScreenSettZVU.h"
#include "ScreenZVU.h"
#include "ScreenBattery.h"


using namespace VA;

extern ScreenMenu Menu;
extern ScreenSysSett SystemSett;
extern ScreenSetTime SetTime;
extern ScreenCOM COMSett;
extern ScreenAutorization Autorization;
extern ScreenCrash sCrash;
extern ScreenZVU sZVU;
extern ScreenSettZVU sSettZVU;
extern ScreenBattery sBatteryControl;

class ScreenGlobal {

	void Loop(void) {
		this->screenName.SetText(Screens.GetPtrCurrentScreen()->GetName());

		this->time.SetText(Screens.GetTime());
		this->date.SetText(Screens.GetDate());

		Memory[rMemory::Hours].U = Screens.GetHours();
		Memory[rMemory::Minutes].U = Screens.GetMinutes();
		Memory[rMemory::Seconds].U = Screens.GetSeconds();
		Memory[rMemory::Day].U = Screens.GetDay();
		Memory[rMemory::Month].U = Screens.GetMonth();
		Memory[rMemory::Years].U = Screens.GetYear();
	}

public:

	Graphics r1_1 	= Graphics(&Screens.Global, 700,  0, 100, 60, 0x031f, Figure::rect, 0, true);
	Graphics r1_2 	= Graphics(&Screens.Global, 440,  0, 360, 60, 0x031f, Figure::roundrect, 15, true);
	Graphics r1_3 	= Graphics(&Screens.Global, 440, 30, 100, 30, 0x031f, Figure::rect, 0, true);
	Graphics crv1_1	= Graphics(&Screens.Global, 439,  0,  15, 15, RA8875_BLACK, Figure::curve, 1, false);
	Graphics crv1_2	= Graphics(&Screens.Global, 440,  0,  15, 15, RA8875_BLACK, Figure::curve, 1, false);
	Graphics crv1_3	= Graphics(&Screens.Global, 441,  0,  15, 15, RA8875_BLACK, Figure::curve, 1, false);
	Graphics line0 	= Graphics(&Screens.Global, 439, 15,   3, 45, RA8875_BLACK, Figure::rect, 0, true);
	Graphics line1 	= Graphics(&Screens.Global,   0, 60, 800,  5, RA8875_BLACK, Figure::rect, 0, true);

	Indicator indCrash = Indicator(&Screens.Global, 360, 1, 56, 56, true);

	Graphics r2 	= Graphics(&Screens.Global, 0, 420, 800, 60,       0x031f, Figure::rect, 0, true);
	Graphics line2 	= Graphics(&Screens.Global, 0, 415, 800,  5, RA8875_BLACK, Figure::rect, 0, true);


	Label screenName 	= Label(&Screens.Global, 440, 0, 360, 60, "", Fonts::TimesNewRoman, FontForms::Bold,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);
	Label time 			= Label(&Screens.Global, 240, 440, 150, 23, "0", Fonts::TimesNewRoman, FontForms::Bold,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);
	Label date 			= Label(&Screens.Global, 400, 440, 200, 23, "0", Fonts::TimesNewRoman, FontForms::Bold,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);

	Button menu = Button(&Screens.Global, 40, 425, 140, 50, 0x031f, "Меню", 7);
	Button back = Button(&Screens.Global, 620, 425, 140, 50, 0x031f, "Назад", 7);

	ScreenGlobal(void) {
		Screens.Global.setInfLoop(this, &ScreenGlobal::Loop);

		this->menu.addCallBack([]() { Screens.JumpScreen(&Menu); });
		this->back.addCallBack([]() {
			if (Screens.GetPtrCurrentScreen() == &Menu) {
				Screens.JumpScreen((int)0);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &sCrash) {
				Screens.JumpScreen(&Menu);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &sEvents) {
				Screens.JumpScreen(&Menu);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &SystemSett) {
				Screens.JumpScreen(&Menu);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &SetTime) {
				Screens.JumpScreen(&SystemSett);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &COMSett) {
				Screens.JumpScreen(&SystemSett);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &Autorization) {
				Screens.JumpScreen(&SystemSett);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &sZVU) {
				Screens.JumpScreen(&Menu);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &sSettZVU) {
				Screens.JumpScreen(&sZVU);
				return;
			}
			if (Screens.GetPtrCurrentScreen() == &sBatteryControl) {
				Screens.JumpScreen(&Menu);
				return;
			}
		});
	}
};
