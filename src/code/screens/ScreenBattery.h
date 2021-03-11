/*
 * ScreenBattery.h
 *
 *  Created on: 9 дек. 2020 г.
 *      Author: ans0ld
 */



#pragma once

#include "Loop.h"
#include "DeviceDCXJ.h"

using namespace VA;

extern DeviceDCXJ DCXJ;

class ScreenBattery : public BaseScreen {

	class WindowSettings : public BaseWindow {

	public:

		Label l1 = Label(this, 20, 0, this->GetW()-40, 60, this->name, Fonts::TimesNewRoman, FontForms::Bold,
					VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::Bottom);
		Graphics line1 = Graphics(this, 50, 65, this->GetW()-100 , 5, 0x0000, Figure::rect, 3, true);

		Button bClose = Button(this, this->GetW()-200, this->GetH()-100, 150, 65, 0x031f, "Закрыть", 10);

		Label lVoltage = Label(this, 50, 110, 300, 50, "Уставка напряжения на секции");
		Label lTolerance = Label(this, 50, 190, 300, 50, "Допуск напряжения на секции");
		Label lNSections = Label(this, 50, 270, 300, 50, "Количество\nсекций");

		Display dVoltage = Display(this, 400, 100, 100, 50, &Memory[eMemory::SettingBatteryDCXJ].U, 5, 2, 100, 2000, &Screens.kbr);
		Display dToleranceV = Display(this, 400, 180, 100, 50, &Memory[eMemory::ToleranceBatteryDCXJ].U, 5, 2, 30, 400, &Screens.kbr);
		Display dNSections = Display(this, 250, 280, 100, 50, &Memory[eMemory::N_SectionDCXJ].U, 2, 0, 6, 60, &Screens.kbr);

		Label unit[2] {
			Label(this, 530, 110, 10, 50, "B"),
			Label(this, 530, 190, 10, 50, "B")
		};
		WindowSettings(void) : BaseWindow("Уставки АКБ", &Screens) {
			this->bClose.addCallBack([&]() {
				this->Close();
			});
			this->dVoltage.addCallBack([&]() {
				eeprom.Write(&Memory[eMemory::SettingBatteryDCXJ].U);
			});
			this->dToleranceV.addCallBack([&]() {
				eeprom.Write(&Memory[eMemory::ToleranceBatteryDCXJ].U);
			});
			this->dNSections.addCallBack([&]() {
				eeprom.Write(&Memory[eMemory::N_SectionDCXJ].U);
			});
		}
	} ToleranceSett;

/*-----------------------------Функциональная область-------------------------------------------------- */
	Graphics bControl 	= Graphics(this, 440, 0, 360, 60, RA8875_BLACK, Figure::rect, 0, false);

/*----------------------------------------------------------------------------------------------------------------*/
	Label temperature1	= Label(this, 2, 0, 220, 60, "Температура:", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY);
	Display value1		= Display(this, 200, 5, 100, 50, &DCXJ.Mem.Temp1, 5, 1, 0, 1000, nullptr);

	Label temVal1	= Label(this, 310, 0, 220, 60, "°C", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY);

/*----------------------------------------------------------------------------------------------------------------*/
	Graphics Vline1 	= Graphics(this, 310, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline2 	= Graphics(this, 620, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);

	Graphics Hline1 	= Graphics(this, 0,	185, 620, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline2 	= Graphics(this, 0, 300, 620, 2, RA8875_BLACK, Figure::rect, 0, true);

/*----------------------------------------------------------------------------------------------------------------*/
	Button left		= Button(this, 648, 170, 120, 55, 0x7BEF, "<<", 0);
	Button right 	= Button(this, 648, 250, 120, 55, 0x7BEF, ">>", 0);
/*----------------------------------------------------------------------------------------------------------------*/
	Indicator ind[6] = {
			Indicator(this, 20, 126, 50, 50, true),
			Indicator(this, 20, 242, 50, 50, true),
			Indicator(this, 20, 357, 50, 50, true),

			Indicator(this, 330,126, 50, 50, true),
			Indicator(this, 330, 242, 50, 50, true),
			Indicator(this, 330, 357, 50, 50, true),
	};
/*----------------------------------------------------------------------------------------------------------------*/
	Display disp[6] = {
			Display(this, 90, 126, 100,50, &Value[0], 5, 2, 0, 1000, nullptr),
			Display(this, 90, 242, 100,50, &Value[1], 5, 2, 0, 1000, nullptr),
			Display(this, 90, 357, 100,50, &Value[2], 5, 2, 0, 1000, nullptr),

			Display(this, 400, 126, 100,50, &Value[3], 5, 2, 0, 1000, nullptr),
			Display(this, 400, 242, 100,50, &Value[4], 5, 2, 0, 1000, nullptr),
			Display(this, 400, 357, 100,50, &Value[5], 5, 2, 0, 1000, nullptr)
	};


/*----------------------------------------------------------------------------------------------------------------*/
	Label section[6] = {
			Label(this, 10, 65, 300, 65, "Секция", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 10, 185, 300, 65, "Секция", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 10, 300, 300, 65, "Секция", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
			Label(this, 320, 65, 300, 65, "Секция", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 320, 185, 300, 65, "Секция", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 320, 300, 300, 65, "Секция", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

	Label Units[6] = {
			Label(this, 210, 136, 50, 30, "B", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 210, 252, 50, 30, "B", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 210, 367, 50, 30, "B", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
/*----------------------------------------------------------------------------------------------------------------*/
			Label(this, 520, 136, 50, 30, "B", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 520, 252, 50, 30, "B", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 520, 367, 50, 30, "B", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

	uint16_t Value[6] = {};
	uint32_t counter = 1;

public:
	uint32_t Max = 60; // количество секций (в блоке максимум 60)
	uint32_t Min = 6; // cекций на экране

	ScreenBattery(void)
		: BaseScreen(&Screens, "Контроль АКБ")
	{
		this->left.addCallBack([&]() {
			if(this->counter >= this->Min + 6) {
				this->counter -= 6;
			}
			else { this->counter = this->Min; }
		});
		this->right.addCallBack([&]() {
			if(this->counter < (this->Max - 6)) {
				this->counter += 6;
			}
			else { this->counter = this->Max; }

		});
// --------  Установка прав администратора на функциональную кнопку (кнопка внесения уставок)---------------------------------//
		this->bControl.SetShowed(false);
		this->bControl.addCallBack([&]() {
			if(Screens.GetLevelAcces() == LevelsAcces::Admin) {
				this->ToleranceSett.Open();
			}
		});
		this->ToleranceSett.dNSections.addCallBack(this, &ScreenBattery::JumpTo);
	}
	void Loop(void) override {
		uint8_t number;
		for(uint8_t i = 0; i < 6; i++) {
			number = this->counter + i - 6;
			this->section[i].SetText("Секция " + std::to_string(number + 1));

			this->Value[i] = DCXJ.Mem.cellVoltage[number];
			uint64_t* status = (uint64_t*)&DCXJ.Mem.sCellBattery;
			this->ind[i].state = (*status) & (1 << number);
		}
	}

	void JumpTo(void) override {
		this->counter = this->Min;
	}
};





