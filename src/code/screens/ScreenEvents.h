/*
 * ScreenEvents.h
 *
 *  Created on: 5 дек. 2020 г.
 *      Author: ans0l
 */

#pragma once
#include "Loop.h"
#include "BaseDevice.h"

using namespace VA;

enum NumberCrash {
	PanelOn = 1,
	LostConect = 10,
	ConectRecovery = 50,
	Fault = 90,

	EndNumber = 100,
	BatteryCrash
};

struct Event_t {
	uint8_t Min;
	uint8_t Hours;
	uint8_t Day;
	uint8_t Sec;
	uint8_t Year;
	uint8_t Month;
	uint16_t Event;
};

extern std::string ListEvent[100];

class ScreenEvents : public BaseScreen {


	Canvas control = Canvas(nullptr, 550, 102, 230, 310, &Screens);
	Graphics rect1 = Graphics(&this->control, 0, 0, this->control.GetW()-0, this->control.GetH()-0, 0x0000, Figure::rect, 0, true);
	Graphics rect2 = Graphics(&this->control, 2, 2, this->control.GetW()-4, this->control.GetH()-4, 0xFFFF, Figure::rect, 0, true);
	Graphics rect3 = Graphics(&this->control, 4, 4, this->control.GetW()-8, this->control.GetH()-8, 0x0000, Figure::rect, 0, true);
	Graphics rect  = Graphics(&this->control, 8, 8, this->control.GetW()-16, this->control.GetH()-16, 0xB5B6, Figure::rect, 0, true);

/*-----------------------------Функциональная область-------------------------------------------------- */
	Graphics bControl 	= Graphics(this, 440, 0, 360, 60, RA8875_BLACK, Figure::rect, 0, false);

/*-----------------------------Кнопки в окне-------------------------------------------------- */
	Button upPage 	= Button(&this->control, 48, 29, 140, 50, 0x031f, "««", 0);
	Button up 		= Button(&this->control, 48, 100, 140, 50, 0x031f, "<<", 0);

	Button down 	= Button(&this->control, 48, 160, 140, 50, 0x031f, ">>", 0);
	Button downPage = Button(&this->control, 48, 231, 140, 50, 0x031f, "»»", 0);

/*----------------------------------------------------------------------------------------------------- */
	Graphics Vline1 	= Graphics(this,  63, 65, 2, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline2 	= Graphics(this, 210, 65, 2, 350, RA8875_BLACK, Figure::rect, 0, true);

	Graphics Hline1 	= Graphics(this, 0, 102, 800, 3, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline2 	= Graphics(this, 0, 166, 800, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline3 	= Graphics(this, 0, 230, 800, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline4 	= Graphics(this, 0, 294, 800, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline5 	= Graphics(this, 0, 358, 800, 2, RA8875_BLACK, Figure::rect, 0, true);

/*----------------------------------------------------------------------------------------------------- */

	Label numm = Label(this,3, 62, 60, 40, "№", Fonts::TimesNewRoman, FontForms::Bold,
					VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);
	Label Time = Label(this,65, 62, 145, 40, "Время", Fonts::TimesNewRoman, FontForms::Bold,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);
	Label Event = Label(this,210, 62, 590, 40, "Событие", Fonts::TimesNewRoman, FontForms::Bold,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);


	Label num[5] = {
		Label(this, 0, 100, 65, 70, "1", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 164, 65, 70, "2", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 228, 65, 70, "33", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 292, 65, 70, "44", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 0, 356, 65, 70, "555", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),

	};

	Label time[5] = {
			Label(this, 65, 95, 145, 85, "00:43:12 00.12.2012", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
			Label(this, 65, 157, 145, 85, "2", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
			Label(this, 65, 221, 145, 85, "33", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
			Label(this, 65, 284, 145, 85, "44", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
			Label(this, 65, 346, 145, 85, "555", Fonts::TimesNewRoman, FontForms::Normal,
				VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
	};

	Label event[5] = {
			Label(this, 215,  95, 585, 85, "",
					Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 215, 157, 585, 85, "",
					Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 215, 221, 585, 85, "",
					Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 215, 284, 585, 85, "",
					Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
			Label(this, 215, 346, 585, 85, "",
					Fonts::TimesNewRoman, FontForms::Normal, VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

	Label allEvent	= Label(this, 2, 0, 200, 60, "Всего событий: ", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Right, VALabelAlignY::CenterY);
	Label numEvent	= Label(this, 200, 0, 160, 60, "1000 / 1000", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY);

private:
	bool openControl = false;

	uint16_t counter = 0;
	uint16_t countMax = 0;
	uint16_t countMin = 0;

public:

	ScreenEvents(void)
		: BaseScreen(&Screens, "Просмотр событий")
	{

		this->bControl.SetShowed(false);
		this->bControl.addCallBack([&]() {
			if (!this->openControl) {
				this->control.Open();
				this->openControl = true;
			}
			else {
				this->control.Close();
				this->openControl = false;
			}
		});

		this->upPage.addCallBack([&]() {
			if((int)(this->counter - 5) >= this->countMin) { this->counter -= 5; }
			else { this->counter = this->countMin; }
			this->Loop();

		});

		this->up.addCallBack([&]() {
			if(this->counter - 1 >= this->countMin) { this->counter--; }
			this->Loop();
		});

		this->down.addCallBack([&]() {
			if(this->counter < this->countMax) { this->counter++; }
			this->Loop();
		});
		this->downPage.addCallBack([&]() {
			if(this->counter < (int)(this->countMax - 5)) { this->counter += 5; }
			else { this->counter = this->countMax; }
			this->Loop();
		});

//		this->allEvent.addCallBack(this, [](void* ptr) {
//			ScreenEvents* sPtr = (ScreenEvents*)ptr;
//			sPtr->addEvent(NumberCrash::EndNumber);
//		});
//		this->numEvent.addCallBack(this, [](void* ptr) {
//			eeprom.Writes(198, 2, Buf);
//			eeprom.Writes(200, MAX_COUNT_EVENT * COUNT_REG_EVENT, Buf);
//			((ScreenEvents*)ptr)->JumpTo();
//		});
	}

	void Loop(void) override {
		Event_t EventBuf[5] = {};

		if(this->numEvent.isClamped() && Screens.GetLevelAcces() == LevelsAcces::Admin) {
			EraseEvent();
		}

		this->numEvent.SetText(std::to_string(Memory[eMemory::cbEvent].U == 0 ? Memory[eMemory::nEvent].U : MAX_COUNT_EVENT) + " / " + std::to_string(MAX_COUNT_EVENT));

		if (Memory[eMemory::cbEvent].U == 0) {
			if (Memory[eMemory::nEvent].U < 4) { this->countMax = 0; }
			else if (Memory[eMemory::nEvent].U < MAX_COUNT_EVENT) {
				this->countMax = Memory[eMemory::nEvent].U - 4;
			}
			else { this->countMax = MAX_COUNT_EVENT - 5; }
		}
		else { this->countMax = MAX_COUNT_EVENT - 5; }

		for (int i = 0; i < 5; i++) {
			for (uint8_t n = 0; n < COUNT_REG_EVENT; n++) {
				*((uint16_t*)&EventBuf[i] + n) = Memory[FIRST_REG_EVENT + (this->counter + i) * COUNT_REG_EVENT + n].U;
			}
			this->num[i].SetShowed(EventBuf[i].Event != 0);
			this->time[i].SetShowed(EventBuf[i].Event != 0);
			this->event[i].SetShowed(EventBuf[i].Event != 0);
/*---------------------------- Расшифровка времени ----------------------------------------------------------- */
			uint16_t number = this->counter + Memory[eMemory::cbEvent].U * MAX_COUNT_EVENT + 1 + i;
			if (number <= Memory[eMemory::nEvent].U + Memory[eMemory::cbEvent].U * MAX_COUNT_EVENT) {
				this->num[i].SetText(number);
			}
			else {
				this->num[i].SetText(number - MAX_COUNT_EVENT);
			}

/*---------------------------- Расшифровка времени ---------------------------------------------------- */
			this->time[i].SetText(this->convertTime(EventBuf[i]));

/*---------------------------- Расшифровка событий ---------------------------------------------------- */

			if (EventBuf[i].Event < NumberCrash::LostConect) {
				this->event[i].SetText(ListEvent[EventBuf[i].Event]);
			}
			else if ( EventBuf[i].Event < NumberCrash::ConectRecovery) {
				this->event[i].SetText(ListEvent[10] + BaseDevice::Devices[EventBuf[i].Event - NumberCrash::LostConect - 1]->Name);
			}
			else if ( EventBuf[i].Event < NumberCrash::Fault) {
				this->event[i].SetText(ListEvent[11] + BaseDevice::Devices[EventBuf[i].Event - NumberCrash::ConectRecovery - 1]->Name);
			}
			else if ( EventBuf[i].Event < NumberCrash::EndNumber ) {
				this->event[i].SetText(ListEvent[12] + BaseDevice::Devices[EventBuf[i].Event - NumberCrash::Fault - 1]->Name);
			}
			else {
				this->event[i].SetText(ListEvent[EventBuf[i].Event - 80]);
			}
		}

	}

	void JumpTo(void) override {
		if (Memory[eMemory::nEvent].U < 4) {
			this->counter = 0;
		}
		else if (Memory[eMemory::nEvent].U < MAX_COUNT_EVENT) {
			this->counter = Memory[eMemory::nEvent].U - 4;
		}
		else {
			this->counter = Memory[eMemory::nEvent].U - 5;
		}

		this->Loop();
	}

	bool JumpFrom(void) override {
		this->control.Close();
		this->openControl = false;
		return true;
	}

	void addEvent(NumberCrash num) {
		Event_t Event;

		if (Memory[eMemory::nEvent].U >= MAX_COUNT_EVENT) {
			Memory[eMemory::nEvent].U = 0;
			Memory[eMemory::cbEvent].U++;

			eeprom.Write(&Memory[eMemory::nEvent].U);
			eeprom.Write(&Memory[eMemory::cbEvent].U);
		}

		Event.Hours		= Memory[rMemory::Hours].U;
		Event.Min		= Memory[rMemory::Minutes].U;
		Event.Sec		= Memory[rMemory::Seconds].U;
		Event.Day		= Memory[rMemory::Day].U;
		Event.Month		= Memory[rMemory::Month].U;
		Event.Year		= Memory[rMemory::Years].U - 2000;
		Event.Event 	= (uint16_t)num;

		eeprom.Writes(FIRST_REG_EVENT + Memory[eMemory::nEvent].U * COUNT_REG_EVENT, COUNT_REG_EVENT, (uint16_t*)&Event);
		Memory[eMemory::nEvent].U++;
		eeprom.Write(&Memory[eMemory::nEvent].U);
	}
private:
	std::string convertTime(Event_t time) {
		std::string temp = "";

		if(time.Hours < 10) temp += "0";
		temp += std::to_string(time.Hours) + ":";

		if(time.Min < 10) temp += "0";
		temp += std::to_string(time.Min) + ":";

		if(time.Sec < 10) temp += "0";
		temp += std::to_string(time.Sec) + " ";

		if(time.Day < 10) temp += "0";
		temp += std::to_string(time.Day) + ".";

		if(time.Month < 10) temp += "0";
		temp += std::to_string(time.Month) + ".";

		temp += std::to_string(time.Year + 2000);

		return temp;
	}
};


