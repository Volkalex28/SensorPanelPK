/*
 * VAEEPROMAT25640.cpp
 *
 *  Created on: Dec 4, 2020
 *      Author: ans0l
 */

#include <VA_EEPROM_AT25640.h>


namespace VA {

EEPROM_AT25640::EEPROM_AT25640(SPI_HandleTypeDef* hspi, uint16_t* pMem, GPIO_TypeDef* port, uint16_t pin, EEPROM_Polarity polarity) {
	this->hspi = hspi;
	this->pMem = pMem;
	this->port = port;
	this->pin = pin;
	this->polarity = polarity;
}

void EEPROM_AT25640::Select(void) {
	SPI_SetPol_LOW(this->hspi);
	HAL_GPIO_WritePin(this->port, this->pin, (this->polarity == EEPROM_Polarity::LOW) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void EEPROM_AT25640::DeSelect(void) {
	HAL_GPIO_WritePin(this->port, this->pin, (this->polarity == EEPROM_Polarity::LOW) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void EEPROM_AT25640::WriteEnable(void)
{
	uint8_t EEPROM_SPI_Write[] = {En_Write};

	this->Select();
	HAL_SPI_Transmit(this->hspi, EEPROM_SPI_Write, sizeof(EEPROM_SPI_Write), 100);
	this->DeSelect();
}

void EEPROM_AT25640::Write(uint16_t* pRegMem) {
	EEPBuf_t toBuff;
	toBuff.Adress = (pRegMem - this->pMem);
	toBuff.Value = *pRegMem;
	osMessageQueuePut(EEPBufHandle, &toBuff, 0, 5);
}

uint8_t EEPROM_AT25640::GetStatus(void) {

	uint8_t Status;
	uint8_t EEPROM_SPI_Write[] = {R_StateReg};

	this->Select();
	HAL_SPI_Transmit(this->hspi, EEPROM_SPI_Write, sizeof(EEPROM_SPI_Write), 1000);
	HAL_SPI_Receive(this->hspi, &Status, 1, 1000);
	this->DeSelect();

	return Status;
}

void EEPROM_AT25640::Reads(uint16_t AdrReg, uint16_t Size) {
	uint8_t EEPROM_SPI_Write[] = {
		R_EEPROM,
		0,
		(uint8_t)(AdrReg*2 >> 8 & 0xFF),
		(uint8_t)(AdrReg*2 & 0xFF)
	};
	std::vector<uint8_t> ReadBuff(Size*2, 0);

	this->Select();
	HAL_SPI_Transmit(this->hspi, EEPROM_SPI_Write, 4, 1000);
	HAL_SPI_Receive(this->hspi, &ReadBuff[0], Size*2, 10000);
	this->DeSelect();

	for(int i = 0; i < Size; i++) {
		*(this->pMem + AdrReg + i) = ReadBuff[0+i*2] << 8 | ReadBuff[1+i*2];
	}
}

void EEPROM_AT25640::Writes(uint16_t startAdress, uint16_t nReg, uint16_t* Buff) {
	for(uint16_t i = 0; i < nReg; i++) {
		if (Buff[i] != this->pMem[startAdress + i]) {
			EEPBuf_t toBuff;
			toBuff.Adress = (startAdress + i);
			toBuff.Value = Buff[i];
			osMessageQueuePut(EEPBufHandle, &toBuff, 0, 5);
			this->pMem[startAdress + i] = toBuff.Value;
		}
	}
}

void EEPROM_AT25640::Update(void) {
	if(osMessageQueueGetCount(EEPBufHandle)) {

		EEPBuf_t Reg;
		osMessageQueueGet(EEPBufHandle, &Reg, NULL, 5);

		uint8_t EEPROM_SPI_Write[] = {
			WR_EEPROM,
			0,
			(uint8_t)(Reg.Adress*2 >> 8 & 0xFF),
			(uint8_t)(Reg.Adress*2 & 0xFF),

			(uint8_t)(Reg.Value >> 8 & 0xFF),
			(uint8_t)(Reg.Value & 0xFF)
		};

		this->WriteEnable();
		this->Select();
		HAL_SPI_Transmit(this->hspi, EEPROM_SPI_Write, sizeof(EEPROM_SPI_Write), 1000);
		this->DeSelect();
	}
}

} /* namespace VA */
