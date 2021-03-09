/**
 * @file RA8875.hpp
 * @author Oleksandr Ananiev (alexander.ananiev@sigma.sofware)
 * @brief Заголовочный файл класса, который описывает драйвер для контроллера 
 * дисплея RA8875
 * 
 */

# pragma once

#include "VA_LCD.hpp"
#include "VATouch.hpp"

/**
 * @brief 
 * 
 */
class RA8875 : public VA::LCD, VA::Touch
{
public:
  enum class displaySizes 
  {
    _480x80,  ///< 480x80  Pixel Display
    _480x128, ///< 480x128 Pixel Display
    _480x272, ///< 480x272 Pixel Display
    _800x480  ///< 800x480 Pixel Display
  };

  RA8875(displaySizes size, void(* Delay)(const uint32_t ticks));

  bool init(void) override;
  void displayOn(void) const override;
  void displayOff(void) const override;
  void setBrightness(const uint8_t percent) const override;

  void setLayer(const VA::LCD::layers layer) override;
  void showLayer(const VA::LCD::layers layer) const override;

  void drawPixel(const VA::Point & point, const VA::Colors color) const override;
  void drawPixels(const VA::Point & startPoint, const uint16_t count, 
    const VA::Colors color) const override;
  void drawPixels(const VA::Point & startPoint, const uint16_t count, 
    const VA::Colors * const color) const override;

  void fillScreen(const VA::Colors color) const override;
  void draw(const VA::Rectangle & object, bool fill = false) const override;
  void draw(const VA::Ellipse   & object, bool fill = false) const override;
  void draw(const VA::Curve     & object, bool fill = false) const override;
  void draw(const VA::RoundRect & object, bool fill = false) const override;
  void draw(const VA::Triangle  & object, bool fill = false) const override;
  
  void touchEnable(bool on) const override;
	bool touched(void) const override;
	bool touchRead(uint16_t & x, uint16_t & y) const override;

private:
  #define del 65
  const displaySizes _size; 

  const uint16_t calcWidth(const displaySizes size) const;
  const uint16_t calcHeight(const displaySizes size) const;

  void _init(void) const;
	void PLLinit(void) const;
  void GPIOX(bool status) const;
  void PWMconf(bool status, const uint8_t clock) const;

  void circleHelper(uint16_t x, uint16_t y, uint16_t r, uint16_t color, 
    bool filled) const;
	void rectHelper(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color,
    bool filled) const;
	void triangleHelper(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, 
    uint16_t x2, uint16_t y2, uint16_t color, bool filled) const;
	void ellipseHelper(uint16_t xCenter, uint16_t yCenter, uint16_t longAxis, 
    uint16_t shortAxis, uint16_t color, bool filled) const;
	void curveHelper(uint16_t xCenter, uint16_t yCenter, uint16_t longAxis, 
    uint16_t shortAxis, uint8_t curvePart, uint16_t color, bool filled) const;
	void roundRectHelper(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r,
    uint16_t color, bool filled) const;

  inline void delay(uint32_t micros) const;
  void(* exDelay)(const uint32_t ticks);

  void writeReg(uint16_t reg, uint16_t val) const;
	uint16_t readReg(uint16_t reg) const;
	void writeData(uint16_t d) const;
	uint16_t readData(void) const;
	void writeCommand(uint16_t d) const;
	uint16_t readStatus(void) const;
	bool waitPoll(uint16_t r, uint16_t f) const;
};
