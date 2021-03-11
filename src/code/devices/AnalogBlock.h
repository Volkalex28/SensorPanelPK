/*
 * AnalogBlock.h
 *
 *  Created on: Feb 2, 2021
 *      Author: ans0l
 */

#pragma once

#include "BaseDevice.h"

class AnalogBlock : public BaseDevice {

	static uint16_t mAdress;

public:

	AnalogBlock(void) : BaseDevice(this->mAdress++, FunctionWrite::F6) {

		RegistersExchange temp;
		temp.FirstReg = 0;
		temp.NReg = 24;
		temp.pBuff = (uint16_t*)&this->Mem;
		this->Exchange.push_back(temp);
		this->Name = "Блок аналоговых сигналов-" + std::to_string(this->Adress - 35);
	}
	struct Memory_t {
		struct statusIO {
			uint16_t O0 : 1;
			uint16_t O1 : 1;
			uint16_t O2 : 1;
			uint16_t O3 : 1;
			uint16_t O4 : 1;
			uint16_t O5 : 1;
			uint16_t O6 : 1;
			uint16_t O7 : 1;
			uint16_t I0 : 1;
			uint16_t I1 : 1;
			uint16_t I2 : 1;
			uint16_t I3 : 1;
			uint16_t I4 : 1;
			uint16_t I5 : 1;
			uint16_t I6 : 1;
			uint16_t I7 : 1;
		} sAnalogIO;
		uint16_t K1;
		uint16_t K2;
		uint16_t K3;
		uint16_t K11;
		uint16_t K12;
		uint16_t K13;
		uint16_t _31;
		uint16_t _32;
		uint16_t _33;
		uint16_t _34;
		uint16_t Umin1;
		uint16_t Umax1;
		uint16_t Umin2;
		uint16_t Umax2;
		uint16_t Umin3;
		uint16_t AI1; //17
		uint16_t AI2;
		uint16_t AI3;
		uint16_t AI11;
		uint16_t AI12;
		uint16_t AI13;
		uint16_t Temp;
	} Mem;
};


uint16_t AnalogBlock::mAdress = 36;







