/*
 * Fonts.c
 *
 *  Created on: 18 нояб. 2020 г.
 *      Author: anan2
 */

#include "Fonts.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

#include "TimesNewRoman/TimesNewRoman.h"

#ifdef __cplusplus
}
#endif

namespace VA::Font
{

TCLISTP * GetPtrFont(Fonts font, FontForms form)
{
  TCLISTP * pFont = 0;
  switch (font)
  {
  case Fonts::TimesNewRoman:
    pFont = TimesNewRoman[(uint8_t)form];
    break;
  }
  return pFont;
}

} // namespace Font
