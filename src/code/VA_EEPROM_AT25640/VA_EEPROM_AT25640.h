/*
 * VAEEPROMAT25640.h
 *
 *  Created on: Dec 4, 2020
 *      Author: ans0ld
 */
#pragma once

#include "main.h"
#include <vector>

namespace VA {

enum Command_Byte_SPI_EEPROM {
	WR_StateReg	= 0x01,
	WR_EEPROM	= 0x02,
	R_EEPROM	= 0x03,
	Dis_Write	= 0x04,
	R_StateReg 	= 0x05,
	En_Write	= 0x06
};
enum StateReg_SPI_EEPROM {
	Bit_Busy 	= (1 << 0x00),
	Bit_WriteEn = (1 << 0x01),
	Bit_Block0 	= (1 << 0x02),
	Bit_Block1 	= (1 << 0x03),
	Bit_WPEN 	= (1 << 0x07)
};

enum class EEPROM_Polarity {
	LOW,
	HIGH
};

class EEPROM_AT25640 {

	SPI_HandleTypeDef* hspi;
	uint16_t* pMem;
	GPIO_TypeDef* port;
	uint16_t pin;
	EEPROM_Polarity polarity;
	void Select(void);
	void DeSelect(void);
	void WriteEnable(void);

public:
	EEPROM_AT25640(SPI_HandleTypeDef* hspi, uint16_t* pMem, GPIO_TypeDef* port, uint16_t pin, EEPROM_Polarity polarity);
	void Write(uint16_t* pRegMem);
	uint8_t GetStatus(void);
	void Update(void);
	void Reads(uint16_t AdrReg, uint16_t Size);
	void Writes(uint16_t startAdress, uint16_t nReg, uint16_t* Buff);

};

}

