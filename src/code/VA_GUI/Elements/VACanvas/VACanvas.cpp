/*
 * Canvas.cpp
 *
 *  Created on: 19 нояб. 2020 г.
 *      Author: ans0ld
 */

#include "VACanvas.h"
#include "Screens/VABaseScreen.h"
#include "VAGUI.h"

namespace VA {

void Canvas::addElement(BaseElement* pEl) {
	if (pEl != nullptr){
		delElement(pEl);
		this->pEl.push_back(pEl);
		pEl->pParentElement = this;
	}
}
void Canvas::delElement(BaseElement* pEl) {
	this->pEl.erase(std::remove(this->pEl.begin(), this->pEl.end(), pEl), this->pEl.end());
}

void Canvas::Close(void) {
	this->pGUI->GetPtrCurrentScreen()->delElement(this);
}

void Canvas::Open(void) {
	this->pGUI->GetPtrCurrentScreen()->addElement(this);
}

}
