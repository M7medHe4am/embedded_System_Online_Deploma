/*
 * Stm32F103C6_GPIO_Driver.c
 *
 *  Created on: Dec 9, 2023
 *      Author: m7med
 */

//=======================================================================================
//								INCLUDES
//=======================================================================================
#include "Stm32F103C6_EXTI_Driver.h"
#include "Stm32F103C6_GPIO_Driver.h"
//=======================================================================================
//							Generic VARIABLES
//=======================================================================================

void (*g_P_CallBack[16])(void)	;


//=======================================================================================
//=======================================================================================
//							Generic FUNCTIONS
//=======================================================================================


void ENABLE_NVIC(uint16_t lineNumber)
{

	switch (lineNumber)
	{

	case 0 :
		NVIC_IRQ6_EXTI0_ENABLE 	;
		break ;
	case 1 :
		NVIC_IRQ7_EXTI1_ENABLE 	;
		break ;
	case 2 :
		NVIC_IRQ8_EXTI2_ENABLE 	;
		break ;
	case 3 :
		NVIC_IRQ9_EXTI3_ENABLE 	;
		break ;
	case 4 :
		NVIC_IRQ10_EXTI4_ENABLE ;
		break ;
	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		NVIC_IRQ23_EXTI5_9_ENABLE 	;
		break ;
	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		NVIC_IRQ40_EXTI10_15_ENABLE ;
		break ;

	}


}
void DISABLE_NVIC(uint16_t lineNumber)
{

	switch (lineNumber)
	{

	case 0 :
		NVIC_IRQ6_EXTI0_DISABLE		;
		break ;
	case 1 :
		NVIC_IRQ7_EXTI1_DISABLE 	;
		break ;
	case 2 :
		NVIC_IRQ8_EXTI2_DISABLE 	;
		break ;
	case 3 :
		NVIC_IRQ9_EXTI3_DISABLE 	;
		break ;
	case 4 :
		NVIC_IRQ10_EXTI4_DISABLE ;
		break ;
	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		NVIC_IRQ23_EXTI5_9_DISABLE 	;
		break ;
	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		NVIC_IRQ40_EXTI10_15_DISABLE ;
		break ;

	}


}

//=======================================================================================
//========================================================================================
//						APIs Functions Definitions
//========================================================================================

/**=======================================================================================
 * @Fn				-MCAL_EXTI_GPIO_Deinit
 * @brief 			-Reset EXTI Registers and NVIC corresponding IRQ Mask
 * @param [in]		-none
 * @retval 			-none
 * Note				-none
 */

void MCAL_EXTI_GPIO_Deinit(void)
{
	//SETTING THE RESET VALUES FOR ALL THE PRIPHERAL REGISTERS
	EXTI->IMR 	= 0x00000000 ;
	EXTI->EMR 	= 0x00000000 ;
	EXTI->RTSR 	= 0x00000000 ;
	EXTI->FTSR	= 0x00000000 ;
	EXTI->EMR 	= 0x00000000 ;
	EXTI->IMR 	= 0xFFFFFFFF ;


	// SETTING THE NVIC TO BE DISABLES
	NVIC_IRQ6_EXTI0_DISABLE			;
	NVIC_IRQ7_EXTI1_DISABLE			;
	NVIC_IRQ8_EXTI2_DISABLE			;
	NVIC_IRQ9_EXTI3_DISABLE			;
	NVIC_IRQ10_EXTI4_DISABLE		;
	NVIC_IRQ23_EXTI5_9_DISABLE		;
	NVIC_IRQ40_EXTI10_15_DISABLE	;

}

/**=======================================================================================
 * @Fn				-MCAL_EXTI_GPIO_init
 * @brief 			-This is used to initialize EXTI from specific GPIO PIN and specify the MASK/Trigger condition and IRZ CallBack
 * @param [in]	 	-EXTI_cnfg set by @ref EXTI_define , EXTI_Trigger_define and EXTI_ITQ_define
 * @retval 			-none
 * Note				-STM32F103C6 has GPIO A,B,C,D,E Modules
 * 					 But LQFP48 Package has only GPIO A,B ,PART of C,D exported as EXTERNAL PINS from the MCU
 * 					 Also mandatory to enable RCC Clock for AFIO and The corresponding GPIO
 */


void MCAL_EXTI_GPIO_Init(EXTI_PINCNFG_t* EXTI_PINCNFG)
{
	//1- Configuring GPIO to be AF INPUT >> FLOATING INPUT
	GPIO_PinConfig_t pinCnfg ;
	pinCnfg.GPIO_PinNumber 	=	EXTI_PINCNFG->EXTI_PIN.GPIO_PIN ;
	pinCnfg.GPIO_Mode		=	GPIO_MODE_FLO_IN				;
	MCAL_GPIO_Init(EXTI_PINCNFG->EXTI_PIN.GPIO_PORT, &pinCnfg);
	//==============================================================
	//2- Configuring GPIO to be AF INPUT >> FLOATING INPUT
	uint8_t AFIO_EXTICR_index 		;
	uint8_t	AFIO_EXTICR_position	;

	AFIO_EXTICR_index 		=  EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber / 4 		;
	AFIO_EXTICR_position	= (EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber % 4) * 4	;

	//Checking for the port selected
	uint8_t selectedPort =	(EXTI_PINCNFG->EXTI_PIN.GPIO_PORT == GPIOA)? 0:\
			(EXTI_PINCNFG->EXTI_PIN.GPIO_PORT == GPIOB)? 1:\
					(EXTI_PINCNFG->EXTI_PIN.GPIO_PORT == GPIOC)? 2:3;

	//CLearing the selected 4 bits
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_position ) ;
	//Updating the selected 4 bins
	AFIO->EXTICR[AFIO_EXTICR_index] |=  ((selectedPort & 0xF)  << AFIO_EXTICR_position ) ;
	//=======================================================================================
	//3- Update Rising/Falling EDGE
	//NOTE THAT BITS ARE CLEARED FIRST BECAUSE THIS FUNCTION COULD BE CALLED DURING RUNTIME INCASE TO UPDATE VALUES
	//CLEARING BITS
	EXTI->RTSR &= ~(1<<EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber)	;
	EXTI->FTSR &= ~(1<<EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber)	;
	//UPDATING
	if (EXTI_PINCNFG->Trigger == EXTI_TRIGGER_RISING)
	{
		EXTI->RTSR |= (1 << EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber) ;
	}
	else if (EXTI_PINCNFG->Trigger == EXTI_TRIGGER_FALLING)
	{
		EXTI->FTSR |= (1 << EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber) ;
	}
	else
	{
		EXTI->RTSR |= (1 << EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber) ;
		EXTI->FTSR |= (1 << EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber) ;
	}
	//=======================================================================================
	//4- Update IRQ Handling CALLBACK
	g_P_CallBack[EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber] = EXTI_PINCNFG->P_CallBack ;

	//=======================================================================================
	//5- ENABLE / DISABLE IRQ in THE EXTI & NVIC
	if(EXTI_PINCNFG->IRQ_EN == IRQ_ENABLE)
	{
		EXTI->IMR |=  (1 << EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber)	;
		ENABLE_NVIC(EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber)			;
	}
	else
	{
		EXTI->IMR &= ~(1 << EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber)	;
		DISABLE_NVIC(EXTI_PINCNFG->EXTI_PIN.EXTI_LineNumber)		;

	}



}

/**=======================================================================================
 * @Fn				-MCAL_EXTI_GPIO_update
 * @brief 			-This is used to update EXTI from specific GPIO PIN and specify the MASK/Trigger condition and IRZ CallBack
 * @param [in]	 	-EXTI_cnfg set by @ref EXTI_define , EXTI_Trigger_define and EXTI_ITQ_define
 * @retval 			-none
 * Note				-STM32F103C6 has GPIO A,B,C,D,E Modules
 * 					 But LQFP48 Package has only GPIO A,B ,PART of C,D exported as EXTERNAL PINS from the MCU
 * 					 Also mandatory to enable RCC Clock for AFIO and The corresponding GPIO
 */




void MCAL_EXTI_GPIO_Update(EXTI_PINCNFG_t* EXTI_PINCNFG)
{

	MCAL_EXTI_GPIO_Init(EXTI_PINCNFG);

}

//=======================================================================================
//						ISR Functions Definitions
//=======================================================================================


void EXTI0_IRQHandler(void)
{
	g_P_CallBack[0]();
	//Clearing the PENDING REGISTER (PR)
	EXTI->PR |= 1 << 0 ;
}


void EXTI1_IRQHandler(void)
{
	g_P_CallBack[1]();
	//Clearing the PENDING REGISTER (PR)
	EXTI->PR |= 1 << 1 ;

}
void EXTI2_IRQHandler(void)
{
	g_P_CallBack[2]();
	//Clearing the PENDING REGISTER (PR)
	EXTI->PR |= 1 << 2 ;

}
void EXTI3_IRQHandler(void)
{
	g_P_CallBack[3]();
	//Clearing the PENDING REGISTER (PR)
	EXTI->PR |= 1 << 3 ;

}

void EXTI4_IRQHandler(void)
{
	g_P_CallBack[4]();
	//Clearing the PENDING REGISTER (PR)
	EXTI->PR |= 1 << 4 ;
}


void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & (1<<5))			{g_P_CallBack[5]();		EXTI->PR |= (1<<5)		;}
	if(EXTI->PR & (1<<6))			{g_P_CallBack[6]();		EXTI->PR |= (1<<6)		;}
	if(EXTI->PR & (1<<7))			{g_P_CallBack[7]();		EXTI->PR |= (1<<7)		;}
	if(EXTI->PR & (1<<8))			{g_P_CallBack[8]();		EXTI->PR |= (1<<8)		;}
	if(EXTI->PR & (1<<9))			{g_P_CallBack[9]();		EXTI->PR |= (1<<9)		;}

}


void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & (1<<10))			{g_P_CallBack[10]();		EXTI->PR |= (1<<10)	;}
	if(EXTI->PR & (1<<11))			{g_P_CallBack[11]();		EXTI->PR |= (1<<11)	;}
	if(EXTI->PR & (1<<12))			{g_P_CallBack[12]();		EXTI->PR |= (1<<12)	;}
	if(EXTI->PR & (1<<13))			{g_P_CallBack[13]();		EXTI->PR |= (1<<13)	;}
	if(EXTI->PR & (1<<14))			{g_P_CallBack[14]();		EXTI->PR |= (1<<14)	;}
	if(EXTI->PR & (1<<15))			{g_P_CallBack[15]();		EXTI->PR |= (1<<15)	;}

}


//=======================================================================================

