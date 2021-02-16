/*
 * Display.h
 *
 *  Created on: 23 нояб. 2020 г.
 *      Author: ans0ld
 */

#ifndef VA_GUI_ELEMENTS_DISPLAY_DISPLAY_H_
#define VA_GUI_ELEMENTS_DISPLAY_DISPLAY_H_

#include "Elements/VALabel/VALabel.h"

namespace VA {

class Keyboard;

class Display : public Label {

	uint16_t min = 0, max = 0;
	uint8_t N_All = 5;
	uint8_t N_point = 0;

	Keyboard* pKeyboard;
	uint16_t* pvalue = nullptr;

public:
	friend class Keyboard;
	template <typename T>
	Display(T ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t* pvalue, uint8_t N_all, uint8_t N_point,
			uint16_t min = 0, uint16_t max = 1, Keyboard* pKeyboard = nullptr)
		: Label(ptr, x, y, w, h, "", Fonts::TimesNewRoman, FontForms::Bold,
		VALabelScale::S2, VALabelAlignX::Right, VALabelAlignY::CenterY, 0x0000) {
		this->min = min;
		this->max = max;
		if (pvalue != nullptr) {
			this->pvalue = pvalue;
		}
		this->pKeyboard = pKeyboard;
		this->SetNum_format(N_all, N_point);
	}

	void SetMin(uint16_t min);
	void SetMax(uint16_t max);
	uint16_t GetMax(void);
	uint16_t GetMin(void);
	void SetNum_format(uint8_t N_all, uint8_t N_point);
	void SetValue(uint16_t pvalue);
	void SetPtr(uint16_t* ptr);
	std::string ValueConvert(uint16_t value);
	uint16_t GetValue() {
		return *this->pvalue;
	}
	uint16_t* GetPValue(void) {
		return this->pvalue;
	}

	virtual void CallBack(void) override;
	virtual void Show(void) override;
};

}

#endif /* VA_GUI_ELEMENTS_DISPLAY_DISPLAY_H_ */
