/*
 * Keyboard.cpp
 *
 *  Created on: 23 нояб. 2020 г.
 *      Author: ans0l
 */

#include <Elements/VAKeyboard/VAKeyboard.h>
#include "VAGUI.h"

namespace VA {

Keyboard::Keyboard(GUI* pGUI)
	: Canvas(nullptr, 50, 20, 268, 400, pGUI)
{
	this->B0.addCallBack([&]() { this->UpdateVal(0); });
	this->B1.addCallBack([&]() { this->UpdateVal(1); });
	this->B2.addCallBack([&]() { this->UpdateVal(2); });
	this->B3.addCallBack([&]() { this->UpdateVal(3); });
	this->B4.addCallBack([&]() { this->UpdateVal(4); });
	this->B5.addCallBack([&]() { this->UpdateVal(5); });
	this->B6.addCallBack([&]() { this->UpdateVal(6); });
	this->B7.addCallBack([&]() { this->UpdateVal(7); });
	this->B8.addCallBack([&]() { this->UpdateVal(8); });
	this->B9.addCallBack([&]() { this->UpdateVal(9); });
	this->Bp.addCallBack([&]() { this->UpdateVal('.'); });
	this->BPM.addCallBack(this, &Keyboard::BPM_Call);
	this->BESC.addCallBack(this, &Keyboard::BESC_Call);
	this->BClr.addCallBack(this, &Keyboard::BClr_Call);
	this->BEnt.addCallBack(this, &Keyboard::BEnt_Call);
}

void Keyboard::UpdateVal(char val) {

	if(val < 10) {
		if(this->str[0] == '0' && !this->point) {
			this->str = "";
		}
		if(this->str.length() < (uint8_t)((this->point) ? \
				this->pval->N_point + this->first_n : \
				this->pval->N_All - this->pval->N_point))
		{
			this->str += std::to_string(val);
		}
	}
	if(val == '.' && this->str.size() < this->pval->N_All) {
		if(!this->point && this->str.length() > 0) {
			this->str += ".";
			this->point = true;
			this->first_n = std::distance(this->str.begin(), this->str.end());
		}
	}
	this->Value.SetText(this->str);
}

void Keyboard::Show(void) {

	BaseElement::ptft->fillRoundRect(this->GetX(), this->GetY(), this->GetW(), this->GetH(), 10, BaseElement::ptft->Colour565To332(0x00));
	BaseElement::ptft->fillRoundRect(this->GetX() + 2, this->GetY() + 2, this->GetW() - 4, this->GetH() - 4, 10, BaseElement::ptft->Colour565To332(0x73CE));
	BaseElement::ptft->fillRoundRect(this->GetX() + 9, this->GetY() + 9 , this->GetW() - 18, 56, 5, BaseElement::ptft->Colour565To332(0x0000));
}

void Keyboard::Close(void) { this->BESC_Call(); }
void Keyboard::Open(Display* pDisp) {

	if(pDisp != nullptr) {
		this->pval = pDisp;

		if(pDisp->GetX() > 400) {
			this->SetPosition(20, 10);
		}
		else {
			this->SetPosition(522, 10);
		}

		this->MaxVal.SetText(this->pval->ValueConvert(this->pval->max));
		this->MinVal.SetText(this->pval->ValueConvert(this->pval->min));

		this->Canvas::Open();
	}
}

void Keyboard::BPM_Call(void) {
//	BaseScreen::GetPtrGUI()->kbr.str += "±";
//	BaseScreen::GetPtrGUI()->kbr.Value.SetText(BaseScreen::GetPtrGUI()->kbr.str);
}
void Keyboard::BESC_Call(void) {
	this->Canvas::Close();
	this->BClr_Call();
}
void Keyboard::BClr_Call(void) {
	this->str = "0";
	this->point = false;
	this->first_n = 0;
	this->UpdateVal(0);
}
void Keyboard::BEnt_Call(void) {

	float input = std::stof(this->Value.GetText());
	float Max = std::stof(this->MaxVal.GetText());
	float Min = std::stof(this->MinVal.GetText());

	if(Min <= input && input <= Max && this->pval != nullptr) {
		this->pval->SetValue(input * powf(10, this->pval->N_point));

		this->BESC_Call();
		this->pval->BaseElement::CallBack();

		this->pval = nullptr;
	}
}

void Keyboard::SetMin(uint32_t min) {
	std::string temp = std::to_string(min);
	this->MinVal.SetText(temp);
}

void Keyboard::SetMax(uint32_t max) {
	std::string temp = std::to_string(max);
	this->MaxVal.SetText(temp);
}

} /* namespace VA */
