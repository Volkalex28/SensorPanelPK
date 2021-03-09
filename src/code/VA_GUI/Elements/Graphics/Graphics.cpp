/*
 * Graphics.cpp
 *
 *  Created on: 29 нояб. 2020 г.
 *      Author: ans0ld
 */

#include "Elements/Graphics/Graphics.h"

namespace VA 
{

Graphics::Graphics(void) 
{ /* There's nothing here */ }

void Graphics::Show() 
{
	switch(this->figure) 
  {
	case Figure::line :
		BaseElement::ptft->drawLine(this->GetX(), this->GetY(), this->GetX() + this->GetW(),
      this->GetY() + this->GetH(), this->colour);
		break;

	case Figure::rect :
		if(this->fill == false) {
			BaseElement::ptft->drawRect(this->GetX(),this->GetY(), this->GetW(), this->GetH(), this->colour);
		}
		else
			BaseElement::ptft->fillRect(this->GetX(),this->GetY(), this->GetW(), this->GetH(), this->colour);
		break;
	case Figure::circle :
		if (this->fill== false) {
			BaseElement::ptft->drawCircle(this->GetX(),this->GetY(), this->r, this->colour);
		}
		else
			BaseElement::ptft->fillCircle(this->GetX(),this->GetY(), this->r, this->colour);
		break;
	case Figure::elipse :
		if (this->fill== false) {
			BaseElement::ptft->drawEllipse(this->GetX(),this->GetY(), this->GetW(), this->GetH(), this->colour);
		}
		else
			BaseElement::ptft->fillEllipse(this->GetX(),this->GetY(), this->GetW(), this->GetH(), this->colour);
		break;
	case Figure::roundrect :
		if (this->fill== false) {
			BaseElement::ptft->drawRoundRect(this->GetX(),this->GetY(), this->GetW(), this->GetH(), this->r, this->colour);
		}
		else
			BaseElement::ptft->fillRoundRect(this->GetX(),this->GetY(), this->GetW(), this->GetH(), this->r, this->colour);
		break;
	case Figure::curve :
		if (this->fill== false) {
			BaseElement::ptft->drawCurve(this->GetX() + this->GetW(), this->GetY() + this->GetH(), this->GetW(), this->GetH(), this->r, this->colour);
		}
		else
			BaseElement::ptft->fillCurve(this->GetX(), this->GetY(), this->GetW(), this->GetH(), this->r, this->colour);
		break;
	}

}


}
