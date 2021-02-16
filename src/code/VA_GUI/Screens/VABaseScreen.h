/*
 * BaseScreen.h
 *
 *  Created on: 11 нояб. 2020 г.
 *      Author: anan2
 */

#pragma once

#include <vector>
#include <algorithm>
#include <Elements/VACanvas/VACanvas.h>
#include <Elements/VAKeyboard/VAKeyboard.h>

#include "Elements/VAButton/VAButton.h"
#include "Elements/VAIndicator/VAIndicator.h"
#include "Elements/VALabel/VALabel.h"
#include "Elements/VADisplay/VADisplay.h"
#include "Elements/Graphics/Graphics.h"

namespace VA {

class BaseScreen {

	friend class GUI;
	friend class Canvas;

	std::string nameScreen = "";

	void addElement(Canvas* pEl);
	void delElement(Canvas* pEl);

	std::vector<BaseElement*> Elements = {};

public:
	BaseScreen(GUI* pGUI, std::string name);

	void addElement(BaseElement* pEl);
	void delElement(BaseElement* pEl);

	std::string GetName(void);

	virtual void Loop(void) {};

protected:
	virtual bool JumpFrom(void) {
		return true;
	}
	virtual void JumpTo(void) { }
};

} /* namespace VA */

//#endif /* VA_GUI_SCREENS_BASESCREEN_H_ */
