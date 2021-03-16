/**
 * @file VALabel.hpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#pragma once

#include <array>
#include <string>
#include <vector>

#include "../Fonts/Fonts.hpp"
#include "VAGraphics.hpp"

namespace VA::Elements
{

class Label : Graphics<Rectangle>
{
public:
  enum class Scale
  {
    S1 = 1,
    S2,
    S3,
    S4
  };
  enum class AlignX
  {
    Left,
    Center,
    Right
  };
  enum class AlignY
  {
    Top,
    Center,
    Bottom
  };

  struct Property
  {
    Font::Fonts font = Font::Fonts::TimesNewRoman;
    Font::FontForms fontForm = Font::FontForms::Normal;
    Scale scale = Scale::S2;
    AlignX alignX = AlignX::Left;
    AlignY alignY = AlignY::Top;
    Colors colorText = Colors::BLACK;
    Colors colorBack = Colors::TRANSPERENT;
    std::string text = "";
  };

protected:
  Scale _scale;
  AlignX _alignX;
  AlignY _alignY;
  Font::Fonts _font;
  Font::FontForms _fontForm;
  Colors _colorText;

  std::string _text;

private:
  struct FillPixels
  {
    uint8_t count;
    uint16_t offset;
  };
  using ConvertedLine_t = std::vector<FillPixels>;
  using ConvertedWord_t = std::array<ConvertedLine_t, SYMBOL_WIDTH>;
  struct ConvertedWordWithLen
  {
    ConvertedWord_t word;
    uint16_t len;
  };
  using ConvertedString_t = std::vector<ConvertedWordWithLen>;
  using ConvertedText_t = std::vector<ConvertedString_t>;

  using Graphics::getColor;
  using Graphics::setColor;

public:
  Label(const Point & nullPoint = Point(), const uint16_t width = 1, const uint16_t height = 1,
    Property && p = { .font = Font::Fonts::TimesNewRoman,
      .fontForm = Font::FontForms::Normal,
      .scale = Scale::S2,
      .alignX = AlignX::Left,
      .alignY = AlignY::Top,
      .colorText = Colors::BLACK,
      .colorBack = Colors::TRANSPERENT,
      .text = "" },
    const bool enable = true, const bool show = true);
  ~Label(void) override;

  const Scale getScale(void) const;
  const AlignX getAlignX(void) const;
  const AlignY getAlignY(void) const;
  const Colors getColorText(void) const;
  const Colors getColorBack(void) const;
  const std::string getText(void) const;

  void setScale(const Scale scale);
  void setAlignX(const AlignX align);
  void setAlignY(const AlignY align);
  void setColorText(const Colors color);
  void setColorBack(const Colors color);

  void setText(const std::string & text);
  template <typename number_t> void setText(const number_t value);

  void draw(const LCD & lcd) const override;

private:
  void UpdateText(ConvertedText_t & temp_string) const;
  std::vector<uint8_t> ToWin1251(const std::string & textUTF8) const;
  std::vector<std::string> CutString(const std::string * const str, const char sym) const;
  void StrToBitmap(const std::vector<std::string> & str, ConvertedString_t & _string) const;
};

template <typename number_t> void Label::setText(const number_t value)
{
  this->_text = std::to_string(value);
}

} // namespace VA::Elements
