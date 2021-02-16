/*
 * Keyboard.h
 *
 *  Created on: 23 нояб. 2020 г.
 *      Author: ans0l
 */

#ifndef VA_GUI_ELEMENTS_VAKEYBOARD_VAKEYBOARD_H_
#define VA_GUI_ELEMENTS_VAKEYBOARD_VAKEYBOARD_H_

#include "Elements/VACanvas/VACanvas.h"
#include "Elements/VADisplay/VADisplay.h"

namespace VA {

class GUI;

class Keyboard: public Canvas {

	std::string str = "0";
	uint16_t tempval = 0;
	Display* pval = nullptr;
	bool point = false;
	uint8_t first_n = 0;

	void UpdateVal(char val);

//	uint32_t maxVal = 40100;
//	uint32_t minVal = 10300;
//
//	uint8_t N_All = 5;
//	uint8_t N_point = 2;

	virtual void Show(void) override;


public:
	//friend class Display;
	void Close(void) override;
	void Open(Display* pDisp);

	uint16_t colour = 0xA534;
	Button B7 = Button(this, 5 + 4, 	70, 80, 60, colour, "7");
	Button B8 = Button(this, 90 + 4, 	70, 80, 60, colour, "8");
	Button B9 = Button(this, 175 + 4, 	70, 80, 60, colour, "9");
	Button B4 = Button(this, 5 + 4, 	135, 80, 60, colour, "4");
	Button B5 = Button(this, 90 + 4, 	135, 80, 60, colour, "5");
	Button B6 = Button(this, 175 + 4, 	135, 80, 60, colour, "6");
	Button B1 = Button(this, 5 + 4, 	200, 80, 60, colour, "1");
	Button B2 = Button(this, 90 + 4, 	200, 80, 60, colour, "2");
	Button B3 = Button(this, 175 + 4, 	200, 80, 60, colour, "3");
	Button B0 = Button(this, 5 + 4, 	265, 80, 60, colour, "0");
	Button Bp = Button(this, 90 + 4, 	265, 80, 60, colour, ".");
	Button BPM = Button(this, 175 + 4, 	265, 80, 60, colour, "±");
	Button BESC = Button(this, 5 + 4, 	330, 80, 60, colour, "ESC");
	Button BClr = Button(this, 90 + 4, 	330, 80, 60, colour, "Clr");
	Button BEnt = Button(this, 175 + 4,	330, 80, 60, colour, "Ent");
	Label LbMin = Label(this, 18, 18, 100, 38, "Min:", Fonts::TimesNewRoman, FontForms::Italic, VALabelScale::S1, VALabelAlignX::Left, VALabelAlignY::Bottom, 0xffff);
	Label LbMax = Label(this, 18, 18, 100, 38, "Max:", Fonts::TimesNewRoman, FontForms::Italic, VALabelScale::S1, VALabelAlignX::Left, VALabelAlignY::Top, 0xffff);
	Label MinVal = Label(this, 60, 18, 100, 38, "0", Fonts::TimesNewRoman, FontForms::Italic, VALabelScale::S1, VALabelAlignX::Left, VALabelAlignY::Bottom, 0xffff);
	Label MaxVal = Label(this, 60, 18, 100, 38, "0", Fonts::TimesNewRoman, FontForms::Italic, VALabelScale::S1, VALabelAlignX::Left, VALabelAlignY::Top, 0xffff);
	Label Value = Label(this, 50, 18, 180, 38, "0", Fonts::TimesNewRoman, FontForms::Bold, VALabelScale::S2, VALabelAlignX::Right, VALabelAlignY::CenterY, 0xffff);

	Keyboard(GUI* pGUI);

	void BPM_Call(void);
	void BESC_Call(void);
	void BClr_Call(void);
	void BEnt_Call(void);

	void SetMax(uint32_t max);
	void SetMin(uint32_t min);
};

} /* namespace VA */

#endif /* VA_GUI_ELEMENTS_VAKEYBOARD_VAKEYBOARD_H_ */
