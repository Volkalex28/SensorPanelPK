/*
 * VAGUI.h
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: anan2
 */

#pragma once

#include "stdint.h"
#include <vector>

#include "Elements/VABaseElement.h"
#include "Screens/VABaseScreen.h"
#include "Window/VABaseWindow.h"
#include "Screens/GlobalSpace.h"

#include "Window/WindowInsufficientLavelAccess.h"

#define UserPassword 7496
#define AdminPassword 2280

namespace VA {

class GUI {

	Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_800x480);
	std::vector<BaseScreen*> Screens = {};

	uint16_t startScreen = 0;

	bool sleep = false;
	uint16_t backLight = 100;
	uint32_t timeOut = 1000;
	uint16_t currentScreen = 0;

	LevelsAcces levelAcces = LevelsAcces::None;

public:

	GUI(uint16_t startScreen);

	BaseScreen* GetPtrCurrentScreen(void) {
		return this->Screens[this->currentScreen];
	}

	GlobalSpace Global = GlobalSpace(this);
	Keyboard kbr = Keyboard(this);

	WindowInsufficientLavelAccess InsufficientLavelAccess =
			WindowInsufficientLavelAccess(this);

	void Init(void);
	void ShowScreen(void);
	void Touched(void);

	void JumpScreen(uint16_t index);
	void JumpScreen(BaseScreen* ptr);
	void SetBackLight(uint8_t Percent);
	void SetTimeOut(uint8_t Min);
	void Sleep(void);
	void Wakeup(void);

	uint16_t GetHours(void);
	uint16_t GetMinutes(void);
	uint16_t GetSeconds(void);
	std::string GetTime(void);
	void SetHours(uint8_t Hours);
	void SetMinutes(uint8_t Minutes);
	void SetSeconds(uint8_t Seconds);

	uint16_t GetYear(void);
	uint16_t GetMonth(void);
	uint16_t GetDay(void);
	std::string GetDate(void);
	void SetYear(uint16_t Year);
	void SetMonth(uint8_t Month);
	void SetDay(uint8_t Day);

	bool OpenLevelAcces(uint16_t pass);
	void CloseLevelAcces(void);
	LevelsAcces GetLevelAcces(void);

	friend class BaseScreen;
	friend class Canvas;
};

} /* namespace VA */
