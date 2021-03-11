/**
 * @file VAGeometric.hpp
 * @author Oleksandr Ananiev (alexander.ananiev@sigma.sofware)
 * @brief 
 * 
 */

#pragma once

#include <cstdlib>
#include <stdint.h>
#include <vector>

#ifndef ASSERT
  #include <assert.h>
  #define ASSERT(exp) assert(exp)
#endif

namespace VA
{
  enum class Colors
  {
    BLACK   = 0x0000,
    BLUE    = 0x001F,
    RED     = 0xF800,
    GREEN   = 0x07E0,
    CYAN    = 0x07FF,
    MAGENTA = 0xF81F,
    YELLOW  = 0xFFE0,
    WHITE   = 0xFFFF
  };

  class Point
  {
    uint16_t _x, _y;

  public:
    Point(const uint16_t x = 0, const uint16_t y = 0);
    Point(const Point & other);
    Point(Point && other);

    const Point & operator=(const Point & other);
    const Point & operator=(Point && other);

    const uint16_t getX(void) const;
    const uint16_t getY(void) const;

    void setX(const uint16_t value);
    void setY(const uint16_t value);
  };

  class Rectangle
  {
  protected:
    Point _nullPoint;
    uint16_t _width, _height;
    Colors _color;

  public:
    Rectangle(const Point & nullPoint = Point(), const uint16_t width = 1, 
      const uint16_t height = 1, const Colors color = Colors::BLACK);
    Rectangle(const Rectangle & other);
    Rectangle(Rectangle && other);

    const Rectangle & operator=(const Rectangle & other);
    const Rectangle & operator=(Rectangle && other);
    
    const Point getNullPoint(void) const;
    const uint16_t getWidth(void) const;
    const uint16_t getHeight(void) const;
    const Point getCenter(void) const;
    const uint16_t getCenterW(void) const;
    const uint16_t getCenterH(void) const;
    const Colors getColor(void) const;

    void setNullPoint(const Point & value);
    void setWidth(const uint16_t value);
    void setHeight(const uint16_t value);
    void setColor(const Colors value);
  };

  class Ellipse : public Rectangle
  {
  protected:
    const Point calcNullPoint(const Point & center, const uint16_t width,
      const uint16_t height);
    
  public:
    Ellipse(const Point & center = Point(), const uint16_t width = 1, 
      const uint16_t height = 1, const Colors color = Colors::BLACK);
    Ellipse(const Rectangle & other);
    Ellipse(Rectangle && other);
    
    void setCenter(const Point & value);
  };

  class Curve : public Ellipse
  {
  public:
    enum class Mode
    {
      MODE0,
      MODE1,
      MODE2,
      MODE3,
      MODE_END
    };
  
  protected:
    Mode _mode;

  public:
    Curve(const Point & nullPoint = Point(), const uint16_t width = 1, 
      const uint16_t height = 1, Mode mode = Mode::MODE0,
      const Colors color = Colors::BLACK);
    Curve(const Curve & other);
    Curve(Curve && other);
    Curve(const Rectangle & other, Mode mode = Mode::MODE0);
    Curve(Rectangle && other, Mode mode = Mode::MODE0);

    const Mode getMode(void) const;
    void setMode(const Mode mode);
  };

  class RoundRect : public Rectangle
  {
  protected:
    uint16_t _radius;

  public:
    RoundRect(const Point & center = Point(), const uint16_t width = 1, 
      const uint16_t height = 1, uint16_t radius = 0,
      const Colors color = Colors::BLACK);
    RoundRect(const RoundRect & other);
    RoundRect(RoundRect && other);
    RoundRect(const Rectangle & other, uint16_t radius = 0);
    RoundRect(Rectangle && other, uint16_t radius = 0);

    const uint16_t getRadius(void) const;
    void setRadius(const uint16_t value);
  };

  class Triangle : public Rectangle
  {
  protected:
    std::vector<Point> _points;

    const Point calcNullPoint(const std::vector<Point> & points) const;
    const uint16_t calcWorH(const Point & nullPoint, 
      const std::vector<Point> & points,
      const uint16_t (Point:: * const get)(void) const) const;
    const void update(void);
  
  private:
    using Rectangle::setNullPoint;
    using Rectangle::setWidth;
    using Rectangle::setHeight;
  
  public:
    Triangle(const Point & point1 = Point(), const Point & point2 = Point(), 
      const Point & point3 = Point(), const Colors color = Colors::BLACK);
    Triangle(const std::vector<Point> & points, const Colors color = Colors::BLACK);
    Triangle(const Point points[3], const Colors color = Colors::BLACK);
    Triangle(const Triangle & other);
    Triangle(Triangle && other);

    const Point operator[](const uint16_t index) const;
    const Point setPoint(const uint16_t index, const Point & point);
    const std::vector<Point> & getPoints(void);
  };

} /* namespace VA */
