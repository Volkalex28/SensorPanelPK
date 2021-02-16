/*
 * Canvas.h
 *
 *  Created on: 19 нояб. 2020 г.
 *      Author: ans0l
 */

#pragma once

#include <Elements/VABaseElement.h>
#include "Elements/VAButton/VAButton.h"
#include "Elements/VAIndicator/VAIndicator.h"

namespace VA {

class GUI;

class Canvas: public BaseElement {
	friend class BaseScreen;
	std::vector <BaseElement*> pEl = {};
public:

	virtual void Close(void);
	virtual void Open(void);
	void addElement(BaseElement* pElement);
	void delElement(BaseElement* pElement);

	template <typename T>
	Canvas(T ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h, GUI* pGUI)
		: BaseElement(ptr, x, y, w, h) {
		this->pGUI = pGUI;
	}
	Canvas() {};
protected:
	GUI* pGUI = nullptr;
};

}



