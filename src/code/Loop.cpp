/*
 * Loop.cpp
 *
 *  Created on: Nov 10, 2020
 *      Author: anan2
 */

#include "Loop.h"

#include "../etl/include/etl/vector.h"

#include "ScreenGlobal.h"
#include "ScreenMenu.h"
#include "ScreenSysSett.h"
#include "ScreenSetTime.h"
#include "ScreenCOM.h"
#include "ScreenAutorization.h"
#include "ScreenCrash.h"
#include "ScreenEvents.h"
#include "ScreenZVU.h"
#include "ScreenSettZVU.h"
#include "ScreenBattery.h"
#include "ScreenMain.h"
#include "ScreenContrlInsulation.h"

etl::vector<uint8_t, 10> v = {0};

Memory_un Memory[17000] = {};
uint16_t Buf[4000] = {};

bool CrashBattery = true;

using namespace VA;

GUI Screens(11);

ScreenGlobal Global;									//0
ScreenMenu Menu;										//1
ScreenSysSett SystemSett;								//2
ScreenSetTime SetTime;									//3
ScreenCOM COMSett;										//4
ScreenAutorization Autorization;						//5
ScreenCrash sCrash;										//6
ScreenEvents sEvents;									//7
ScreenZVU sZVU;											//8
ScreenSettZVU sSettZVU;									//9
ScreenBattery sBatteryControl;							//10
//ScreenMain sMain;										//11
ScreenContrlInsulation sContrlInsulation;				//12

WindowReboot Reboot;

EEPROM_AT25640 eeprom(&hspi1, &Memory->U, NSS1_GPIO_Port, NSS1_Pin, EEPROM_Polarity::LOW);

Modbus Modbus1;
Modbus Modbus2;

#include "DeviceB118.h"
#include "DeviceDCXJ.h"

DeviceB118 B118[4] = {
		DeviceB118(ModeDevice::V220),
		DeviceB118(ModeDevice::V220),
		DeviceB118(ModeDevice::V220),
#ifdef CHINA
		DeviceB118(ModeDevice::V220)
#else
		DeviceB118(ModeDevice::V60)
#endif
};
DeviceDCXJ DCXJ;

void Setup(void) {

	eeprom.Reads(0, rMemory::StartAdress);

	if(Memory[0].U != 0x112 || Memory[3].U != 0x163) {
		uint16_t Buf1[] = { 50, 5, 0, 0, 192, 0, 100, 96, 1, 100 };
		uint16_t Buf2[] = { 0, 2600, 2310, 1900, 1050, 1000, 100, 2800, 2420, 2000, 1050, 1000, 100 };

		eeprom.Writes(10, sizeof(Buf1)/2, Buf1);
		eeprom.Writes(100, sizeof(Buf2)/2, Buf2);

		Memory[0].U = 0x112;
		Memory[3].U = 0x163;
		eeprom.Write(&Memory[0].U);
		eeprom.Write(&Memory[3].U);

		EraseEvent();
	}

	Screens.Init();
	Screens.SetBackLight(Memory[eMemory::Backlight].U);
	Screens.SetTimeOut(Memory[eMemory::TimeOut].U);

	ModbusInitStruct ModbusInit;

	ModbusInit.Adress 		= Memory[eMemory::SlaveIdCOM1].U;
	ModbusInit.huart		= &huart4;
	ModbusInit.Memory		= &Memory[1000].U;
	ModbusInit.NRegMax		= sizeof(Memory)/2 - (ModbusInit.Memory - &Memory->U);
	ModbusInit.Interface	= ModbusInterface::RS485;
	ModbusInit.Dir_Port		= DIR4_GPIO_Port;
	ModbusInit.Dir_Pin		= DIR4_Pin;
	ModbusInit.Dir_Polarity = VA_MODBUS_POLARITY_LOW;
	ModbusInit.WaitSlave	= 500;
	ModbusInit.CountRepeat	= 2;
	Modbus1.Init(&ModbusInit, ModbusRegime::Slave, &htim7);
	Modbus1.SetBaudRate(Memory[eMemory::BaudRateCOM1].U*100);
	Modbus1.SetParity((UART_Parity)Memory[eMemory::ParityCOM1].U);

	ModbusInit.huart		= &huart1;
	ModbusInit.Dir_Port		= DIR1_GPIO_Port;
	ModbusInit.Dir_Pin		= DIR1_Pin;
	Modbus2.Init(&ModbusInit, ModbusRegime::Master);

	sSettZVU.addElement(&sZVU.regime);
	sSettZVU.addElement(&sZVU.condition);
	sSettZVU.addElement(&sZVU.selectedRegime);

	for (uint8_t i = 0; i < sizeof(sZVU.selectedCondition)/sizeof(sZVU.selectedCondition[0]); i++) {
		sSettZVU.addElement(&sZVU.selectedCondition[i]);
	}

	EventInit();
}

void LoopTask(void *argument) {

	while(true) {
		Screens.Global.Loop();
		if(Screens.GetPtrCurrentScreen() != &sZVU) {
			sZVU.Loop();
		}
		Memory[rMemory::VoltageB118].U = sZVU.OutputVoltage;
		Memory[rMemory::CurrentB118].U = sZVU.OutputCurrent;
		Memory[rMemory::Crash].U = !Global.indCrash.state;
		sBatteryControl.Max = Memory[eMemory::N_SectionDCXJ].U;

		bool state = true;
		for(uint16_t i = 0; i < BaseDevice::Devices.size(); i++) {
			if(BaseDevice::Devices[i]->ErrorConnection) {
				sCrash.addCrash((NumberCrash)(11 + i));
				state = false;
			}
			else {
				sCrash.delCrash((NumberCrash)(11 + i));
			}
		}
		for(uint16_t i = 0; i < 4; i++) {
			if(B118[i].Mem.State.Crash || B118[i].Mem.State.Protect) {
				sCrash.addCrash((NumberCrash)(91 + i));
				state = false;
			}
			else {
				sCrash.delCrash((NumberCrash)(91 + i));
			}
		}
		if(!CrashBattery) 	{
			sCrash.addCrash(NumberCrash::BatteryCrash);
			state = false;
		}
		else sCrash.delCrash(NumberCrash::BatteryCrash);

		Global.indCrash.state = state;

		HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, Global.indCrash.state ? GPIO_PIN_RESET : GPIO_PIN_SET);
		HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, Global.indCrash.state ? GPIO_PIN_RESET : GPIO_PIN_SET);

		taskYIELD();
		osDelay(5);
	}
  
}

void ExchangeTask(void *argument) {

	while(true) {
		for(uint16_t i = 0; i < BaseDevice::Devices.size(); i++) {
			for(uint16_t n = 0; n < BaseDevice::Devices[i]->Exchange.size(); n++) {
				if(BaseDevice::Devices[i]->Enable) {
					BaseDevice::Devices[i]->ErrorConnection = !Modbus2.ReadsHoldingRegisters(
							BaseDevice::Devices[i]->Adress, BaseDevice::Devices[i]->Exchange[n].FirstReg,
							BaseDevice::Devices[i]->Exchange[n].NReg, BaseDevice::Devices[i]->Exchange[n].pBuff
						);
					osDelay(500);
				}
				else { BaseDevice::Devices[i]->ErrorConnection = false; }

//				if(BaseDevice::Devices[i]->ErrorConnection || !BaseDevice::Devices[i]->Enable) {
//					memset(BaseDevice::Devices[i]->Exchange[n].pBuff, 0, BaseDevice::Devices[i]->Exchange[n].NReg*2);
//				}
			}
		}

		for(uint16_t n = 0; n < 4; n++) {
//
			WriteBuf_t temp;
// раньше применяли в китайцах
//			if(B118[n].Enable && !B118[n].ErrorConnection && !B118[n].Mem.State.State) {
//				if(abs(B118[n].Mem.Uout - B118[n].pSettings[*B118[n].pRegime]->Uset) >= 30) {
//					temp.Adress = n + 1;
//					temp.AdrReg = 0;
//					temp.Value  = B118[n].pSettings[*B118[n].pRegime]->Uset;
//					//osMessageQueuePut(WriteBufHandle, &temp, 0, 5);
//					write(temp);
//					//break;
//				}
//				if(B118[n].Mem.Imax != B118[n].pSettings[*B118[n].pRegime]->Iset) {
//					temp.Adress = n + 1;
//					temp.AdrReg = 2;
//					temp.Value  = B118[n].pSettings[*B118[n].pRegime]->Iset;
//					//osMessageQueuePut(WriteBufHandle, &temp, 0, 5);
//					write(temp);
//					//break;
//				}
//				if(B118[n].Mem.Umax != B118[n].pSettings[*B118[n].pRegime]->Umax) {
//					temp.Adress = n + 1;
//					temp.AdrReg = 3;
//					temp.Value  = B118[n].pSettings[*B118[n].pRegime]->Umax;
//					//osMessageQueuePut(WriteBufHandle, &temp, 0, 5);
//					write(temp);
//					//break;
//				}
//				if(B118[n].Mem.Umin != B118[n].pSettings[*B118[n].pRegime]->Umin) {
//					temp.Adress = n + 1;
//					temp.AdrReg = 4;
//					temp.Value  = B118[n].pSettings[*B118[n].pRegime]->Umin;
//					//osMessageQueuePut(WriteBufHandle, &temp, 0, 5);
//					write(temp);
//					//break;
//				}
//			}
			if(B118[n].Enable && !B118[n].ErrorConnection) {
				if(B118[n].Mem.State.State != *B118[n].pPusk) {
					temp.Adress = n + 1;
					temp.AdrReg = 5;
					temp.Value  = *B118[n].pPusk;
					osMessageQueuePut(WriteBufHandle, &temp, 0, 5);
					//break;
				}
			}
		}

		uint64_t* ptr = (uint64_t*)&DCXJ.Mem.sCellBattery;
		CrashBattery = true;
		for(uint16_t i = 0; i < 60; i++) {
			if(DCXJ.Enable && DCXJ.ErrorConnection == false) {
				if(i >= sBatteryControl.Max) break;
				if(abs((int)(Memory[eMemory::SettingBatteryDCXJ].U - DCXJ.Mem.cellVoltage[i])) > Memory[eMemory::ToleranceBatteryDCXJ].U) {
					(*ptr) &= ~(1 << i);
					CrashBattery = false;
				}
				else {
					(*ptr) |= (1 << i);
				}
			}
			else break;
		}

		WriteBuf_t temp;
		while(osMessageQueueGetCount(WriteBufHandle)) {
			osMessageQueueGet(WriteBufHandle, &temp, NULL, 5);
			if(Modbus2.WriteHoldingRegister(temp.Adress, temp.AdrReg, temp.Value)) {
				osDelay(500);
			}
		}
	}
}

void write(WriteBuf_t temp) {
//	if(Modbus2.WriteHoldingRegister(temp.Adress, temp.AdrReg, temp.Value)) {
//		osDelay(500);
//	}
	osMessageQueuePut(WriteBufHandle, &temp, 0, 5);
}

void ShowDefault(void *argument) {

	while(true) {
		osDelay(5);
		Screens.Touched();
		Screens.ShowScreen();
		HAL_IWDG_Refresh(&hiwdg);
	}
}

void EEPROMTask(void *argument) {

	Setup();
	while(true) {
		eeprom.Update();
		taskYIELD();
		osDelay(5);
	}

}
void EraseEvent(void) {
	eeprom.Writes(198, 2, Buf);
	eeprom.Writes(FIRST_REG_EVENT, MAX_COUNT_EVENT * COUNT_REG_EVENT, Buf);
}

void SleepTFT(void *argument) {
	Screens.Sleep();
}

void VA_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	Modbus1.Modbus_TxCpltCallback(huart);
	Modbus2.Modbus_TxCpltCallback(huart);
}
void VA_USART_IRQHandler(UART_HandleTypeDef *huart) {
	Modbus1.Modbus_IRQHandler(huart);
	Modbus2.Modbus_IRQHandler(huart);
}