#pragma once

#include "Loop.h"

using namespace VA;



class ScreenSetAnalogPl : public BaseScreen {

	uint16_t val = 0;
public:

	Graphics Vline1 	= Graphics(this, 180, 65, 2, 350, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Vline2 	= Graphics(this, 490, 105, 2, 310, RA8875_BLACK, Figure::rect, 0, true);
    Graphics Vline3 	= Graphics(this, 335, 150, 2, 265, RA8875_BLACK, Figure::rect, 0, true);
    Graphics Vline4 	= Graphics(this, 645, 150, 2, 265, RA8875_BLACK, Figure::rect, 0, true);
    
	Graphics Hline1 	= Graphics(this, 0, 195, 800, 2, RA8875_BLACK, Figure::rect, 0, true);
	Graphics Hline2 	= Graphics(this, 180, 105, 620, 2, RA8875_BLACK, Figure::rect, 0, true);
    Graphics Hline3 	= Graphics(this, 180, 150, 620, 2, RA8875_BLACK, Figure::rect, 0, true);

	Label lVoltage		= Label(this, 180, 65, 620, 45, "Напряжение",  Fonts::TimesNewRoman, FontForms::Normal,
	 						VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lWarning 		= Label(this, 180, 105, 310, 45, "Предупрежрение",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lCrash 	    = Label(this, 490, 105, 310, 45, "Авария",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lBusI		    = Label(this, 0, 205, 180, 70, "Шина ±ЕСI",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lBusII	    = Label(this, 0, 275, 180, 70, "Шина ±ЕСII",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label lAB		    = Label(this, 0, 345, 180, 70, "АБ",  Fonts::TimesNewRoman, FontForms::Normal,
							VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);

    Label label[4] = {
		Label(this, 180, 150, 155, 45, "Min", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 335, 150, 155, 45, "Max", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
		Label(this, 490, 150, 155, 45, "Min", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
        Label(this, 645, 150, 155, 45, "Max", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY),
	};

    Display disp[10] = {
		Display(this, 205, 215, 105, 40, &Memory[eMemory::MinSetWarnEC1].U, 4, 1, min, max, &Screens.kbr),
		Display(this, 360, 215, 105, 40, &Memory[eMemory::MaxSetWarnEC1].U, 4, 1, min, max, &Screens.kbr),
		Display(this, 515, 215, 105, 40, &Memory[eMemory::MinSetCrashEC1].U, 4, 1, min, max, &Screens.kbr),
		Display(this, 670, 215, 105, 40, &Memory[eMemory::MaxSetCrashEC1].U, 4, 1, min, max, &Screens.kbr),
		Display(this, 205, 285, 105, 40, &Memory[eMemory::MinSetWarnEC2].U, 4, 1, min, max, &Screens.kbr),
		Display(this, 360, 285, 105, 40, &Memory[eMemory::MaxSetWarnEC2].U, 4, 1, min, max, &Screens.kbr),
		Display(this, 515, 285, 105, 40, &Memory[eMemory::MinSetCrashEC2].U, 4, 1, min, max, &Screens.kbr),
		Display(this, 670, 285, 105, 40, &Memory[eMemory::MaxSetCrashEC2].U, 4, 1, min, max, &Screens.kbr),
        Display(this, 205, 355, 105, 40, &Memory[eMemory::MinSetWarnAB].U, 4, 1, min, max, &Screens.kbr),
		Display(this, 515, 355, 105, 40, &Memory[eMemory::MinSetCrashAB].U, 4, 1, min, max, &Screens.kbr),
	};

	ScreenSetAnalogPl(void) : BaseScreen(&Screens, "Уставки") {


	}
};