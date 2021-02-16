/*
 * DeviceDCXJ.h
 *
 *  Created on: 9 дек. 2020 г.
 *      Author: anan2
 */

#pragma once


#include "BaseDevice.h"

class DeviceDCXJ : public BaseDevice {
	static uint16_t mAdress;
public:

	DeviceDCXJ(void) : BaseDevice(this->mAdress++, FunctionWrite::F6) {

		RegistersExchange temp;
		temp.FirstReg = 0;
		temp.NReg = 62;
		temp.pBuff = (uint16_t*)&this->Mem;
		this->Exchange.push_back(temp);
		this->Name = "Блок контроля батарей-" + std::to_string(this->Adress - 63);
	}

	struct Memory_t {
		uint16_t Temp1;
		uint16_t Temp2;
		uint16_t cellVoltage[60];
		struct statusBattery_t {
			uint16_t status1  : 1;
			uint16_t status2  : 1;
			uint16_t status3  : 1;
			uint16_t status4  : 1;
			uint16_t status5  : 1;
			uint16_t status6  : 1;
			uint16_t status7  : 1;
			uint16_t status8  : 1;
			uint16_t status9  : 1;
			uint16_t status10 : 1;
			uint16_t status11 : 1;
			uint16_t status12 : 1;
			uint16_t status13 : 1;
			uint16_t status14 : 1;
			uint16_t status15 : 1;
			uint16_t status16 : 1;
			uint16_t status17 : 1;
			uint16_t status18 : 1;
			uint16_t status19 : 1;
			uint16_t status20 : 1;
			uint16_t status21 : 1;
			uint16_t status22 : 1;
			uint16_t status23 : 1;
			uint16_t status24 : 1;
			uint16_t status25 : 1;
			uint16_t status26 : 1;
			uint16_t status27 : 1;
			uint16_t status28 : 1;
			uint16_t status29 : 1;
			uint16_t status30 : 1;
			uint16_t status31 : 1;
			uint16_t status32 : 1;
			uint16_t status33 : 1;
			uint16_t status34 : 1;
			uint16_t status35 : 1;
			uint16_t status36 : 1;
			uint16_t status37 : 1;
			uint16_t status38 : 1;
			uint16_t status39 : 1;
			uint16_t status40 : 1;
			uint16_t status41 : 1;
			uint16_t status42 : 1;
			uint16_t status43 : 1;
			uint16_t status44 : 1;
			uint16_t status45 : 1;
			uint16_t status46 : 1;
			uint16_t status47 : 1;
			uint16_t status48 : 1;
			uint16_t status49 : 1;
			uint16_t status50 : 1;
			uint16_t status51 : 1;
			uint16_t status52 : 1;
			uint16_t status53 : 1;
			uint16_t status54 : 1;
			uint16_t status55 : 1;
			uint16_t status56 : 1;
			uint16_t status57 : 1;
			uint16_t status58 : 1;
			uint16_t status59 : 1;
			uint16_t status60 : 1;
		} sCellBattery;
	} Mem;
};

uint16_t DeviceDCXJ::mAdress = 64;

