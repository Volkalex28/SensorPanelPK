/*
 * Fonts.c
 *
 *  Created on: 18 нояб. 2020 г.
 *      Author: anan2
 */


#include "Fonts.h"

TCLISTP* GetPtrFont(Fonts font, FontForms form) {
	TCLISTP* pFont = 0;
	switch(font) {
	case Fonts::TimesNewRoman:
		pFont = TimesNewRoman[(uint8_t)form];
		break;
	}
	return pFont;
}
