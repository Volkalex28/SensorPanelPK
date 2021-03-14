/**
 * @file VAGraphics.hpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#pragma once

#include "../Geometric/VAGeometric.hpp"
#include "VABaseElement.hpp"

namespace VA
{

template <class Parent_t = Rectangle> class Graphics : public Parent_t, public BaseElement
{
public:
  Graphics(const Parent_t && other, const bool enable = true, const bool show = true);
  ~Graphics(void) override;

  bool isMe(Point point) const override;
  void draw(const LCD & lcd) const override;
};

#include "VAGraphics.ipp"

} // namespace VA
