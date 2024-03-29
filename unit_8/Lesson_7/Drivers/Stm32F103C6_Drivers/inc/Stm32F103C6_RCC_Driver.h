/*
 * Stm32F103C6_RCC_Driver.h
 *
 *  Created on: Dec 27, 2023
 *      Author: m7med
 */

#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC_STM32F103C6_RCC_DRIVER_H_

//=======================================================================================
//									INCLUDES
//=======================================================================================
#include "stm32f103x6.h"
//=======================================================================================


//=======================================================================================
//									CLOCKS MACROS
//=======================================================================================

#define HSICLK 				(uint32_t)8000000
#define HSECLK				(uint32_t)16000000
#define PLLCLK				(uint32_t)16000000




//=======================================================================================
//						APIs Supported by "MCAL RCC DRIVER "
//=======================================================================================


uint32_t MCAL_RCC_getSYSCLKFreq(void);
uint32_t MCAL_RCC_getAHBCLKFreq(void);
uint32_t MCAL_RCC_getAPB1CLKFreq(void);
uint32_t MCAL_RCC_getAPB2CLKFreq(void);










#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
