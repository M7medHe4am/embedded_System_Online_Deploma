/*
 * unit7_section1.c
 *
 * Created: 11/28/2023 8:03:05 PM
 * Author : m7med
 */ 

//#include <avr/io.h>
#include <stdint.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "utils.h"
#define PORTA *((volatile uint8_t*)0x3B)
#define DDRA *((volatile uint8_t*)0x3A)

#define PORTC *((volatile uint8_t*)0x35)
#define DDRC *((volatile uint8_t*)0x34)
#define PINC *((volatile uint8_t*)0x33)

#define SFIOR *((volatile uint8_t*)0x50)

void GPIO_init(){
	//ALL PORTD pin >>output
	DDRA = 0xFF;
	//PORTC pin0 >> input floating
	clearBit(DDRC,0);
	setBit(PORTC,0);
	clearBit(SFIOR,4);
}

int main(void)
{
	GPIO_init();
	int i=0;
	while (1)
	{
		while(readBit(PINC,0)==0)
		{
			if(i<8)
			{
				setBit(PORTA,i);
				_delay_ms(300);
				i++;
			}
			else
			{
				PORTA = 0x00;
				_delay_ms(300);
				i=0;
			}
			
			
		}
	
	}
    return 0;
}

    
