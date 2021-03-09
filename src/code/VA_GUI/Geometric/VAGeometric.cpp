/**
 * @file VAGeometric.cpp
 * @author Oleksandr Ananiev (alexander.ananiev@sigma.sofware)
 * @brief 
 * 
 */

#include <utility>

#include "VAGeometric.hpp"

using namespace VA;

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

// ============================================================================
// Point
// ============================================================================

Point::Point(const uint16_t x, const uint16_t y) : _x(x), _y(y)
{ /* There's nothing here */ }

Point::Point(const Point & other) : Point(other._x, other._y)
{ /* There's nothing here */ }

Point::Point(Point && other) : Point(other._x, other._y)
{ /* There's nothing here */ }

const Point & Point::operator=(const Point & other) 
{
  this->_x = other.getX();
  this->_y = other.getY();

  return *this;
}

const Point & Point::operator=(Point && other) 
{
  this->_x = other._x;
  this->_y = other._y;

  return *this;
}

const uint16_t Point::getX(void) const { return this->_x; }

const uint16_t Point::getY(void) const { return this->_y; }

void Point::setX(const uint16_t value) { this->_x = value; }

void Point::setY(const uint16_t value) { this->_y = value; }

// ============================================================================
// Rectangle
// ============================================================================

Rectangle::Rectangle(const Point & nullPoint, const uint16_t width, 
  const uint16_t height, const Colors color) 
  : _nullPoint(nullPoint), _width(width), _height(height), _color(color)
{ /* There's nothing here */ }

Rectangle::Rectangle(Rectangle && other) 
  : _nullPoint(std::move(other._nullPoint)), _width(std::move(other._width)),
    _height(std::move(other._height)), _color(std::move(other._color))
{ /* There's nothing here */ }

Rectangle::Rectangle(const Rectangle & other)
  : Rectangle(other.getNullPoint(), other.getWidth(), other.getHeight(),
    other.getColor())
{ /* There's nothing here */ }

const Rectangle & Rectangle::operator=(const Rectangle & other) 
{
  this->_nullPoint = other.getNullPoint();
  this->_width = other.getWidth();
  this->_height = other.getHeight();
  this->_color = other.getColor();

  return *this;
}

const Rectangle & Rectangle::operator=(Rectangle && other) 
{
  this->_nullPoint = std::move(other._nullPoint);
  this->_width = other._width;
  this->_height = other._height;
  this->_color = other._color;

  return *this;
}

const Point Rectangle::getNullPoint(void) const { return this->_nullPoint; }

const uint16_t Rectangle::getWidth(void) const  { return this->_width; }

const uint16_t Rectangle::getHeight(void) const { return this->_height; }

const Point Rectangle::getCenter(void) const
{
  return Point(this->getCenterW(), this->getCenterH());
}

const uint16_t Rectangle::getCenterW(void) const
{
  return this->_nullPoint.getX() + this->getWidth() / 2;
}

const uint16_t Rectangle::getCenterH(void) const
{
  return this->_nullPoint.getY() + this->getHeight() / 2;
}

const Colors Rectangle::getColor(void) const      { return this->_color; }

void Rectangle::setNullPoint(const Point & value) { this->_nullPoint = value; }

void Rectangle::setWidth(const uint16_t value)    { this->_width = value; }

void Rectangle::setHeight(const uint16_t value)   { this->_height = value; }

void Rectangle::setColor(const Colors value)      { this->_color = value; }

// ============================================================================
// Ellipse
// ============================================================================

const Point Ellipse::calcNullPoint(const Point & center, const uint16_t width,
  const uint16_t height) 
{
  int32_t x = center.getX(), y = center.getY();
  x -= width / 2;
  y -= height / 2;

  return Point(x > 0 ? x : 0, y > 0 ? y : 0);
}

Ellipse::Ellipse(const Point & center, const uint16_t width, 
  const uint16_t height, const Colors color)
  : Rectangle(this->calcNullPoint(center, width, height), width, height, color)
{ /* There's nothing here */ }

Ellipse::Ellipse(const Rectangle & other) : Rectangle(other)
{ /* There's nothing here */ }

Ellipse::Ellipse(Rectangle && other) : Rectangle(std::move(other))
{ /* There's nothing here */ }

void Ellipse::setCenter(const Point & value) 
{
  this->setNullPoint(this->calcNullPoint(value, this->getWidth(), this->getHeight()));
}

// ============================================================================
// Curve
// ============================================================================

Curve::Curve(const Point & center, const uint16_t width, const uint16_t height,
  Mode mode, const Colors color) 
  : Ellipse(center, width, height, color), _mode(Mode::MODE0)
{
  this->setMode(mode);
}

Curve::Curve(const Curve & other) : Ellipse(other)
{ /* There's nothing here */ }

Curve::Curve(Curve && other) : Ellipse(std::move(other))
{ /* There's nothing here */ }

Curve::Curve(const Rectangle & other, Mode mode)
  : Ellipse(other), _mode(Mode::MODE0)
{
  this->setMode(mode);
}

Curve::Curve(Rectangle && other, Mode mode) 
  : Ellipse(std::move(other)), _mode(Mode::MODE0)
{
  this->setMode(mode);
}

const Curve::Mode Curve::getMode(void) const { return this->_mode; }

void Curve::setMode(const Mode mode) 
{
  if(mode < Mode::MODE_END)
  { 
    this->_mode = mode;
  }
}

// ============================================================================
// RoundRect
// ============================================================================

RoundRect::RoundRect(const Point & nullPoint, const uint16_t width,
  const uint16_t height, uint16_t radius, const Colors color) 
  : Rectangle(nullPoint, width, height, color), _radius(0)
{ 
  this->setRadius(radius);
}

RoundRect::RoundRect(const RoundRect & other) : Rectangle(other)
{ /* There's nothing here */ }

RoundRect::RoundRect(RoundRect && other) : Rectangle(std::move(other))
{ /* There's nothing here */ }

RoundRect::RoundRect(const Rectangle & other, uint16_t radius) 
  : Rectangle(other), _radius(0)
{
  this->setRadius(radius);
}

RoundRect::RoundRect(Rectangle && other, uint16_t radius) 
  : Rectangle(std::move(other)), _radius(0)
{
  this->setRadius(radius);
}

const uint16_t RoundRect::getRadius(void) const
{
  return this->_radius;
}

void RoundRect::setRadius(const uint16_t value) 
{
  const uint16_t maxRadius = MIN(this->_width, this->_height) / 2;
  
  this->_radius = value > maxRadius ? maxRadius : value;
}

// ============================================================================
// Triangle
// ============================================================================

const Point Triangle::calcNullPoint(const std::vector<Point> & points) const
{
  Point point(-1, -1);

  for(auto & i : points)
  {
    uint16_t temp = i.getX();
    if(temp < point.getX()) { point.setX(temp); }

    temp = i.getY();
    if(temp < point.getY()) { point.setY(temp); }

  }

  return point;
}

const void Triangle::update(void) 
{
  this->setNullPoint(this->calcNullPoint(this->_points));
  this->setWidth(this->calcWorH(this->_nullPoint, this->_points, &Point::getX));
  this->setHeight(this->calcWorH(this->_nullPoint, this->_points, &Point::getY));
}

const uint16_t Triangle::calcWorH(const Point & nullPoint, 
  const std::vector<Point> & points,
  const uint16_t (Point:: * const get)(void) const) const
{
  uint16_t max = 0;

  for(auto & i : points)
  {
    uint16_t temp = (i.*get)();
    if(temp > max) { max = temp; }
  }

  return max - (nullPoint.*get)();
}

Triangle::Triangle(const std::vector<Point> & points, const Colors color) 
  : Rectangle(), _points(3, Point())
{
  ASSERT(points.size() == 3);

  this->_points = points;

  this->update();
  this->setColor(color);
}

Triangle::Triangle(const Point & point1, const Point & point2, const Point & point3, 
  const Colors color) : Triangle({point1, point2, point3}, color)
{ /* There's nothing here */ }

Triangle::Triangle(const Point points[3], const Colors color) 
  : Triangle(points[0], points[1], points[2], color)
{ /* There's nothing here */ }

Triangle::Triangle(const Triangle & other) 
  : Rectangle(other), _points(other._points)
{ /* There's nothing here */ }

Triangle::Triangle(Triangle && other) 
{ /* There's nothing here */ }

const Point Triangle::operator[](const uint16_t index) const
{
  if(index >= 3) 
  {
    return Point();
  }
  return this->_points[index];
}

const Point Triangle::setPoint(const uint16_t index, const Point & point) 
{
  if(index >= 3) 
  {
    return Point();
  }

  this->_points[index] = point;

  this->update();

  return point;
}

const std::vector<Point> & Triangle::getPoints(void) 
{
  return this->_points;
}
