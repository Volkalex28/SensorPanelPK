/*
 * VAWindow.h
 *
 *  Created on: Dec 2, 2020
 *      Author: anan2
 */

#pragma once

#include <Elements/VACanvas/VACanvas.h>
#include "Elements/Graphics/Graphics.h"

namespace VA {

class BaseWindow: public Canvas {

	Canvas back = Canvas(nullptr, 0, 0, BaseElement::ptft->width(), BaseElement::ptft->height(), this->Canvas::pGUI);
	Graphics rect1 = Graphics(this, 0, 0, 1, 1, 0x0000, Figure::rect, 0, true);
	Graphics rect2 = Graphics(this, 2, 2, 1, 1, 0xFFFF, Figure::rect, 0, true);
	Graphics rect3 = Graphics(this, 4, 4, 1, 1, 0x0000, Figure::rect, 0, true);
	Graphics rect  = Graphics(this, 8, 8, 1, 1, 0xB5B6, Figure::rect, 0, true);

protected:
	std::string name;

public:
	BaseWindow(std::string name, GUI* pGUI, uint16_t x = 100, uint16_t y = 50, uint16_t w = 600, uint16_t h = 380);

	void Open(void) override;
	void Close(void) override;
};

} /* namespace VA */
