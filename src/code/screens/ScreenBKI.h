/*
 * ScreenBKI.h
 *
 *  Created on: Feb 10, 2021
 *      Author: ans0l
 */

#pragma once

#include "Loop.h"
#include "ScreenContrlInsulation.h"

extern ScreenContrlInsulation sContrlInsulation;

using namespace VA;

class ScreenBKI : public BaseScreen {

	uint16_t Value[6] = {}; 	//
	uint32_t counter = 1;		//

/*-----------------------Вертикальные линии -------------------------------------------------------------------*/
	Graphics Vline1 	= Graphics(this, 205, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline2 	= Graphics(this, 410, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline3 	= Graphics(this, 620, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);

/*-----------------------Горизонтальные линии ----------------------------------------------------------------*/
	Graphics Hline1 	= Graphics(this, 0,	185, 620, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline2 	= Graphics(this, 0, 300, 620, 2, RA8875_BLACK, Figure::rect, 0, true);

/*-----------------------Кнопки переключения------------------------------------------------------------------*/
	Button bBKI		= Button(this, 648, 170, 120, 55, 0x7BEF, ">", 0);// кнопка перехода на экран фидеров

	Button bSetBKI 	= Button(this, 648, 330, 120, 55, 0x7BEF, "#", 0); //кнопка перехода на настройки фидеров

/*----------------------------------------------------------------------------------------------------------------*/
	Label lfider[3] = {
		Label(this, 10, 65, 300, 65, "Напряжение первой секции", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 10, 185, 300, 65, "Сопротивление первой секции", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 10, 300, 300, 65, "Напряжение первой секции", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

/*----------------------------------------------------------------------------------------------------------------*/
	Label section[6] = {
		Label(this, 235, 65, 300, 65, "Основная шина", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 235, 185, 300, 65, "+ Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 235, 300, 300, 65, "+ Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
		Label(this, 440, 65, 300, 65, "Дополнительная шина", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 440, 185, 300, 65, "- Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 440, 300, 300, 65, "- Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),

	};

/*-----------------------Дисплеии вывода значения сопротивления Полюсов------------------------------------------------------------------*/
	Display disp[6] = {
		Display(this, 235, 126, 100,50, &Value[0], 5, 2, 0, 1000, nullptr),
		Display(this, 235, 242, 100,50, &Value[1], 5, 2, 0, 1000, nullptr),
		Display(this, 235, 357, 100,50, &Value[2], 5, 2, 0, 1000, nullptr),

		Display(this, 440, 126, 100,50, &Value[3], 5, 2, 0, 1000, nullptr),
		Display(this, 440, 242, 100,50, &Value[4], 5, 2, 0, 1000, nullptr),
		Display(this, 440, 357, 100,50, &Value[5], 5, 2, 0, 1000, nullptr)
	};

/*-----------------------Дисплеии вывода значения сопротивления Полюсов------------------------------------------------------------------*/

	Label Units[6] = {
		Label(this, 355, 136, 50, 30, "В", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 355, 252, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 355, 367, 50, 30, "В", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
		Label(this, 560, 136, 50, 30, "В", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 560, 252, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 560, 367, 50, 30, "В", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

public:

	ScreenBKI(void) : BaseScreen(&Screens, "Блок контроля изоляции: ") {
		//this->bBKI.addCallBack([]() { Screens.JumpScreen(&sContrlInsulation); });
		//this->bSetBKI.addCallBack([]() { Screens.JumpScreen(&sContrlInsulation); });

	}

	void Loop(void) override {

	}

	void JumpTo(void) override {

	}
};
