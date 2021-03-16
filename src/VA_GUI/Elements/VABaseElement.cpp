/**
 * @file BaseElement.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include "VABaseElement.hpp"

namespace VA::Elements
{

BaseElement::BaseElement(const bool enable, const bool show) : _enabled(enable), _showed(show)
{
}

BaseElement::~BaseElement()
{
}

const bool BaseElement::isShowed(void) const
{
  return this->_showed;
}

const bool BaseElement::isEnabled(void) const
{
  return this->_enabled;
}

void BaseElement::enable(const bool state)
{
  this->_enabled = state;
}

void BaseElement::show(const bool state)
{
  this->_showed = state;
}

void BaseElement::draw(const LCD & lcd) const
{
}

} // namespace VA