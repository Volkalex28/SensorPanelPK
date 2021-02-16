/*
 * WindowReboot.h
 *
 *  Created on: Dec 2, 2020
 *      Author: anan2
 */

#pragma once

#include "Loop.h"
#include "VAGUI.h"

using namespace VA;

class WindowReboot : public BaseWindow {

public:

	Label l1 = Label(this, 20, 0, this->GetW()-40, 60, this->name, Fonts::TimesNewRoman, FontForms::Bold,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::Bottom);
	Graphics line1 = Graphics(this, 50, 65, this->GetW()-100 , 5, 0x0000, Figure::rect, 3, true);

	Label label = Label(this, 50, 100, this->GetW()-100, this->GetH()-170, "", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::Top);

	Button bYes = Button(this, 100, this->GetH()-100, 150, 65, RA8875_GREEN, "Да", 10);
	Button bNot = Button(this, this->GetW()-250, this->GetH()-100, 150, 65, RA8875_RED, "Нет", 10);

	WindowReboot(void)
		: BaseWindow("Перезагрузка панели", &Screens)
	{
		this->bNot.addCallBack([&]() {
			this->Close();
		});
		this->bYes.addCallBack([]() {
			NVIC_SystemReset();
		});
		this->label.SetText("Для применения измененеий необходимо перезагрузить панель\n\nПерезагрузить?");
	}
};



