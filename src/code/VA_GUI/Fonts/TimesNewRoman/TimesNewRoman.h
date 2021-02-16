#ifndef TimesNewRomanH
#define TimesNewRomanH

#include "stdint.h"

#ifndef SMfgTypes
#define SMfgTypes

/*======= binary input =======*/
#define b2b(b7, b6, b5, b4, b3, b2, b1, b0) ((uint8_t)((b7*128) + (b6*64) + (b5*32) + (b4*16) + (b3*8) + (b2*4) + (b1*2) + (b0)))

typedef const uint8_t TCDATA;
typedef TCDATA* TCLISTP;

#endif

extern TCLISTP* TimesNewRoman[3];

#endif
