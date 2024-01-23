/*
 * Timers.c
 *
 * Created: 1/22/2024 4:31:33 PM
 *  Author: m7med
 */ 
#include "Timer.h"



uint16_t OVF_COUNTER = 0 ;
TIMER0_Config_t g_TIMER0_Config;
//=======================================================================================
//						APIs Supported by "MCAL TIMER0 DRIVER "
//=======================================================================================

void MCAL_TIMER0_init(TIMER0_Config_t *TIMER0CNFG)
{
	g_TIMER0_Config = *TIMER0CNFG;
	//Setting the Device mode 
		TCCR0 |= TIMER0CNFG->DEVICE_MODE ;
	//Setting the device clock source 
		TCCR0 |= TIMER0CNFG->CLOCK_SOURCE;
	//SETTING THE INT 
		TIMSK |= TIMER0CNFG->OCM_INT;
		TIMSK |= TIMER0CNFG->OVF_INT;
		
}
void MCAL_TIMER0_Deinit(void)
{
	TCCR0 |= CLOCK_SOURCE_DISABLED;
	
}

uint8_t MCAL_TIMER0_GET_CounterVal(void)
{	
	return  TCNT0 ;
	
}
void MCAL_TIMER0_SET_CounterVal(uint8_t val)
{
	TCNT0 = val ;
	
}

uint16_t MCAL_TIMER0_GET_OverFlowVal(void)
{
	
	return OVF_COUNTER;
	
}
void MCAL_TIMER0_SET_OverFlowVal(uint16_t val)
{
	OVF_COUNTER = val ;
}


void MCAL_TIMER0_SET_OC0(void)
{
		TCCR0 |= (1<<COM00) | (1<<COM01) ;
}
void MCAL_TIMER0_CLEAR_OC0(void)
{
	TCCR0 &= ~(1<<COM00);
	TCCR0 |= (1<<COM01) ;
	
}
void MCAL_TIMER0_TOGGLE_OC0(void)
{
	TCCR0 &= ~(1<<COM01);
	TCCR0 |= (1<<COM00) ;
	
}
void MCAL_TIMER0_SET_CompareVal(uint8_t val)
{
	//SETTING THE COMPARE VALUE
	OCR0 |= val;
}
uint8_t MCAL_TIMER0_GET_CompareVal(void)
{
	return OCR0;
	
}

ISR(TIMER0_COMP_vect)
{
	g_TIMER0_Config.p_CallBack_OCM();
}

ISR(TIMER0_OVF_vect)
{
	OVF_COUNTER++;
	g_TIMER0_Config.p_CallBack_OVF();
}