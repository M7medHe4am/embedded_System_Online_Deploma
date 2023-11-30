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


void GPIO_init(){
	DDRA = 0xFF;
	
}

int main(void)
{
	GPIO_init();
	int i;
	while (1)
	{
		for (i=0;i<8;i++)
		{
			setBit(PORTA,i);
			_delay_ms(100);
		}
	
		for (i=7;i>=0;i--)
		{
			clearBit(PORTA,i);
			_delay_ms(100);
		}
	}
    return 0;
}

    