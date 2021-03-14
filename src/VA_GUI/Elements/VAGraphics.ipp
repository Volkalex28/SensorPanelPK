/**
 * @file VAGraphics.ipp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

template <class Parent_t>
Graphics<Parent_t>::Graphics(const Parent_t && other, const bool enable, const bool show)
  : Parent_t(other), BaseElement(enable, show)
{
}

template <class Parent_t> Graphics<Parent_t>::~Graphics(void)
{
}

template <class Parent_t> bool Graphics<Parent_t>::isMe(Point point) const
{
  auto checkCoordinate = [](const uint16_t start, const uint16_t lenght, const uint16_t point) {
    return (start <= point && point < start + lenght);
  };

  if (checkCoordinate(this->getNullPoint().getX(), this->getWidth(), point.getX()))
  {
    if (checkCoordinate(this->getNullPoint().getY(), this->getHeight(), point.getY()))
    {
      return true;
    }
  }
  return false;
}

template <class Parent_t> void Graphics<Parent_t>::draw(const LCD & lcd) const
{
  if (this->_showed)
  {
    lcd.draw(*this, true);
  }
}
