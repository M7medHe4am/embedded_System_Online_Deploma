/*
 * keypad.h
 *
 * Created: 12/13/2023 4:15:29 AM
 *  Author: m7med
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "avr/io.h"
#define F_CPU	8000000U
#include "util/delay.h"

#define KEYPAD_PORT		PORTD
#define KEYPAD_DATA_DIR	DDRD
#define KEYPAD_PIN		PIND

#define R0	0
#define R1	1
#define R2	2
#define R3	3
#define C0	4
#define C1	5
#define C2	6
#define C3	7


void  Keypad_init();
char Keypad_getkey();




#endif /* KEYPAD_H_ */