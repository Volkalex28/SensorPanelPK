/*
 * ScreenSetTime.h
 *
 *  Created on: 30 нояб. 2020 г.
 *      Author: anan2
 */

#pragma once

#include "Loop.h"

using namespace VA;

class ScreenSetTime : public BaseScreen {

public:

	Display Hours 	= Display(this, 110, 150, 50, 60, &Memory[rMemory::Hours].U, 2, 0, 0, 23, &Screens.kbr);
	Display Minutes = Display(this, 320, 150, 50, 60, &Memory[rMemory::Minutes].U, 2, 0, 0, 59, &Screens.kbr);
	Display Seconds	= Display(this, 530, 150, 50, 60, &Memory[rMemory::Seconds].U, 2, 0, 0, 59, &Screens.kbr);

	Display Day 	= Display(this, 110, 300, 50, 60, &Memory[rMemory::Day].U, 2, 0, 1, 31, &Screens.kbr);
	Display Month 	= Display(this, 320, 300, 50, 60, &Memory[rMemory::Month].U, 2, 0, 1, 12, &Screens.kbr);
	Display Year	= Display(this, 530, 300, 100, 60, &Memory[rMemory::Years].U, 4, 0, 2000, 9999, &Screens.kbr);

	Label lHours	= Label(this, 110, 90, 50, 60, "Часы", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x0);
	Label lMinutes	= Label(this, 320, 90, 50, 60, "Минуты", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x0);
	Label lSeconds	= Label(this, 530, 90, 50, 60, "Секунды", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x0);

	Label lDay		= Label(this, 110, 240, 50, 60, "День", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x0);
	Label lMonth	= Label(this, 320, 240, 50, 60, "Месяц", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x0);
	Label lYear		= Label(this, 530, 240, 100, 60, "Год", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x0);

	ScreenSetTime(void)
		: BaseScreen(&Screens, "Установка даты и времени")
	{
		this->Hours.addCallBack([&]() { Screens.SetHours(*this->Hours.GetPValue()); });
		this->Minutes.addCallBack([&]() { Screens.SetMinutes(*this->Minutes.GetPValue()); });
		this->Seconds.addCallBack([&]() { Screens.SetSeconds(*this->Seconds.GetPValue()); });

		this->Day.addCallBack([&]() { Screens.SetDay(*this->Day.GetPValue()); });
		this->Month.addCallBack([&]() { Screens.SetMonth(*this->Month.GetPValue()); });
		this->Year.addCallBack([&]() { Screens.SetYear(*this->Year.GetPValue()); });
	}
};


