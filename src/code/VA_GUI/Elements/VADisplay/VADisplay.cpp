/*
 * Display.cpp
 *
 *  Created on: 23 нояб. 2020 г.
 *      Author: ans0ld
 */

#include "Elements/VADisplay/VADisplay.h"
#include "VAGUI.h"

namespace VA {

void Display::Show(void) {

	BaseElement::ptft->drawRect(this->GetX(), this->GetY(), this->GetW() + 7 , this->GetH(), RA8875_BLACK);
	BaseElement::ptft->drawRect(this->GetX() + 1, this->GetY() + 1, this->GetW() + 5 , this->GetH() -  2, RA8875_BLACK);

	if(!this->BaseElement::state) {
		BaseElement::ptft->drawRect(this->GetX() + 2, this->GetY() + 2, this->GetW() + 3 , this->GetH() - 4, RA8875_WHITE);
		BaseElement::ptft->drawRect(this->GetX() + 3, this->GetY() + 3, this->GetW() + 1, this->GetH() -  6, RA8875_WHITE);
	}
	else {
		BaseElement::ptft->drawRect(this->GetX() + 2, this->GetY() + 2, this->GetW() + 3 , this->GetH() - 4,
				BaseElement::ptft->Colour565To332(0x031f));
		BaseElement::ptft->drawRect(this->GetX() + 3, this->GetY() + 3, this->GetW() + 1, this->GetH() -  6,
				BaseElement::ptft->Colour565To332(0x031f));
	}

	BaseElement::ptft->drawRect(this->GetX() + 4, this->GetY() + 4, this->GetW() - 1 , this->GetH() -  8, RA8875_BLACK);
	BaseElement::ptft->drawRect(this->GetX() + 5, this->GetY() + 5, this->GetW() - 3 , this->GetH() -  10, RA8875_BLACK);

	std::string temp = "";
	if(this->pvalue != nullptr)
		temp = this->ValueConvert(*this->pvalue);
	this->SetText(temp);
	this->Label::Show();
}

void Display::CallBack(void) {

	if (this->pKeyboard != nullptr) {
		this->pKeyboard->Open(this);
	}
}

uint16_t Display::GetMax(void){
	return this->max;
}
uint16_t Display::GetMin(void){
	return this->min;
}
void Display::SetMax(uint16_t max){
	this->max = max;
}

void Display::SetMin(uint16_t min){
	this->min = min;
}

void Display::SetNum_format(uint8_t N_All, uint8_t N_point){
	if (N_All > 0 && N_All <= 5) {
		this->N_All = N_All;
		if (N_point < N_All) {
			this->N_point = N_point;
		}
	}
}

void Display::SetValue(uint16_t pvalue) {
	*this->pvalue = pvalue;
}

std::string Display::ValueConvert(uint16_t value) {

	std::string temp = std::to_string(value);

	for(int i = 0; temp.length() <= this->N_point; i++) {
		temp.insert(0, "0");
	}
	if(this->N_point > 0) {
		temp.insert(temp.length() - this->N_point, ".");
	}
	return temp;
}

void Display::SetPtr(uint16_t* ptr) {
	this->pvalue = ptr;
}

} /* namespace VA */
