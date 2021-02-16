/*
 * ScreenCrash.h
 *
 *  Created on: Dec 3, 2020
 *      Author: anan2
 */

#pragma once

#include "Loop.h"
#include "ScreenEvents.h"
#include "BaseDevice.h"

using namespace VA;

extern ScreenEvents sEvents;
extern std::string ListEvent[100];

class ScreenCrash : public BaseScreen {

	Graphics Vline1 	= Graphics(this,   0, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline2 	= Graphics(this, 620, 65, 5, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline3 	= Graphics(this,  63, 65, 2, 350, RA8875_BLACK, Figure::rect, 0, true);

	Graphics Hline1 	= Graphics(this, 5, 123, 615, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline2 	= Graphics(this, 5, 182, 615, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline3 	= Graphics(this, 5, 240, 615, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline4 	= Graphics(this, 5, 298, 615, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline5 	= Graphics(this, 5, 357, 615, 2, RA8875_BLACK, Figure::rect, 0, true);

	Label num[6] = {
		Label(this, 0, 65, 65, 65, "1", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 123, 65, 65, "2", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 182, 65, 65, "33", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 240, 65, 65, "44", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 298, 65, 65, "555", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 357, 65, 65, "666", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY)
	};

	Label crash[6] = {
		Label(this, 70, 60, 550, 70, "Здесь будет название какой-то аварии, а",// пока это тестовое сообщение",
			Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 70, 118, 550, 70, "Здесь будет название какой-то аварии, а пока это тестовое сообщение",
			Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 70, 177, 550, 70, "Здесь будет название какой-то аварии, а пока это тестовое сообщение",
			Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 70, 235, 550, 70, "Здесь будет название какой-то аварии, а пока это тестовое сообщение",
			Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 70, 293, 550, 70, "Здесь будет название какой-то аварии, а пока это тестовое сообщение",
			Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 70, 352, 550, 70, "Здесь будет название какой-то аварии, а пока это тестовое сообщение",
			Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY)
	};

	Label allCrash	= Label(this, 0, 0, 200, 60, "Всего аварий: ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Right, VALabelAlignY::CenterY);
	Label numCrash	= Label(this, 200, 0, 100, 60, "", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY);

public:

	Button bUp		= Button(this, 650, 90, 120, 90, 0x031f, "Вверх");
	//Graphics trUp	= Graphics(this, 650, 90, 120, 90, RA8875_BLACK, Figure::, r, fill)
	Button bDown	= Button(this, 650, 300, 120, 90, 0x031f, "Вниз");

private:

	std::vector<NumberCrash> Buf = {};
	uint16_t counter = 0;

public:

	bool addCrash(NumberCrash number) {
		uint16_t pos = std::distance(this->Buf.cbegin(), std::find(this->Buf.cbegin(), this->Buf.cend(), number));

		if(pos >= this->Buf.size()) {
			this->Buf.push_back(number);
			sEvents.addEvent(number);
			return true;
		}
		return false;
	}

	void delCrash(NumberCrash number) {
		uint16_t pos = std::distance(this->Buf.cbegin(), std::find(this->Buf.cbegin(), this->Buf.cend(), number));

		if (NumberCrash::LostConect < number && number < NumberCrash::ConectRecovery && pos < this->Buf.size()) {
			uint16_t temp = number + NumberCrash::ConectRecovery - NumberCrash::LostConect;
			sEvents.addEvent((NumberCrash)temp);
		}
		this->Buf.erase(std::remove(this->Buf.begin(), this->Buf.end(), number), this->Buf.end());
	}

	ScreenCrash(void)
		: BaseScreen(&Screens, "Просмотр аварий")
	{
		this->bUp.addCallBack([&]() {
			if(this->counter - 1 >= 0) {
				this->counter--;
			}
		});
		this->bDown.addCallBack([&]() {
			if(this->counter < (int)(this->Buf.size() - 6)) {
				this->counter++;
			}
		});
	}

	void Loop(void) override {
		numCrash.SetText(std::to_string(this->Buf.size()));

		while(this->counter > 0 && this->counter > (int)(this->Buf.size() - 6)) {
			this->counter--;
		}

		uint16_t number = 0;
		for(uint16_t i = 0; i < 6; i++) {
			if((int)(this->Buf.size() - this->counter - i) > 0) {
				number = this->Buf.size() - i - this->counter - 1;
				this->num[i].SetText(std::to_string(number+1));

				if (this->Buf[number] < NumberCrash::LostConect) {
					this->crash[i].SetText(ListEvent[this->Buf[number]]);
				}
				else if (this->Buf[number] < NumberCrash::ConectRecovery) {
					this->crash[i].SetText(ListEvent[10] + BaseDevice::Devices[this->Buf[number] - NumberCrash::LostConect - 1]->Name);
				}
				else if (this->Buf[number] < NumberCrash::Fault) {
					this->crash[i].SetText(ListEvent[11] + BaseDevice::Devices[this->Buf[number] - NumberCrash::ConectRecovery - 1]->Name);
				}
				else if (this->Buf[number] < NumberCrash::EndNumber ) {
					this->crash[i].SetText(ListEvent[12] + BaseDevice::Devices[this->Buf[number] - NumberCrash::Fault - 1]->Name);
				}
				else {
					this->crash[i].SetText(ListEvent[this->Buf[number] - 80]);
				}
			}
			else {
				this->num[i].SetText("");
				this->crash[i].SetText("");
			}
		}
	}

	void JumpTo(void) override {
		this->counter = 0;
		this->Loop();
	}
};
