/*
 * VAIndicator.cpp
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: anan2
 */

#include "VAIndicator.h"

namespace VA {

void Indicator::Show() {
	uint16_t x = 0, y = 0;
	this->GetCenter(x, y);

	BaseElement::ptft->fillEllipse(x, y, this->GetW()/2-0, this->GetH()/2-0, BaseElement::ptft->Colour565To332(RA8875_BLACK));
	BaseElement::ptft->fillEllipse(x, y, this->GetW()/2-3, this->GetH()/2-3, BaseElement::ptft->Colour565To332(RA8875_WHITE));
	BaseElement::ptft->fillEllipse(x, y, this->GetW()/2-5, this->GetH()/2-5, BaseElement::ptft->Colour565To332(RA8875_BLACK));

	BaseElement::ptft->fillEllipse(x, y, this->GetW()/2-7, this->GetH()/2-7, BaseElement::ptft->Colour565To332((this->state) ? RA8875_GREEN : RA8875_RED));
	BaseElement::ptft->fillEllipse(x - this->GetW()/7, y - this->GetH()/7, this->GetW()/14, this->GetH()/14, BaseElement::ptft->Colour565To332(RA8875_WHITE));
}

void Indicator::CallBack() {
	if (this->indicate == true) { return; }
	this->state = !this->state;
}

} /* namespace VA */
