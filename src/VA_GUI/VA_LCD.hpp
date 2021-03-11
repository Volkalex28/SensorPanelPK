/**
 * @file VADisplay.hpp
 * @author Oleksandr Ananiev (alexander.ananiev@sigma.sofware)
 * @brief 
 * 
 */

#pragma once

#include <cstdlib>
#include <stdint.h>

#include "./Geometric/VAGeometric.hpp"

namespace VA
{

class LCD
{
public:
  enum class layers { LAYER1, LAYER2, LAYER_END };

  virtual bool init(void) = 0;
  virtual void displayOn(void) const = 0;
  virtual void displayOff(void) const = 0;
  virtual void setBrightness(const uint8_t percent) const = 0;

  const uint16_t getWigth(void) const;
  const uint16_t getHeight(void) const;
  const layers getLayer(void) const;
  virtual void setLayer(const layers layer);
  virtual void showLayer(const layers layer) const = 0;

  virtual void drawPixel(const Point & point, const Colors color) const = 0;
  virtual void drawPixels(const Point & startPoint, const uint16_t count, 
    const Colors color) const = 0;
  virtual void drawPixels(const Point & startPoint, const uint16_t count, 
    const Colors * const color) const = 0;

  virtual void fillScreen(const Colors color) const = 0;
  virtual void draw(const Rectangle & object, bool fill = false) const = 0;
  virtual void draw(const Ellipse   & object, bool fill = false) const = 0;
  virtual void draw(const Curve     & object, bool fill = false) const = 0;
  virtual void draw(const RoundRect & object, bool fill = false) const = 0;
  virtual void draw(const Triangle  & object, bool fill = false) const = 0;

protected:
  uint16_t _width, _height;
  layers _currentLayer;

  LCD(const uint16_t width, const uint16_t height);
  virtual ~LCD(void);

};

} /* namespace VA */
