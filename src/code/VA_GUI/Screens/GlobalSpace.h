/*
 * GlobalSpace.h
 *
 *  Created on: Dec 1, 2020
 *      Author: anan2
 */

#pragma once

#include "VABaseScreen.h"

using namespace VA;

class GlobalSpace: public BaseScreen {
	BaseElement::Callback FooLoop;

	GUI* pGUI;
public:
	template<class T>
	void setInfLoop(T* pObj, void (T::*pFoo)(void)) {
		this->FooLoop.add(pObj, pFoo);
	}

	void Loop(void) override;

	GlobalSpace(GUI* pGUI) : BaseScreen(pGUI, "") {
		this->pGUI = pGUI;
	}
};
