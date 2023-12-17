/*
 * keypad.c
 *
 * Created: 12/13/2023 4:15:40 AM
 *  Author: m7med
 */ 
#include "keypad.h"

int keypad_rows[] = {R0,R1,R2,R3};
int keypad_cols[] = {C0,C1,C2,C3};




void  Keypad_init()
{
	//setting the upper part of keypad ports as inputs
	KEYPAD_DATA_DIR &= ~ ((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));
	//setting the lower part of keypad ports as outputs
	KEYPAD_DATA_DIR |=	 ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));
	//setting the upper pins as (Pull up inputs) >> "logic '1' "
	// Writing "logic '1' "	on the lower pins 
	KEYPAD_PORT = 0xFF;
	
}
char Keypad_getkey()
{
	int i , j; 
	
	
	
	for (i= 0 ; i < 4 ; i++)
	{
		//setting all columns ports as high
		KEYPAD_PORT |= ((1<<keypad_cols[0]) | (1<<keypad_cols[1]) | (1<<keypad_cols[2]) | (1<<keypad_cols[3]));
		//sending a low to a random keypad column
		KEYPAD_PORT &= ~(1<<keypad_cols[i]) ; 
		
		for (j=0 ; j < 4 ; j++)
		{
			if(!((KEYPAD_PIN>>keypad_rows[j]) & 1))
			{
				//if the button still pressed >> loop until it is released
				while (!((KEYPAD_PIN>>keypad_rows[j]) & 1));
				switch (i)
				{
					case 0 :
					{
						if(j == 0 )	return  '7'	;	
						else if (j==1)	return	'4';
						else if (j==2)	return	'1';
						else if (j==3)	return	'?';
						break ;
					}
					case 1 :
					{
						if(j == 0 )	return  '8'	;
						else if (j==1)	return	'5';
						else if (j==2)	return	'2';
						else if (j==3)	return	'0';
						break ;
					}
					case 2 :
					{
						if(j == 0 )	return  '9'	;
						else if (j==1)	return	'6';
						else if (j==2)	return	'3';
						else if (j==3)	return	'=';
						break ;
					}
					case 3 :
					{
						if(j == 0 )	return  '/'	;
						else if (j==1)	return	'*';
						else if (j==2)	return	'-';
						else if (j==3)	return	'+';
						break ;
					}
				}
				
			}
			
		}
		
	}
	return 'A';	
}




