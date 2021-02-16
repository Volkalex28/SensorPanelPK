/*
 * VAIndicator.h
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: anan2
 */

#pragma once

#include <Elements/VABaseElement.h>

namespace VA {

class Indicator: public BaseElement {

	bool indicate;

public:
	bool state = false;
	template <typename T>
	Indicator(T ptr, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool indicate = false)
		: BaseElement(ptr, x, y, w, h)
	{
		this->indicate = indicate;
	}

	virtual void CallBack(void) override;
	virtual void Show(void) override;
};

} /* namespace VA */
