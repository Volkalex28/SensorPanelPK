/*
 * BaseDevice.h
 *
 *  Created on: Dec 6, 2020
 *      Author: anan2
 */

#pragma once

#include "Loop.h"

class BaseDevice {

public:

	static std::vector<BaseDevice*> Devices;

	uint8_t Adress;

	std::string Name = "";

	enum class FunctionWrite {
		F6,
		F10
	} Function;

	bool ErrorConnection = false;
	bool Enable = true;

	struct RegistersExchange {
		uint16_t FirstReg;
		uint8_t NReg;
		uint16_t* pBuff;
	};
	std::vector<RegistersExchange> Exchange = {};

protected:
	BaseDevice(uint8_t Adress, FunctionWrite foo) {
		if (Adress != 0) { this->Adress = Adress; }
		else this->Adress = 255;
		this->Function = foo;

		this->Devices.push_back(this);
	}
};
