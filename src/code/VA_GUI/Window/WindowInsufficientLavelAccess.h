/*
 * WindowInsufficientLavelAccess.h
 *
 *  Created on: Dec 3, 2020
 *      Author: anan2
 */

#pragma once

#include "VABaseWindow.h"
#include "Screens/VABaseScreen.h"

using namespace VA;

class WindowInsufficientLavelAccess : public BaseWindow {

public:

	Label l1 = Label(this, 20, 0, this->GetW()-40, 60, this->name, Fonts::TimesNewRoman, FontForms::Bold,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::Bottom);
	Graphics line1 = Graphics(this, 50, 65, this->GetW()-100 , 5, 0x0000, Figure::rect, 3, true);

	Label label = Label(this, 50, 100, this->GetW()-100, this->GetH()-170, "Выберите действие", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);

	Button bAutorization = Button(this, 50, this->GetH()-100, 250, 65, RA8875_GREEN, "Авторизация...", 10);
	Button bCencel = Button(this, this->GetW()-250, this->GetH()-100, 150, 65, RA8875_RED, "Отмена", 10);

	WindowInsufficientLavelAccess(GUI* pGUI)
		: BaseWindow("Недостаточный уровень доступа", pGUI)
	{
		this->bCencel.addCallBack([&]() {
			this->Close();
		});
		this->bAutorization.addCallBack([&]() {
			this->Close();
		});
	}
};
