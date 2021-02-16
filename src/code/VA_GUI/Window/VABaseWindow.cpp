/*
 * VAWindow.cpp
 *
 *  Created on: Dec 2, 2020
 *      Author: anan2
 */

#include <Window/VABaseWindow.h>

namespace VA {

BaseWindow::BaseWindow(std::string name, GUI* pGUI, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
	: Canvas(nullptr, x, y, w, h, pGUI)
{
	this->name = name;
}

void BaseWindow::Open(void) {
	this->rect1.SetSize(this->GetW()-0, this->GetH()-0);
	this->rect2.SetSize(this->GetW()-4, this->GetH()-4);
	this->rect3.SetSize(this->GetW()-8, this->GetH()-8);
	this->rect.SetSize(this->GetW()-16, this->GetH()-16);

	this->back.Open();
	this->Canvas::Open();
}
void BaseWindow::Close(void) {

	this->Canvas::Close();
	this->back.Close();
}

} /* namespace VA */
