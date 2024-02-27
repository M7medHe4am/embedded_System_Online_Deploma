/*
 * I2C_EEPROM.c
 *
 *  Created on: Jan 16, 2024
 *      Author: m7med
 */


#include "I2C_EEPROM.h"





void EEPROM_init(void)
{

	//=========================I2C INIT=========================//
	//     PB6 :I2C1_SCL
	//     PB7 :I2C1_SDA
	I2C_Config_t I2CCNFG ;


	//I2C Controller ACT AS A MASTER
	I2CCNFG.ENGC					= I2C_ENGC_ENABLE		;
	I2CCNFG.ACK_EN					= I2C_ACK_ENABLE		;
	I2CCNFG.CLK_Speed_Mode			= I2C_CLK_SPEED_SM		;
	I2CCNFG.CLK_Stretching			= I2C_STRETCH_ENABLE	;
	I2CCNFG.Device_Mode				= I2C_DEVICE_MODE_I2C	;
	I2CCNFG.p_Slave_Event_CallBAck	= NULL					;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_init(I2C1, &I2CCNFG);

}

uint8_t EEPROM_write_Nbytes(uint16_t memoryAddress , uint8_t* bytes,uint8_t dataLength)
{
	uint8_t i=0;

	//MISRA C++ 2008 ,18-4-1 - Dynamic heap memory allocation shall not be used
	//Violate MISRA RULE
	//(uint8_t *)malloc(dataLength +2 );
	//OR
	uint8_t buffer[256];
	buffer[0] = (uint8_t)(memoryAddress >> 8) ;		//Upper byte Memory address
	buffer[1] = (uint8_t)(memoryAddress) ;			//Lower byte Memory address

	for (i=2 ;i <(dataLength+2) ; i++)
	{
		buffer[i] = bytes[i-2];
	}






	MCAL_I2C_MASTER_Tx(I2C1, START, EEPROM_SLAVE_ADDRESS, buffer,(dataLength + 2), WITH_STOP);

	return 0;

}

uint8_t EEPROM_read_byte(uint16_t memoryAddress , uint8_t* dataOut, uint8_t dataLength)
{

	uint8_t buffer[2];
	buffer[0] = (uint8_t)(memoryAddress >> 8) ;		//Upper byte Memory address
	buffer[1] = (uint8_t)(memoryAddress) ;			//Lower byte Memory address
	MCAL_I2C_MASTER_Tx(I2C1, START,  EEPROM_SLAVE_ADDRESS, buffer, 2, WITHOUT_STOP);//writing the address only
	MCAL_I2C_MASTER_Rx(I2C1, REPEATED_START,EEPROM_SLAVE_ADDRESS,  dataOut, dataLength, WITH_STOP);

	return 0;

}




