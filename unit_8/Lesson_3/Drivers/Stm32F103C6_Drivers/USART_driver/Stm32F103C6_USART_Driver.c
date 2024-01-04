/*
 * Stm32F103C6_USART_Driver.c
 *
 *  Created on: Dec 9, 2023
 *      Author: m7med
 */
#include "Stm32F103C6_USART_Driver.h"






//=======================================================================================
//									STATIC FUNCTIONS PROTOTYPES
//=======================================================================================

static uint8_t USART_NUMBER(USART_TypeDef* USARTx);
static void USART_USART1_CLCK_EN_DS(EN_DS_CHOISE choise);
static void USART_USART2_CLCK_EN_DS(EN_DS_CHOISE choise);
static void USART_USART3_CLCK_EN_DS(EN_DS_CHOISE choise);
static void NVIC_USART1_EN_DS(EN_DS_CHOISE choise);
static void NVIC_USART2_EN_DS(EN_DS_CHOISE choise);
static void NVIC_USART3_EN_DS(EN_DS_CHOISE choise);
//=======================================================================================


//=======================================================================================
//									MACROS
//=======================================================================================

#define USART1CNFG	0
#define USART2CNFG	1
#define USART3CNFG	2

//=======================================================================================
//								GLOBAL VARIABLES
//=======================================================================================

USART_Config_t CNFG[3] ;
void (*USART_EN_DS[])(EN_DS_CHOISE) = {USART_USART1_CLCK_EN_DS , USART_USART2_CLCK_EN_DS , USART_USART3_CLCK_EN_DS} ;
uint32_t (*USART_getCLCK[])(void) = {MCAL_RCC_getAPB2CLK ,MCAL_RCC_getAPB1CLK ,MCAL_RCC_getAPB1CLK } ;
void (*NVIC_EN_DS[])(EN_DS_CHOISE) = {NVIC_USART1_EN_DS ,NVIC_USART2_EN_DS ,NVIC_USART3_EN_DS } ;

//=======================================================================================
//						APIs Supported by "MCAL USART DRIVER "
//=======================================================================================

/**======================================================================================
 * @Fn				-MCAL_USART_init
 * @brief 			-Initializes USART
 * @param [in]		-USARTx: where x can be (A...3 depending on the device used)
 * @param [in] 		-USART_Config_t: ALL USART Configuration
 * @retval 			-none
 * Note				-Supported feature : ASYNCH only , CLCK 8 MHZ
 *
 */

void MCAL_USART_init(USART_TypeDef* USARTx, USART_Config_t* USART_Config)
{
	uint32_t pclk, USARTDIV_100 , DIV_MANTISSA , DIV_FRACTION;
	uint8_t USARTNUMBER  ;
	USARTNUMBER = USART_NUMBER(USARTx) ;

	//Assigning the configurations to its USART number
	CNFG[USARTNUMBER] = *USART_Config ;
	//enable the usart clock
	USART_EN_DS[USARTNUMBER](enable);

	//Enable the USART by writing the UE bit in USART_CR1 register to 1

	USARTx->CR1 |= 1<<13 ;

	//program the USART MODE in USART_CR1
	USARTx->CR1 |= USART_Config->USART_Mode		;

	//Program the M bit in USART_CR1 to define the word length.

	USARTx->CR1	|=	USART_Config->payloadLength	;

	//Program the number of stop bits in USART_CR2.
	USARTx->CR2	|=	USART_Config->stopBits		;
	//program the USART PARITY in USART_CR1
	USARTx->CR1	|= USART_Config->parity			;
	//program the USART HWFLOW CTRL in USART_CR3
	USARTx->CR3	|=	USART_Config->HWflowCtrl	;

	//program the BaudRate Configurations in USART_BRR
	//PCLK1 for USART 2 ,3
	//PCLK2 for USART 1
	pclk = USART_getCLCK[USARTNUMBER]() ;

	//BaudRate Calculations

	USARTDIV_100 		=	(pclk*100)/(16*USART_Config->baudRate)		;
	DIV_MANTISSA 		=	USARTDIV_100/100 ;
	DIV_FRACTION		= 	((USARTDIV_100-100*DIV_MANTISSA)*16)/100	;
	//Assigning the DIV_MANTISSA , DIV_FRACTION into BRR register
	USARTx->BRR	&= ~(0XFFFF);
	USARTx->BRR |=	(DIV_MANTISSA << 4)	|	(DIV_FRACTION & 0xF)	;

	//program the Interrupt Configurations in USART_CR1
	//Enable/Disable interrupt
	if(USART_Config->IRQ_ENABLE != USART_IRQ_ENABLE_NONE)
	{
		USARTx->CR1	|=	USART_Config->IRQ_ENABLE	;
		NVIC_EN_DS[USARTNUMBER](enable);
	}

}



/**======================================================================================
 * @Fn				-MCAL_USART_Deinit
 * @brief 			-DeInitializes USART
 * @param [in]		-USARTx: where x can be (A...3 depending on the device used)
 * @retval 			-none
 * Note				-Supported feature : ASYNCH only , CLCK 8 MHZ
 * 					- MODULE RESET USING RCC
 *
 */
void MCAL_USART_Deinit(USART_TypeDef* USARTx)
{
	uint8_t USARTNUMBER  ;
	USARTNUMBER = USART_NUMBER(USARTx) ;
	USART_EN_DS[USARTNUMBER](disable);
	NVIC_EN_DS[USARTNUMBER](disable);
}




/**======================================================================================
 * @Fn				-MCAL_USART_SendData
 * @brief 			-send buffer on USART
 * @param [in]		-USARTx: where x can be (A...3 depending on the device used)
 * @param [in]		-pTxBuffer
 * @param [in]		-polling (EN/DS)
 * @param [in]		-USART_Config_t: ALL USART Configuration
 * @retval 			-NONE
 * Note				-MUST initialize USART first
 * 					-When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
 * 					the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 * 					because it is replaced by the parity
 */




void MCAL_USART_SendData(USART_TypeDef* USARTx,uint16_t* pTxBuffer,EN_DS_CHOISE polling )
{
	USART_Config_t* USART_Config;
	USART_Config =  &CNFG[USART_NUMBER(USARTx)];


	//wait until TXE flag is set in the USART_SR
	if(polling == enable)
	{
		while (! (USARTx->SR & 1<<7));
	}

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity
	if(USART_Config->payloadLength == USART_PAYLOAD_9BIT)
	{
		USARTx->DR = (*pTxBuffer	& 0x01FF )	;
	}
	else
	{
		USARTx->DR = (*pTxBuffer	& 0xFF ) 	;
	}


}



void MCAL_USART_WAIT_TC(USART_TypeDef* USARTx)
{
	//wait untill TC flag is set in the USART_SR
	while (! (USARTx->SR & 1 << 6));
}


/**======================================================================================
 * @Fn				-MCAL_USART_ReceiveData
 * @brief 			-Reveive buffer on USART
 * @param [in]		-USARTx: where x can be (A...3 depending on the device used)
 * @param [in]		-pRxBuffer
 * @param [in]		-polling (EN/DS)
 * @param [in]		-USART_Config_t: ALL USART Configuration
 * @retval 			-none
 * Note				-MUST initialize USART first
 * 					-When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
 * 					the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 * 					because it is replaced by the parity
 */


void MCAL_USART_ReceiveData(USART_TypeDef* USARTx,uint16_t* pRxBuffer,EN_DS_CHOISE polling  )
{
	USART_Config_t* USART_Config;
	USART_Config =  &CNFG[USART_NUMBER(USARTx)];
	//	Bit 5 RXNE: Read data register not empty
	//	0: Data is not received
	//	1: Received data is ready to be read
	//wait until RXNE flag is set in the USART_SR
	if(polling == enable)
	{
		while (! (USARTx->SR & 1<<5));
	}


	if(USART_Config->payloadLength == USART_PAYLOAD_9BIT)
	{
		if(USART_Config->parity == USART_PARITY_NONE)
		{
			(*(uint16_t *)pRxBuffer) = USARTx->DR;
		}
		else
		{
			(*(uint16_t *)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
	}
	else
	{
		if(USART_Config->parity == USART_PARITY_NONE)
		{
			(*(uint16_t *)pRxBuffer) = USARTx->DR;
		}
		else
		{
			(*(uint16_t *)pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);
		}
	}

}

/**======================================================================================
 * @Fn				-MCAL_USART_GPIO_SetPins
 * @brief 			-initialize GPIO pins
 * @param [in]		-USARTx: where x can be (A...3 depending on the device used)
 * @param [in]		-USART_Config_t: ALL USART Configuration
 * @retval 			-none
 * Note				-none
 */



void MCAL_USART_GPIO_SetPins(USART_TypeDef* USARTx)
{

	USART_Config_t* USART_Config;
	USART_Config =  &CNFG[USART_NUMBER(USARTx)];
	GPIO_PinConfig_t GPIO_pinCnfg;

	if(USARTx == USART1)
	{

		//Tx pin Configurations >> PA9 AF_OUT_PP <<
		GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_9			;
		GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_AF_OUT_PP	;
		GPIO_pinCnfg.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
		MCAL_GPIO_Init(GPIOA, &GPIO_pinCnfg);
		//Rx pin Configurations >> PA10 AF_floating_in <<
		GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_10			;
		GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_FLO_IN	;
		MCAL_GPIO_Init(GPIOA, &GPIO_pinCnfg);
		//CTS pin Configurations >> PA11 AF_floating_in <<
		if((USART_Config->HWflowCtrl == USART_HWFlowCtrl_CTS )||(USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS_CTS ))
		{
			GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_11			;
			GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_FLO_IN	;
			MCAL_GPIO_Init(GPIOA, &GPIO_pinCnfg);
		}
		//RTS pin Configurations >> PA11 AF_OUT_PP <<
		if((USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS )||(USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS_CTS ))
		{
			GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_12			;
			GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_AF_OUT_PP	;
			GPIO_pinCnfg.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			MCAL_GPIO_Init(GPIOA, &GPIO_pinCnfg);
		}

	}
	else if(USARTx == USART2)
	{
		//Tx pin Configurations >> PA2 AF_OUT_PP <<
		GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_2			;
		GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_AF_OUT_PP	;
		GPIO_pinCnfg.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
		MCAL_GPIO_Init(GPIOA, &GPIO_pinCnfg);
		//Rx pin Configurations >> PA13 AF_floating_in <<
		GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_3			;
		GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_FLO_IN	;
		MCAL_GPIO_Init(GPIOA, &GPIO_pinCnfg);
		//CTS pin Configurations >> PA0 AF_floating_in <<
		if((USART_Config->HWflowCtrl == USART_HWFlowCtrl_CTS )||(USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS_CTS ))
		{
			GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_0			;
			GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_FLO_IN	;
			MCAL_GPIO_Init(GPIOA, &GPIO_pinCnfg);
		}
		//RTS pin Configurations >> PA1 AF_OUT_PP <<
		if((USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS )||(USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS_CTS ))
		{
			GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_1			;
			GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_AF_OUT_PP	;
			GPIO_pinCnfg.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			MCAL_GPIO_Init(GPIOA, &GPIO_pinCnfg);
		}


	}
	else
	{
		//Tx pin Configurations >> PB10 AF_OUT_PP <<
		GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_10			;
		GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_AF_OUT_PP	;
		GPIO_pinCnfg.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
		MCAL_GPIO_Init(GPIOB, &GPIO_pinCnfg);
		//Rx pin Configurations >> PB11 AF_floating_in <<
		GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_11			;
		GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_FLO_IN	;
		MCAL_GPIO_Init(GPIOB, &GPIO_pinCnfg);
		//CTS pin Configurations >> PB13 AF_floating_in <<
		if((USART_Config->HWflowCtrl == USART_HWFlowCtrl_CTS )||(USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS_CTS ))
		{
			GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_13			;
			GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_FLO_IN	;
			MCAL_GPIO_Init(GPIOB, &GPIO_pinCnfg);
		}
		//RTS pin Configurations >> PB14 AF_OUT_PP <<
		if((USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS )||(USART_Config->HWflowCtrl == USART_HWFlowCtrl_RTS_CTS ))
		{
			GPIO_pinCnfg.GPIO_PinNumber 	=	GPIO_PIN_14			;
			GPIO_pinCnfg.GPIO_Mode			=	GPIO_MODE_AF_OUT_PP	;
			GPIO_pinCnfg.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			MCAL_GPIO_Init(GPIOB, &GPIO_pinCnfg);
		}


	}





}


//=======================================================================================
//									ISR FUNCTIONS
//=======================================================================================
void USART1_IRQHandler(void)
{
	CNFG[USART1CNFG].p_IRQ_CallBAck ();
}
void USART2_IRQHandler(void)
{
	CNFG[USART2CNFG].p_IRQ_CallBAck ();
}
void USART3_IRQHandler(void)
{

	CNFG[USART3CNFG].p_IRQ_CallBAck ();

}



//=======================================================================================


//=======================================================================================
//									STATIC FUNCTIONS IMPLEMENTATION
//=======================================================================================




static uint8_t USART_NUMBER(USART_TypeDef* USARTx)
{
	if(USARTx == USART1)
	{
		return USART1CNFG  ;
	}
	else if(USARTx == USART2)
	{
		return USART2CNFG  ;
	}
	else
	{
		return USART3CNFG  ;
	}

}

static void USART_USART1_CLCK_EN_DS(EN_DS_CHOISE choise)
{
	if (choise == enable)
	{
		RCC_USART1_CLK_EN();
	}
	else
	{
		RCC_USART1_RESET();
	}

}

static void USART_USART2_CLCK_EN_DS(EN_DS_CHOISE choise )
{
	if (choise == enable)
	{
		RCC_USART2_CLK_EN();
	}
	else
	{
		RCC_USART2_RESET();
	}
}

static void USART_USART3_CLCK_EN_DS(EN_DS_CHOISE choise)
{
	if (choise == enable)
	{
		RCC_USART3_CLK_EN();
	}
	else
	{
		RCC_USART3_RESET();
	}
}

//NVIC IRQ EN /DS
static void NVIC_USART1_EN_DS(EN_DS_CHOISE choise)
{
	if (choise == enable)
	{
		NVIC_IRQ37_USART1_ENABLE ;
	}
	else
	{
		NVIC_IRQ37_USART1_DISABLE ;
	}

}

static void NVIC_USART2_EN_DS(EN_DS_CHOISE choise)
{
	if (choise == enable)
	{
		NVIC_IRQ38_USART2_ENABLE ;
	}
	else
	{
		NVIC_IRQ38_USART2_DISABLE;
	}

}
static void NVIC_USART3_EN_DS(EN_DS_CHOISE choise)
{
	if (choise == enable)
	{
		NVIC_IRQ39_USART3_ENABLE ;
	}
	else
	{
		NVIC_IRQ39_USART3_DISABLE;
	}

}


//=======================================================================================




