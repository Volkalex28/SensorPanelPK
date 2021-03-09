/*!
 * @file     Adafruit_RA8875.cpp
 *
 * @mainpage Adafruit RA8875 TFT Driver
 *
 * @author   Limor Friend/Ladyada, K.Townsend/KTOWN for Adafruit Industries
 *
 * @section intro_sec Introduction
 *
 * This is the library for the Adafruit RA8875 Driver board for TFT displays
 * ---------------> http://www.adafruit.com/products/1590
 * The RA8875 is a TFT driver for up to 800x480 dotclock'd displays
 * It is tested to work with displays in the Adafruit shop. Other displays
 * may need timing adjustments and are not guanteed to work.
 *
 * Adafruit invests time and resources providing this open
 * source code, please support Adafruit and open-source hardware
 * by purchasing products from Adafruit!
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * BSD license, check license.txt for more information.
 * All text above must be included in any redistribution.
 *
 * @section  HISTORY
 *
 * v1.0 - First release
 *
 */

#include "Adafruit_RA8875.h"
#include "math.h"

/**************************************************************************/
/*!
      Constructor for a new RA8875 instance

      @param CS  Location of the SPI chip select pin
      @param RST Location of the reset pin
*/
/**************************************************************************/

void delay(volatile uint32_t micros) {
//	micros *= SystemCoreClock/1000000000000000/5;
	while(micros--);
}
/**************************************************************************/
/*!
      Initialises the LCD driver and any HW required by the display

      @param s The display size, which can be either:
                  'RA8875_480x80'  (3.8" displays) or
                  'RA8875_480x128' (3.9" displays) or
                  'RA8875_480x272' (4.3" displays) or
                  'RA8875_800x480' (5" and 7" displays)

      @return True if we reached the end
*/


/**************************************************************************/
Adafruit_RA8875::Adafruit_RA8875(enum RA8875sizes s) {
	this->_size = s;

	if (this->_size == RA8875_480x80) {
		this->_width = 480;
		this->_height = 80;
	}
	else if (this->_size == RA8875_480x128) {
		this->_width = 480;
		this->_height = 128;
	} else if (this->_size == RA8875_480x272) {
		this->_width = 480;
		this->_height = 272;
	} else if (this->_size == RA8875_800x480) {
		this->_width = 800;
		this->_height = 480;
	} else {
		return;
	}
	this->_rotation = 0;
}

bool Adafruit_RA8875::begin() {

	if (this->readReg(0) != 0x75) { //75
	  return false;
	}

	this->initialize();

	return true;
}

/************************* Initialization *********************************/

/**************************************************************************/
/*!
      Performs a SW-based reset of the RA8875
*/
/**************************************************************************/
void Adafruit_RA8875::softReset(void) {
	this->writeCommand(RA8875_PWRR);
	this->writeData(RA8875_PWRR_SOFTRESET);
	this->writeData(RA8875_PWRR_NORMAL);
	HAL_Delay(1);
}

/**************************************************************************/
/*!
      Initialise the PLL
*/
/**************************************************************************/
void Adafruit_RA8875::PLLinit(void) {
	if (this->_size == RA8875_480x80 || this->_size == RA8875_480x128 ||
		  this->_size == RA8875_480x272
	) {
		this->writeReg(RA8875_PLLC1, RA8875_PLLC1_PLLDIV1 + 10);
		HAL_Delay(1);
		this->writeReg(RA8875_PLLC2, RA8875_PLLC2_DIV4);
		HAL_Delay(1);
	}
	else /* (_size == RA8875_800x480) */ {
		this->writeReg(RA8875_PLLC1, RA8875_PLLC1_PLLDIV1 + 11);
		HAL_Delay(1);
		this->writeReg(RA8875_PLLC2, RA8875_PLLC2_DIV4);
		HAL_Delay(1);
  }
}

/**************************************************************************/
/*!
      Initialises the driver IC (clock setup, etc.)
*/
/**************************************************************************/
void Adafruit_RA8875::initialize(void) {
	this->PLLinit();
	this->writeReg(RA8875_SYSR, RA8875_SYSR_8BPP | RA8875_SYSR_MCU8);

	/* Timing values */
	uint16_t pixclk;
	uint16_t hsync_start;
	uint16_t hsync_pw;
	uint16_t hsync_finetune;
	uint16_t hsync_nondisp;
	uint16_t vsync_pw;
	uint16_t vsync_nondisp;
	uint16_t vsync_start;

	/* Set the correct values for the display being used */
	if (this->_size == RA8875_480x80) {
		pixclk = RA8875_PCSR_PDATL | RA8875_PCSR_4CLK;
		hsync_nondisp = 10;
		hsync_start = 8;
		hsync_pw = 48;
		hsync_finetune = 0;
		vsync_nondisp = 3;
		vsync_start = 8;
		vsync_pw = 10;
		this->_voffset = 192; // This uses the bottom 80 pixels of a 272 pixel controller
	}
	else if (this->_size == RA8875_480x128 || this->_size == RA8875_480x272) {
		pixclk = RA8875_PCSR_PDATL | RA8875_PCSR_4CLK;
		hsync_nondisp = 10;
		hsync_start = 8;
		hsync_pw = 48;
		hsync_finetune = 0;
		vsync_nondisp = 3;
		vsync_start = 8;
		vsync_pw = 10;
		this->_voffset = 0;
	}
	else { // (_size == RA8875_800x480)
		pixclk = RA8875_PCSR_PDATL | RA8875_PCSR_2CLK;
		hsync_nondisp = 26;
		hsync_start = 32;
		hsync_pw = 96;
		hsync_finetune = 0;
		vsync_nondisp = 32;
		vsync_start = 23;
		vsync_pw = 2;
		this->_voffset = 0;
	}

	this->writeReg(RA8875_PCSR, pixclk);
	HAL_Delay(1);

	this->writeReg(0x10, 0x0A);

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
	this->writeReg(RA8875_VDHR0, (uint16_t)(this->_height - 1 + this->_voffset) & 0xFF);
	this->writeReg(RA8875_VDHR1, (uint16_t)(this->_height - 1 + this->_voffset) >> 8);
	// V non-display period = VNDR + 1
	this->writeReg(RA8875_VNDR0, vsync_nondisp - 1);
	this->writeReg(RA8875_VNDR1, vsync_nondisp >> 8);
	// Vsync start position = VSTR + 1
	this->writeReg(RA8875_VSTR0, vsync_start - 1);
	this->writeReg(RA8875_VSTR1, vsync_start >> 8);
	// Vsync pulse width = VPWR + 1
	this->writeReg(RA8875_VPWR, RA8875_VPWR_LOW + vsync_pw - 1);

	/*---for  2 layers----------------------------------------------*/

	this->writeReg(0x20 , 0x80);

	/*--------------------------------------------------------------*/

	/* Set active window X */
	// horizontal start point
	this->writeReg(RA8875_HSAW0, 0);
	this->writeReg(RA8875_HSAW1, 0);
	// horizontal end point
	this->writeReg(RA8875_HEAW0, (uint16_t)(this->_width - 1) & 0xFF);
	this->writeReg(RA8875_HEAW1, (uint16_t)(this->_width - 1) >> 8);

	/* Set active window Y */
	// vertical start point
	this->writeReg(RA8875_VSAW0, 0 + this->_voffset);
	this->writeReg(RA8875_VSAW1, 0 + this->_voffset);
	// vertical end point
	this->writeReg(RA8875_VEAW0, (uint16_t)(this->_height - 1 + this->_voffset) & 0xFF);
	this->writeReg(RA8875_VEAW1, (uint16_t)(this->_height - 1 + this->_voffset) >> 8);

	/* ToDo: Setup touch panel? */

	/* Clear the entire window */
	this->writeReg(RA8875_MCLR, RA8875_MCLR_START | RA8875_MCLR_FULL);
	HAL_Delay(50);
}

/**************************************************************************/
/*!
      Returns the display width in pixels

      @return  The 1-based display width in pixels
*/
/**************************************************************************/
uint16_t Adafruit_RA8875::width(void) { return this->_width; }

/**************************************************************************/
/*!
      Returns the display height in pixels

      @return  The 1-based display height in pixels
*/
/**************************************************************************/
uint16_t Adafruit_RA8875::height(void) { return this->_height; }

/**************************************************************************/
/*!
 Returns the current rotation (0-3)

 @return  The Rotation Setting
 */
/**************************************************************************/
int8_t Adafruit_RA8875::getRotation(void) { return this->_rotation; }

/**************************************************************************/
/*!
 Sets the current rotation (0-3)

 @param rotation The Rotation Setting
 */
/**************************************************************************/
void Adafruit_RA8875::setRotation(int8_t rotation) {
	switch (rotation) {
		case 2:
			this->_rotation = rotation;
		break;
		default:
			this->_rotation = 0;
		break;
	}
}

/************************* Text Mode ***********************************/

/**************************************************************************/
/*!
      Sets the display in text mode (as opposed to graphics mode)
*/
/**************************************************************************/
void Adafruit_RA8875::textMode(void) {
	/* Set text mode */
	this->writeCommand(RA8875_MWCR0);
	uint16_t temp = this->readData();
	temp |= RA8875_MWCR0_TXTMODE; // Set bit 7
	this->writeData(temp);

	/* Select the internal (ROM) font */
	this->writeCommand(0x21);
	temp = this->readData();
	temp &= ~((1 << 7) | (1 << 5)); // Clear bits 7 and 5
	this->writeData(temp);
}

/**************************************************************************/
/*!
      Sets the display in text mode (as opposed to graphics mode)

      @param x The x position of the cursor (in pixels, 0..1023)
      @param y The y position of the cursor (in pixels, 0..511)
*/
/**************************************************************************/
void Adafruit_RA8875::textSetCursor(uint16_t x, uint16_t y) {
	x = this->applyRotationX(x);
	y = this->applyRotationY(y);

	/* Set cursor location */
	this->writeCommand(0x2A);
	this->writeData(x & 0xFF);
	this->writeCommand(0x2B);
	this->writeData(x >> 8);
	this->writeCommand(0x2C);
	this->writeData(y & 0xFF);
	this->writeCommand(0x2D);
	this->writeData(y >> 8);
}

/**************************************************************************/
/*!
      Sets the fore and background color when rendering text

      @param foreColor The RGB565 color to use when rendering the text
      @param bgColor   The RGB565 colot to use for the background
*/
/**************************************************************************/
void Adafruit_RA8875::textColor(uint16_t foreColor, uint16_t bgColor) {
	/* Set Fore Color */
	this->writeCommand(0x63);
	this->writeData((foreColor & 0xf800) >> 11);
	this->writeCommand(0x64);
	this->writeData((foreColor & 0x07e0) >> 5);
	this->writeCommand(0x65);
	this->writeData((foreColor & 0x001f));

	/* Set Background Color */
	this->writeCommand(0x60);
	this->writeData((bgColor & 0xf800) >> 11);
	this->writeCommand(0x61);
	this->writeData((bgColor & 0x07e0) >> 5);
	this->writeCommand(0x62);
	this->writeData((bgColor & 0x001f));

	/* Clear transparency flag */
	this->writeCommand(0x22);
	uint16_t temp = this->readData();
	temp &= ~(1 << 6); // Clear bit 6
	this->writeData(temp);
}

/**************************************************************************/
/*!
      Sets the fore color when rendering text with a transparent bg

      @param foreColor The RGB565 color to use when rendering the text
*/
/**************************************************************************/
void Adafruit_RA8875::textTransparent(uint16_t foreColor) {
	/* Set Fore Color */
	this->writeCommand(0x63);
	this->writeData((foreColor & 0xf800) >> 11);
	this->writeCommand(0x64);
	this->writeData((foreColor & 0x07e0) >> 5);
	this->writeCommand(0x65);
	this->writeData((foreColor & 0x001f));

	/* Set transparency flag */
	this->writeCommand(0x22);
	uint16_t temp = this->readData();
	temp |= (1 << 6); // Set bit 6
	this->writeData(temp);
}

/**************************************************************************/
/*!
      Sets the text enlarge settings, using one of the following values:

      0 = 1x zoom
      1 = 2x zoom
      2 = 3x zoom
      3 = 4x zoom

      @param scale   The zoom factor (0..3 for 1-4x zoom)
*/
/**************************************************************************/
void Adafruit_RA8875::textEnlarge(uint8_t scale) {
	if (scale > 3) {
		scale = 3; // highest setting is 3
	}

	/* Set font size flags */
	//this->writeCommand(0x22);
	uint16_t temp = this->readReg(0x22) & ~0xF;
	temp |= (scale << 2) & 0xF;
	temp |= scale & 0xF;

	this->writeReg(0x22, temp);

	this->_textScale = scale;
}

/**************************************************************************/
/*!
     Enable Cursor Visibility and Blink
     Here we set bits 6 and 5 in 40h
     As well as the set the blink rate in 44h
     The rate is 0 through max 255
     the lower the number the faster it blinks (00h is 1 frame time,
     FFh is 256 Frames time.
     Blink Time (sec) = BTCR[44h]x(1/Frame_rate)

     @param rate The frame rate to blink
 */
/**************************************************************************/

void Adafruit_RA8875::cursorBlink(uint8_t rate) {
	this->writeCommand(RA8875_MWCR0);
	uint16_t temp = this->readData();
	temp |= RA8875_MWCR0_CURSOR;
	this->writeData(temp);

	this->writeCommand(RA8875_MWCR0);
	temp = this->readData();
	temp |= RA8875_MWCR0_BLINK;
	this->writeData(temp);

	if (rate > 255) {
		rate = 255;
	}
	this->writeCommand(RA8875_BTCR);
	this->writeData(rate);
}

/**************************************************************************/
/*!
      Renders some text on the screen when in text mode

      @param buffer    The buffer containing the characters to render
      @param len       The size of the buffer in bytes
*/
/**************************************************************************/
void Adafruit_RA8875::textWrite(const char *buffer, uint16_t len) {
	if (len == 0) {
		len = strlen(buffer);
	}
	this->writeCommand(RA8875_MRWC);
	for (uint16_t i = 0; i < len; i++) {
		this->writeData(buffer[i]);
		delay(30);
	}
}


/**************************************************************************/
/*!
 	 загрузка символа шрифта


*/
/**************************************************************************/
void Adafruit_RA8875::CharFont(uint8_t pos, uint8_t* data) {
	this->writeReg(0x40, this->readReg(0x40) & ~0x80);
	this->writeReg(0x23, pos);
	this->writeReg(0x21, this->readReg(0x21) & ~0x80);
	this->writeReg(0x41, (this->readReg(0x41) & ~0x08) | 0x04);
	this->writeCommand(0x02);
	//пишем данные символа 8х16
	for (uint8_t x = 0; x < 16; x++) {
		this->writeData(*data++);
	}
}


void Adafruit_RA8875::DownloadFont(uint8_t* buffer, uint16_t begin, uint16_t len) {
	for (uint16_t i = 0; i < len; i++) {
		this->CharFont(begin + i, buffer + i * 16);
	}
	//writeReg(0x41, 0x00); //запись в слой


}

/************************* Graphics ***********************************/

/**************************************************************************/
/*!
      Sets the display in graphics mode (as opposed to text mode)
*/
/**************************************************************************/
void Adafruit_RA8875::graphicsMode(void) {
	this->writeCommand(RA8875_MWCR0);
	uint16_t temp = this->readData();
	temp &= ~RA8875_MWCR0_TXTMODE; // bit #7
	this->writeData(temp);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/

uint8_t Adafruit_RA8875::Colour565To332(uint16_t colour) {
	struct RGB565 {
		uint16_t B : 5;
		uint16_t G : 6;
		uint16_t R : 5;
	}* pCol565;

	struct RGB332 {
		uint8_t B : 2;
		uint8_t G : 3;
		uint8_t R : 3;
	} Col332;

	pCol565 = (RGB565*)&colour;

	Col332.R = roundf(pCol565->R * 0.2255f);
	Col332.G = roundf(pCol565->G * 0.1111f);
	Col332.B = roundf(pCol565->B * 0.0968f);

	return *(uint8_t*)&Col332;
}


/**************************************************************************/
/*!
      Waits for screen to finish by polling the status!

      @param regname The register name to check
      @param waitflag The value to wait for the status register to match

      @return True if the expected status has been reached
*/
/**************************************************************************/
bool Adafruit_RA8875::waitPoll(uint16_t regname, uint16_t waitflag) {
	/* Wait for the command to finish */
	while (1) {
		uint16_t temp = this->readReg(regname);
		delay(1);
		if (!(temp & waitflag)) {
			return true;
		}
	}
	return false; // MEMEFIX: yeah i know, unreached! - add timeout?
}

/**************************************************************************/
/*!
      Sets the current X/Y position on the display before drawing

      @param x The 0-based x location
      @param y The 0-base y location
*/
/**************************************************************************/
void Adafruit_RA8875::setXY(uint16_t x, uint16_t y) {
	this->writeReg(RA8875_CURH0, x);
	this->writeReg(RA8875_CURV0, y);
}

/**************************************************************************/
/*!
      HW accelerated function to push a chunk of raw pixel data

      @param num The number of pixels to push
      @param p   The pixel color to use
*/
/**************************************************************************/
void Adafruit_RA8875::pushPixels(uint32_t num, uint16_t p) {
	this->writeData(RA8875_DATAWRITE);
	while (num--) {
		this->writeData(p);
	}
}

/**************************************************************************/
/*!
    Fill the screen with the current color
*/
/**************************************************************************/
// void Adafruit_RA8875::fillRect(void) {
// 	this->writeCommand(RA8875_DCR);
// 	this->writeData(RA8875_DCR_LINESQUTRI_STOP | RA8875_DCR_DRAWSQUARE);
// 	this->writeData(RA8875_DCR_LINESQUTRI_START | RA8875_DCR_FILL | RA8875_DCR_DRAWSQUARE);
// }

/**************************************************************************/
/*!
    Apply current rotation in the X direction

    @return the X value with current rotation applied
 */
/**************************************************************************/
int16_t Adafruit_RA8875::applyRotationX(int16_t x) {
	switch (this->_rotation) {
		case 2:
		x = this->_width - 1 - x;
		break;
	}
	return x;
}

/**************************************************************************/
/*!
    Apply current rotation in the Y direction

    @return the Y value with current rotation applied
 */
/**************************************************************************/
int16_t Adafruit_RA8875::applyRotationY(int16_t y) {
	switch (this->_rotation) {
		case 2:
		y = this->_height - 1 - y;
		break;
	}
	return y + this->_voffset;
}

/**************************************************************************/
/*!
      Draws a single pixel at the specified location

      @param x     The 0-based x location
      @param y     The 0-base y location
      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawPixel(int16_t x, int16_t y, uint16_t color) {
	x = this->applyRotationX(x);
	y = this->applyRotationY(y);

	this->writeReg(RA8875_CURH0, x);
	this->writeReg(RA8875_CURH1, x >> 8);
	this->writeReg(RA8875_CURV0, y);
	this->writeReg(RA8875_CURV1, y >> 8);
	this->writeCommand(RA8875_MRWC);
	this->writeData(RA8875_DATAWRITE);
	this->writeData(color);
}

/**************************************************************************/
/*!
 Draws a series of pixels at the specified location without the overhead

 @param p     An array of RGB565 color pixels
 @param num   The number of the pixels to draw
 @param x     The 0-based x location
 @param y     The 0-base y location
 */
/**************************************************************************/
//void Adafruit_RA8875::drawPixels(uint16_t *p, uint32_t num, int16_t x, int16_t y) {
//	x = this->applyRotationX(x);
//	y = this->applyRotationY(y);
//
//	this->writeReg(RA8875_CURH0, x);
//	this->writeReg(RA8875_CURH1, x >> 8);
//	this->writeReg(RA8875_CURV0, y);
//	this->writeReg(RA8875_CURV1, y >> 8);
//
//	uint16_t dir = RA8875_MWCR0_LRTD;
//	if (this->_rotation == 2) {
//		dir = RA8875_MWCR0_RLTD;
//	}
//	this->writeReg(RA8875_MWCR0, (readReg(RA8875_MWCR0) & ~RA8875_MWCR0_DIRMASK) | dir);
//
//	this->writeCommand(RA8875_MRWC);
//	this->writeData(RA8875_DATAWRITE);
//	while (num--) {
//		this->writeData(*p++);
//	}
//}
void Adafruit_RA8875::drawPixels(uint16_t p, uint32_t num, int16_t x, int16_t y) {
//	x = this->applyRotationX(x);
//	y = this->applyRotationY(y);

	this->writeReg(RA8875_CURH0, x);
	this->writeReg(RA8875_CURH1, x >> 8);
	this->writeReg(RA8875_CURV0, y);
	this->writeReg(RA8875_CURV1, y >> 8);

//	uint16_t dir = RA8875_MWCR0_LRTD;
//	if (this->_rotation == 2) {
//		dir = RA8875_MWCR0_RLTD;
//	}
//	this->writeReg(RA8875_MWCR0, (readReg(RA8875_MWCR0) & ~RA8875_MWCR0_DIRMASK) | dir);

	this->writeCommand(RA8875_MRWC);
	this->writeData(RA8875_DATAWRITE);
	while (num--) {
		this->writeData(p);
	}
}
/**************************************************************************/
/*!
      Draws a HW accelerated line on the display

      @param x0    The 0-based starting x location
      @param y0    The 0-base starting y location
      @param x1    The 0-based ending x location
      @param y1    The 0-base ending y location
      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
	x0 = this->applyRotationX(x0);
	y0 = this->applyRotationY(y0);
	x1 = this->applyRotationX(x1);
	y1 = this->applyRotationY(y1);

	/* Set X */
	this->writeCommand(0x91);
	this->writeData(x0);
	this->writeCommand(0x92);
	this->writeData(x0 >> 8);

	/* Set Y */
	this->writeCommand(0x93);
	this->writeData(y0);
	this->writeCommand(0x94);
	this->writeData(y0 >> 8);

	/* Set X1 */
	this->writeCommand(0x95);
	this->writeData(x1);
	this->writeCommand(0x96);
	this->writeData((x1) >> 8);

	/* Set Y1 */
	this->writeCommand(0x97);
	this->writeData(y1);
	this->writeCommand(0x98);
	this->writeData((y1) >> 8);

	/* Set Color */
	this->writeCommand(0x63);
	this->writeData((color & 0xf800) >> 11);
	this->writeCommand(0x64);
	this->writeData((color & 0x07e0) >> 5);
	this->writeCommand(0x65);
	writeData((color & 0x001f));

	/* Draw! */
	this->writeCommand(RA8875_DCR);
	writeData(0x80);

	/* Wait for the command to finish */
	this->waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

/**************************************************************************/
/*!
    Draw a vertical line

    @param x The X position
    @param y The Y position
    @param h Height
    @param color The color
*/
/**************************************************************************/
void Adafruit_RA8875::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	this->drawLine(x, y, x, y + h, color);
}

/**************************************************************************/
/*!
     Draw a horizontal line

     @param x The X position
     @param y The Y position
     @param w Width
     @param color The color
*/
/**************************************************************************/
void Adafruit_RA8875::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	this->drawLine(x, y, x + w, y, color);
}

/**************************************************************************/
/*!
      Draws a HW accelerated rectangle on the display

      @param x     The 0-based x location of the top-right corner
      @param y     The 0-based y location of the top-right corner
      @param w     The rectangle width
      @param h     The rectangle height
      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	this->rectHelper(x, y, x + w - 1, y + h - 1, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled rectangle on the display

      @param x     The 0-based x location of the top-right corner
      @param y     The 0-based y location of the top-right corner
      @param w     The rectangle width
      @param h     The rectangle height
      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	this->rectHelper(x, y, x + w - 1, y + h - 1, color, true);
}

/**************************************************************************/
/*!
      Fills the screen with the spefied RGB565 color

      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillScreen(uint16_t color) {
	this->rectHelper(0, 0, this->_width - 1, this->_height - 1, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated circle on the display

      @param x     The 0-based x location of the center of the circle
      @param y     The 0-based y location of the center of the circle
      @param r     The circle's radius
      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color) {
	this->circleHelper(x, y, r, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled circle on the display

      @param x     The 0-based x location of the center of the circle
      @param y     The 0-based y location of the center of the circle
      @param r     The circle's radius
      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillCircle(int16_t x, int16_t y, int16_t r, uint16_t color) {
	this->circleHelper(x, y, r, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated triangle on the display

      @param x0    The 0-based x location of point 0 on the triangle
      @param y0    The 0-based y location of point 0 on the triangle
      @param x1    The 0-based x location of point 1 on the triangle
      @param y1    The 0-based y location of point 1 on the triangle
      @param x2    The 0-based x location of point 2 on the triangle
      @param y2    The 0-based y location of point 2 on the triangle
      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawTriangle(int16_t x0, int16_t y0, int16_t x1,
                                   int16_t y1, int16_t x2, int16_t y2,
                                   uint16_t color) {
	this->triangleHelper(x0, y0, x1, y1, x2, y2, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled triangle on the display

      @param x0    The 0-based x location of point 0 on the triangle
      @param y0    The 0-based y location of point 0 on the triangle
      @param x1    The 0-based x location of point 1 on the triangle
      @param y1    The 0-based y location of point 1 on the triangle
      @param x2    The 0-based x location of point 2 on the triangle
      @param y2    The 0-based y location of point 2 on the triangle
      @param color The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillTriangle(int16_t x0, int16_t y0, int16_t x1,
                                   int16_t y1, int16_t x2, int16_t y2,
                                   uint16_t color) {
	this->triangleHelper(x0, y0, x1, y1, x2, y2, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated ellipse on the display

      @param xCenter   The 0-based x location of the ellipse's center
      @param yCenter   The 0-based y location of the ellipse's center
      @param longAxis  The size in pixels of the ellipse's long axis
      @param shortAxis The size in pixels of the ellipse's short axis
      @param color     The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawEllipse(int16_t xCenter, int16_t yCenter,
                                  int16_t longAxis, int16_t shortAxis,
                                  uint16_t color) {
	this->ellipseHelper(xCenter, yCenter, longAxis, shortAxis, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled ellipse on the display

      @param xCenter   The 0-based x location of the ellipse's center
      @param yCenter   The 0-based y location of the ellipse's center
      @param longAxis  The size in pixels of the ellipse's long axis
      @param shortAxis The size in pixels of the ellipse's short axis
      @param color     The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillEllipse(int16_t xCenter, int16_t yCenter,
                                  int16_t longAxis, int16_t shortAxis,
                                  uint16_t color) {
	this->ellipseHelper(xCenter, yCenter, longAxis, shortAxis, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated curve on the display

      @param xCenter   The 0-based x location of the ellipse's center
      @param yCenter   The 0-based y location of the ellipse's center
      @param longAxis  The size in pixels of the ellipse's long axis
      @param shortAxis The size in pixels of the ellipse's short axis
      @param curvePart The corner to draw, where in clock-wise motion:
                            0 = 180-270°
                            1 = 270-0°
                            2 = 0-90°
                            3 = 90-180°
      @param color     The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::drawCurve(int16_t xCenter, int16_t yCenter,
                                int16_t longAxis, int16_t shortAxis,
                                uint8_t curvePart, uint16_t color) {
	this->curveHelper(xCenter, yCenter, longAxis, shortAxis, curvePart, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled curve on the display

      @param xCenter   The 0-based x location of the ellipse's center
      @param yCenter   The 0-based y location of the ellipse's center
      @param longAxis  The size in pixels of the ellipse's long axis
      @param shortAxis The size in pixels of the ellipse's short axis
      @param curvePart The corner to draw, where in clock-wise motion:
                            0 = 180-270°
                            1 = 270-0°
                            2 = 0-90°
                            3 = 90-180°
      @param color     The RGB565 color to use when drawing the pixel
*/
/**************************************************************************/
void Adafruit_RA8875::fillCurve(int16_t xCenter, int16_t yCenter,
                                int16_t longAxis, int16_t shortAxis,
                                uint8_t curvePart, uint16_t color) {
	this->curveHelper(xCenter, yCenter, longAxis, shortAxis, curvePart, color, true);
}

/**************************************************************************/
/*!
      Draws a HW accelerated rounded rectangle on the display

      @param x   The 0-based x location of the rectangle's upper left corner
      @param y   The 0-based y location of the rectangle's upper left corner
      @param w   The size in pixels of the rectangle's width
      @param h   The size in pixels of the rectangle's height
      @param r   The radius of the curves in the corners of the rectangle
      @param color  The RGB565 color to use when drawing the pixel
 */
/**************************************************************************/
void Adafruit_RA8875::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                    int16_t r, uint16_t color) {
	this->roundRectHelper(x, y, x + w, y + h, r, color, false);
}

/**************************************************************************/
/*!
      Draws a HW accelerated filled rounded rectangle on the display

      @param x   The 0-based x location of the rectangle's upper left corner
      @param y   The 0-based y location of the rectangle's upper left corner
      @param w   The size in pixels of the rectangle's width
      @param h   The size in pixels of the rectangle's height
      @param r   The radius of the curves in the corners of the rectangle
      @param color  The RGB565 color to use when drawing the pixel
 */
/**************************************************************************/
void Adafruit_RA8875::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                    int16_t r, uint16_t color) {
	this->roundRectHelper(x, y, x + w, y + h, r, color, true);
}

/**************************************************************************/
/*!
      Helper function for higher level circle drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::circleHelper(int16_t x, int16_t y, int16_t r, uint16_t color, bool filled) {
	x = this->applyRotationX(x);
	y = this->applyRotationY(y);

	/* Set X */
	this->writeCommand(0x99);
	this->writeData(x);
	this->writeCommand(0x9a);
	this->writeData(x >> 8);

	/* Set Y */
	this->writeCommand(0x9b);
	this->writeData(y);
	this->writeCommand(0x9c);
	this->writeData(y >> 8);

	/* Set Radius */
	this->writeCommand(0x9d);
	this->writeData(r);

	/* Set Color */
	this->writeCommand(0x63);
	this->writeData((color & 0xf800) >> 11);
	this->writeCommand(0x64);
	this->writeData((color & 0x07e0) >> 5);
	this->writeCommand(0x65);
	this->writeData((color & 0x001f));

	/* Draw! */
	this->writeCommand(RA8875_DCR);
	if (filled) {
		this->writeData(RA8875_DCR_CIRCLE_START | RA8875_DCR_FILL);
	} else {
		this->writeData(RA8875_DCR_CIRCLE_START | RA8875_DCR_NOFILL);
	}

	/* Wait for the command to finish */
	this->waitPoll(RA8875_DCR, RA8875_DCR_CIRCLE_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level rectangle drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::rectHelper(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, bool filled) {
	x = this->applyRotationX(x);
	y = this->applyRotationY(y);
	w = this->applyRotationX(w);
	h = this->applyRotationY(h);

	/* Set X */
	this->writeCommand(0x91);
	this->writeData(x);
	this->writeCommand(0x92);
	this->writeData(x >> 8);

	/* Set Y */
	this->writeCommand(0x93);
	this->writeData(y);
	this->writeCommand(0x94);
	this->writeData(y >> 8);

	/* Set X1 */
	this->writeCommand(0x95);
	this->writeData(w);
	this->writeCommand(0x96);
	writeData((w) >> 8);

	/* Set Y1 */
	this->writeCommand(0x97);
	writeData(h);
	this->writeCommand(0x98);
	writeData((h) >> 8);

	/* Set Color */
	this->writeCommand(0x63);
	this->writeData((color & 0xE0) >> 5);
	this->writeCommand(0x64);
	this->writeData((color & 0x1C) >> 2);
	this->writeCommand(0x65);
	this->writeData((color & 0x03));

	/* Draw! */
	this->writeCommand(RA8875_DCR);
	if (filled) {
		this->writeData(0xB0);
	} else {
		this->writeData(0x90);
	}

	/* Wait for the command to finish */
	this->waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level triangle drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::triangleHelper(int16_t x0, int16_t y0, int16_t x1,
                                     int16_t y1, int16_t x2, int16_t y2,
                                     uint16_t color, bool filled) {
	x0 = this->applyRotationX(x0);
	y0 = this->applyRotationY(y0);
	x1 = this->applyRotationX(x1);
	y1 = this->applyRotationY(y1);
	x2 = this->applyRotationX(x2);
	y2 = this->applyRotationY(y2);

	/* Set Point 0 */
	this->writeCommand(0x91);
	this->writeData(x0);
	this->writeCommand(0x92);
	this->writeData(x0 >> 8);
	this->writeCommand(0x93);
	this->writeData(y0);
	this->writeCommand(0x94);
	this->writeData(y0 >> 8);

	/* Set Point 1 */
	this->writeCommand(0x95);
	this->writeData(x1);
	this->writeCommand(0x96);
	this->writeData(x1 >> 8);
	this->writeCommand(0x97);
	this->writeData(y1);
	this->writeCommand(0x98);
	this->writeData(y1 >> 8);

	/* Set Point 2 */
	this->writeCommand(0xA9);
	writeData(x2);
	this->writeCommand(0xAA);
	this->writeData(x2 >> 8);
	this->writeCommand(0xAB);
	this->writeData(y2);
	this->writeCommand(0xAC);
	this->writeData(y2 >> 8);

	/* Set Color */
	this->writeCommand(0x63);
	this->writeData((color & 0xE0) >> 5);
	this->writeCommand(0x64);
	this->writeData((color & 0x1C) >> 2);
	this->writeCommand(0x65);
	this->writeData((color & 0x03));

	/* Draw! */
	this->writeCommand(RA8875_DCR);
	if (filled) {
		this->writeData(0xA1);
	} else {
		this->writeData(0x81);
	}

	/* Wait for the command to finish */
	this->waitPoll(RA8875_DCR, RA8875_DCR_LINESQUTRI_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level ellipse drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::ellipseHelper(int16_t xCenter, int16_t yCenter,
                                    int16_t longAxis, int16_t shortAxis,
                                    uint16_t color, bool filled) {
	xCenter = this->applyRotationX(xCenter);
	yCenter = this->applyRotationY(yCenter);

	/* Set Center Point */
	this->writeCommand(0xA5);
	this->writeData(xCenter);
	this->writeCommand(0xA6);
	this->writeData(xCenter >> 8);
	this->writeCommand(0xA7);
	this->writeData(yCenter);
	this->writeCommand(0xA8);
	this->writeData(yCenter >> 8);

	/* Set Long and Short Axis */
	this->writeCommand(0xA1);
	this->writeData(longAxis);
	this->writeCommand(0xA2);
	this->writeData(longAxis >> 8);
	this->writeCommand(0xA3);
	this->writeData(shortAxis);
	this->writeCommand(0xA4);
	this->writeData(shortAxis >> 8);

	/* Set Color */
	this->writeCommand(0x63);
	this->writeData((color & 0xE0) >> 5);
	this->writeCommand(0x64);
	this->writeData((color & 0x1C) >> 2);
	this->writeCommand(0x65);
	this->writeData((color & 0x03));

	/* Draw! */
	this->writeCommand(0xA0);
	if (filled) {
		this->writeData(0xC0);
	} else {
		this->writeData(0x80);
	}

	/* Wait for the command to finish */
	this->waitPoll(RA8875_ELLIPSE, RA8875_ELLIPSE_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level curve drawing code
*/
/**************************************************************************/
void Adafruit_RA8875::curveHelper(int16_t xCenter, int16_t yCenter,
                                  int16_t longAxis, int16_t shortAxis,
                                  uint8_t curvePart, uint16_t color,
                                  bool filled) {
	xCenter = this->applyRotationX(xCenter);
	yCenter = applyRotationY(yCenter);
	curvePart = (curvePart + _rotation) % 4;

	/* Set Center Point */
	this->writeCommand(0xA5);
	this->writeData(xCenter);
	this->writeCommand(0xA6);
	this->writeData(xCenter >> 8);
	this->writeCommand(0xA7);
	this->writeData(yCenter);
	this->writeCommand(0xA8);
	this->writeData(yCenter >> 8);

	/* Set Long and Short Axis */
	this->writeCommand(0xA1);
	this->writeData(longAxis);
	this->writeCommand(0xA2);
	this->writeData(longAxis >> 8);
	this->writeCommand(0xA3);
	this->writeData(shortAxis);
	this->writeCommand(0xA4);
	this->writeData(shortAxis >> 8);

	/* Set Color */
	this->writeCommand(0x63);
	this->writeData((color & 0xE0) >> 5);
	this->writeCommand(0x64);
	this->writeData((color & 0x1C) >> 2);
	this->writeCommand(0x65);
	this->writeData((color & 0x03));

	/* Draw! */
	this->writeCommand(0xA0);
	if (filled) {
		this->writeData(0xD0 | (curvePart & 0x03));
	}
	else {
		this->writeData(0x90 | (curvePart & 0x03));
	}

	/* Wait for the command to finish */
	this->waitPoll(RA8875_ELLIPSE, RA8875_ELLIPSE_STATUS);
}

/**************************************************************************/
/*!
      Helper function for higher level rounded rectangle drawing code
 */
/**************************************************************************/
void Adafruit_RA8875::roundRectHelper(int16_t x, int16_t y, int16_t w,
                                      int16_t h, int16_t r, uint16_t color,
                                      bool filled) {
	x = this->applyRotationX(x);
	y = this->applyRotationY(y);
	w = this->applyRotationX(w);
	h = this->applyRotationY(h);
	if (x > w)
		this->swap(x, w);
	if (y > h)
		this->swap(y, h);

	/* Set X */
	this->writeCommand(0x91);
	this->writeData(x);
	this->writeCommand(0x92);
	this->writeData(x >> 8);

	/* Set Y */
	this->writeCommand(0x93);
	this->writeData(y);
	this->writeCommand(0x94);
	this->writeData(y >> 8);

	/* Set X1 */
	this->writeCommand(0x95);
	this->writeData(w);
	this->writeCommand(0x96);
	this->writeData((w) >> 8);

	/* Set Y1 */
	this->writeCommand(0x97);
	this->writeData(h);
	this->writeCommand(0x98);
	this->writeData((h) >> 8);

	this->writeCommand(0xA1);
	this->writeData(r);
	this->writeCommand(0xA2);
	this->writeData((r) >> 8);

	this->writeCommand(0xA3);
	this->writeData(r);
	this->writeCommand(0xA4);
	this->writeData((r) >> 8);

	/* Set Color */
	this->writeCommand(0x63);
	this->writeData((color & 0xE0) >> 5);
	this->writeCommand(0x64);
	this->writeData((color & 0x1C) >> 2);
	this->writeCommand(0x65);
	this->writeData((color & 0x03));

	/* Draw! */
	this->writeCommand(RA8875_ELLIPSE);
	if (filled) {
		this->writeData(0xE0);
	} else {
		writeData(0xA0);
	}

	/* Wait for the command to finish */
	this->waitPoll(RA8875_ELLIPSE, RA8875_DCR_LINESQUTRI_STATUS);
}
/**************************************************************************/
/*!
      Set the scroll window

      @param x  X position of the scroll window
      @param y  Y position of the scroll window
      @param w  Width of the Scroll Window
      @param h  Height of the Scroll window
      @param mode Layer to Scroll

 */
/**************************************************************************/
void Adafruit_RA8875::setScrollWindow(int16_t x, int16_t y, int16_t w,
                                      int16_t h, uint8_t mode) {
	// Horizontal Start point of Scroll Window
	this->writeCommand(0x38);
	this->writeData(x);
	this->writeCommand(0x39);
	this->writeData(x >> 8);

	// Vertical Start Point of Scroll Window
	this->writeCommand(0x3a);
	this->writeData(y);
	this->writeCommand(0x3b);
	this->writeData(y >> 8);

	// Horizontal End Point of Scroll Window
	this->writeCommand(0x3c);
	this->writeData(x + w);
	this->writeCommand(0x3d);
	this->writeData((x + w) >> 8);

	// Vertical End Point of Scroll Window
	this->writeCommand(0x3e);
	this->writeData(y + h);
	this->writeCommand(0x3f);
	this->writeData((y + h) >> 8);

	// Scroll function setting
	this->writeCommand(0x52);
	this->writeData(mode);
}

/**************************************************************************/
/*!
    Scroll in the X direction

    @param dist The distance to scroll

 */
/**************************************************************************/
void Adafruit_RA8875::scrollX(int16_t dist) {
	this->writeCommand(0x24);
	this->writeData(dist);
	this->writeCommand(0x25);
	this->writeData(dist >> 8);
}

/**************************************************************************/
/*!
     Scroll in the Y direction

     @param dist The distance to scroll

 */
/**************************************************************************/
void Adafruit_RA8875::scrollY(int16_t dist) {
	this->writeCommand(0x26);
	this->writeData(dist);
	this->writeCommand(0x27);
	this->writeData(dist >> 8);
}

/************************* Mid Level ***********************************/

/**************************************************************************/
/*!
    Set the Extra General Purpose IO Register

    @param on Whether to turn Extra General Purpose IO on or not

 */
/**************************************************************************/
void Adafruit_RA8875::GPIOX(bool on) {
  if (on) {
	  this->writeReg(RA8875_GPIOX, 1);
  }
  else {
	  this->writeReg(RA8875_GPIOX, 0);
  }
}

/**************************************************************************/
/*!
    Set the duty cycle of the PWM 1 Clock

    @param p The duty Cycle (0-255)
*/
/**************************************************************************/
void Adafruit_RA8875::PWM1out(uint8_t p) { this->writeReg(RA8875_P1DCR, p); }

/**************************************************************************/
/*!
     Set the duty cycle of the PWM 2 Clock

     @param p The duty Cycle (0-255)
*/
/**************************************************************************/
void Adafruit_RA8875::PWM2out(uint8_t p) { this->writeReg(RA8875_P2DCR, p); }

/**************************************************************************/
/*!
    Configure the PWM 1 Clock

    @param on Whether to enable the clock
    @param clock The Clock Divider
*/
/**************************************************************************/
void Adafruit_RA8875::PWM1config(bool on, uint8_t clock) {
	if (on) {
		this->writeReg(RA8875_P1CR, RA8875_P1CR_ENABLE | (clock & 0xF));
	}
	else {
		this->writeReg(RA8875_P1CR, RA8875_P1CR_DISABLE | (clock & 0xF));
	}
}

/**************************************************************************/
/*!
     Configure the PWM 2 Clock

     @param on Whether to enable the clock
     @param clock The Clock Divider
*/
/**************************************************************************/
void Adafruit_RA8875::PWM2config(bool on, uint8_t clock) {
	if (on) {
		this->writeReg(RA8875_P2CR, RA8875_P2CR_ENABLE | (clock & 0xF));
	}
	else {
		this->writeReg(RA8875_P2CR, RA8875_P2CR_DISABLE | (clock & 0xF));
	}
}

/**************************************************************************/
/*!
      Enables or disables the on-chip touch screen controller

      @param on Whether to turn touch sensing on or not
*/
/**************************************************************************/
void Adafruit_RA8875::touchEnable(bool on) {
	uint16_t adcClk = (uint16_t)RA8875_TPCR0_ADCCLK_DIV4;

	if (this->_size == RA8875_800x480) { // match up touch size with LCD size
		adcClk = (uint16_t)RA8875_TPCR0_ADCCLK_DIV16;
	}

	if (on) {
		/* Enable Touch Panel (Reg 0x70) */
		this->writeReg(RA8875_TPCR0, RA8875_TPCR0_ENABLE | RA8875_TPCR0_WAIT_4096CLK |
								   RA8875_TPCR0_WAKEENABLE | adcClk); // 10mhz max!
		/* Set Auto Mode      (Reg 0x71) */
		this->writeReg(RA8875_TPCR1, RA8875_TPCR1_AUTO |
								   // RA8875_TPCR1_VREFEXT |
								   RA8875_TPCR1_DEBOUNCE);
		/* Enable TP INT */
		this->writeReg(RA8875_INTC1, this->readReg(RA8875_INTC1) | RA8875_INTC1_TP);
	}
	else {
		/* Disable TP INT */
		this->writeReg(RA8875_INTC1, this->readReg(RA8875_INTC1) & ~RA8875_INTC1_TP);
		/* Disable Touch Panel (Reg 0x70) */
		this->writeReg(RA8875_TPCR0, RA8875_TPCR0_DISABLE);
	}
}

/**************************************************************************/
/*!
      Checks if a touch event has occured

      @return  True is a touch event has occured (reading it via
               touchRead() will clear the interrupt in memory)
*/
/**************************************************************************/
bool Adafruit_RA8875::touched(void) {
	if (this->readReg(RA8875_INTC2) & RA8875_INTC2_TP) {
		return true;
	}
	return false;
}

/**************************************************************************/
/*!
      Reads the last touch event

      @param x  Pointer to the uint16_t field to assign the raw X value
      @param y  Pointer to the uint16_t field to assign the raw Y value

      @return True if successful

      @note Calling this function will clear the touch panel interrupt on
            the RA8875, resetting the flag used by the 'touched' function
*/
/**************************************************************************/
bool Adafruit_RA8875::touchRead(uint16_t& x, uint16_t& y) {
	uint16_t tx, ty;
	uint8_t temp;

	tx = this->readReg(RA8875_TPXH);
	ty = this->readReg(RA8875_TPYH);
	temp = this->readReg(RA8875_TPXYL);
	tx <<= 2;
	ty <<= 2;
	tx |= temp & 0x03;        // get the bottom x bits
	ty |= (temp >> 2) & 0x03; // get the bottom y bits

	x = tx;
	y = ty;

	/* Clear TP INT Status */
	this->writeReg(RA8875_INTC2, RA8875_INTC2_TP);

	return true;
}

/**************************************************************************/
/*!
      Turns the display on or off

      @param on Whether to turn the display on or not
*/
/**************************************************************************/
void Adafruit_RA8875::displayOn(bool on) {
	if (on) {
		this->writeReg(RA8875_PWRR, RA8875_PWRR_NORMAL | RA8875_PWRR_DISPON);
	}
	else {
		this->writeReg(RA8875_PWRR, RA8875_PWRR_NORMAL | RA8875_PWRR_DISPOFF);
	}
}

/**************************************************************************/
/*!
    Puts the display in sleep mode, or disables sleep mode if enabled

    @param sleep Whether to sleep or not
*/
/**************************************************************************/
void Adafruit_RA8875::sleep(bool sleep) {
	if (sleep) {
		this->writeReg(RA8875_PWRR, RA8875_PWRR_DISPOFF | RA8875_PWRR_SLEEP);
	}
	else {
		this->writeReg(RA8875_PWRR, RA8875_PWRR_DISPOFF);
	}
}

/************************* Low Level ***********************************/

/**************************************************************************/
/*!
    Write data to the specified register

    @param reg Register to write to
    @param val Value to write
*/
/**************************************************************************/
void Adafruit_RA8875::writeReg(uint16_t reg, uint16_t val) {
	this->writeCommand(reg);
	this->writeData(val);
}

/**************************************************************************/
/*!
    Set the register to read from

    @param reg Register to read

    @return The value
*/
/**************************************************************************/
uint16_t Adafruit_RA8875::readReg(uint16_t reg) {
	this->writeCommand(reg);
	return this->readData();
}

volatile uint16_t del = 65;
/**************************************************************************/
/*!
    Write data to the current register

    @param d Data to write
*/
/**************************************************************************/
void Adafruit_RA8875::writeData(uint16_t d) {

	*(LCD_DATA)= d;
	delay(del);
}

/**************************************************************************/
/*!
    Read the data from the current register

    @return The Value
*/
/**************************************************************************/
uint16_t Adafruit_RA8875::readData(void) { return *(LCD_DATA); }

/**************************************************************************/
/*!
    Write a command to the current register

    @param d The data to write as a command
 */
/**************************************************************************/
void Adafruit_RA8875::writeCommand(uint16_t d) {

	*(LCD_REG) = d;
	delay(del);
}

/**************************************************************************/
/*!
    Read the status from the current register

    @return The value
 */
/**************************************************************************/
uint16_t Adafruit_RA8875::readStatus(void) { return *(LCD_REG); }

/**************************************************************************/
void Adafruit_RA8875::useLayers(bool on) { this->writeReg(0x20 , 0x80 * on); }

void Adafruit_RA8875::layerEffect(RA8875Layers efx) {
	uint16_t temp = this->readReg(RA8875_LTPR0);
	switch(efx) {
		case LAYER1: //only layer 1 visible  [000]
			temp = 0x00;
		break;
		case LAYER2: //only layer 2 visible  [001]
			temp = 0x01;
		break;
		default:
			return;//do nothing
		break;
	}
	this->writeReg(RA8875_LTPR0, temp);
}

void Adafruit_RA8875::writeTo(RA8875Layers d) {
	uint16_t temp = this->readReg(RA8875_MWCR1);
	temp &= ~(3<<2);// Clear bits 3 and 2
	switch(d)
  {
  case LAYER1:
    temp &= ~(1<<0); //clear bit 0
    _currentLayer = 0;
		break;
  case LAYER2:
    temp |= (1<<0); //bit set 0
    _currentLayer = 1;
		break;
  default:
    return;
	}
	this->writeData(temp);
}
