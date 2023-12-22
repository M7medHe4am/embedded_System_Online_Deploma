/*
 * adaptor.h
 *
 * Created: 12/17/2023 4:23:47 PM
 *  Author: m7med
 */


#ifndef ADAPTOR_H_
#define ADAPTOR_H_
#include "project_config.h"


#ifdef ATMEGA_32


//========================================INCLUDES=========================================
#include "avr/io.h"
#define F_CPU	8000000U
#include "util/delay.h"
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
//=========================================================================================

//===================================GPIO CONFIGURATIONS===================================

//DATA PORT
#define LCD_DATA_PORT	PORTA
#define LCD_DATA_DIR	DDRA

//CNTRL PORT
#define LCD_CTRL_PORT	PORTB
#define LCD_CTRL_DIR	DDRB

// CNTRL PINS
#define LCD_RS_PIN	(1)
#define LCD_RW_PIN	(2) // KEPT LOW ALL THE TIME >> AS BUSY FLAG ISN'T USED
#define LCD_EN_PIN	(3)

//========================================FUNCTIONS========================================

#define delay_function_ms(ms)	_delay_ms(ms)

#endif


#ifdef STM_32

//========================================INCLUDES=========================================
#include "Stm32F103C6_GPIO_Driver.h"
//=========================================================================================

//===================================GPIO CONFIGURATIONS===================================

//DATA PORT
#define LCD_DATA_PORT	GPIOA


//CNTRL PORT
#define LCD_CTRL_PORT	GPIOA


// CNTRL PINS
#define LCD_RS_PIN	GPIO_PIN_8
#define LCD_RW_PIN	GPIO_PIN_9 // KEPT LOW ALL THE TIME >> AS BUSY FLAG ISN'T USED
#define LCD_EN_PIN	GPIO_PIN_10
//=========================================================================================



//========================================FUNCTIONS========================================


void delay_function_ms(uint32_t time);

//=========================================================================================






#endif











#endif /* ADAPTOR_H_ */
