/*
 * ScreenAutorization.h
 *
 *  Created on: Dec 3, 2020
 *      Author: anan2
 */

#pragma once

#include "Loop.h"

using namespace VA;

class ScreenAutorization : public BaseScreen {
	uint16_t pass = 0;

	class WindowInfo : public BaseWindow {

		Label label = Label(this, 0, 0, this->GetW(), this->GetH()-170, "", Fonts::TimesNewRoman, FontForms::Normal,
					VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY);
		Button bClose = Button(this, 59, this->GetH()-100, 150, 65, 0x031f, "Закрыть", 10);

	public:
		WindowInfo(void) : BaseWindow("", &Screens, 522, 70, 268, 340) {
			this->bClose.addCallBack([&]() {
				this->Close();
			});
		}

		void Open(std::string text) {
			label.SetText(text);
			this->BaseWindow::Open();
		}
	} Info;

public:

	Button bOpen	= Button(this, 300, 100, 200, 75, 0x031f, "Открыть доступ");
	Button bClose	= Button(this, 300, 200, 200, 75, 0x031f, "Закрыть доступ");
	Display disp	= Display(nullptr, 500, 0, 1, 1, &this->pass, 4, 0, 0, 9999);

	ScreenAutorization(void)
		: BaseScreen(&Screens, "Авторизация")
	{
		this->bOpen.addCallBack([&]() {
			Screens.kbr.Open(&this->disp);
		});
		this->bClose.addCallBack([&]() {
			Screens.CloseLevelAcces();
			this->Info.Open("Доступ закрыт");
		});
		this->disp.addCallBack([&]() {
			Screens.OpenLevelAcces(this->pass) ? this->Info.Open("Доступ открыт") : this->Info.Open("Неверный пароль");
		});

		Screens.InsufficientLavelAccess.bAutorization.addCallBack([&]() {
			Screens.JumpScreen(this);
			this->bOpen.CallBack();
		});
	}
};


