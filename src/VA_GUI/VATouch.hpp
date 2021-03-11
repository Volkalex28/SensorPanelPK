/**
 * @file VATouch.hpp
 * @author Oleksandr Ananiev (alexander.ananiev@sigma.sofware)
 * @brief 
 * 
 */

#include "stdint.h"

#include "Geometric/VAGeometric.hpp"

namespace VA
{

struct Touch
{
  virtual void touchEnable(bool on) const = 0;
	virtual bool touched(void) const = 0;
	virtual const Point touchRead(void) const = 0;

protected:
  Touch(void) {}
  virtual ~Touch(void) {}
};

} /* namespace VA */
