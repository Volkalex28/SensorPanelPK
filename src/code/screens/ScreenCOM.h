/*
 * ScreenCOM.h
 *
 *  Created on: Dec 2, 2020
 *      Author: anan2
 */

#pragma once

#include "Loop.h"

#include "WindowReboot.h"

using namespace VA;

extern WindowReboot Reboot;

class ScreenCOM : public BaseScreen {
	const std::vector<uint16_t> SpeedCOM = {48, 96, 192, 384, 576, 1152, 1280, 2304, 2560};
	uint8_t SpeedCOMindex;
	bool toEEPROMRate = false;
	bool toEEPROMParity = false;

public:

	Button bRateM 	= Button(this, 80, 100, 200, 80, 0x031f, "<< Скорость");
	Button bRateP 	= Button(this, 520, 100, 200, 80, 0x031f, "Скорость >>");
	Label lRate		= Label(this, 280, 100, 240, 80, "", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Canvas rectRate = Canvas(this, 300, 100, 200, 80, &Screens);
	Graphics rectRate1 = Graphics(&rectRate, 0, 0, rectRate.GetW()-0, rectRate.GetH()-0, 0x0000, Figure::rect, 0, false);
	Graphics rectRate2 = Graphics(&rectRate, 1, 1, rectRate.GetW()-2, rectRate.GetH()-2, 0xFFFF, Figure::rect, 0, false);
	Graphics rectRate3 = Graphics(&rectRate, 2, 2, rectRate.GetW()-4, rectRate.GetH()-4, 0xFFFF, Figure::rect, 0, false);
	Graphics rectRate4 = Graphics(&rectRate, 3, 3, rectRate.GetW()-6, rectRate.GetH()-6, 0x0000, Figure::rect, 0, false);

	Button bParityM = Button(this, 80, 200, 200, 80, 0x031f, "<< Паритет");
	Button bParityP = Button(this, 520, 200, 200, 80, 0x031f, "Паритет >>");
	Label lParity	= Label(this, 280, 200, 240, 80, "", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Canvas rectParity = Canvas(this, 300, 200, 200, 80, &Screens);
	Graphics rectParity1 = Graphics(&rectParity, 0, 0, rectParity.GetW()-0, rectParity.GetH()-0, 0x0000, Figure::rect, 0, false);
	Graphics rectParity2 = Graphics(&rectParity, 1, 1, rectParity.GetW()-2, rectParity.GetH()-2, 0xFFFF, Figure::rect, 0, false);
	Graphics rectParity3 = Graphics(&rectParity, 2, 2, rectParity.GetW()-4, rectParity.GetH()-4, 0xFFFF, Figure::rect, 0, false);
	Graphics rectParity4 = Graphics(&rectParity, 3, 3, rectParity.GetW()-6, rectParity.GetH()-6, 0x0000, Figure::rect, 0, false);

	Label lSlaveId 		= Label(this, 80, 320, 420, 50, "SlaveID Панели:");
	Display dSlaveId 	= Display(this, 350, 315, 100, 50, &Memory[eMemory::SlaveIdCOM1].U, 3, 0, 1, 255, &Screens.kbr);

	ScreenCOM(void);// : BaseScreen(&Screens, "Параметры СОМ") {

//		this->bRateM.addCallBack([&]() {
//			if(this->SpeedCOMindex - 1 >= 0) {
//				Memory[eMemory::BaudRateCOM1].U = this->SpeedCOM.at(--this->SpeedCOMindex);
//				this->toEEPROMRate = true;
//			}
//		});
//		this->bRateP.addCallBack([&]() {
//			if((uint8_t)(this->SpeedCOMindex + 1) < this->SpeedCOM.size()) {
//				Memory[eMemory::BaudRateCOM1].U = this->SpeedCOM.at(++this->SpeedCOMindex);
//				this->toEEPROMRate = true;
//			}
//		});
//		this->lRate.addCallBack([&]() {
//			if(this->toEEPROMRate) {
//				eeprom.Write(&Memory[eMemory::BaudRateCOM1].U);
//				Modbus1.SetBaudRate(Memory[eMemory::BaudRateCOM1].U*100);
//				this->toEEPROMRate = false;
//			}
//		});
//
//		this->bParityM.addCallBack([&]() {
//			if(Memory[eMemory::ParityCOM1].U - 1 >= 0) {
//				Memory[eMemory::ParityCOM1].U--;
//				this->toEEPROMParity = true;
//			}
//		});
//		this->bParityP.addCallBack([&]() {
//			if(Memory[eMemory::ParityCOM1].U < 2) {
//				Memory[eMemory::ParityCOM1].U++;
//				this->toEEPROMParity = true;
//			}
//		});
//		this->lParity.addCallBack([&]() {
//			if(this->toEEPROMParity) {
//				eeprom.Write(&Memory[eMemory::ParityCOM1].U);
//				Modbus1.SetParity((UART_Parity)Memory[eMemory::ParityCOM1].U);
//				this->toEEPROMParity = false;
//			}
//		});
//
//		this->dSlaveId.addCallBack([]() {
//			eeprom.Write(&Memory[eMemory::SlaveIdCOM1].U);
//			Modbus1.SetSlaveId(Memory[eMemory::SlaveIdCOM1].U);
//		});
//
//		this->bRateM.SetLevelAcces(LevelsAcces::User);
//		this->bRateP.SetLevelAcces(LevelsAcces::User);
//		this->bParityM.SetLevelAcces(LevelsAcces::User);
//		this->bParityP.SetLevelAcces(LevelsAcces::User);
//		this->dSlaveId.SetLevelAcces(LevelsAcces::User);
//	}

	void Loop(void) override {

		for(	this->SpeedCOMindex = 0;
				this->SpeedCOM[this->SpeedCOMindex] != Memory[eMemory::BaudRateCOM1].U &&
						this->SpeedCOMindex < this->SpeedCOM.size();
				this->SpeedCOMindex++
			);
		if(this->SpeedCOMindex == this->SpeedCOM.size()) {
			this->SpeedCOMindex = 0;
		}

		this->lRate.SetText(std::to_string(Memory[eMemory::BaudRateCOM1].U*100));

		if(Memory[eMemory::ParityCOM1].U == (uint16_t)UART_Parity::None) { this->lParity.SetText("Нет\n(None)"); }
		else if(Memory[eMemory::ParityCOM1].U == (uint16_t)UART_Parity::Odd) { this->lParity.SetText("Нечетный\n(Odd)"); }
		else { this->lParity.SetText("Четный\n(Even)"); }

		static bool rate = false;
		if(this->toEEPROMRate) {
			if(!rate) {
				this->rectRate.Open();
				this->addElement(&this->lRate);
				rate = true;
			}
		}
		else {
			this->rectRate.Close();
			rate = false;
		}

		static bool parity = false;
		if(this->toEEPROMParity) {
			if(!parity) {
				this->rectParity.Open();
				this->addElement(&this->lParity);
				parity = true;
			}
		}
		else {
			this->rectParity.Close();
			parity = false;
		}
	}
};


