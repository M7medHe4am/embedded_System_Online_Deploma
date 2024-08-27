/*
 * stm32f103x6_EXTI.c
 *
 *  Created on: Aug 27, 2024
 *      Author: m7med
 */

/*---------------------Includes---------------------*/

#include "../INCS/stm32f103x6_EXTI.h"

/*--------------------------------------------------*/
//=======================================================================================
//							Generic VARIABLES
//=======================================================================================

void(*g_p_callback[16])(void);

//=======================================================================================
//						Static FUNCTIONS
//=======================================================================================


static void GPIO_CNFG(EXTI_PinConfig_t* EXTIx,GPIO_TypeDef_t* GPIOx);
static void AFIO_CNFG(EXTI_PinConfig_t* EXTIx,GPIO_TypeDef_t* GPIOx);
static void NVIC_CNFG(uint8_t EXTIx ,NVIC_status_t status);
//=======================================================================================


void MCAL_EXTI_init(EXTI_PinConfig_t* EXTIx,GPIO_TypeDef_t* GPIOx)
{
	//GPIO CONFIGS
	GPIO_CNFG(EXTIx,GPIOx);
	//AFIO CONFIGS
	AFIO_CNFG(EXTIx,GPIOx);
	uint8_t pinNumber =(EXTIx->EXTI_Line/4) ;
	g_p_callback[pinNumber]=EXTIx->P_CallBack ;


	//Removing the mask from the EXTIx
	EXTI->IMR |= 1<<pinNumber ;


	//RISING , FALLING EDGE SELECTION
	if(EXTIx->EXTI_Edge == EXTI_FALLING )
	{

		EXTI->FTSR |= 1<<pinNumber ;
	}
	else if (EXTIx->EXTI_Edge == EXTI_RISING )
	{
		EXTI->RTSR |= 1<<pinNumber ;
	}
	else
	{
		EXTI->FTSR |= 1<<pinNumber ;
		EXTI->RTSR |= 1<<pinNumber ;
	}




	NVIC_CNFG(EXTIx->EXTI_Line,Enable);


}




void MCAL_EXTI_Deinit(uint8_t EXTIx,GPIO_TypeDef_t* GPIOx)
{
	uint8_t pinNumber =(EXTIx/4) ;
	//MASKING THE EXTIx
	EXTI->IMR &= ~(1<<pinNumber) ;
	EXTI->FTSR &= ~(1<<pinNumber);
	EXTI->RTSR &= ~(1<<pinNumber);
	NVIC_CNFG(EXTIx,Disable);

}




//=======================================================================================
//						Static FUNCTIONS
//=======================================================================================


static void GPIO_CNFG(EXTI_PinConfig_t* EXTIx,GPIO_TypeDef_t* GPIOx)
{
	//GPIO CNFGS
	GPIO_PinConfig_t PINCNFG ;
	PINCNFG.GPIO_Mode = EXTIx->EXTI_Mode ;
	PINCNFG.GPIO_PinNumber = EXTIx->EXTI_Line ;
	PINCNFG.GPIO_Direction = EXTIx->EXTI_Direction ;
	PINCNFG.GPIO_Speed = EXTIx->EXTI_Speed ;
	MCAL_GPIO_init(GPIOx,&PINCNFG);


}

static void AFIO_CNFG(EXTI_PinConfig_t* EXTIx,GPIO_TypeDef_t* GPIOx)
{
	//AFIO CONFIGS
	int i = 0 ;
	uint8_t pinNumber = (EXTIx->EXTI_Line/4) ;
	if(pinNumber >= EXTI12  )
	{
		i=3;
		pinNumber -=12 ;
	}
	else if(pinNumber >=EXTI8)
	{
		i=2 ;
		pinNumber -=8 ;
	}
	else if(pinNumber >=EXTI4)
	{
		i=1 ;
		pinNumber -=4 ;
	}


	if(GPIOx == GPIOA)
	{
		AFIO->EXTICR[i] &= ~(1<<pinNumber) ;
	}
	else if(GPIOx == GPIOB)
	{
		AFIO->EXTICR[i] |= 1<<pinNumber ;
	}
	else if(GPIOx == GPIOC)
	{
		AFIO->EXTICR[i] |= 2<<pinNumber ;
	}

	else if(GPIOx == GPIOD)
	{
		AFIO->EXTICR[i] |= 3<<pinNumber ;
	}



}


static void NVIC_CNFG(uint8_t EXTIx ,NVIC_status_t status)
{

	uint8_t pinNumber = (EXTIx/4) ;
	int i =0 ;
	switch (pinNumber)
	{
	case 0 :
		i=6;
		break ;
	case 1 :
		i=7;
		break ;
	case 2 :
		i=8;
		break ;
	case 3 :
		i = 9 ;
		break ;
	case 4 :
		i =10 ;
		break ;
	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		i=23 ;
		break ;
	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		i=40 ;

	}
	if(status == Enable )
	{
		NVIC_ISER0 |= 1<<i ;
	}
	else if (status == Disable)
	{
		NVIC_ICER0 |= 1<<i ;
	}



}


//=======================================================================================
//						ISR Functions Definitions
//=======================================================================================
void EXTI0_IRQHandler(void)
{
	g_p_callback[0]();
	EXTI->PR |= 1<<0 ;
}


void EXTI1_IRQHandler(void)
{
	g_p_callback[1]();
	EXTI->PR |= 1<<1 ;

}
void EXTI2_IRQHandler(void)
{
	g_p_callback[2]();
	EXTI->PR |= 1<<2 ;

}
void EXTI3_IRQHandler(void)
{
	g_p_callback[3]();
	EXTI->PR |= 1<<3 ;

}

void EXTI4_IRQHandler(void)
{
	g_p_callback[4]();
	EXTI->PR |= 1<<4 ;
}


void EXTI9_5_IRQHandler(void)
{

	if(EXTI->PR & (1<<5))			{g_p_callback[5]();		EXTI->PR |= (1<<5)		;}
	if(EXTI->PR & (1<<6))			{g_p_callback[6]();		EXTI->PR |= (1<<6)		;}
	if(EXTI->PR & (1<<7))			{g_p_callback[7]();		EXTI->PR |= (1<<7)		;}
	if(EXTI->PR & (1<<8))			{g_p_callback[8]();		EXTI->PR |= (1<<8)		;}
	if(EXTI->PR & (1<<9))			{g_p_callback[9]();		EXTI->PR |= (1<<9)		;}


}


void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & (1<<10))			{g_p_callback[10]();		EXTI->PR |= (1<<10)	;}
	if(EXTI->PR & (1<<11))			{g_p_callback[11]();		EXTI->PR |= (1<<11)	;}
	if(EXTI->PR & (1<<12))			{g_p_callback[12]();		EXTI->PR |= (1<<12)	;}
	if(EXTI->PR & (1<<13))			{g_p_callback[13]();		EXTI->PR |= (1<<13)	;}
	if(EXTI->PR & (1<<14))			{g_p_callback[14]();		EXTI->PR |= (1<<14)	;}
	if(EXTI->PR & (1<<15))			{g_p_callback[15]();		EXTI->PR |= (1<<15)	;}

}


//=======================================================================================



