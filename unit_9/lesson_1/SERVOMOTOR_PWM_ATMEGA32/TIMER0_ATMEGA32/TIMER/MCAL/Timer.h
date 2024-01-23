/*
 * Timer.h
 *
 * Created: 1/22/2024 4:31:21 PM
 *  Author: m7med
 */ 


#ifndef TIMER_H_
#define TIMER_H_



//=======================================================================================
//									INCLUDES
//=======================================================================================
#include <avr/io.h>
#include <avr/interrupt.h>

//=======================================================================================
//=======================================================================================
//									TYPED DEFINED ENUMS
//=======================================================================================



//=======================================================================================
//								CONFIGURATIONS STRUCTURES
//=======================================================================================
typedef struct 
{
	uint8_t CLOCK_SOURCE ;					//@ref TIMER0_CLOCK_SOURCE_DEFINE
	
	uint8_t DEVICE_MODE ;				//@ref TIMER0_DEVICE_MODE_DEFINE
	
	uint8_t		OCM_INT;			//@ref TIMER0_OCM_INT_DEFINE 
									//Timer/CounterTimer/Counter0 Output Compare Match Interrupt Enable
	uint8_t		OVF_INT;			//@ref TIMER0_OVF_INT_DEFINE
									//Timer/CounterTimer/Counter0 Overflow Interrupt Enable	
									
	void(*p_CallBack_OCM)(void);			//set the C function which will be Called once the OCM_INT IRQ HAPPENS
	void(*p_CallBack_OVF)(void);			//set the C function which will be Called once the OVF_INT IRQ HAPPENS
	
}TIMER0_Config_t;


//=======================================================================================
//=======================================================================================
//									@ref MACROS
//=======================================================================================

//@ref TIMER0_CLOCK_SOURCE_DEFINE
#define CLOCK_SOURCE_DISABLED				(0)
#define CLOCK_SOURCE_NO_PRESCALLING				(1 << CS00)
#define CLOCK_SOURCE_PRESCALER_8					(2<<CS00)
#define CLOCK_SOURCE_PRESCALER_64				(3<<CS00)
#define CLOCK_SOURCE_PRESCALER_256				(4<<CS00)
#define CLOCK_SOURCE_PRESCALER_1024				(5<<CS00)
#define CLOCK_SOURCE_EXT_CLK_FALLING				(6<<CS00)	//External clock source on T0 pin. Clock on falling edge.
#define CLOCK_SOURCE_EXT_CLK_RISING				(7<<CS00)		//External clock source on T0 pin. Clock on rising edge.

//@ref TIMER0_DEVICE_MODE_DEFINE

#define DEVICE_MODE_NORMAL					(0)
#define DEVICE_MODE_PWM_PHASE_CORRECT	(1 << WGM00)
#define DEVICE_MODE_CTC					(1<< WGM01)
#define DEVICE_MODE_PWM_FAST				((1 << WGM00) | (1<< WGM01))

//@ref TIMER0_OCM_INT_DEFINE    
#define OCM_INT_ENABLE				(1 << OCIE0)
#define OCM_INT_DISABLE				(0)



//@ref TIMER0_OVF_INT_DEFINE
#define OVF_INT_ENABLE				(1 << TOIE0)
#define OVF_INT_DISABLE				(0)



//=======================================================================================
//						APIs Supported by "MCAL TIMER0 DRIVER "
//=======================================================================================

void MCAL_TIMER0_init(TIMER0_Config_t *TIMER0CNFG);
void MCAL_TIMER0_Deinit(void);

uint8_t MCAL_TIMER0_GET_CounterVal(void);
void MCAL_TIMER0_SET_CounterVal(uint8_t val);
void MCAL_TIMER0_SET_OverFlowVal(uint16_t val);
uint16_t MCAL_TIMER0_GET_OverFlowVal(void);

void MCAL_TIMER0_SET_OC0(void);
void MCAL_TIMER0_CLEAR_OC0(void);
void MCAL_TIMER0_TOGGLE_OC0(void);
void MCAL_TIMER0_SET_CompareVal(uint8_t val);
uint8_t MCAL_TIMER0_GET_CompareVal(void);






#endif /* TIMER_H_ */