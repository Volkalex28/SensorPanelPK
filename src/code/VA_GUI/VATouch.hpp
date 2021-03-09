/**
 * @file VATouch.hpp
 * @author Oleksandr Ananiev (alexander.ananiev@sigma.sofware)
 * @brief 
 * 
 */

#include "stdint.h"

namespace VA
{

struct Touch
{
  virtual void touchEnable(bool on) const = 0;
	virtual bool touched(void) const = 0;
	virtual bool touchRead(uint16_t & x, uint16_t & y) const = 0;

protected:
  Touch(void) {}
  virtual ~Touch(void) {}
};

} /* namespace VA */
