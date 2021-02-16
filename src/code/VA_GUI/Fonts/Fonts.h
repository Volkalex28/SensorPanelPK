/*
 * Fonts.h
 *
 *  Created on: 18 нояб. 2020 г.
 *      Author: anan2
 */

#ifndef _FONTS_H_
#define _FONTS_H_

#include "TimesNewRoman/TimesNewRoman.h"

enum class Fonts {
	TimesNewRoman
};

enum class FontForms {
	Normal,
	Bold,
	Italic
};

TCLISTP* GetPtrFont(Fonts font, FontForms form);

#endif
