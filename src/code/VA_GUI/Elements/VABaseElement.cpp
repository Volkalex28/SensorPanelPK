/*
 * BaseElement.cpp
 *
 *  Created on: Nov 11, 2020
 *      Author: anan2
 */

#include "VABaseElement.h"
#include "Screens/VABaseScreen.h"
#include "Elements/VACanvas/VACanvas.h"

namespace VA {

Adafruit_RA8875* BaseElement::ptft = nullptr;

BaseElement::BaseElement(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
	this->SetSize(w, h);
	this->SetPosition(x, y);
}

BaseElement::BaseElement(std::nullptr_t ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
	: BaseElement(x, y, w, h)
{

}

BaseElement::BaseElement(BaseScreen* pScreen, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
	: BaseElement(x, y, w, h)
{
	if(pScreen != nullptr) {
		pScreen->addElement(this);
	}
}

BaseElement::BaseElement(Canvas* pCanvas, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
	if(pCanvas != nullptr) {
		this->pParentElement = pCanvas;
		pCanvas->addElement(this);
	}

	this->SetSize(w, h);
	this->SetPosition(x, y);
}
void BaseElement::CallBack(void) {

	this->ExternalCallBack();
}

bool BaseElement::isIam(uint16_t tx, uint16_t ty) {
	if(this->GetX() <= tx && tx < this->GetX() + this->w) {
		if(this->GetY() <= ty && ty < this->GetY() + this->h) {
			return true;
		}
	}
	return false;
}

bool BaseElement::Push(uint16_t tx, uint16_t ty, bool state) {

	if(this->isIam(tx, ty)) {
		if (this->state == true && state == false){
			this->CallBack();
		}
		this->state = state;
		if (this->state) {
			if(this->counterClamp > 0) {
				this->counterClamp--;
			}
			else {
				this->clamped = true;
			}
		}
		else {
			this->clamped = false;
			this->counterClamp = 10;
		}
		return true;
	}
	this->state = false;
	return false;
}
uint16_t BaseElement::GetX(void) {
	return this->x + ((this->pParentElement != nullptr) ? this->pParentElement->GetX() : 0);
}
uint16_t BaseElement::GetY(void) {
	return this->y + ((this->pParentElement != nullptr) ? this->pParentElement->GetY() : 0);
}
uint16_t BaseElement::GetW(void) {
	return this->w;
}

uint16_t BaseElement::GetH(void) {
	return this->h;
}

uint16_t BaseElement::GetCenterX(void) {
	return this->GetX() + this->w / 2;
}

uint16_t BaseElement::GetCenterY(void) {
	return this->GetY() + this->h / 2 ;
}

void BaseElement::Move(int16_t x, int16_t y) {
	if(this->x + x < 0) { this->x = x = 0; }
	if(this->y + y < 0) { this->y = y = 0; }
	this->SetPosition(this->x + x, this->y + y);
}

void BaseElement::GetCenter(uint16_t& x, uint16_t& y) {
	x = this->GetCenterX();
	y = this->GetCenterY();
}

void BaseElement::SetPosition(uint16_t x, uint16_t y) {
	uint16_t _w = 0, _h = 0;

	if (this->pParentElement != nullptr) {
		_w = this->pParentElement->GetW();
		_h = this->pParentElement->GetH();
	}
	else {
		_w = BaseElement::ptft->width();
		_h = BaseElement::ptft->height();
	}
	if(x + this->w > _w) {
		this->x = _w - this->w;
	}
	else {
		this->x = x;
	}

	if(y + this->h > _h) {
		this->y = _h - this->h;
	}
	else {
		this->y = y;
	}
}

void BaseElement::SetSize( uint16_t w, uint16_t h) {
	uint16_t _w, _h;

	if (this->pParentElement != nullptr){
		_w = this->pParentElement->GetW();
		_h = this->pParentElement->GetH();
	}
	else {
		_w = BaseElement::ptft->width();
		_h = BaseElement::ptft->height();
	}
	if (this->x + w > _w) {
		if (w > _w) {
			w = _w;
		}
	}

	this->w = w;

	if (this->y + h >_h ){
		if(h > _h) {
			h = _h;
		}
	}
	this->h = h;
	SetPosition(this->x, this->y);
}

void BaseElement::SetShowed(bool state) {
	this->showed = state;
}
bool BaseElement::isShowed(void) {
	return this->showed;
}

void BaseElement::SetLevelAcces(LevelsAcces level) {
	if(level > LevelsAcces::Admin) {
		level = LevelsAcces::Admin;
	}
	this->levelAcces = level;
}

bool BaseElement::CheckLevelAcces(LevelsAcces level) {
	return ((uint16_t)this->levelAcces <= (uint16_t)level);
}

bool BaseElement::isClamped(void) {
	return this->clamped;
}

bool BaseElement::isEnabled(void) {
	return this->enabled;
}
void BaseElement::SetEnabled(bool enabled) {
	this->enabled = enabled;
}


} /* namespace VA */
