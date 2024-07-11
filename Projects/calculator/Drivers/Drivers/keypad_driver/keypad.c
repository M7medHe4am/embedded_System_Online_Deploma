/*
 * keypad.c
 *
 * Created: 12/13/2023 4:15:40 AM
 *  Author: m7med
 */ 
#include "keypad.h"

//=====================GLOBAL VARIABLES=============================
uint8_t UPPER[] = {R0,R1,R2,R3};
uint8_t LOWER[] = {C0,C1,C2,C3};
//==================================================================


//========================================FUNCTIONS========================================

void KEYPAD_init(void)
{
	//writing low on all pins to prevent any sparks 
	KEYPAD_DATA_PORT = 0x00;
	
	//configuring upper 4 pins as input with PU 
	//>>input configs 
	KEYPAD_DATA_DIR &= ~((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));
	//configuring lower 4 pins as output
	KEYPAD_DATA_DIR |=  ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));
	
	//>>pullUp resistor config for the upper Pins >> writing high on the PORT PINS 
	//writing high on the lower pins 
	KEYPAD_DATA_PORT = 0xFF ;
	 
}



uint8_t KEYPAD_read_button()
{
	uint8_t i,j ;
	for (i=0 ; i <4 ; i++)
	{
		//writing high on the lower pins
		KEYPAD_DATA_PORT |=  ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));
		
		//writing low to a one keypad column atime 
		KEYPAD_DATA_PORT &= ~((1<<LOWER[i]));
		for (j=0 ; j<4 ; j++)
		{
			if(!(((1<<UPPER[j])&KEYPAD_READ_PIN)>>UPPER[j]))
			{
				//if the button still pressed >> loop until it is released
				while(!(((1<<UPPER[j])&KEYPAD_READ_PIN)>>UPPER[j]));
				switch(i)
				{
					case 0 :
					{
						if(j==0)			return '7'	;
						else if (j==1)		return '4'	;
						else if (j==2)		return '1'	;
						else				return 'C'	;
						break;
					}	
					case 1 :
					{
						if(j==0)			return '8'	;
						else if (j==1)		return '5'	;
						else if (j==2)		return '2'	;
						else				return '0'	;
						break;
					}
					case 2 :
					{
						if(j==0)			return '9'	;
						else if (j==1)		return '6'	;
						else if (j==2)		return '3'	;
						else				return '='	;
						break;
					}
					default :
					{
						if(j==0)			return '/'	;
						else if (j==1)		return '*'	;
						else if (j==2)		return '-'	;
						else				return '+'	;
						break;
					}
					
				}
				
				
			}
		}
	
	}
	
	return 'A';
}



//=========================================================================================

