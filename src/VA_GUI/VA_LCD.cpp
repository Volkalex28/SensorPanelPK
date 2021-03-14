/**
 * @file VA_LCD.cpp
 * @author Oleksandr Ananiev (alexander.ananiev@sigma.sofware)
 * @brief
 *
 */

#include "VA_LCD.hpp"

namespace VA
{

LCD::LCD(const uint16_t width, const uint16_t height)
  : _width(width), _height(height), _currentLayer(layers::LAYER1)
{ /* There's nothing here */
}

LCD::~LCD(void)
{ /* There's nothing here */
}

const LCD::layers operator+(const LCD::layers layer, const int val)
{
  const uint8_t _layer = (uint8_t)layer + val;
  return _layer < (uint8_t)LCD::layers::LAYER_END ? (LCD::layers)_layer
                                                   : LCD::layers::LAYER1;
}

const uint16_t LCD::getWigth(void) const { return this->_width; }
const uint16_t LCD::getHeight(void) const { return this->_height; }

const LCD::layers LCD::getLayer(void) const { return this->_currentLayer; }

void LCD::setLayer(const layers layer)
{
  this->_currentLayer = (layer < layers::LAYER_END) ? layer : this->_currentLayer;
}

} // namespace VA
