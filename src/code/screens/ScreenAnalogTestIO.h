#pragma once 

#include "Loop.h"


class ScreenAnalogTestIO : public BaseScreen {

    Indicator Input[7] = {
		Indicator(this, 35, 130, 50, 50, true),
		Indicator(this, 100, 130, 50, 50, true),
		Indicator(this, 165, 130, 50, 50, true),
		Indicator(this, 230,130, 50, 50, true),
		Indicator(this, 295, 130, 50, 50, true),
		Indicator(this, 360, 130, 50, 50, true),
        Indicator(this, 425, 130, 50, 50, true),
	};

    Indicator Output[7] = {
		Indicator(this, 35, 300, 50, 50, false),
		Indicator(this, 100, 300, 50, 50, false),
		Indicator(this, 165, 300, 50, 50, false),
		Indicator(this, 230,300, 50, 50, false),
		Indicator(this, 295, 300, 50, 50, false),
		Indicator(this, 360, 300, 50, 50, false),
        Indicator(this, 425, 300, 50, 50, false),
	};

    Label Connector[2] = {
		Label(this, 500, 125, 100, 65, "X4", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 500, 295, 100, 65, "X10", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
	};
    Label Units[14] = {
		Label(this, 40, 95, 50, 30, "I1", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 105, 95, 50, 30, "I2", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 170, 95, 50, 30, "I3", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 235, 95, 50, 30, "I4", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 300, 95, 50, 30, "I5", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 365, 95, 50, 30, "I6", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
        Label(this, 430, 95, 50, 30, "I7", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 40, 360, 50, 30, "O1", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 105, 360, 50, 30, "O2", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 170, 360, 50, 30, "O3", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 235, 360, 50, 30, "O4", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 300, 360, 50, 30, "O5", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),  
        Label(this, 365, 360, 50, 30, "O6", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),
		Label(this, 430, 360, 50, 30, "O7", Fonts::TimesNewRoman, FontForms::Normal,
			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY),   
	};

public:
	ScreenAnalogTestIO(void) : BaseScreen(&Screens, "Аналоговая плата") {
	

    }
};
