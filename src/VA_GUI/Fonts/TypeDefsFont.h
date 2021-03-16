/**
 * @file TypeDefsFont.h
 * @author Oleksandr Ananiev (anan20000228@gmail.com)
 * @brief 
 * 
 */

#ifndef __TYPEDEFSFONT_H__
#define __TYPEDEFSFONT_H__

#include "stdint.h"

/*======= binary input =======*/
#define b2b(b7, b6, b5, b4, b3, b2, b1, b0) ((uint8_t)((b7*128) + (b6*64) + (b5*32) + (b4*16) + (b3*8) + (b2*4) + (b1*2) + (b0)))

typedef const uint8_t TCDATA;
typedef TCDATA* TCLISTP;

#endif // __TYPEDEFSFONT_H__