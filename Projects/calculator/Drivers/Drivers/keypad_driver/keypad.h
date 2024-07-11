/*
 * keypad.h
 *
 * Created: 12/13/2023 4:15:29 AM
 *  Author: m7med
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


//==========================================NOTES==========================================
//in this code , the calculator is being introduced 
//You can use the keypad with or without calculator as following 
//=========================================================================================

//in this code , the busyFlag (BF) isn't used , instead delays is used to do the job
//=========================================================================================
//========================================INCLUDES=========================================
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "avr/io.h"
//#define F_CPU	8000000U
//#include "util/delay.h"
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

//=========================================================================================

//========================================FUNCTIONS========================================

void KEYPAD_init(void);
uint8_t KEYPAD_read_button();

//=========================================================================================









#endif /* KEYPAD_H_ */