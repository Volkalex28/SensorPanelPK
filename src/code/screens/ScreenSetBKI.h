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

	Label lFiderCount			= Label(this, 500, 130, 150, 100, "Количество фидеров, шт.");
//	Display dFiderCount 		= Display(this, 650, 145, 75, 60, &Memory[eMemory::Backlight].U, 3, 0, 1, 100, &Screens.kbr);

public:

	ScreenSetBKI(void) : BaseScreen(&Screens, "Параметры БКИ: ") {
//		this->bBKI.addCallBack([]() { Screens.JumpScreen(&sContrlInsulation); });
//		this->bSetBKI.addCallBack([]() { Screens.JumpScreen(&sContrlInsulation); });

	}

	void Loop(void) override {

	}

	void JumpTo(void) override {

	}
};
