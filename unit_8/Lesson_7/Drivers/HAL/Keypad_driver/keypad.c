/*
 * keypad.c
 *
 * Created: 12/13/2023 4:15:40 AM
 *  Author: m7med
 */

#include "keypad.h"

//=====================GLOBAL VARIABLES=============================
uint8_t UPPER[] = {R0,R1,R2,R3};  //rows
uint8_t LOWER[] = {C0,C1,C2,C3};  //Columns
//==================================================================


//========================================FUNCTIONS========================================

void KEYPAD_init(void)
{

#ifdef ATMEGA_32
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

#endif
#ifdef STM_32

	GPIO_PinConfig_t pinCnfg;
	/*//writing low on all pins to prevent any sparks
	//MCAL_GPIO_WritePORT(KEYPAD_DATA_PORT, 0);
	//configuring upper 4 pins as input with PU
	//R0
	pinCnfg.GPIO_PinNumber = R0;
	pinCnfg.GPIO_Mode = GPIO_MODE_IN_PU;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//R1
	pinCnfg.GPIO_PinNumber = R1;
	pinCnfg.GPIO_Mode = GPIO_MODE_IN_PU;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//R2
	pinCnfg.GPIO_PinNumber = R2;
	pinCnfg.GPIO_Mode = GPIO_MODE_IN_PU;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//R3
	pinCnfg.GPIO_PinNumber = R3;
	pinCnfg.GPIO_Mode = GPIO_MODE_IN_PU ;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	 */
	//R0
	pinCnfg.GPIO_PinNumber = R0;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//R1
	pinCnfg.GPIO_PinNumber = R1;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//R2
	pinCnfg.GPIO_PinNumber = R2;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//R3
	pinCnfg.GPIO_PinNumber = R3;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//configuring lower 4 pins as output

	//C0
	pinCnfg.GPIO_PinNumber = C0;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//C1
	pinCnfg.GPIO_PinNumber = C1;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//C2
	pinCnfg.GPIO_PinNumber = C2;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);
	//C3
	pinCnfg.GPIO_PinNumber = C3;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinCnfg);


	//writing high on the lower pins
	/*MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,C0,1);
	MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,C1,1);
	MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,C2,1);
	MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,C3,1);
	 */

	MCAL_GPIO_WritePORT(KEYPAD_DATA_PORT,0xFF);
#endif

}



uint8_t KEYPAD_read_button()
{
	uint8_t i,j ;
	for (i=0 ; i <4 ; i++)
	{
#ifdef ATMEGA_32
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
#endif
#ifdef STM_32
				//writing high on the lower pins
				MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,LOWER[0],1);
				MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,LOWER[1],1);
				MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,LOWER[2],1);
				MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,LOWER[3],1);
				MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,LOWER[i],0);
				//writing low to a one keypad column atime (lower pin)
			//	MCAL_GPIO_WritePIN(KEYPAD_DATA_PORT,i, 0);
				for (j=0 ; j<4 ; j++)
				{
					if((MCAL_GPIO_ReadPIN(KEYPAD_DATA_PORT,UPPER[j]))==0)
					{
						//if the button still pressed >> loop until it is released
						while((MCAL_GPIO_ReadPIN(KEYPAD_DATA_PORT,UPPER[j]))==0);
#endif
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


