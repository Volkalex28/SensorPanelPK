/*
 * VAGUI.cpp
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: anan2
 */

#include "VAGUI.h"

namespace VA {

GUI::GUI(uint16_t startScreen = 1) {
	this->startScreen = startScreen;
}

void GUI::Init() {
	this->tft.begin();
	this->tft.displayOn(true);
	this->tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
	this->tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
	this->tft.touchEnable(true);
	//this->tft.PWM1out(255);

	this->JumpScreen(this->startScreen);

	this->tft.writeTo(LAYER1);
	this->tft.fillScreen(0xB5B6);
	this->tft.writeTo(LAYER2);
	this->tft.fillScreen(0xB5B6);
}

void GUI::ShowScreen() {

	static uint16_t CurrentLayer = RA8875Layers::LAYER1;

	if(this->sleep == false) {
		this->tft.writeTo((RA8875Layers)CurrentLayer);
		this->tft.fillScreen(0xB5B6);

		for(uint8_t n = 0; n < 2; n++) {
			uint16_t index = n*this->currentScreen;
			uint16_t end = this->Screens[index]->Elements.size();
			for(uint16_t i = 0; i < end; i++) {
				if (this->Screens[index]->Elements[i]->isShowed()) {
					this->Screens[index]->Elements[i]->Show();
				}
			}
			if(this->currentScreen == 0) break;
		}

		this->tft.layerEffect((RA8875Layers)CurrentLayer);

		++CurrentLayer %= RA8875Layers::LAYER_END;
	}
}

void GUI::Touched(void) {
	uint16_t x = 0, y = 0;
	static bool accessState = false;
	bool tstate = this->tft.touched();
	if(this->sleep == false) {
		this->tft.touchRead(x, y);

		x = this->tft.width() - (x - 80)*this->tft.width()/(965-80);
		y = this->tft.height() - (y - 80)*this->tft.height()/(915-80);

		for(uint8_t n = 2; n > 0; n--) {
			uint16_t index = (n-1)*this->currentScreen;

			for(uint16_t i = this->Screens[index]->Elements.size(); i > 0; i--) {
				if (this->Screens[index]->Elements[i-1]->isEnabled()) {
					bool state = (this->Screens[index]->Elements[i-1]->CheckLevelAcces(this->levelAcces)) ? tstate : false;
					if(this->Screens[index]->Elements[i-1]->Push(x, y, state)) {
						x = -1;
						if(tstate && !state) {
							accessState = true;
						}
					}
				}

			}
			if (accessState && !tstate) {
				this->InsufficientLavelAccess.Open();
				accessState = false;
			}
			if(this->currentScreen == 0) return;
		}
	}
	else if(tstate == true) {
		this->Wakeup();
	}
	if(tstate == false && this->sleep == false && osTimerIsRunning(sleepTimerHandle) == 0) {
		osTimerStart(sleepTimerHandle, this->timeOut);
	}
	if(tstate == true && this->sleep == false && osTimerIsRunning(sleepTimerHandle) == 1) {
		osTimerStop(sleepTimerHandle);
	}
}

void GUI::JumpScreen(uint16_t index) {
	if(index >= this->Screens.size())
		index = this->Screens.size() - 1;

	if(this->GetPtrCurrentScreen()->JumpFrom()) {
		this->kbr.Close();
		this->currentScreen = (index != 0) ? index : this->startScreen;
		this->GetPtrCurrentScreen()->JumpTo();
	}
}
void GUI::JumpScreen(BaseScreen* ptr) {
	uint16_t pos = std::distance(this->Screens.cbegin(), std::find(this->Screens.cbegin(), this->Screens.cend(), ptr));
	this->JumpScreen(pos);
}

void GUI::SetBackLight(uint8_t Percent) {
	this->tft.PWM1out(Percent * 1/*2.55f*/);
	this->backLight = Percent;
}
void GUI::SetTimeOut(uint8_t Min) {
	this->timeOut = Min*60000;
}

void GUI::Sleep(void) {
	this->tft.PWM1out(0);
	this->sleep = true;
	this->CloseLevelAcces();
}

void GUI::Wakeup(void) {
	this->SetBackLight(this->backLight);
	this->sleep = false;
}

RTC_TimeTypeDef _GUI_Time = {0};
RTC_DateTypeDef _GUI_Date = {0};

uint16_t GUI::GetHours(void) {
	HAL_RTC_GetTime(&hrtc, &_GUI_Time, RTC_FORMAT_BIN);
	return _GUI_Time.Hours;
}
uint16_t GUI::GetMinutes(void) {
	HAL_RTC_GetTime(&hrtc, &_GUI_Time, RTC_FORMAT_BIN);
	return _GUI_Time.Minutes;
}
uint16_t GUI::GetSeconds(void) {
	HAL_RTC_GetTime(&hrtc, &_GUI_Time, RTC_FORMAT_BIN);
	return _GUI_Time.Seconds;
}
std::string GUI::GetTime(void) {
	HAL_RTC_GetTime(&hrtc, &_GUI_Time, RTC_FORMAT_BIN);
	std::string Hours 	= std::to_string(_GUI_Time.Hours);
	std::string Minutes = std::to_string(_GUI_Time.Minutes);
	std::string Seconds = std::to_string(_GUI_Time.Seconds);
	if (_GUI_Time.Hours < 10) 	{ Hours.insert(0, "0"); }
	if (_GUI_Time.Minutes < 10) { Minutes.insert(0, "0"); }
	if (_GUI_Time.Seconds < 10) { Seconds.insert(0, "0"); }
	return (Hours + ":" + Minutes + ":" + Seconds);
}
void GUI::SetHours(uint8_t Hours) {
	if(Hours < 24) {
		this->GetHours();
		_GUI_Time.Hours = Hours;
		HAL_RTC_SetTime(&hrtc, &_GUI_Time, RTC_FORMAT_BIN);
	}
}
void GUI::SetMinutes(uint8_t Minutes) {
	if(Minutes < 60) {
		this->GetMinutes();
		_GUI_Time.Minutes = Minutes;
		HAL_RTC_SetTime(&hrtc, &_GUI_Time, RTC_FORMAT_BIN);
	}
}
void GUI::SetSeconds(uint8_t Seconds) {
	if(Seconds < 60) {
		this->GetSeconds();
		_GUI_Time.Seconds = Seconds;
		HAL_RTC_SetTime(&hrtc, &_GUI_Time, RTC_FORMAT_BIN);
	}
}

uint16_t GUI::GetYear(void) {
	HAL_RTC_GetDate(&hrtc, &_GUI_Date, RTC_FORMAT_BIN);
	return _GUI_Date.Year + 2000;
}
uint16_t GUI::GetMonth(void) {
	HAL_RTC_GetDate(&hrtc, &_GUI_Date, RTC_FORMAT_BIN);
	return _GUI_Date.Month;
}
uint16_t GUI::GetDay(void) {
	HAL_RTC_GetDate(&hrtc, &_GUI_Date, RTC_FORMAT_BIN);
	return _GUI_Date.Date;
}
std::string GUI::GetDate(void) {
	HAL_RTC_GetDate(&hrtc, &_GUI_Date, RTC_FORMAT_BIN);
	std::string Year 	= std::to_string(_GUI_Date.Year + 2000);
	std::string Month = std::to_string(_GUI_Date.Month);
	std::string Day = std::to_string(_GUI_Date.Date);
	if (_GUI_Date.Month < 10) { Month.insert(0, "0"); }
	if (_GUI_Date.Date < 10) { Day.insert(0, "0"); }
	return (Day + "." + Month + "." + Year);
}
void GUI::SetYear(uint16_t Year) {
	if(2000 <= Year && Year < 10000) {
		this->GetYear();
		_GUI_Date.Year = Year - 2000;
		HAL_RTC_SetDate(&hrtc, &_GUI_Date, RTC_FORMAT_BIN);
	}
}
void GUI::SetMonth(uint8_t Month) {
	if(1 <= Month && Month <= 12) {
		this->GetMonth();
		_GUI_Date.Month = Month;
		HAL_RTC_SetDate(&hrtc, &_GUI_Date, RTC_FORMAT_BIN);
	}
}
void GUI::SetDay(uint8_t Day) {
	if(1 <= Day && Day <= 31) {
		this->GetDay();
		_GUI_Date.Date = Day;
		HAL_RTC_SetDate(&hrtc, &_GUI_Date, RTC_FORMAT_BIN);
	}
}

bool GUI::OpenLevelAcces(uint16_t pass) {
	if(pass == UserPassword) {
		this->levelAcces = LevelsAcces::User;
	}
	else if(pass == AdminPassword) {
		this->levelAcces = LevelsAcces::Admin;
	}
	else {
		this->levelAcces = LevelsAcces::None;
		return false;
	}
	return true;
}

void GUI::CloseLevelAcces(void) {
	this->levelAcces = LevelsAcces::None;
}

LevelsAcces GUI::GetLevelAcces(void) {
	return this->levelAcces;
}

} /* namespace VA */
