#include "ScreenCOM.h"


ScreenCOM::ScreenCOM(): BaseScreen(&Screens, "Параметры СОМ"){
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
