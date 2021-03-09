/*
 * Graphics.h
 *
 *  Created on: 29 нояб. 2020 г.
 *      Author: ans0ld
 */

#pragma once

#include "Elements/VABaseElement.h"

namespace VA 
{

enum class Figure 
{
	line,
	rect,
	circle,
	elipse,
	roundrect,
	curve
};

class Graphics: public BaseElement 
{
private:
	uint16_t colour;
	uint16_t r;
	bool fill;
	Figure figure;

public:
	template <typename T>
	Graphics(T ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour,
    Figure fig, uint16_t r = 1, bool fill = false);
	Graphics(void);
	virtual void Show() override;
};

template<typename T>
Graphics::Graphics(T ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
  uint16_t colour, Figure fig, uint16_t r, bool fill) 
	: BaseElement(ptr, x, y, w, h), colour(BaseElement::ptft->Colour565To332(colour)),
    r(r), fill(fill), figure(fig)
{ /* There's nothing here */ }

} /* namespace VA */
