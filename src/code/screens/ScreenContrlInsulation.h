/*
 * ScreenContrlInsulation.h
 *
 *  Created on: Feb 6, 2021
 *      Author: ans0l
 */

#pragma once

#include "Loop.h"

using namespace VA;

class ScreenContrlInsulation : public BaseScreen {

	uint16_t Value[6] = {0}; 	// значения сопротивлений изоляции
	uint32_t counter;		// номер фидера

/*-----------------------Вертикальные линии -------------------------------------------------------------------*/
	Graphics Vline1 	= Graphics(this, 210, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline2 	= Graphics(this, 415, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline3 	= Graphics(this, 620, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);

/*-----------------------Горизонтальные линии ----------------------------------------------------------------*/
	Graphics Hline1 	= Graphics(this, 0,	185, 620, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline2 	= Graphics(this, 0, 300, 620, 2, RA8875_BLACK, Figure::rect, 0, true);

/*-----------------------Кнопки переключения------------------------------------------------------------------*/
	Button left		= Button(this, 648, 170, 120, 55, 0x7BEF, "<<", 0);
	Button right 	= Button(this, 648, 250, 120, 55, 0x7BEF, ">>", 0);

	Button SetBKI 	= Button(this, 648, 250, 120, 55, 0x7BEF, ">>", 0);

/*----------------------------------------------------------------------------------------------------------------*/
	Label lfider[3] = {
		Label(this, 5, 85, 300, 65, " ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 5, 205, 300, 65, " ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 5, 320, 300, 65, " ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

/*----------------------------------------------------------------------------------------------------------------*/
	Label section[6] = {
		[0] = Label(this, 235, 65, 300, 65, "+ Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		[1] = Label(this, 235, 185, 300, 65, "+ Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		[2] = Label(this, 235, 300, 300, 65, "+ Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
		[3] = Label(this, 440, 65, 300, 65, "- Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		[4] = Label(this, 440, 185, 300, 65, "- Полюса", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		[5] = Label(this, 440, 300, 300, 65, "- Полюса", Fonts::TimesNewRoman, FontForms::Normal,
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
		Label(this, 355, 136, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 355, 252, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 355, 367, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
		Label(this, 560, 136, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 560, 252, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 560, 367, 50, 30, "кОм", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

public:

	uint32_t Max = 32; 	// количество фидеров
	uint32_t Min = 3; 	// количество фидеров на экране

	ScreenContrlInsulation(void) : BaseScreen(&Screens, "Блок контроля изоляции: ") {


	}

	void Loop(void) override {
		uint8_t number;
			for(uint8_t i = 0; i < 3; i++) {
				number = this->counter + i - 3;
				this->lfider[i].SetText("Сопротивление\n" + std::to_string(number + 1) + "-го фидера");
			}
	}

	void JumpTo(void) override {
		this->counter = this->Min;
	}
};

