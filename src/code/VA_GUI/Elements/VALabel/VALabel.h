/*
 * VALabel.h
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: anan2
 */
#pragma once

#include "Elements/VABaseElement.h"
#include "Fonts/Fonts.h"

namespace VA {

enum VALabelScale {
	S1 = 1,
	S2,
	S3,
	S4
};
enum class VALabelAlignX {
	Left, CenterX, Right
};
enum class VALabelAlignY {
	Top, CenterY, Bottom
};

class Label: public BaseElement {
	std::string string;
	VALabelScale scale;
	VALabelAlignX aligneX;
	VALabelAlignY aligneY;
	Fonts Font;
	FontForms FontForm;
	uint16_t Colour;

	struct FillPixels {
		uint8_t count;
		uint16_t offset;
	};

	//etl::vector<etl::vector<etl::vector<etl::vector<FillPixels, 25>, 16>, 10>, 5> _string;
	//etl::vector<etl::vector<uint16_t, 10>, 5> len_string;

	void UpdateText(std::vector<std::vector<std::vector<std::vector<FillPixels>>>> & temp_string,
			std::vector<std::vector<uint16_t>> & temp_len_string);
	std::vector<uint8_t> ToWin1251(const std::string& textUTF8);
	std::vector<std::string> CutString(std::string* str, char sym);
	void StrToBitmap(const std::vector<std::string>& str,
			std::vector<std::vector<std::vector<FillPixels>>> & _string,
			std::vector<uint16_t> & len_string);

	bool converting = false;

public:
	template <typename T>
	Label(T ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h, std::string string = "", Fonts Font = Fonts::TimesNewRoman,
			FontForms FontForm = FontForms::Normal, VALabelScale scale = S2, VALabelAlignX alnX = VALabelAlignX::Left,
			VALabelAlignY alnY = VALabelAlignY::Top, uint16_t Colour = 0x00)
		: BaseElement(ptr, x, y, w, h)
	{
		this->Colour = Colour;
		this->Font = Font;
		this->FontForm = FontForm;
		this->scale = scale;
		this->aligneX = alnX;
		this->aligneY = alnY;
		this->SetText(string);
	}

	virtual void Show() override;
	void SetText(std::string string);


	void SetText(uint16_t string) {
		this->SetText(std::to_string(string));
	}

	std::string GetText(void);
};

} /* namespace VA */
