/*
 * VALabel.cpp
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: anan2
 */

#include "VALabel.h"

namespace VA
{

// 1 - 15 * 30
// 2 - 24 * 48
// 3 - 32 * 64
void Label::Show()
{

	uint16_t n_col_space = GetPtrFont(this->Font, this->FontForm)[0x20][0];

	std::vector<std::vector<std::vector<std::vector<FillPixels>>>> _string;
	std::vector<std::vector<uint16_t>> len_string;

	this->UpdateText(_string, len_string);

	for(uint8_t i = 0; i < _string.size(); i++) {

		int16_t length = 0;
		for(uint8_t n = 0; n < len_string[i].size(); n++) {
			length += len_string[i][n];
		}
		length += n_col_space*(len_string[i].size()-1);
		//if(length < 0) length = 0;

		int16_t x = 0, y = 0;

		switch(this->aligneX) {
		case VALabelAlignX::Left :
			x = this->GetX();
			break;
		case VALabelAlignX::CenterX :
			x = this->GetCenterX() - length * this->scale / 2;
			break;
		case VALabelAlignX::Right :
			x = this->GetX() + this->GetW() - length * this->scale;
			break;
		}
		switch(this->aligneY) {
		case VALabelAlignY::Top :
			y = this->GetY() + this->scale * 16 * i;
			break;
		case VALabelAlignY::CenterY :
			y = this->GetY() + this->GetH() / (_string.size() + 1) * (i + 1) - this->scale * 8;
			break;
		case VALabelAlignY::Bottom :
			y = this->GetY() + this->GetH() - this->scale * 16 * (_string.size() - i);
			break;
		}
		uint16_t len = 0;
		uint16_t n_end = _string[i].size();
		for(uint8_t n = 0; n < n_end; n++)
		{
			for(uint8_t row = 0; row < 16; row++) for(uint8_t col = 0; col < _string[i][n][row].size(); col++)
			{
				for(uint8_t py = 0; py < this->scale; py++)
				{
					BaseElement::ptft->drawPixels(this->Colour,
						this->scale*_string[i][n][row][col].count,
						x + this->scale*(_string[i][n][row][col].offset + len),
						y + row*this->scale + py);
				}
			}
			len += len_string[i][n] + n_col_space;
		}
	}
}

std::string Label::GetText(void) { return this->string; }

void Label::SetText(std::string string) { this->string = string; }

void Label::UpdateText(std::vector<std::vector<std::vector<std::vector<FillPixels>>>> & temp_string,
	std::vector<std::vector<uint16_t>> & temp_len_string)
{

	std::vector<std::string> str = this->CutString(&this->string, '\n');
	for(uint16_t i = 0; i < str.size(); i++)
	{
		temp_string.push_back(std::vector<std::vector<std::vector<FillPixels>>>());
		temp_len_string.push_back(std::vector<uint16_t>());

		std::vector<std::string> words = this->CutString(&str[i], ' ');
		this->StrToBitmap(words, temp_string[i], temp_len_string[i]);

		uint16_t n_col_space = GetPtrFont(this->Font, this->FontForm)[0x20][0];
		for(uint16_t j = 0; j < temp_string.size(); j++)
		{
			uint16_t length = 0;
			for(uint8_t n = 0; n < temp_string[j].size(); n++)
			{
				if(length + temp_len_string[j][n] * this->scale <= this->GetW() || length == 0)
				{
					length += (temp_len_string[j][n] + n_col_space) * this->scale;
				}
				else
				{
					std::vector<std::vector<std::vector<FillPixels>>> temp(temp_string[j].begin() + n, temp_string[j].end());
					std::vector<uint16_t> len_temp(temp_len_string[j].begin() + n, temp_len_string[j].end());

					temp_string[j].erase(temp_string[j].begin() + n, temp_string[j].end());
					temp_len_string[j].erase(temp_len_string[j].begin() + n, temp_len_string[j].end());

					temp_string.insert(temp_string.begin() + j + 1, temp);
					temp_len_string.insert(temp_len_string.begin() + j + 1, len_temp);

					break;
				}
			}
		}
	}
}

void Label::StrToBitmap(const std::vector<std::string>& str, std::vector<std::vector<std::vector<FillPixels>>>& _string,
		std::vector<uint16_t>& len_string)
{

	TCLISTP* pFont = GetPtrFont(this->Font, this->FontForm);
	for (const auto& word : str) {
		std::vector<uint8_t> nums_sym = this->ToWin1251(word);

		std::vector<std::vector<FillPixels>> str_row_fillpixels(16, std::vector<FillPixels>(0));

		uint16_t len = 0;
		for(const auto& symbol : nums_sym)
		{
			uint8_t n_col = pFont[symbol][0];
			uint8_t n_bytes = (n_col+7)/8;

			for(int row = 0; row < 16; row++)
			{
				uint32_t sym = 0;
				for(uint8_t byte = 0; byte < n_bytes; byte++)
				{
					sym += (pFont[symbol][1 + byte + row*n_bytes] << (byte*8));
				}
				bool pixel = false;
				for(uint8_t col = 0; col < n_col+1; col++)
				{
					if(sym & (1 << col) && !pixel)
					{
						pixel = true;
						FillPixels temp;
						temp.offset = col + len;
						temp.count = 0;
						str_row_fillpixels[row].push_back(temp);
					}
					if(!(sym & (1 << col)) && pixel) { pixel = false; }
					if(pixel)
					{
						str_row_fillpixels[row][str_row_fillpixels[row].size()-1].count++;
					}
				}
			}
			len += n_col+1;
		}
		len_string.push_back(len);
		_string.push_back(str_row_fillpixels);
	}
}

std::vector<uint8_t> Label::ToWin1251(const std::string& textUTF8)
{
	std::vector<uint8_t> textWin1251;

    for(auto IT = textUTF8.begin(); IT != textUTF8.end();)
    {

    	uint32_t num_end = *IT++;
		uint8_t mask = 0xFF;
		int8_t counter = 0;

		for (int i = 7; num_end & (1 << i); i--)
		{
			counter++;
			mask &= ~(1 << i);
		}
		num_end &= mask;

		if (counter--)
		{
			num_end <<= (6 * counter);
			while (counter--)
			{
				num_end += (*IT++ & 0x7F) << (6 * counter);
			}
		}

		if (num_end >= 0x0410 && num_end <= 0x044F) { num_end -= 0x0350; }
		else if (num_end > 0x7F)
		{
			try
			{
				static std::map<uint32_t, uint8_t> conv = {    { 0x0402, 0x80 }, { 0x0403, 0x81 },
					{ 0x201A, 0x82 }, { 0x0453, 0x83 }, { 0x201E, 0x84 }, { 0x2026, 0x85 },
					{ 0x2020, 0x86 }, { 0x2021, 0x87 }, { 0x20AC, 0x88 }, { 0x2030, 0x89 },
					{ 0x0409, 0x8A }, { 0x2039, 0x8B }, { 0x040A, 0x8C }, { 0x040C, 0x8D },
					{ 0x040B, 0x8E }, { 0x040F, 0x8F }, { 0x0452, 0x90 }, { 0x2018, 0x91 },
					{ 0x2019, 0x92 }, { 0x201C, 0x93 }, { 0x201D, 0x94 }, { 0x2022, 0x95 },
					{ 0x2013, 0x96 }, { 0x2014, 0x97 }, { 0x2122, 0x99 }, { 0x0459, 0x9A },
					{ 0x203A, 0x9B }, { 0x045A, 0x9C }, { 0x045C, 0x9D }, { 0x045B, 0x9E },
					{ 0x045F, 0x9F }, { 0x00A0, 0xA0 }, { 0x040E, 0xA1 }, { 0x045E, 0xA2 },
					{ 0x0408, 0xA3 }, { 0x00A4, 0xA4 }, { 0x0490, 0xA5 }, { 0x00A6, 0xA6 },
					{ 0x00A7, 0xA7 }, { 0x0401, 0xA8 }, { 0x00A9, 0xA9 }, { 0x0404, 0xAA },
					{ 0x00AB, 0xAB }, { 0x00AC, 0xAC }, { 0x00AE, 0xAE }, { 0x0407, 0xAF },
					{ 0x00B0, 0xB0 }, { 0x00B1, 0xB1 }, { 0x0406, 0xB2 }, { 0x0456, 0xB3 },
					{ 0x0491, 0xB4 }, { 0x00B5, 0xB5 }, { 0x00B6, 0xB6 }, { 0x00B7, 0xB7 },
					{ 0x0451, 0xB8 }, { 0x2116, 0xB9 }, { 0x0454, 0xBA }, { 0x00BB, 0xBB },
					{ 0x0458, 0xBC }, { 0x0405, 0xBD }, { 0x0455, 0xBE }, { 0x0457, 0xBF }
				};
				num_end = conv[num_end];
			}
			catch (...) { num_end = 0; }
		}
		if (num_end == 0) { num_end = 0x20; }

        textWin1251.push_back(num_end);
    }

    return textWin1251;
}

std::vector<std::string> Label::CutString(std::string* str, char sym)
{
	std::vector<std::string> temp = {};

	std::size_t _pos = 0;
	std::size_t pos = 0;
	while(pos < str->size())
	{

		pos = std::distance(str->cbegin(), std::find(str->cbegin() + _pos, str->cend(), sym));

		temp.push_back(str->substr(_pos, pos - _pos));
		_pos = pos + 1;
	}
	return temp;
}

} /* namespace VA */
