/**
 * @file Fonts.hpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "TypeDefsFont.h"

#ifdef __cplusplus
}
#endif

namespace VA::Font
{
#define SYMBOL_WIDTH (16)

enum class Fonts
{
  TimesNewRoman
};

enum class FontForms
{
  Normal,
  Bold,
  Italic
};

TCLISTP * GetPtrFont(Fonts font, FontForms form);

} // namespace VA::Font
