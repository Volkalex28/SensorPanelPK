/**
 * @file VAIndicator.hpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#pragma once

#include "VAGraphics.hpp"

namespace VA::Elements
{
class IndicatorCircular : public Graphics<Ellipse>
{
protected:
  bool _state;
  Colors _colorFalse;

public:
  struct Property
  {
    bool state = false;
    Colors colorTrue = Colors::GREEN;
    Colors colorFalse = Colors::RED;
  };

  IndicatorCircular(const Point & center = Point(), const uint16_t width = 1, const uint16_t height = 1,
    Property && prop = { .state = false, .colorTrue = Colors::GREEN, .colorFalse = Colors::RED },
    const bool enable = true, const bool show = true);
  ~IndicatorCircular(void) override;

  const bool isState(void) const;
  void state(const bool state);

  const Colors getColorTrue(void) const;
  const Colors getColorFalse(void) const;
  void setColorTrue(const Colors color);
  void setColorFalse(const Colors color);

  void draw(const LCD & lcd) const override;

private:
  using Graphics::getColor;
  using Graphics::setColor;
};

} // namespace VA::Elements
