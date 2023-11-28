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

#define PORTD *((volatile uint8_t*)0x32)
#define DDRD *((volatile uint8_t*)0x31)


void GPIO_init(){
	
	//PORTD pins (4,5,6,7) direction >> output
	DDRD |=	(1<<4);
	DDRD |=	(1<<5);
	DDRD |=	(1<<6);
	DDRD |=	(1<<7);

}

int main(void)
{
	GPIO_init();
   
	while (1)
	{
		//LED 1 >> on
		PORTD |= (1<<5);
		_delay_ms(500);   //delay
		//LED 1 >> off
		PORTD &= ~(1<<5);
		
		//LED 2 >> on
		PORTD |= (1<<6);
		_delay_ms(500);   //delay
		//LED 2 >> off
		PORTD &= ~(1<<6);
		
		//LED 3 >> on		
		PORTD |= (1<<7);
		_delay_ms(500);   //delay
		//LED 3 >> off
		PORTD &= ~(1<<7);
		
		//BUZZER >> on
		PORTD |= (1<<4);
		_delay_ms(500);
		//BUZZER >> off
		PORTD &= ~(1<<4);

	}
    return 0;
}

    