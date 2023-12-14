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

#define PORTD *((volatile uint8_t*)0x32)
#define DDRD *((volatile uint8_t*)0x31)


void GPIO_init(){
	
	//PORTD pins (4,5,6,7) direction >> output
	int i;
	for (i=4;i<8;i++)
	{
		setBit(DDRD,i);
	}
}

int main(void)
{
	GPIO_init();
   int i;
	while (1)
	{
		for (i=5;i<8;i++)
		{
			setBit(PORTD,i);
			_delay_ms(500);
			clearBit(PORTD,i);
		}
		setBit(PORTD,4);
		_delay_ms(500);
		clearBit(PORTD,4);
	}
    return 0;
}


    