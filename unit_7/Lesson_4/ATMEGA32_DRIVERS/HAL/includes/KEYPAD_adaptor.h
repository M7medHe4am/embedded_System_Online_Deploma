/*
 * KAYPAD_adaptor.h
 *
 * Created: 12/18/2023 5:39:17 PM
 *  Author: m7med
 */


#ifndef KAYPAD_ADAPTOR_H_
#define KAYPAD_ADAPTOR_H_

#include "project_config.h"

#ifdef ATMEGA_32


//========================================INCLUDES=========================================
#include "avr/io.h"
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

//=========================================================================================

//===================================GPIO CONFIGURATIONS===================================
////DATA PORT
#define KEYPAD_DATA_PORT	PORTD
#define KEYPAD_DATA_DIR		DDRD
#define KEYPAD_READ_PIN		PIND

//pins MACROS
#define R0		(0)
#define R1		(1)
#define R2		(2)
#define R3		(3)
#define C0		(4)
#define C1		(5)
#define C2		(6)
#define C3		(7)

#endif

#ifdef STM_32

//========================================INCLUDES=========================================
#include "Stm32F103C6_GPIO_Driver.h"
//=========================================================================================

//===================================GPIO CONFIGURATIONS===================================

////DATA PORT
#define KEYPAD_DATA_PORT	GPIOB



//pins MACROS
#define R0		GPIO_PIN_0
#define R1		GPIO_PIN_1
#define R2		GPIO_PIN_3
#define R3		GPIO_PIN_4
#define C0		GPIO_PIN_5
#define C1		GPIO_PIN_6
#define C2		GPIO_PIN_7
#define C3		GPIO_PIN_8

//=========================================================================================




#endif




#endif /* KAYPAD_ADAPTOR_H_ */
