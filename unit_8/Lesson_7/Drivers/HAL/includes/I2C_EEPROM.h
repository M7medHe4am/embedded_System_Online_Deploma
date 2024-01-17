/*
 * I2C_EEPROM.h
 *
 *  Created on: Jan 16, 2024
 *      Author: m7med
 */

#ifndef INCLUDES_I2C_EEPROM_H_
#define INCLUDES_I2C_EEPROM_H_


#include "Stm32F103C6_I2C_Driver.h"

//EEPROM is an I2C SLAVE
//IDLE mode : device is in high impedance state and waits for the data
//Master Transmitter Mode : The device transmits data to a slave receiver
//Master Receiver Mode : the device receives data from a slave transmitter

#define EEPROM_SLAVE_ADDRESS	0x2A   // STATIC


//=======================================================================================
//						APIs Supported by "HAL I2C_EEPROM DRIVER "
//=======================================================================================

void EEPROM_init(void);
uint8_t EEPROM_write_Nbytes(uint16_t memoryAddress , uint8_t* bytes,uint8_t dataLength);
uint8_t EEPROM_read_byte(uint16_t memoryAddress , uint8_t* dataOut,uint8_t dataLength);

//=======================================================================================


#endif /* INCLUDES_I2C_EEPROM_H_ */
