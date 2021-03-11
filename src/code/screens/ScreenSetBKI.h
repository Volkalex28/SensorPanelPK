/*
 * ScreenSetBKI.h
 *
 *  Created on: Feb 10, 2021
 *      Author: ans0l
 */

#pragma once

#include "Loop.h"

using namespace VA;

class ScreenSetBKI : public BaseScreen {

	Label label[4] = {
		Label(this, 75, 110, 350, 65, "Количество фидеров, шт.", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 75, 170, 350, 65, "Колибровочній коэф-т", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 75, 230, 350, 65, "Rиз (предупред), кОм", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
        Label(this, 75, 290, 350, 65, "Rиз (авария), кОм", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

	Display disp[4] 			= {
		 Display(this, 450, 120, 100, 40, &Memory[eMemory::numBKI].U, 2, 0, 3, 32, &Screens.kbr),
		 Display(this, 450, 180, 100, 40, &Memory[eMemory::coefBKI].U, 4, 0, 0, 32000, &Screens.kbr),
		 Display(this, 450, 240, 100, 40, &Memory[eMemory::warnInsulation].U, 4, 0, 0, 32000, &Screens.kbr),
		 Display(this, 450, 300, 100, 40, &Memory[eMemory::crashInsulation].U, 4, 0, 0, 32000, &Screens.kbr),
	};



public:

	ScreenSetBKI(void) : BaseScreen(&Screens, "Параметры БКИ: ") {
		this->disp[0].addCallBack([&]() {
			eeprom.Write(&Memory[eMemory::numBKI].U);
		});
		this->disp[1].addCallBack([&]() {
			eeprom.Write(&Memory[eMemory::coefBKI].U);
		});
		this->disp[2].addCallBack([&]() {
			eeprom.Write(&Memory[eMemory::warnInsulation].U);
		});
		this->disp[3].addCallBack([&]() {
			eeprom.Write(&Memory[eMemory::crashInsulation].U);
		});
	}

	void Loop(void) override {

	}

	void JumpTo(void) override {

	}
};
