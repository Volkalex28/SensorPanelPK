/*
 * ScreenSettZVU.h
 *
 *  Created on: Dec 6, 2020
 *      Author: ans0lв
 */

#pragma once

#include "ScreenZVU.h"
#include "Loop.h"
//#include "DeviceB118.h";

using namespace VA;

#define min 0
#define max 3000

void write(WriteBuf_t temp);

class ScreenSettZVU : public BaseScreen {

	void _write(uint16_t Reg, uint16_t Val, uint16_t Regime) {
		WriteBuf_t temp;
		temp.AdrReg = Reg;
		temp.Value = Val;
		if(this->chosenDevise == 0) {
			if(Memory[eMemory::RegimeB118].U == Regime) {
				temp.Adress = 1;
				write(temp);
				temp.Adress = 2;
				write(temp);
				temp.Adress = 3;
				write(temp);
			}
		}
		else {
			if(Memory[eMemory::RegimeB118M].U == Regime) {
				temp.Adress = 4;
				write(temp);
			}
		}
	}

public:


	Display disp[8] 			= {
		 Display(this, 415, 145, 100, 40, &Memory[eMemory::MaxVoltageRecharge].U, 4, 1, min, max, &Screens.kbr),
		 Display(this, 415, 235, 100, 40, &Memory[eMemory::MinVoltageRecharge].U, 4, 1, min, max, &Screens.kbr),
		 Display(this, 665, 145, 100, 40, &Memory[eMemory::MaxCurrentRecharge].U, 4, 1, min, max, &Screens.kbr),
		 Display(this, 665, 235, 100, 40, &Memory[eMemory::MinCurrentRecharge].U, 4, 1, min, max, &Screens.kbr),
		 Display(this, 415, 285, 100, 40, &Memory[eMemory::MaxVoltageBoostCharge].U, 4, 1, min, max, &Screens.kbr),
		 Display(this, 415, 375, 100, 40, &Memory[eMemory::MinVoltageBoostCharge].U, 4, 1, min, max, &Screens.kbr),
		 Display(this, 665, 285, 100, 40, &Memory[eMemory::MaxCurrentBoostCharge].U, 4, 1, min, max, &Screens.kbr),
		 Display(this, 665, 375, 100, 40, &Memory[eMemory::MinCurrentBoostCharge].U, 4, 1, min, max, &Screens.kbr),
	};

/*----------------------------------------------------------------------------------------------------- */
	Graphics vline				= Graphics(this, 280, 62, 3, 356, 0x00, Figure::rect, 0, true);
	Graphics hline				= Graphics(this, 0, 135, 800, 3, 0x00, Figure::rect, 0, true);

/*----------------------------------------------------------------------------------------------------- */
	Button bRecharge 			= Button(this, 10, 170, 260, 80, 0x031f, "Подзаряд");
	Button bBoostCharge 		= Button(this, 10, 310, 260, 80, 0x031f, "Ускоренный заряд");


/*----------------------------------------------------------------------------------------------------- */
	Label selectedVoltage 		= Label(this, 280, 65, 260, 70, "Напряжение задания",  Fonts::TimesNewRoman, FontForms::Normal,
						VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);
	Label currentLimit 			= Label(this, 540, 65, 260, 70, "Токоограничение",  Fonts::TimesNewRoman, FontForms::Normal,
						VALabelScale::S2, VALabelAlignX::CenterX, VALabelAlignY::CenterY, 0x00);


/*---------------------------------- Подзаряд  напряжение ------------------------------------------------------- */
	Display drechargeVoltage 	= Display(this, 365, 180, 100, 60, &Memory[eMemory::VoltageRecharge].U, 4, 1, 0, 00, &Screens.kbr);
	Label lrechargeVoltage 		= Label(this, 480, 170, 40, 80, "B",  Fonts::TimesNewRoman, FontForms::Normal,
	    				VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY, 0x00);

/*---------------------------------- Подзаряд  токоограничение ------------------------------------------------------- */
	Display drechargeCurrent  	= Display(this, 615, 180, 100, 60, &Memory[eMemory::CurrentRecharge].U, 4, 1, 0, 1000, &Screens.kbr);
	Label lrechargeCurrent 		= Label(this, 735, 170, 40, 80, "%",  Fonts::TimesNewRoman, FontForms::Normal,
						VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY, 0x00);

/*-------------------------------- Ускоренный заряд напряжение   ------------------------------------------------ */
	Display dboostChargeVoltage = Display(this, 365, 320, 100, 60, &Memory[eMemory::VoltageBoostCharge].U, 4, 1, 0, 00, &Screens.kbr);
	Label lboostChargeVoltage 	= Label(this, 480, 310, 40, 80, "B",  Fonts::TimesNewRoman, FontForms::Normal,
		    			VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY, 0x00);

/*---------------------------------- Ускоренный заряд  токоограничение ------------------------------------------------------- */
	Display dboostChargeCurrent = Display(this, 615, 320, 100, 60, &Memory[eMemory::CurrentBoostCharge].U, 4, 1, 0, 1000, &Screens.kbr);
	Label lboostChargeCurrent 	= Label(this, 735, 310, 40, 80, "%",  Fonts::TimesNewRoman, FontForms::Normal,
						VALabelScale::S2, VALabelAlignX::Left, VALabelAlignY::CenterY, 0x00);


/*----------------------------------------------------------------------------------------------------- */

	uint8_t chosenDevise = 0;

    ScreenSettZVU(void)
		: BaseScreen(&Screens, "Уставки ЗВУ")
	{
//    	this->addElement(&sZVU.regime);
//    	this->addElement(&sZVU.condition);
    	//---------------------------------------------------------------------------//

    	this->disp[0].addCallBack([&]() {
    		 eeprom.Write(this->disp[0].GetPValue());
    		 this->_write(3, *this->disp[0].GetPValue(), 0);
		});
    	this->disp[1].addCallBack([&]() {
			 eeprom.Write(this->disp[1].GetPValue());
			 this->_write(4, *this->disp[1].GetPValue(), 0);
		});
    	//---------------------------------------------------------------------------//
    	this->disp[2].addCallBack([&]() {
			 eeprom.Write(this->disp[2].GetPValue());
		});
    	this->disp[3].addCallBack([&]() {
			 eeprom.Write(this->disp[3].GetPValue());
		});
    	//---------------------------------------------------------------------------//
    	this->disp[4].addCallBack([&]() {
			 eeprom.Write(this->disp[4].GetPValue());
    		 this->_write(3, *this->disp[4].GetPValue(), 0);
		});
    	this->disp[5].addCallBack([&]() {
			 eeprom.Write(this->disp[5].GetPValue());
			 this->_write(4, *this->disp[5].GetPValue(), 0);
		});
    	//---------------------------------------------------------------------------//
		this->disp[6].addCallBack([&]() {
			 eeprom.Write(this->disp[6].GetPValue());
		});
		this->disp[7].addCallBack([&]() {
			 eeprom.Write(this->disp[7].GetPValue());
		});

//------------------------------------------------------------------------------//
		this->drechargeVoltage.SetLevelAcces(LevelsAcces::User);
		this->drechargeVoltage.addCallBack([&]() {
			 eeprom.Write(this->drechargeVoltage.GetPValue());
			 this->_write(0, *this->drechargeVoltage.GetPValue(), 0);
		});

		this->drechargeCurrent.SetLevelAcces(LevelsAcces::User);
		this->drechargeCurrent.addCallBack([&]() {
			eeprom.Write(this->drechargeCurrent.GetPValue());
			this->_write(2, *this->drechargeCurrent.GetPValue(), 0);
		});

		this->dboostChargeVoltage.SetLevelAcces(LevelsAcces::User);
		this->dboostChargeVoltage.addCallBack([&]() {
			eeprom.Write(this->dboostChargeVoltage.GetPValue());
			this->_write(0, *this->dboostChargeVoltage.GetPValue(), 1);
		});

		this->dboostChargeCurrent.SetLevelAcces(LevelsAcces::User);
		this->dboostChargeCurrent.addCallBack([&]() {
			eeprom.Write(this->dboostChargeCurrent.GetPValue());
			this->_write(2, *this->dboostChargeCurrent.GetPValue(), 1);
		});

//-------------------------------------------------------------------------------//
		this->bRecharge.SetLevelAcces(LevelsAcces::User);
		this->bRecharge.addCallBack([&]() {
			if(this->chosenDevise == 0) {
				Memory[eMemory::RegimeB118].U = 0;
				eeprom.Write(&Memory[eMemory::RegimeB118].U);
			}
			else {
				Memory[eMemory::RegimeB118M].U = 0;
				eeprom.Write(&Memory[eMemory::RegimeB118M].U);
			}
			this->_write(0, *this->drechargeVoltage.GetPValue(), 0);
			this->_write(2, *this->drechargeCurrent.GetPValue(), 0);
		});
		this->bBoostCharge.SetLevelAcces(LevelsAcces::User);
		this->bBoostCharge.addCallBack([&]() {
			if(this->chosenDevise == 0) {
				Memory[eMemory::RegimeB118].U = 1;
				eeprom.Write(&Memory[eMemory::RegimeB118].U);
			}
			else {
				Memory[eMemory::RegimeB118M].U = 1;
				eeprom.Write(&Memory[eMemory::RegimeB118M].U);
			}
			this->_write(0, *this->dboostChargeVoltage.GetPValue(), 1);
			this->_write(2, *this->dboostChargeCurrent.GetPValue(), 1);
		});
	}

    void Loop(void) override {
    	UpdateRegime();
//    	this->drechargeVoltage.SetMax(Memory[eMemory::MaxVoltageRecharge].U);
//		this->drechargeVoltage.SetMin(Memory[eMemory::MinVoltageRecharge].U);
//		this->drechargeCurrent.SetMax(Memory[eMemory::MaxCurrentRecharge].U);
//		this->drechargeCurrent.SetMin(Memory[eMemory::MinCurrentRecharge].U);
//		this->dboostChargeVoltage.SetMax(Memory[eMemory::MaxVoltageBoostCharge].U);
//		this->dboostChargeVoltage.SetMin(Memory[eMemory::MinVoltageBoostCharge].U);
//		this->dboostChargeCurrent.SetMax(Memory[eMemory::MaxCurrentBoostCharge].U);
//		this->dboostChargeCurrent.SetMin(Memory[eMemory::MinCurrentBoostCharge].U);
		for (uint8_t i = 0; i < 8; i++) {
			this->disp[i].SetShowed(Screens.GetLevelAcces() == LevelsAcces::Admin);
			this->disp[i].SetEnabled(Screens.GetLevelAcces() == LevelsAcces::Admin);
		}
    }

    void JumpTo(void) override {
    	this->Loop();
    }


};
