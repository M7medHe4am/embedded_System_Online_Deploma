/*
 * project_config.h
 *
 *  Created on: Dec 19, 2023
 *      Author: m7med
 */

#ifndef INCLUDES_PROJECT_CONFIG_H_
#define INCLUDES_PROJECT_CONFIG_H_

////DEFINE THE MCU USED HERE

#define STM_32
//#define ATMEGA_32

#ifdef ATMEGA_32
//========================================INCLUDES=========================================
#include "avr/io.h"
#include "util/delay.h"
//=========================================================================================

//========================================MACROS=========================================

#define F_CPU	8000000U
//=========================================================================================




#endif
#ifdef STM_32

#endif







#endif /* INCLUDES_PROJECT_CONFIG_H_ */
