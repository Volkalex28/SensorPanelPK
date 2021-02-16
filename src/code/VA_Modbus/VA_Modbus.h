#ifndef __MODBUS_H
#define __MODBUS_H

#include "main.h"

namespace VA {

#define VA_MODBUS_TIM_NONE			nullptr
#define VA_MODBUS_DIR_NONE			0

#define VA_MODBUS_POLARITY_HIGH		GPIO_PIN_SET
#define VA_MODBUS_POLARITY_LOW		GPIO_PIN_RESET
#define VA_MODBUS_POLARITY_NONE		GPIO_PIN_RESET

enum class ModbusRegime {
	Master,
	Slave
};

enum class ModbusInterface {
	USB,
	RS485,
	OTHER = USB
};

enum class UART_Parity { None, Odd, Even };

struct ModbusInitStruct {
	uint8_t Adress = 0;
	uint16_t WaitSlave = 300;
	UART_HandleTypeDef* huart = nullptr;
	uint16_t* Memory = nullptr;
	ModbusInterface Interface = ModbusInterface::OTHER;
	GPIO_TypeDef* Dir_Port = VA_MODBUS_DIR_NONE;
	uint16_t Dir_Pin = VA_MODBUS_DIR_NONE;
	GPIO_PinState Dir_Polarity = VA_MODBUS_POLARITY_NONE;
	uint8_t CountRepeat = 3;
	uint16_t NRegMax = 1;
};

class Modbus {
	enum ModbusConfig {
		N_Byte_Reseive = 256
	};
	enum ModbusFunction {
		Read_Holding_Registers  = 0x03,
		Preset_Single_Register = 0x06,
		Write_Holding_Register  = 0x06,
		Preset_Multiple_Registers = 0x10,
		Write_Multiple_Registers = 0x10

	};

	uint8_t Adress;
	UART_HandleTypeDef* huart;
	uint16_t* Memory;
	uint8_t BufRx[ModbusConfig::N_Byte_Reseive];
	uint8_t BufTx[ModbusConfig::N_Byte_Reseive];
	uint8_t data_length;
	uint16_t NRegMax;

	ModbusInterface Interface;
	GPIO_TypeDef* Dir_Port;
	uint16_t Dir_Pin;
	GPIO_PinState Dir_Rx;
	GPIO_PinState Dir_Tx;

	ModbusRegime Regime;

	uint16_t WaitSlave;
	uint8_t CountRepeat;

	TIM_HandleTypeDef* htim;
	uint16_t* pBuf = nullptr;
	uint16_t NReg = 0;

	bool isAdress(uint8_t adr);
	uint16_t crc_calc(uint8_t* pBuf, uint16_t usLen);

	void ReadHoldingRegister(void);
	void PresetSingleRegister(void);
	void PresetMultipleRegisters(void);

	void Init_TIM(TIM_HandleTypeDef* htim);
	void UART_IDLECallback(UART_HandleTypeDef *huart);
	bool MasterTransmit(uint16_t NReg, uint16_t* pBuf, uint16_t NBytes);

	void ReadOn(void);

public:
	Modbus(void) {};
	Modbus(ModbusInitStruct* InitStruct, ModbusRegime Regime, TIM_HandleTypeDef* htim = nullptr);
	~Modbus(void) {};

	void SetSlaveId(uint8_t id);
	bool SetBaudRate(uint32_t baudrate);
	bool SetParity(UART_Parity parity);

	bool ReadsHoldingRegisters(uint8_t idSlawe, uint16_t AdrReg, uint16_t NReg, uint16_t* pBuf);
	bool WriteHoldingRegister(uint8_t idSlawe, uint16_t AdrReg, uint16_t Buf);
	bool WriteMultipleRegisters(uint8_t idSlawe, uint16_t AdrReg, uint16_t NReg, uint16_t* pBuf);

	void Init(ModbusInitStruct* InitStruct, ModbusRegime Regime, TIM_HandleTypeDef* htim = nullptr);
	void Modbus_IRQHandler(UART_HandleTypeDef *huart);
	void Modbus_TxCpltCallback(UART_HandleTypeDef *huart);
};

}

#endif
