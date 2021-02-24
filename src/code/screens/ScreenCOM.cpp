#include "ScreenCOM.h"

ScreenCOM::ScreenCOM(): BaseScreen(&Screens, "Параметры СОМ") {
	this->bRateM.addCallBack([&]() {
				if(this->SpeedCOMindex - 1 >= 0) {
					Memory[eMemory::BaudRateCOM1].U = this->SpeedCOM.at(--this->SpeedCOMindex);
					this->toEEPROMRate = true;
				}
			});
			this->bRateP.addCallBack([&]() {
				if((uint8_t)(this->SpeedCOMindex + 1) < this->SpeedCOM.size()) {
					Memory[eMemory::BaudRateCOM1].U = this->SpeedCOM.at(++this->SpeedCOMindex);
					this->toEEPROMRate = true;
				}
			});
			this->lRate.addCallBack([&]() {
				if(this->toEEPROMRate) {
					eeprom.Write(&Memory[eMemory::BaudRateCOM1].U);
					Modbus1.SetBaudRate(Memory[eMemory::BaudRateCOM1].U*100);
					this->toEEPROMRate = false;
				}
			});

			this->bParityM.addCallBack([&]() {
				if(Memory[eMemory::ParityCOM1].U - 1 >= 0) {
					Memory[eMemory::ParityCOM1].U--;
					this->toEEPROMParity = true;
				}
			});
			this->bParityP.addCallBack([&]() {
				if(Memory[eMemory::ParityCOM1].U < 2) {
					Memory[eMemory::ParityCOM1].U++;
					this->toEEPROMParity = true;
				}
			});
			this->lParity.addCallBack([&]() {
				if(this->toEEPROMParity) {
					eeprom.Write(&Memory[eMemory::ParityCOM1].U);
					Modbus1.SetParity((UART_Parity)Memory[eMemory::ParityCOM1].U);
					this->toEEPROMParity = false;
				}
			});

			this->dSlaveId.addCallBack([]() {
				eeprom.Write(&Memory[eMemory::SlaveIdCOM1].U);
				Modbus1.SetSlaveId(Memory[eMemory::SlaveIdCOM1].U);
			});

			this->bRateM.SetLevelAcces(LevelsAcces::User);
			this->bRateP.SetLevelAcces(LevelsAcces::User);
			this->bParityM.SetLevelAcces(LevelsAcces::User);
			this->bParityP.SetLevelAcces(LevelsAcces::User);
			this->dSlaveId.SetLevelAcces(LevelsAcces::User);
}

void ScreenCOM::Loop(void) {

		for(	this->SpeedCOMindex = 0;
				this->SpeedCOM[this->SpeedCOMindex] != Memory[eMemory::BaudRateCOM1].U &&
						this->SpeedCOMindex < this->SpeedCOM.size();
				this->SpeedCOMindex++
			);
		if(this->SpeedCOMindex == this->SpeedCOM.size()) {
			this->SpeedCOMindex = 0;
		}

		this->lRate.SetText(std::to_string(Memory[eMemory::BaudRateCOM1].U*100));

		if(Memory[eMemory::ParityCOM1].U == (uint16_t)UART_Parity::None) { this->lParity.SetText("Нет\n(None)"); }
		else if(Memory[eMemory::ParityCOM1].U == (uint16_t)UART_Parity::Odd) { this->lParity.SetText("Нечетный\n(Odd)"); }
		else { this->lParity.SetText("Четный\n(Even)"); }

		static bool rate = false;
		if(this->toEEPROMRate) {
			if(!rate) {
				this->rectRate.Open();
				this->addElement(&this->lRate);
				rate = true;
			}
		}
		else {
			this->rectRate.Close();
			rate = false;
		}

		static bool parity = false;
		if(this->toEEPROMParity) {
			if(!parity) {
				this->rectParity.Open();
				this->addElement(&this->lParity);
				parity = true;
			}
		}
		else {
			this->rectParity.Close();
			parity = false;
		}
}