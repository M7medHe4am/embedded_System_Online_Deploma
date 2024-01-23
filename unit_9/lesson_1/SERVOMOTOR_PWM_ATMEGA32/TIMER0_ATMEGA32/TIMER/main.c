/*
 * TIMER.c
 *
 * Created: 1/22/2024 4:26:35 PM
 * Author : m7med
 */ 

#define F_CPU 8000000UL
#include "MCAL/Timer.h"
#include "util/delay.h"
#define NULL ((void *)0)


int main(void)
{
	//Setting the OC0 pin as output 
	DDRB |= (1<<3);
	sei();
	TIMER0_Config_t TIMER0CNFG;
	TIMER0CNFG.DEVICE_MODE = DEVICE_MODE_PWM_FAST;
	TIMER0CNFG.CLOCK_SOURCE= CLOCK_SOURCE_PRESCALER_8;
	TIMER0CNFG.OCM_INT = OCM_INT_DISABLE;
	TIMER0CNFG.OVF_INT = OVF_INT_DISABLE;
	TIMER0CNFG.p_CallBack_OVF = NULL ;
	TIMER0CNFG.p_CallBack_OCM =NULL;
	//Setting as NON-inverting mode 
	//0 -> OCR >> 1 , OCR -> OVF >>0 
	 MCAL_TIMER0_CLEAR_OC0();
	
	//COMPARE VALUE
	//11 tick -> -90
	//18 tick -> 0
	//25 tick -> +90
	
	//MCAL_TIMER0_SET_CompareVal(11);
	//MCAL_TIMER0_SET_CompareVal(18);
	MCAL_TIMER0_SET_CompareVal(25);
	
	
	MCAL_TIMER0_init(&TIMER0CNFG);
	while (1)
	{
		
		
		
	}
}

