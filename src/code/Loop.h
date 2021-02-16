/*
 * Loop.h
 *
 *  Created on: Nov 10, 2020
 *      Author: anan2
 */

#pragma once

//#define CHINA

#include "main.h"
#include "VAGUI.h"
#include "VA_EEPROM_AT25640/VA_EEPROM_AT25640.h"
#include "VA_Modbus/VA_Modbus.h"

#define MAX_COUNT_EVENT 950
#define FIRST_REG_EVENT 200
#define COUNT_REG_EVENT (sizeof(Event_t)/2)

extern EEPROM_AT25640 eeprom;
extern Modbus Modbus1;

void UpdateRegime(void);
void EventInit(void);
void EraseEvent(void);

union Memory_un {
	uint16_t 	U;
	int16_t 	S;
	uint8_t		B[2];
};

enum eMemory {
	Backlight = 10,
	TimeOut,
	BaudRateCOM1 = 14,
	ParityCOM1,
	SlaveIdCOM1,
	BaudRateCOM2,
	ParityCOM2,
	SlaveIdCOM2,

	RegimeB118 = 100,   // режимы В118 220
/*-------------------------------- Подзаряд   ------------------------------------------------ */
	MaxVoltageRecharge,
	VoltageRecharge,
	MinVoltageRecharge,
	MaxCurrentRecharge,
	CurrentRecharge,
	MinCurrentRecharge,
/*-------------------------------- Ускоренный заряд   ---------------------------------------------- */
	MaxVoltageBoostCharge,
	VoltageBoostCharge,
	MinVoltageBoostCharge,
	MaxCurrentBoostCharge,
	CurrentBoostCharge,
	MinCurrentBoostCharge,

	RegimeB118M,   // режимы В118 110

/*-------------------------------- Подзаряд M (110) ------------------------------------------------ */
	MaxVoltageRechargeM,
	VoltageRechargeM,
	MinVoltageRechargeM,
	MaxCurrentRechargeM,
	CurrentRechargeM,
	MinCurrentRechargeM,
/*-------------------------------- Ускоренный заряд  M (110)---------------------------------------------- */
	MaxVoltageBoostChargeM,
	VoltageBoostChargeM,
	MinVoltageBoostChargeM,
	MaxCurrentBoostChargeM,
	CurrentBoostChargeM,
	MinCurrentBoostChargeM,

	SettingBatteryDCXJ = 140,
	ToleranceBatteryDCXJ,
	N_SectionDCXJ,

/*-------------------------------- События   ---------------------------------------------- */
	nEvent = 198,
	cbEvent

};

enum rMemory {
	StartAdress = 4000,
	Hours = StartAdress,
	Minutes,
	Seconds,
	Day,
	Month,
	Years,
	PuskB118,
	PuskB118M,
	VoltageB118,
	CurrentB118,
	Crash
};

extern Memory_un Memory[17000];
extern uint16_t Buf[4000];
extern GUI Screens;
