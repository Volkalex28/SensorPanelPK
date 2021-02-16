/*
 * GlobalSpace.cpp
 *
 *  Created on: Dec 2, 2020
 *      Author: anan2
 */

#include "GlobalSpace.h"
#include "VAGUI.h"

void GlobalSpace::Loop(void) {
	this->FooLoop();

	if(this->pGUI != nullptr) {
		this->pGUI->GetPtrCurrentScreen()->Loop();
	}
}
