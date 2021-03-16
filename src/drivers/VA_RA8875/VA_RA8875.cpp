/**
 * @file RA8875.cpp
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief
 *
 */

#include "math.h"

#include "VA_RA8875.hpp"

namespace VA
{

#ifndef ASSERT
#include "assert.h"
#define ASSERT(exp) assert(exp)
#endif

#define LCD_DATA ((volatile uint16_t *)0x60000000)
#define LCD_REG ((volatile uint16_t *)0x60020000)

#define RA8875_DATAWRITE 0x00 ///< See datasheet
#define RA8875_DATAREAD 0x40  ///< See datasheet
#define RA8875_CMDWRITE 0x80  ///< See datasheet
#define RA8875_CMDREAD 0xC0   ///< See datasheet

// Registers & bits
#define RA8875_PWRR 0x01           ///< See datasheet
#define RA8875_PWRR_DISPON 0x80    ///< See datasheet
#define RA8875_PWRR_DISPOFF 0x00   ///< See datasheet
#define RA8875_PWRR_SLEEP 0x02     ///< See datasheet
#define RA8875_PWRR_NORMAL 0x00    ///< See datasheet
#define RA8875_PWRR_SOFTRESET 0x01 ///< See datasheet

#define RA8875_MRWC 0x02 ///< See datasheet

#define RA8875_GPIOX 0xC7 ///< See datasheet

#define RA8875_PLLC1 0x88         ///< See datasheet
#define RA8875_PLLC1_PLLDIV2 0x80 ///< See datasheet
#define RA8875_PLLC1_PLLDIV1 0x00 ///< See datasheet

#define RA8875_PLLC2 0x89        ///< See datasheet
#define RA8875_PLLC2_DIV1 0x00   ///< See datasheet
#define RA8875_PLLC2_DIV2 0x01   ///< See datasheet
#define RA8875_PLLC2_DIV4 0x02   ///< See datasheet
#define RA8875_PLLC2_DIV8 0x03   ///< See datasheet
#define RA8875_PLLC2_DIV16 0x04  ///< See datasheet
#define RA8875_PLLC2_DIV32 0x05  ///< See datasheet
#define RA8875_PLLC2_DIV64 0x06  ///< See datasheet
#define RA8875_PLLC2_DIV128 0x07 ///< See datasheet

#define RA8875_SYSR 0x10       ///< See datasheet
#define RA8875_SYSR_8BPP 0x00  ///< See datasheet
#define RA8875_SYSR_16BPP 0x0C ///< See datasheet
#define RA8875_SYSR_MCU8 0x00  ///< See datasheet
#define RA8875_SYSR_MCU16 0x03 ///< See datasheet

#define RA8875_PCSR 0x04       ///< See datasheet
#define RA8875_PCSR_PDATR 0x00 ///< See datasheet
#define RA8875_PCSR_PDATL 0x80 ///< See datasheet
#define RA8875_PCSR_CLK 0x00   ///< See datasheet
#define RA8875_PCSR_2CLK 0x01  ///< See datasheet
#define RA8875_PCSR_4CLK 0x02  ///< See datasheet
#define RA8875_PCSR_8CLK 0x03  ///< See datasheet

#define RA8875_HDWR 0x14 ///< See datasheet

#define RA8875_HNDFTR 0x15         ///< See datasheet
#define RA8875_HNDFTR_DE_HIGH 0x00 ///< See datasheet
#define RA8875_HNDFTR_DE_LOW 0x80  ///< See datasheet

#define RA8875_HNDR 0x16      ///< See datasheet
#define RA8875_HSTR 0x17      ///< See datasheet
#define RA8875_HPWR 0x18      ///< See datasheet
#define RA8875_HPWR_LOW 0x00  ///< See datasheet
#define RA8875_HPWR_HIGH 0x80 ///< See datasheet

#define RA8875_VDHR0 0x19     ///< See datasheet
#define RA8875_VDHR1 0x1A     ///< See datasheet
#define RA8875_VNDR0 0x1B     ///< See datasheet
#define RA8875_VNDR1 0x1C     ///< See datasheet
#define RA8875_VSTR0 0x1D     ///< See datasheet
#define RA8875_VSTR1 0x1E     ///< See datasheet
#define RA8875_VPWR 0x1F      ///< See datasheet
#define RA8875_VPWR_LOW 0x00  ///< See datasheet
#define RA8875_VPWR_HIGH 0x80 ///< See datasheet

#define RA8875_HSAW0 0x30 ///< See datasheet
#define RA8875_HSAW1 0x31 ///< See datasheet
#define RA8875_VSAW0 0x32 ///< See datasheet
#define RA8875_VSAW1 0x33 ///< See datasheet

#define RA8875_HEAW0 0x34 ///< See datasheet
#define RA8875_HEAW1 0x35 ///< See datasheet
#define RA8875_VEAW0 0x36 ///< See datasheet
#define RA8875_VEAW1 0x37 ///< See datasheet

#define RA8875_MCLR 0x8E            ///< See datasheet
#define RA8875_MCLR_START 0x80      ///< See datasheet
#define RA8875_MCLR_STOP 0x00       ///< See datasheet
#define RA8875_MCLR_READSTATUS 0x80 ///< See datasheet
#define RA8875_MCLR_FULL 0x00       ///< See datasheet
#define RA8875_MCLR_ACTIVE 0x40     ///< See datasheet

#define RA8875_DCR 0x90                   ///< See datasheet
#define RA8875_DCR_LINESQUTRI_START 0x80  ///< See datasheet
#define RA8875_DCR_LINESQUTRI_STOP 0x00   ///< See datasheet
#define RA8875_DCR_LINESQUTRI_STATUS 0x80 ///< See datasheet
#define RA8875_DCR_CIRCLE_START 0x40      ///< See datasheet
#define RA8875_DCR_CIRCLE_STATUS 0x40     ///< See datasheet
#define RA8875_DCR_CIRCLE_STOP 0x00       ///< See datasheet
#define RA8875_DCR_FILL 0x20              ///< See datasheet
#define RA8875_DCR_NOFILL 0x00            ///< See datasheet
#define RA8875_DCR_DRAWLINE 0x00          ///< See datasheet
#define RA8875_DCR_DRAWTRIANGLE 0x01      ///< See datasheet
#define RA8875_DCR_DRAWSQUARE 0x10        ///< See datasheet

#define RA8875_ELLIPSE 0xA0        ///< See datasheet
#define RA8875_ELLIPSE_STATUS 0x80 ///< See datasheet

#define RA8875_MWCR0 0x40         ///< See datasheet
#define RA8875_MWCR0_GFXMODE 0x00 ///< See datasheet
#define RA8875_MWCR0_TXTMODE 0x80 ///< See datasheet
#define RA8875_MWCR0_CURSOR 0x40  ///< See datasheet
#define RA8875_MWCR0_BLINK 0x20   ///< See datasheet

#define RA8875_MWCR0_DIRMASK 0x0C ///< Bitmask for Write Direction
#define RA8875_MWCR0_LRTD 0x00    ///< Left->Right then Top->Down
#define RA8875_MWCR0_RLTD 0x04    ///< Right->Left then Top->Down
#define RA8875_MWCR0_TDLR 0x08    ///< Top->Down then Left->Right
#define RA8875_MWCR0_DTLR 0x0C    ///< Down->Top then Left->Right

#define RA8875_BTCR 0x44  ///< See datasheet
#define RA8875_CURH0 0x46 ///< See datasheet
#define RA8875_CURH1 0x47 ///< See datasheet
#define RA8875_CURV0 0x48 ///< See datasheet
#define RA8875_CURV1 0x49 ///< See datasheet

#define RA8875_P1CR 0x8A         ///< See datasheet
#define RA8875_P1CR_ENABLE 0x80  ///< See datasheet
#define RA8875_P1CR_DISABLE 0x00 ///< See datasheet
#define RA8875_P1CR_CLKOUT 0x10  ///< See datasheet
#define RA8875_P1CR_PWMOUT 0x00  ///< See datasheet

#define RA8875_P1DCR 0x8B ///< See datasheet

#define RA8875_P2CR 0x8C         ///< See datasheet
#define RA8875_P2CR_ENABLE 0x80  ///< See datasheet
#define RA8875_P2CR_DISABLE 0x00 ///< See datasheet
#define RA8875_P2CR_CLKOUT 0x10  ///< See datasheet
#define RA8875_P2CR_PWMOUT 0x00  ///< See datasheet

#define RA8875_P2DCR 0x8D ///< See datasheet

#define RA8875_PWM_CLK_DIV1 0x00     ///< See datasheet
#define RA8875_PWM_CLK_DIV2 0x01     ///< See datasheet
#define RA8875_PWM_CLK_DIV4 0x02     ///< See datasheet
#define RA8875_PWM_CLK_DIV8 0x03     ///< See datasheet
#define RA8875_PWM_CLK_DIV16 0x04    ///< See datasheet
#define RA8875_PWM_CLK_DIV32 0x05    ///< See datasheet
#define RA8875_PWM_CLK_DIV64 0x06    ///< See datasheet
#define RA8875_PWM_CLK_DIV128 0x07   ///< See datasheet
#define RA8875_PWM_CLK_DIV256 0x08   ///< See datasheet
#define RA8875_PWM_CLK_DIV512 0x09   ///< See datasheet
#define RA8875_PWM_CLK_DIV1024 0x0A  ///< See datasheet
#define RA8875_PWM_CLK_DIV2048 0x0B  ///< See datasheet
#define RA8875_PWM_CLK_DIV4096 0x0C  ///< See datasheet
#define RA8875_PWM_CLK_DIV8192 0x0D  ///< See datasheet
#define RA8875_PWM_CLK_DIV16384 0x0E ///< See datasheet
#define RA8875_PWM_CLK_DIV32768 0x0F ///< See datasheet

#define RA8875_TPCR0 0x70               ///< See datasheet
#define RA8875_TPCR0_ENABLE 0x80        ///< See datasheet
#define RA8875_TPCR0_DISABLE 0x00       ///< See datasheet
#define RA8875_TPCR0_WAIT_512CLK 0x00   ///< See datasheet
#define RA8875_TPCR0_WAIT_1024CLK 0x10  ///< See datasheet
#define RA8875_TPCR0_WAIT_2048CLK 0x20  ///< See datasheet
#define RA8875_TPCR0_WAIT_4096CLK 0x30  ///< See datasheet
#define RA8875_TPCR0_WAIT_8192CLK 0x40  ///< See datasheet
#define RA8875_TPCR0_WAIT_16384CLK 0x50 ///< See datasheet
#define RA8875_TPCR0_WAIT_32768CLK 0x60 ///< See datasheet
#define RA8875_TPCR0_WAIT_65536CLK 0x70 ///< See datasheet
#define RA8875_TPCR0_WAKEENABLE 0x08    ///< See datasheet
#define RA8875_TPCR0_WAKEDISABLE 0x00   ///< See datasheet
#define RA8875_TPCR0_ADCCLK_DIV1 0x00   ///< See datasheet
#define RA8875_TPCR0_ADCCLK_DIV2 0x01   ///< See datasheet
#define RA8875_TPCR0_ADCCLK_DIV4 0x02   ///< See datasheet
#define RA8875_TPCR0_ADCCLK_DIV8 0x03   ///< See datasheet
#define RA8875_TPCR0_ADCCLK_DIV16 0x04  ///< See datasheet
#define RA8875_TPCR0_ADCCLK_DIV32 0x05  ///< See datasheet
#define RA8875_TPCR0_ADCCLK_DIV64 0x06  ///< See datasheet
#define RA8875_TPCR0_ADCCLK_DIV128 0x07 ///< See datasheet

#define RA8875_TPCR1 0x71            ///< See datasheet
#define RA8875_TPCR1_AUTO 0x00       ///< See datasheet
#define RA8875_TPCR1_MANUAL 0x40     ///< See datasheet
#define RA8875_TPCR1_VREFINT 0x00    ///< See datasheet
#define RA8875_TPCR1_VREFEXT 0x20    ///< See datasheet
#define RA8875_TPCR1_DEBOUNCE 0x04   ///< See datasheet
#define RA8875_TPCR1_NODEBOUNCE 0x00 ///< See datasheet
#define RA8875_TPCR1_IDLE 0x00       ///< See datasheet
#define RA8875_TPCR1_WAIT 0x01       ///< See datasheet
#define RA8875_TPCR1_LATCHX 0x02     ///< See datasheet
#define RA8875_TPCR1_LATCHY 0x03     ///< See datasheet

#define RA8875_TPXH 0x72  ///< See datasheet
#define RA8875_TPYH 0x73  ///< See datasheet
#define RA8875_TPXYL 0x74 ///< See datasheet

#define RA8875_INTC1 0xF0     ///< See datasheet
#define RA8875_INTC1_KEY 0x10 ///< See datasheet
#define RA8875_INTC1_DMA 0x08 ///< See datasheet
#define RA8875_INTC1_TP 0x04  ///< See datasheet
#define RA8875_INTC1_BTE 0x02 ///< See datasheet

#define RA8875_INTC2 0xF1     ///< See datasheet
#define RA8875_INTC2_KEY 0x10 ///< See datasheet
#define RA8875_INTC2_DMA 0x08 ///< See datasheet
#define RA8875_INTC2_TP 0x04  ///< See datasheet
#define RA8875_INTC2_BTE 0x02 ///< See datasheet

#define RA8875_SCROLL_BOTH 0x00   ///< See datasheet
#define RA8875_SCROLL_LAYER1 0x40 ///< See datasheet
#define RA8875_SCROLL_LAYER2 0x80 ///< See datasheet
#define RA8875_SCROLL_BUFFER 0xC0 ///< See datasheet

#define RA8875_DPCR 0x20
#define RA8875_LTPR0 0x52
#define RA8875_MWCR1 0x41

RA8875::RA8875(displaySizes size, void (*volatile Delay)(const uint32_t ticks))
  : LCD(this->calcWidth(size), this->calcHeight(size)), Touch(), _size(size), exDelay(Delay)
{
  ASSERT(Delay);
}

RA8875::~RA8875(void)
{
  /* There's nothing here */
}

bool RA8875::init(void)
{
  if (this->readReg(0) != 0x75)
  {
    return false;
  }

  this->_init();
  this->displayOn();
  this->GPIOX(true);                           // Enable TFT - display enable tied to GPIOX
  this->PWMconf(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  this->touchEnable(true);

  return true;
}

void RA8875::displayOn(void) const
{
  this->writeReg(RA8875_PWRR, RA8875_PWRR_NORMAL | RA8875_PWRR_DISPON);
}

void RA8875::displayOff(void) const
{
  this->writeReg(RA8875_PWRR, RA8875_PWRR_NORMAL | RA8875_PWRR_DISPOFF);
}

void RA8875::setBrightness(const uint8_t percent) const
{
  this->writeReg(RA8875_P1DCR, percent > 100 ? 255 : percent * 2.55f);
}

void RA8875::setLayer(const layers layer)
{
  uint16_t temp = this->readReg(RA8875_MWCR1) & ~(3 << 2);

  switch (layer)
  {
  case layers::LAYER1:
    temp &= ~(1 << 0);
    break;
  case layers::LAYER2:
    temp |= (1 << 0);
    break;
  default:
    return;
  }

  this->writeData(temp);
  this->LCD::setLayer(layer);
}

void RA8875::showLayer(const layers layer) const
{
  if (layer >= layers::LAYER_END)
  {
    return;
  }

  this->writeReg(RA8875_LTPR0, (uint16_t)layer);
}

void RA8875::drawPixel(const Point & point, const Colors color) const
{
  if (color == Colors::TRANSPERENT)
    return;

  const uint16_t x = point.getX();
  const uint16_t y = point.getY();

  this->writeReg(RA8875_CURH0, x);
  this->writeReg(RA8875_CURH1, x >> 8);
  this->writeReg(RA8875_CURV0, y);
  this->writeReg(RA8875_CURV1, y >> 8);
  this->writeCommand(RA8875_MRWC);
  this->writeData(RA8875_DATAWRITE);
  this->writeData((uint16_t)this->Color565To332(color));
}

void RA8875::drawPixels(const Point & startPoint, const uint16_t count, const Colors color) const
{
  if (color == Colors::TRANSPERENT)
    return;

  const uint16_t x = startPoint.getX();
  const uint16_t y = startPoint.getY();
  uint16_t num = count;

  this->writeReg(RA8875_CURH0, x);
  this->writeReg(RA8875_CURH1, x >> 8);
  this->writeReg(RA8875_CURV0, y);
  this->writeReg(RA8875_CURV1, y >> 8);

  this->writeReg(RA8875_MRWC, RA8875_DATAWRITE);

  const uint16_t _color = (uint16_t)this->Color565To332(color);

  while (num--)
  {
    this->writeData(_color);
  }
}

void RA8875::drawPixels(const Point & startPoint, const uint16_t count, const Colors * const color) const
{
  const uint16_t x = startPoint.getX();
  const uint16_t y = startPoint.getY();
  uint16_t num = count;
  const Colors * ptrColor = color;

  this->writeReg(RA8875_CURH0, x);
  this->writeReg(RA8875_CURH1, x >> 8);
  this->writeReg(RA8875_CURV0, y);
  this->writeReg(RA8875_CURV1, y >> 8);

  this->writeCommand(RA8875_MRWC);
  this->writeData(RA8875_DATAWRITE);

  while (num--)
  {
    Colors color = *(ptrColor++);
    if (color == Colors::TRANSPERENT)
      color = Colors::BACKGROUND;

    this->writeData((uint16_t)this->Color565To332(color));
  }
}

void RA8875::fillScreen(const Colors color) const
{
  this->draw(Rectangle({ 0, 0 }, this->getWigth(), this->getHeight(), color), true);
}

void RA8875::draw(const Rectangle & object, bool fill) const
{
  if (object.getColor() == Colors::TRANSPERENT)
    return;

  const uint16_t x = object.getNullPoint().getX();
  const uint16_t y = object.getNullPoint().getY();

  this->rectHelper(x, y, x + object.getWidth() - 1, y + object.getHeight() - 1, (uint16_t)object.getColor(), fill);
}

void RA8875::draw(const Ellipse & object, bool fill) const
{
  if (object.getColor() == Colors::TRANSPERENT)
    return;

  const uint16_t w = object.getWidth();
  const uint16_t h = object.getHeight();

  if (w != h)
  {
    this->ellipseHelper(
      object.getCenterW(), object.getCenterH(), (w - 1) / 2, (h - 1) / 2, (uint16_t)object.getColor(), fill);
  }
  else
  {
    this->circleHelper(object.getCenterW(), object.getCenterH(), (w - 1) / 2, (uint16_t)object.getColor(), fill);
  }
}

void RA8875::draw(const Curve & object, bool fill) const
{
  if (object.getColor() == Colors::TRANSPERENT)
    return;

  this->curveHelper(object.getCenterW(),
    object.getCenterH(),
    (object.getWidth() - 1) / 2,
    (object.getHeight() - 1) / 2,
    (uint8_t)object.getMode(),
    (uint16_t)object.getColor(),
    fill);
}

void RA8875::draw(const RoundRect & object, bool fill) const
{
  if (object.getColor() == Colors::TRANSPERENT)
    return;

  const uint16_t x = object.getNullPoint().getX();
  const uint16_t y = object.getNullPoint().getY();

  this->roundRectHelper(
    x, y, x + object.getWidth() - 1, y + object.getHeight() - 1, object.getRadius(), (uint16_t)object.getColor(), fill);
}

void RA8875::draw(const Triangle & object, bool fill) const
{
  if (object.getColor() == Colors::TRANSPERENT)
    return;

  this->triangleHelper(object[0].getX(),
    object[0].getY(),
    object[1].getX(),
    object[1].getY(),
    object[2].getX(),
    object[2].getY(),
    (uint16_t)object.getColor(),
    fill);
}

bool RA8875::isTouched(void) const
{
  return (this->readReg(RA8875_INTC2) & RA8875_INTC2_TP);
}

const VA::Point RA8875::getTouchPoint(void) const
{
  bool currentTouthState = this->isTouched();
  if (currentTouthState)
  {
    const Point touthPoint0 = this->touchRead();

    if (touchPointFiltred == Point())
    {
      touchPointFiltred = touthPoint0;
    }

    const auto filtrationCoordinate = [&](const uint16_t (VA::Point::*memberGet)(void) const) {
      const float K = 0.65f;
      return (touchPointFiltred.*memberGet)() * K + (touthPoint0.*memberGet)() * (1 - K);
    };

    if (touthPoint0.getX() < this->getWigth())
    {
      touchPointFiltred.setX(filtrationCoordinate(&VA::Point::getX));
    }
    if (touthPoint0.getY() < this->getHeight())
    {
      touchPointFiltred.setY(filtrationCoordinate(&VA::Point::getY));
    }
  }
  else if (!previosTouthState && !currentTouthState)
  {
    touchPointFiltred = Point();
  }
  previosTouthState = currentTouthState;

  return this->touchPointFiltred;
}

const Point RA8875::touchRead(void) const
{
  uint16_t tx, ty;
  uint8_t temp;

  tx = this->readReg(RA8875_TPXH);
  ty = this->readReg(RA8875_TPYH);
  temp = this->readReg(RA8875_TPXYL);
  tx <<= 2;
  ty <<= 2;
  tx |= temp & 0x03;        // get the bottom x bits
  ty |= (temp >> 2) & 0x03; // get the bottom y bits

  tx = this->_width - (tx - correctCoordinate::X0) * this->_width / (correctCoordinate::X - correctCoordinate::X0);
  ty = this->_height - (ty - correctCoordinate::Y0) * this->_height / (correctCoordinate::Y - correctCoordinate::Y0);

  /* Clear TP INT Status */
  this->writeReg(RA8875_INTC2, RA8875_INTC2_TP);

  return Point(tx, ty);
}

const VA::Colors RA8875::Color565To332(const VA::Colors color) const
{
  const uint16_t _color = (uint16_t)color;

  struct RGB565
  {
    uint16_t B : 5;
    uint16_t G : 6;
    uint16_t R : 5;
  };

  struct RGB332
  {
    uint8_t B : 2;
    uint8_t G : 3;
    uint8_t R : 3;
  };

  const RGB565 * pCol565 = (const RGB565 *)&_color;

  const RGB332 col332 = { .B = (uint8_t)roundf(pCol565->B * 0.0968f),
    .G = (uint8_t)roundf(pCol565->G * 0.1111f),
    .R = (uint8_t)roundf(pCol565->R * 0.2255f) };

  return (VA::Colors) * (uint8_t *)&col332;
}

const uint16_t RA8875::calcWidth(const displaySizes size) const
{
  switch (size)
  {
  case displaySizes::_480x80:
  case displaySizes::_480x128:
  case displaySizes::_480x272:
    return 480;
  case displaySizes::_800x480:
    return 800;
  default:
    return 480;
  };
}

const uint16_t RA8875::calcHeight(const displaySizes size) const
{
  switch (size)
  {
  case displaySizes::_480x80:
    return 80;
  case displaySizes::_480x128:
    return 128;
  case displaySizes::_480x272:
    return 272;
  case displaySizes::_800x480:
    return 480;
  default:
    return 80;
  };
}

void RA8875::_init(void) const
{
  this->PLLinit();
  this->writeReg(RA8875_SYSR, RA8875_SYSR_16BPP | RA8875_SYSR_MCU16);

  /* Timing values */
  uint16_t pixclk;
  uint16_t hsync_start;
  uint16_t hsync_pw;
  uint16_t hsync_finetune;
  uint16_t hsync_nondisp;
  uint16_t vsync_pw;
  uint16_t vsync_nondisp;
  uint16_t vsync_start;
  uint8_t voffset;

  /* Set the correct values for the display being used */
  if (this->_size == displaySizes::_480x80)
  {
    pixclk = RA8875_PCSR_PDATL | RA8875_PCSR_4CLK;
    hsync_nondisp = 10;
    hsync_start = 8;
    hsync_pw = 48;
    hsync_finetune = 0;
    vsync_nondisp = 3;
    vsync_start = 8;
    vsync_pw = 10;
    voffset = 192; // This uses the bottom 80 pixels of a 272 pixel controller
  }
  else if (this->_size == displaySizes::_480x128 || this->_size == displaySizes::_480x272)
  {
    pixclk = RA8875_PCSR_PDATL | RA8875_PCSR_4CLK;
    hsync_nondisp = 10;
    hsync_start = 8;
    hsync_pw = 48;
    hsync_finetune = 0;
    vsync_nondisp = 3;
    vsync_start = 8;
    vsync_pw = 10;
    voffset = 0;
  }
  else
  { // (_size == RA8875_800x480)
    pixclk = RA8875_PCSR_PDATR | RA8875_PCSR_CLK;
    hsync_nondisp = 26;
    hsync_start = 32;
    hsync_pw = 96;
    hsync_finetune = 0;
    vsync_nondisp = 32;
    vsync_start = 23;
    vsync_pw = 2;
    voffset = 0;
  }

  this->writeReg(RA8875_PCSR, pixclk);

  this->exDelay(1);

  // this->writeReg(0x10, 0x0A);

  /* Horizontal settings registers */
  // H width: (HDWR + 1) * 8 = 480
  this->writeReg(RA8875_HDWR, (_width / 8) - 1);
  this->writeReg(RA8875_HNDFTR, RA8875_HNDFTR_DE_HIGH + hsync_finetune);
  // H non-display: HNDR * 8 + HNDFTR + 2 = 10
  this->writeReg(RA8875_HNDR, (hsync_nondisp - hsync_finetune - 2) / 8);
  // Hsync start: (HSTR + 1)*8
  this->writeReg(RA8875_HSTR, hsync_start / 8 - 1);
  // HSync pulse width = (HPWR+1) * 8
  this->writeReg(RA8875_HPWR, RA8875_HPWR_LOW + (hsync_pw / 8 - 1));

  /* Vertical settings registers */
  this->writeReg(RA8875_VDHR0, (uint16_t)(this->_height - 1 + voffset) & 0xFF);
  this->writeReg(RA8875_VDHR1, (uint16_t)(this->_height - 1 + voffset) >> 8);
  // V non-display period = VNDR + 1
  this->writeReg(RA8875_VNDR0, vsync_nondisp - 1);
  this->writeReg(RA8875_VNDR1, vsync_nondisp >> 8);
  // Vsync start position = VSTR + 1
  this->writeReg(RA8875_VSTR0, vsync_start - 1);
  this->writeReg(RA8875_VSTR1, vsync_start >> 8);
  // Vsync pulse width = VPWR + 1
  this->writeReg(RA8875_VPWR, RA8875_VPWR_LOW + vsync_pw - 1);

  /*---for  2 layers----------------------------------------------*/

  this->writeReg(0x20, 0x80);

  /*--------------------------------------------------------------*/

  /* Set active window X */
  // horizontal start point
  this->writeReg(RA8875_HSAW0, 0);
  this->writeReg(RA8875_HSAW1, 0);
  // horizontal end point
  this->writeReg(RA8875_HEAW0, (uint16_t)(this->_width) & 0xFF);
  this->writeReg(RA8875_HEAW1, (uint16_t)(this->_width) >> 8);

  /* Set active window Y */
  // vertical start point
  this->writeReg(RA8875_VSAW0, 0 + voffset);
  this->writeReg(RA8875_VSAW1, 0 + voffset);
  // vertical end point
  this->writeReg(RA8875_VEAW0, (uint16_t)(this->_height + voffset) & 0xFF);
  this->writeReg(RA8875_VEAW1, (uint16_t)(this->_height + voffset) >> 8);

  /* ToDo: Setup touch panel? */

  /* Clear the entire window */
  this->writeReg(RA8875_MCLR, RA8875_MCLR_START | RA8875_MCLR_FULL);

  this->exDelay(50);
}

void RA8875::PLLinit(void) const
{
  if (this->_size == displaySizes::_480x80 || this->_size == displaySizes::_480x128 ||
      this->_size == displaySizes::_480x272)
  {
    this->writeReg(RA8875_PLLC1, RA8875_PLLC1_PLLDIV1 + 10);
    this->exDelay(1);
    this->writeReg(RA8875_PLLC2, RA8875_PLLC2_DIV4);
    this->exDelay(1);
  }
  else /* (_size == RA8875_800x480) */
  {
    this->writeReg(RA8875_PLLC1, 5);
    this->exDelay(1);
    this->writeReg(RA8875_PLLC2, RA8875_PLLC2_DIV2);
    this->exDelay(1);
  }
}

void RA8875::GPIOX(bool status) const
{
  this->writeReg(RA8875_GPIOX, status);
}

void RA8875::PWMconf(bool status, const uint8_t clock) const
{
  this->writeReg(RA8875_P1CR, (status ? RA8875_P1CR_ENABLE : RA8875_P1CR_DISABLE) | (clock & 0xF));
}

void RA8875::setColor(uint32_t color) const
{
  if (((VA::Colors)color) == Colors::NOT_CHANGE)
    return;

  color = (uint16_t)this->Color565To332((VA::Colors)color);

  this->writeReg(0x63, (color & 0xE0) >> 5);
  this->writeReg(0x64, (color & 0x1C) >> 2);
  this->writeReg(0x65, (color & 0x03));

  // this->writeCommand(0x63);
  // this->writeData((color & 0xf800) >> 11);
  // this->writeCommand(0x64);
  // this->writeData((color & 0x07e0) >> 5);
  // this->writeCommand(0x65);
  // this->writeData((color & 0x001f));
}

void RA8875::circleHelper(uint16_t x, uint16_t y, uint16_t r, uint32_t color, bool filled) const
{
  /* Set X */
  this->writeReg(0x99, x);
  this->writeReg(0x9a, x >> 8);

  /* Set Y */
  this->writeReg(0x9b, y);
  this->writeReg(0x9c, y >> 8);

  /* Set Radius */
  this->writeReg(0x9d, r);

  /* Set Color */
  this->setColor(color);

  /* Draw! */
  this->writeReg(RA8875_DCR, RA8875_DCR_CIRCLE_START | (filled ? RA8875_DCR_FILL : RA8875_DCR_NOFILL));

  /* Wait for the command to finish */
  this->waitPoll(RA8875_DCR, RA8875_DCR_CIRCLE_STATUS);
}

void RA8875::rectHelper(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color, bool filled) const
{
  /* Set X */
  this->writeReg(0x91, x);
  this->writeReg(0x92, x >> 8);

  /* Set Y */
  this->writeReg(0x93, y);
  this->writeReg(0x94, y >> 8);

  /* Set X1 */
  this->writeReg(0x95, w);
  this->writeReg(0x96, w >> 8);

  /* Set Y1 */
  this->writeReg(0x97, h);
  this->writeReg(0x98, h >> 8);

  /* Set Color */
  this->setColor(color);

  /* Draw! */
  this->writeReg(RA8875_DCR, filled ? 0xB0 : 0x90);

  /* Wait for the command to finish */
  this->waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

void RA8875::triangleHelper(
  uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color, bool filled) const
{
  /* Set Point 0 */
  this->writeReg(0x91, x0);
  this->writeReg(0x92, x0 >> 8);
  this->writeReg(0x93, y0);
  this->writeReg(0x94, y0 >> 8);

  /* Set Point 1 */
  this->writeReg(0x95, x1);
  this->writeReg(0x96, x1 >> 8);
  this->writeReg(0x97, y1);
  this->writeReg(0x98, y1 >> 8);

  /* Set Point 2 */
  this->writeReg(0xA9, x2);
  this->writeReg(0xAA, x2 >> 8);
  this->writeReg(0xAB, y2);
  this->writeReg(0xAC, y2 >> 8);

  /* Set Color */
  this->setColor(color);

  /* Draw! */
  this->writeReg(RA8875_DCR, filled ? 0xA1 : 0x81);

  /* Wait for the command to finish */
  this->waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

void RA8875::ellipseHelper(
  uint16_t xCenter, uint16_t yCenter, uint16_t longAxis, uint16_t shortAxis, uint32_t color, bool filled) const
{
  /* Set Center Point */
  this->writeReg(0xA5, xCenter);
  this->writeReg(0xA6, xCenter >> 8);
  this->writeReg(0xA7, yCenter);
  this->writeReg(0xA8, yCenter >> 8);

  /* Set Long and Short Axis */
  this->writeReg(0xA1, longAxis);
  this->writeReg(0xA2, longAxis >> 8);
  this->writeReg(0xA3, shortAxis);
  this->writeReg(0xA4, shortAxis >> 8);

  /* Set Color */
  this->setColor(color);

  /* Draw! */
  this->writeReg(0xA0, filled ? 0xC0 : 0x80);

  /* Wait for the command to finish */
  this->waitPoll(RA8875_ELLIPSE, RA8875_ELLIPSE_STATUS);
}

void RA8875::curveHelper(uint16_t xCenter, uint16_t yCenter, uint16_t longAxis, uint16_t shortAxis, uint8_t curvePart,
  uint32_t color, bool filled) const
{
  /* Set Center Point */
  this->writeReg(0xA5, xCenter);
  this->writeReg(0xA6, xCenter >> 8);
  this->writeReg(0xA7, yCenter);
  this->writeReg(0xA8, yCenter >> 8);

  /* Set Long and Short Axis */
  this->writeReg(0xA1, longAxis);
  this->writeReg(0xA2, longAxis >> 8);
  this->writeReg(0xA3, shortAxis);
  this->writeReg(0xA4, shortAxis >> 8);

  /* Set Color */
  this->setColor(color);

  /* Draw! */
  this->writeReg(0xA0, (filled ? 0xD0 : 0x90) | (curvePart & 0x03));

  /* Wait for the command to finish */
  this->waitPoll(RA8875_ELLIPSE, RA8875_ELLIPSE_STATUS);
}

void RA8875::roundRectHelper(
  uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint32_t color, bool filled) const
{
  auto calcR = [](uint16_t r, uint16_t len) { return (len < r * 2) ? len / 2 : r; };

  const uint16_t rx = calcR(r, w - x);
  const uint16_t ry = calcR(r, h - y);

  /* Set X */
  this->writeReg(0x91, x);
  this->writeReg(0x92, x >> 8);

  /* Set Y */
  this->writeReg(0x93, y);
  this->writeReg(0x94, y >> 8);

  /* Set X1 */
  this->writeReg(0x95, w);
  this->writeReg(0x96, w >> 8);

  /* Set Y1 */
  this->writeReg(0x97, h);
  this->writeReg(0x98, h >> 8);

  this->writeReg(0xA1, rx);
  this->writeReg(0xA2, rx >> 8);

  this->writeReg(0xA3, ry);
  this->writeReg(0xA4, ry >> 8);

  /* Set Color */
  this->setColor(color);

  /* Draw! */
  this->writeReg(RA8875_ELLIPSE, filled ? 0xE0 : 0xA0);

  /* Wait for the command to finish */
  this->waitPoll(RA8875_ELLIPSE, RA8875_DCR_LINESQUTRI_STATUS);
}

void RA8875::touchEnable(bool on) const
{
  const uint16_t adcClk =
    (uint16_t)(this->_size == displaySizes::_800x480 ? RA8875_TPCR0_ADCCLK_DIV16 : RA8875_TPCR0_ADCCLK_DIV4);

  if (on)
  {
    /* Enable Touch Panel (Reg 0x70) */
    this->writeReg(RA8875_TPCR0,
      RA8875_TPCR0_ENABLE | RA8875_TPCR0_WAIT_4096CLK | RA8875_TPCR0_WAKEENABLE | adcClk); // 10mhz max!
    /* Set Auto Mode      (Reg 0x71) */
    this->writeReg(RA8875_TPCR1, RA8875_TPCR1_AUTO | RA8875_TPCR1_DEBOUNCE);
    /* Enable TP INT */
    this->writeReg(RA8875_INTC1, this->readReg(RA8875_INTC1) | RA8875_INTC1_TP);
  }
  else
  {
    /* Disable TP INT */
    this->writeReg(RA8875_INTC1, this->readReg(RA8875_INTC1) & ~RA8875_INTC1_TP);
    /* Disable Touch Panel (Reg 0x70) */
    this->writeReg(RA8875_TPCR0, RA8875_TPCR0_DISABLE);
  }
}

void RA8875::delay(volatile uint32_t micros) const
{
  while (micros--)
    continue;
}

void RA8875::writeCommand(const uint16_t reg) const
{
  *(LCD_REG) = reg;
  this->delay(del);
}

void RA8875::writeData(const uint16_t data) const
{
  *(LCD_DATA) = data;
  this->delay(del);
}

void RA8875::writeReg(const uint16_t reg, const uint16_t data) const
{
  this->writeCommand(reg);
  this->writeData(data);
}

const uint16_t RA8875::readCommand(void) const
{
  this->delay(del);
  return *(LCD_REG);
}

const uint16_t RA8875::readData(void) const
{
  this->delay(del);
  return *(LCD_DATA);
}

const uint16_t RA8875::readReg(const uint16_t reg) const
{
  this->writeCommand(reg);
  return this->readData();
}

const bool RA8875::waitPoll(const uint16_t regname, const uint16_t waitflag) const
{
  while (true)
  {
    const uint16_t temp = this->readReg(regname);

    if ((temp & waitflag) == false)
    {
      return true;
    }
  }
  return false;
}

} // namespace VA