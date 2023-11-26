/*
 * atmega32_unit6Lesson4.c
 *
 * Created: 11/26/2023 2:49:52 AM
 * Author : m7med
 */ 
#define F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "stdint.h"


//#define  IO_BASE 0x20
//externalInt
//#define MCUCR *((volatile uint32_t*)(IO_BASE+0x35))
//#define MCUCSR *((volatile uint32_t*)(IO_BASE+0x34))
//#define GICR *((volatile uint32_t*)(IO_BASE+0x3B))
//status Register
//#define SREG *((volatile uint32_t*)(IO_BASE+0x3F))
//PORTD
//#define PORTD *((volatile uint32_t*)(IO_BASE+0x12))
//#define DDRD *((volatile uint32_t*)(IO_BASE+0x11))






void IRQ_init()
{	
	//the I-bit (bit 7) in the Status Register (SREG) is set (one), 
	//SREG |= (1<<7);
	sei();
	//INT0 (bit 6) bit is set >> the external pin interrupt is enabled.
	GICR |= (1<<6);
	//INT1 (bit 7) bit is set >> the external pin interrupt is enabled.
	GICR |= (1<<7);
	//INT2 (bit 5) bit is set >> the external pin interrupt is enabled.
	GICR |= (1<<5);
}

int main(void)
{
	IRQ_init();
	//allow PORTD pins (5,6,7) as output (bit = 1)
	 DDRD |= (1<<5);
	 DDRD |= (1<<6);
	 DDRD |= (1<<7);
	//int0 >> Any logical change controlled by MCUCR Register
	MCUCR |= (1<<0); 
	MCUCR &= ~(1<<1);
	//int1 >> The rising edge controlled by MCUCR Register
	MCUCR |= (1<<2);
	MCUCR |= (1<<3);
	//int2 >> The falling edge controlled by MCUCSR Register
	MCUCSR &= ~(1<<6); 
    while (1)
	{
		//PORTD pins(5,6,7) Resetting
		PORTD &= ~(1<<5);
		PORTD &= ~(1<<6);
		PORTD &= ~(1<<7);
	}
}
ISR(INT0_vect)
{
	//PORTD pin 5 setting 
	PORTD |= (1<<5);
	_delay_ms(1000);
}

ISR(INT1_vect)
{
	//PORTD pin 6 setting 
	PORTD |= (1<<6);
	_delay_ms(1000);
}
ISR(INT2_vect)
{
	//PORTD pin 7 setting 
	PORTD |= (1<<7);
	_delay_ms(1000);
}