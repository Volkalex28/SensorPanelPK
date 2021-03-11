/**
 * @file VA_LCD.cpp
 * @author Oleksandr Ananiev (alexander.ananiev@sigma.sofware)
 * @brief 
 * 
 */

#include "VA_LCD.hpp"

using namespace VA;

LCD::LCD(const uint16_t width, const uint16_t height) 
  : _width(width), _height(height), _currentLayer(layers::LAYER1)
{ /* There's nothing here */ }

LCD::~LCD(void) 
{ /* There's nothing here */ }

const uint16_t LCD::getWigth(void) const { return this->_width; }
const uint16_t LCD::getHeight(void) const { return this->_height; }

const LCD::layers LCD::getLayer(void) const { return this->_currentLayer; }

void LCD::setLayer(const layers layer) 
{
  this->_currentLayer = (layer < layers::LAYER_END) ? layer : this->_currentLayer;
}
