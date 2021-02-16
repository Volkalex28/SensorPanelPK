/*
 * BaseScreen.cpp
 *
 *  Created on: 11 нояб. 2020 г.
 *      Author: anan2
 */

#include "VABaseScreen.h"
#include "VAGUI.h"

namespace VA {

BaseScreen::BaseScreen(GUI* pGUI, std::string name) {
	this->nameScreen = name;
	if(pGUI != nullptr) {
		pGUI->Screens.push_back(this);
		BaseElement::ptft = &pGUI->tft;
	}
}

void BaseScreen::addElement(BaseElement* pEl) {
	this->delElement(pEl);
	this->Elements.push_back(pEl);
}
void BaseScreen::delElement(BaseElement* pEl) {
	this->Elements.erase(std::remove(this->Elements.begin(), this->Elements.end(), pEl), this->Elements.end());
}
void BaseScreen::addElement(Canvas* pEl) {
	this->addElement((BaseElement*)pEl);
	for (uint16_t i = 0; i < pEl->pEl.size(); i++) {
		this->addElement(pEl->pEl[i]);
	}
}
void BaseScreen::delElement(Canvas* pEl) {
	this->delElement((BaseElement*)pEl);
	for (uint16_t i = 0; i < pEl->pEl.size(); i++) {
		this->delElement(pEl->pEl[i]);
	}
}

std::string BaseScreen::GetName(void) {
	return this->nameScreen;
}

} /* namespace VA */
