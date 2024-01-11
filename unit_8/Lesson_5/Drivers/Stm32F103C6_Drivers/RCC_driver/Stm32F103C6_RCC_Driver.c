/*
 * Stm32F103C6_RCC_Driver.c
 *
 *  Created on: Dec 9, 2023
 *      Author: m7med
 */

//=======================================================================================
//									INCLUDES
//=======================================================================================
#include "Stm32F103C6_RCC_Driver.h"
//=======================================================================================

//=======================================================================================
//									CLOCKS DIVIDER
//=======================================================================================

//AHB divider
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHBTABLE[]	=	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 3 , 4 , 6 , 7 , 8 , 9 } ;

//APB divider
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
const uint8_t	APBTABLE[]	=	{ 0 , 0  , 0  , 0 , 1 , 2 , 3 , 4}	;


//=======================================================================================
//						APIs Supported by "MCAL RCC DRIVER "
//=======================================================================================




uint32_t MCAL_RCC_getSYSCLK(void)
{


	//	Bits 3:2 SWS: System clock switch status
	//	Set and cleared by hardware to indicate which clock source is used as system clock.
	//	00: HSI oscillator used as system clock
	//	01: HSE oscillator used as system clock
	//	10: PLL used as system clock
	//	11: not applicable
	switch ((RCC->CFGR >> 2) & 0b11)
	{
	case 0 :
		return HSICLK	;
		break ;
	case 1 :
		//todo need to calculate it // HSE USER SHOULD SPECIFY IT
		return HSECLK	;
		break ;
	default	:
		//todo need to calculate it PLLCLK and PLLMUL & PLL SOURCE MUX
		return PLLCLK	;
		break ;
	}


}
uint32_t MCAL_RCC_getAHBCLK(void)
{
	//Bits 7:4 HPRE: AHB prescaler
	return ( MCAL_RCC_getSYSCLK() >> AHBTABLE[(RCC->CFGR >> 4)  & 0b1111] )	;

}
uint32_t MCAL_RCC_getAPB1CLK(void)
{

	//Bits 10:8 PPRE1: APB low-speed prescaler (APB1)

	return ( MCAL_RCC_getAHBCLK()	>> APBTABLE[(RCC->CFGR >> 8 ) & 0b111 ]	);



}
uint32_t MCAL_RCC_getAPB2CLK(void)
{

//	Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return (MCAL_RCC_getAHBCLK()	>> APBTABLE[(RCC->CFGR >> 11 ) & 0b111 ])	;


}
