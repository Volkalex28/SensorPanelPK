#include "VA_Modbus.h"

namespace VA {

bool Modbus::isAdress(uint8_t adr) {
	return (adr == this->Adress);
}

uint16_t Modbus::crc_calc(uint8_t* pBuf, uint16_t usLen) {
	static const uint8_t aucCRCHi[] = {
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40
	};
	static const uint8_t aucCRCLo[] = {
		0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
		0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
		0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
		0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
		0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
		0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
		0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
		0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
		0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
		0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
		0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
		0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
		0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
		0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
		0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
		0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
		0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
		0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
		0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
		0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
		0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
		0x41, 0x81, 0x80, 0x40
	};

	uint8_t ucCRCHi = 0xFF;
	uint8_t ucCRCLo = 0xFF;
	uint16_t iIndex;

	while(usLen--) {
		iIndex = ucCRCLo ^ *(pBuf++);
		ucCRCLo = (unsigned char)( ucCRCHi ^ aucCRCHi[iIndex] );
		ucCRCHi = aucCRCLo[iIndex];
	}
	return (uint16_t)(ucCRCHi << 8 | ucCRCLo);
}

void Modbus::SetSlaveId(uint8_t id) {
	this->Adress = id;
}

void Modbus::ReadHoldingRegister(void) {

	uint16_t adresReg = (uint16_t)(this->BufRx[2] << 8 | this->BufRx[3]);
	this->BufTx[2] = this->BufRx[5] << 1;

	if(adresReg + this->BufRx[5] > this->NRegMax) {
		return;
	}

	this->BufTx[0] = this->BufRx[0];
	this->BufTx[1] = this->BufRx[1];
	for(int i = 0, n = adresReg; i < this->BufTx[2]; i += 2, n++) {
		this->BufTx[3+i] = this->Memory[n] >> 8 & 0xFF;
		this->BufTx[4+i] = this->Memory[n] & 0xFF;
	}

	uint16_t CRC16 = this->crc_calc(this->BufTx, 3+this->BufTx[2]);
	this->BufTx[3+this->BufTx[2]] = CRC16 & 0xFF;
	this->BufTx[4+this->BufTx[2]] = CRC16 >> 8 & 0xFF;
}

void Modbus::PresetSingleRegister(void) {

	uint16_t adresReg = (uint16_t)(this->BufRx[2] << 8 | this->BufRx[3]);

	if(adresReg > this->NRegMax) {
		return;
	}

	this->BufTx[0] = this->BufRx[0];
	this->BufTx[1] = this->BufRx[1];
	this->BufTx[2] = this->BufRx[2];
	this->BufTx[3] = this->BufRx[3];

	this->Memory[adresReg] = (uint16_t)(this->BufRx[4] << 8 | this->BufRx[5]);

	this->BufTx[4] = this->Memory[adresReg] >> 8 & 0xFF;
	this->BufTx[5] = this->Memory[adresReg] & 0xFF;

	uint16_t CRC16 = this->crc_calc(this->BufTx, 6);
	this->BufTx[6] = CRC16 & 0xFF;
	this->BufTx[7] = CRC16 >> 8 & 0xFF;
}

void Modbus::PresetMultipleRegisters(void) {

	uint16_t adresReg = (uint16_t)(this->BufRx[2] << 8 | this->BufRx[3]);
	uint16_t N_Reg = (uint16_t)(this->BufRx[4] << 8 | this->BufRx[5]);

	if(adresReg + N_Reg > this->NRegMax) {
		return;
	}

	this->BufTx[0] = this->BufRx[0];
	this->BufTx[1] = this->BufRx[1];
	this->BufTx[2] = this->BufRx[2];
	this->BufTx[3] = this->BufRx[3];
	this->BufTx[4] = this->BufRx[4];
	this->BufTx[5] = this->BufRx[5];

	for(int i = 0, n = 7; i < N_Reg; i++, n += 2) {
		this->Memory[adresReg+i] = (uint16_t)(this->BufRx[n] << 8 | this->BufRx[n+1]);
	}
	uint16_t CRC16 = this->crc_calc(this->BufTx, 6);
	this->BufRx[6] = CRC16 & 0xFF;
	this->BufRx[7] = CRC16 >> 8 & 0xFF;
}

bool Modbus::ReadsHoldingRegisters(uint8_t idSlawe, uint16_t AdrReg, uint16_t NReg, uint16_t* pBuf) {

	this->BufTx[0] = idSlawe;
	this->BufTx[1] = ModbusFunction::Read_Holding_Registers;

	this->BufTx[2] = AdrReg >> 8 & 0xFF;
	this->BufTx[3] = AdrReg & 0xFF;

	this->BufTx[4] = NReg >> 8 & 0xFF;
	this->BufTx[5] = NReg & 0xFF;

	uint16_t CRC16 = this->crc_calc(this->BufTx, 6);
	this->BufTx[6] = CRC16 & 0xFF;
	this->BufTx[7] = CRC16 >> 8 & 0xFF;

	return this->MasterTransmit(NReg, pBuf, 8);
}

bool Modbus::WriteHoldingRegister(uint8_t idSlawe, uint16_t AdrReg, uint16_t Buf) {

	this->BufTx[0] = idSlawe;
	this->BufTx[1] = ModbusFunction::Write_Holding_Register;

	this->BufTx[2] = AdrReg >> 8 & 0xFF;
	this->BufTx[3] = AdrReg & 0xFF;

	this->BufTx[4] = Buf >> 8 & 0xFF;
	this->BufTx[5] = Buf & 0xFF;

	uint16_t CRC16 = this->crc_calc(this->BufTx, 6);
	this->BufTx[6] = CRC16 & 0xFF;
	this->BufTx[7] = CRC16 >> 8 & 0xFF;

	return this->MasterTransmit(1, nullptr, 8);
}

bool Modbus::WriteMultipleRegisters(uint8_t idSlawe, uint16_t AdrReg, uint16_t NReg, uint16_t* pBuf) {

	this->BufTx[0] = idSlawe;
	this->BufTx[1] = ModbusFunction::Write_Multiple_Registers;

	this->BufTx[2] = AdrReg >> 8 & 0xFF;
	this->BufTx[3] = AdrReg & 0xFF;

	this->BufTx[4] = NReg >> 8 & 0xFF;
	this->BufTx[5] = NReg & 0xFF;

	this->BufTx[6] = NReg << 1;
	for (uint8_t i = 0; i < NReg; i++) {
		this->BufTx[7 +i*2] = pBuf[i] >> 8 & 0xff;
		this->BufTx[8 +i*2] = pBuf[i] & 0xff;
	}

	uint16_t CRC16 = this->crc_calc(this->BufTx, 7 + this->BufTx[6]);
	this->BufTx[7 + this->BufTx[6]] = CRC16 & 0xFF;
	this->BufTx[8 + this->BufTx[6]] = CRC16 >> 8 & 0xFF;

	return this->MasterTransmit(NReg, pBuf, 9 + this->BufTx[6]);

}

bool Modbus::MasterTransmit(uint16_t NReg, uint16_t* pBuf, uint16_t NBytes) {

	this->pBuf = pBuf;
	this->NReg = NReg;

	for (uint8_t i = 0; i < this->CountRepeat && this->NReg != 0; i++) {

		HAL_GPIO_WritePin(this->Dir_Port, this->Dir_Pin, this->Dir_Tx);
		HAL_UART_Transmit_DMA(this->huart, this->BufTx, NBytes);

		uint32_t end = HAL_GetTick() + this->WaitSlave;
		while(HAL_GetTick() < end && this->NReg != 0) { }

	}
	return this->NReg == 0;

}


Modbus::Modbus(ModbusInitStruct* InitStruct, ModbusRegime Regime, TIM_HandleTypeDef* htim) {
	this->Init(InitStruct, Regime, htim);
}

void Modbus::Init(ModbusInitStruct* InitStruct, ModbusRegime Regime, TIM_HandleTypeDef* htim) {
	this->Adress = InitStruct->Adress;
	this->huart = InitStruct->huart;
	this->Memory = InitStruct->Memory;
	this->htim = htim;
	this->Regime = Regime;
	this->WaitSlave = InitStruct->WaitSlave;
	this->CountRepeat = InitStruct->CountRepeat;
	this->NRegMax = InitStruct->NRegMax;

	if(InitStruct->Interface == ModbusInterface::RS485)
	{
		this->Interface = ModbusInterface::RS485;
		this->Dir_Port = InitStruct->Dir_Port;
		this->Dir_Pin = InitStruct->Dir_Pin;
		if(InitStruct->Dir_Polarity == VA_MODBUS_POLARITY_HIGH)
		{
			this->Dir_Rx = GPIO_PIN_SET;
			this->Dir_Tx = GPIO_PIN_RESET;
		}
		else
		{
			this->Dir_Rx = GPIO_PIN_RESET;
			this->Dir_Tx = GPIO_PIN_SET;
		}
	}

	__HAL_UART_ENABLE_IT(this->huart, UART_IT_IDLE);

	if(this->htim != nullptr) {
		this->Init_TIM(this->htim);
	}

	if(this->Interface == ModbusInterface::RS485) {
		HAL_GPIO_WritePin(this->Dir_Port, this->Dir_Pin, this->Dir_Rx);
	}

	if(this->Regime == ModbusRegime::Slave) {
		HAL_UART_Receive_DMA(this->huart, this->BufRx, ModbusConfig::N_Byte_Reseive);
	}
}

void Modbus::Init_TIM(TIM_HandleTypeDef* htim) {
	this->htim = htim;
	HAL_TIM_Base_Start_IT(this->htim);
}

bool Modbus::SetBaudRate(uint32_t baudrate) {
	this->huart->Init.BaudRate = baudrate;

	return HAL_UART_Init(this->huart) == HAL_OK;
}

bool Modbus::SetParity(UART_Parity parity) {

	this->huart->Init.WordLength = ((parity == UART_Parity::None) ? UART_WORDLENGTH_8B : UART_WORDLENGTH_9B);

	if(parity == UART_Parity::None) {
		this->huart->Init.Parity = UART_PARITY_NONE;
	}
	else if(parity == UART_Parity::Odd) {
		this->huart->Init.Parity = UART_PARITY_ODD;
	}
	else {
		this->huart->Init.Parity = UART_PARITY_EVEN;
	}

	return HAL_UART_Init(this->huart) == HAL_OK;
}

void Modbus::ReadOn(void) {

	__HAL_TIM_SET_COUNTER(this->htim, 0);
//	HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_TogglePin(OUT2_GPIO_Port, OUT2_Pin);
}

void Modbus::UART_IDLECallback(UART_HandleTypeDef *huart) {
	if(this->Regime == ModbusRegime::Slave) {
		if(this->isAdress(this->BufRx[0])) {
			if(this->crc_calc(this->BufRx, this->data_length) == 0) {
				if(this->Interface == ModbusInterface::RS485)
					HAL_GPIO_WritePin(this->Dir_Port, this->Dir_Pin, this->Dir_Tx);

				this->ReadOn();

				switch (this->BufRx[1]) {
				case ModbusFunction::Read_Holding_Registers: {
					this->ReadHoldingRegister();
					HAL_UART_Transmit_DMA(this->huart, this->BufTx, 5+this->BufTx[2]);
					return;
				} break;

				case ModbusFunction::Preset_Single_Register:{
					this->PresetSingleRegister();
					HAL_UART_Transmit_DMA(this->huart, this->BufTx, 8);
					return;
				} break;

				case ModbusFunction::Preset_Multiple_Registers: {
					this->PresetMultipleRegisters();
					HAL_UART_Transmit_DMA(this->huart, this->BufTx, 8);
					return;
				} break;

				default: {
					if(this->Interface == ModbusInterface::RS485)
						HAL_GPIO_WritePin(this->Dir_Port, this->Dir_Pin, this->Dir_Rx);
				} break;
				}
			}
		}
		HAL_UART_Receive_DMA(this->huart, this->BufRx, ModbusConfig::N_Byte_Reseive);
	}
	else if(this->Regime == ModbusRegime::Master) {
		if(this->BufRx[0] == this->BufTx[0]) {
			if(this->crc_calc(this->BufRx, this->data_length) == 0) {

				switch(this->BufRx[1]) {
				case ModbusFunction::Read_Holding_Registers:
					for(uint16_t i = 0; i < this->NReg; i++) {
						this->pBuf[i] = this->BufRx[3+i*2] << 8 | this->BufRx[4+i*2];
					}
					break;
				case ModbusFunction::Write_Holding_Register:
					break;
				case ModbusFunction::Write_Multiple_Registers:
					break;
				}

				if(this->BufRx[1] == this->BufTx[1]) {
					this->NReg = 0;
				}
			}
		}
	}
}

void Modbus::Modbus_TxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == this->huart) {
		if(this->Interface == ModbusInterface::RS485)
			HAL_GPIO_WritePin(this->Dir_Port, this->Dir_Pin, this->Dir_Rx);
		HAL_UART_Receive_DMA(this->huart, this->BufRx, ModbusConfig::N_Byte_Reseive);
	}
}

void Modbus::Modbus_IRQHandler(UART_HandleTypeDef *huart) {
	if(huart == this->huart) {
		if(__HAL_UART_GET_FLAG(this->huart, UART_FLAG_IDLE) != RESET) {
			__HAL_UART_CLEAR_IDLEFLAG(this->huart);
			HAL_UART_DMAStop(this->huart);
			this->data_length  = N_Byte_Reseive - __HAL_DMA_GET_COUNTER(this->huart->hdmarx);
			HAL_UART_AbortReceive(this->huart);
			this->UART_IDLECallback(this->huart);
		}
	}
}
}
