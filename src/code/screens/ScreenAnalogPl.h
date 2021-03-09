#pragma once

#include "Loop.h"
#include "ScreenAnalogCoef.h"
#include "ScreenSetAnalogPl.h"	

extern ScreenAnalogCoef sAnalogCoef;	
extern ScreenSetAnalogPl sSetAnalogPl;

class ScreenAnalogPl : public BaseScreen {

    Button settZero	    = Button(this, 165, 100, 470, 60, 0x7BEF, "Уставки нулей", 0);
	Button coeff	    = Button(this, 165, 170, 470, 60, 0x7BEF, "Коэффициенты", 0);
	Button sett         = Button(this, 165, 240, 470, 60, 0x7BEF, "Уставки", 0);
    Button test         = Button(this, 165, 310, 470, 60, 0x7BEF, "Тест выходов", 0);
    


public:

	ScreenAnalogPl(void) : BaseScreen(&Screens, "Аналоговая плата") {
		this->coeff.addCallBack([]() { Screens.JumpScreen(&sAnalogCoef); });
		this->sett.addCallBack([]() { Screens.JumpScreen(&sSetAnalogPl); });

    }
};

