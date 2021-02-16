/*
 * VAButton.cpp
 *
 *  Created on: 11 нояб. 2020 г.
 *      Author: anan2
 */

#include "VAButton.h"

namespace VA {

void Button::Show(void) {
	if (this->r == 0) {
		BaseElement::ptft->fillRect(this->GetX(), this->GetY(), this->GetW(), this->GetH(), RA8875_BLACK);
		BaseElement::ptft->fillRect(this->GetX()+1, this->GetY()+1, this->GetW() + 1 , this->GetH() + 1, RA8875_BLACK);

		if (this->state == false) {
			BaseElement::ptft->fillRect(this->GetX() + 3,  this->GetY() + 3, this->GetW() - 6, this->GetH() - 6,
					BaseElement::ptft->Colour565To332(this->Colour));
		}
		else {
			BaseElement::ptft->fillRect(this->GetX() + 5, this->GetY() + 5, this->GetW() - 7, this->GetH() - 7,
					BaseElement::ptft->Colour565To332(this->Colour));
		}
	}
	else {
		BaseElement::ptft->fillRoundRect(this->GetX(), this->GetY(), this->GetW(), this->GetH(), this->r, RA8875_BLACK);
		BaseElement::ptft->fillRoundRect(this->GetX()+1, this->GetY()+1, this->GetW() + 1 , this->GetH() + 1, this->r, RA8875_BLACK);

		if (this->state == false) {
			BaseElement::ptft->fillRoundRect(this->GetX() + 3,  this->GetY() + 3, this->GetW() - 6, this->GetH() - 6, this->r,
					BaseElement::ptft->Colour565To332(this->Colour));
		}
		else {
			BaseElement::ptft->fillRoundRect(this->GetX() + 5, this->GetY() + 5, this->GetW() - 7, this->GetH() - 7, this->r,
					BaseElement::ptft->Colour565To332(this->Colour));
		}
	}


	this->Label::Show();
}

} /* namespace VA */
