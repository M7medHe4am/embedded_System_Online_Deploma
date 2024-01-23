/*
 * WDT.c
 *
 * Created: 1/22/2024 2:22:17 PM
 * Author : m7med
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


#define LED_DDR			DDRC
#define LED_PORT 			PORTC

#define RESET_DDR			DDRC
#define RESET_PORT 		PORTC


void WDOGT_DISABLE(void)
{
	WDTCR	|= (1<<WDTOE) | (1<<WDE) ;
	WDTCR = 0x00 ;
}


void WDOGT_init(void)
{
	//WDTCR	|= (1<<WDE) | (0b110 << WDP0) ;
	WDTCR |= (1<< WDE) | (1<<WDP1) | (1 << WDP2);
	WDTCR &= ~(1<<WDP0) ;
}

int main(void)
{
	_delay_ms(2000);
	//PC0 >> DIR OUT
	LED_DDR |= (1<<0);
	//Setting another LED to know if the system is reset
	//PC1 >> DIR OUT
	RESET_DDR |= (1<<1);
	//PC1 >> TOGGLE LED
	RESET_PORT ^=(1<<1);
	

	while (1)
	{
		WDOGT_init();
		//PC0 >> TOGGLE LED
		LED_PORT ^=(1<<0);
		_delay_ms(2000);
		WDOGT_DISABLE();

	}
}