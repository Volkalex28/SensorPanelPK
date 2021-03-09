#pragma once

#include "Loop.h"

class ScreenAnalogCoef : public BaseScreen {
    uint16_t val = 0;
    Label label[8] = {
		Label(this, 65, 90, 135, 65, "Вход Х1", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 65, 140, 135, 65, "Вход Х2", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 65, 190, 135, 65, "Вход Х3", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
        Label(this, 65, 240, 135, 65, "Вход Х11", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 65, 290, 135, 65, "Вход Х12", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 65, 340, 135, 65, "Вход Х13", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
        Label(this, 210, 55, 160, 65, "Значение", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 375, 55, 135, 65, "Коэф-т", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};

    Display dValue[6] 			= {
		 Display(this, 210, 100, 100, 40, &val, 4, 1, 0, 00, nullptr),
		 Display(this, 210, 150, 100, 40, &val, 4, 1, 0, 00, nullptr),
		 Display(this, 210, 200, 100, 40, &val, 4, 1, 0, 00, nullptr),
		 Display(this, 210, 250, 100, 40, &val, 4, 1, 0, 00, nullptr),
		 Display(this, 210, 300, 100, 40, &val, 4, 1, 0, 00, nullptr),
		 Display(this, 210, 350, 100, 40, &val, 4, 1, 0, 00, nullptr),

	};
    Display dCoef[6] 			= {
		 Display(this, 375, 100, 100, 40, &Memory[eMemory::CoefX1].U, 4, 1, 0, 32000, &Screens.kbr),
		 Display(this, 375, 150, 100, 40, &Memory[eMemory::CoefX2].U, 4, 1, 0, 32000, &Screens.kbr),
		 Display(this, 375, 200, 100, 40, &Memory[eMemory::CoefX3].U, 4, 1, 0, 32000, &Screens.kbr),
		 Display(this, 375, 250, 100, 40, &Memory[eMemory::CoefX11].U, 4, 1, 0, 32000, &Screens.kbr),
		 Display(this, 375, 300, 100, 40, &Memory[eMemory::CoefX12].U, 4, 1, 0, 32000, &Screens.kbr),
		 Display(this, 375, 350, 100, 40, &Memory[eMemory::CoefX13].U, 4, 1, 0, 32000, &Screens.kbr),
	};

public:
	ScreenAnalogCoef(void) : BaseScreen(&Screens, "Коэффициенты") {

    }
};

