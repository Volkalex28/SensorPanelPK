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

	ScreenCOM(void);

	void Loop(void) override;
};


