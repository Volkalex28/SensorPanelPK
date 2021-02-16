/*
 * VAButton.h
 *
 *  Created on: 11 нояб. 2020 г.
 *      Author: anan2
 */

#pragma once

#include "Elements/VALabel/VALabel.h"

namespace VA {

class Button : public Label {
	uint16_t r;
public:
	uint16_t Colour;
	template <typename T>
	Button(T ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t Colour = RA8875_BLUE, std::string string = "", uint16_t r = 0)
		: Label(ptr, x, y, w, h, string, Fonts::TimesNewRoman, FontForms::Bold, VALabelScale::S2, VALabelAlignX::CenterX,
				VALabelAlignY::CenterY)
	{
		this->r = r;
		this->Colour = Colour;
	}

	virtual void Show(void) override;

};

} /* namespace VA */
