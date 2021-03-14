/**
 * @file BaseElement.hpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#pragma once

#include "../Geometric/VAGeometric.hpp"
#include "../VA_LCD.hpp"

namespace VA
{

class BaseElement
{
protected:
  bool _enabled;
  bool _showed;

  BaseElement(const bool enable = true, const bool show = true);
  virtual ~BaseElement();

public:
  virtual bool isMe(Point point) const = 0;
  const bool isShowed(void) const;
  const bool isEnabled(void) const;
  void enable(const bool state);
  void show(const bool state);

  virtual void draw(const LCD & lcd) const;
};

} // namespace VA
