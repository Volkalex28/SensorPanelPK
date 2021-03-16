/**
 * @file VAIndicatorCircular.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include "VAIndicator.hpp"

namespace VA::Elements
{

IndicatorCircular::~IndicatorCircular(void)
{
}

IndicatorCircular::IndicatorCircular(const Point & center, const uint16_t width, const uint16_t height,
  Property && prop, const bool enable, const bool show)
  : Graphics<Ellipse>({ center, width, height, prop.colorTrue }, enable, show), _state(prop.state),
    _colorFalse(prop.colorFalse)
{
}

const bool IndicatorCircular::isState(void) const
{
  return this->_state;
}

void IndicatorCircular::state(const bool state)
{
  this->_state = state;
}

const Colors IndicatorCircular::getColorTrue(void) const
{
  return this->getColor();
}

const Colors IndicatorCircular::getColorFalse(void) const
{
  return this->_colorFalse;
}

void IndicatorCircular::setColorTrue(const Colors color)
{
  this->setColor(color);
}

void IndicatorCircular::setColorFalse(const Colors color)
{
  this->_colorFalse = color;
}

void IndicatorCircular::draw(const LCD & lcd) const
{
  lcd.draw(Ellipse(this->getCenter(), this->_width * 1.00f, this->_height * 1.00f, Colors::BLACK));
  lcd.draw(Ellipse(this->getCenter(), this->_width * 0.92f, this->_height * 0.92f, Colors::WHITE));
  lcd.draw(Ellipse(this->getCenter(), this->_width * 0.85f, this->_height * 0.85f, Colors::BLACK));
  lcd.draw(Ellipse(this->getCenter(), this->_width * 0.78f, this->_height * 0.78f,
    this->_state ? this->getColorTrue() : this->_colorFalse));
  lcd.draw(
    Ellipse(Rectangle(Point(this->_nullPoint.getX() + this->_width / 4, this->_nullPoint.getY() + this->_height / 4),
      this->_width / 7, this->_height / 7, Colors::WHITE)));
}
} // namespace VA::Elements
