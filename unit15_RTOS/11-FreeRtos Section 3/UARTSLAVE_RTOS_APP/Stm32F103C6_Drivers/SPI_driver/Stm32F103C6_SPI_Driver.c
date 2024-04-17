/*
 * Stm32F103C6_USART_Driver.c
 *
 *  Created on: Jan 9, 2024
 *      Author: m7med
 */

//=======================================================================================
//									INCLUDES
//=======================================================================================
#include "Stm32F103C6_SPI_Driver.h"
//=======================================================================================


//=======================================================================================
//									STATIC FUNCTIONS PROTOTYPES
//=======================================================================================

static uint8_t SPI_NUMBER(SPI_TypeDef* SPIx);
static void SPI1_EN_DS(SPI_EN_DS choise);
static void SPI2_EN_DS(SPI_EN_DS choise);
static void SPI1_NVIC_EN_DS(SPI_EN_DS choise);
static void SPI2_NVIC_EN_DS(SPI_EN_DS choise);
//=======================================================================================
//=======================================================================================
//								GLOBAL VARIABLES
//=======================================================================================


SPI_Config_t SPI_CNFG[2] ;

void (*SPI_ENABLE_DISABLE[])(SPI_EN_DS choise) = {SPI1_EN_DS,SPI2_EN_DS};

void (*SPI_NVIC_ENABLE_DISABLE[])(SPI_EN_DS choise) = {SPI1_NVIC_EN_DS,SPI2_NVIC_EN_DS};
//=======================================================================================
//								MACROS
//=======================================================================================

#define SPI1CNFG			0
#define SPI2CNFG			1

//=======================================================================================

//=======================================================================================
//						APIs Supported by "MCAL SPI DRIVER "
//=======================================================================================
/**======================================================================================
 * @Fn				-MCAL_SPI_init
 * @brief 			-Initializes SPI
 * @param [in]		-SPIx: where x can be (1,2.....) depending on the device used
 * @param [in] 		-SPI_Config_t: ALL SPI Configuration
 * @retval 			-none
 * Note				-SUPPORTED FULL DUPLEX ONLY
 *
 */

void MCAL_SPI_init(SPI_TypeDef* SPIx,SPI_Config_t* SPICNFG)
{

	uint16_t tempReg_CR1 = 0;
	uint16_t tempReg_CR2 = 0;
	//ENABLE PERIHPERAL CLOCK
	uint8_t SPINUM ;
	SPINUM = SPI_NUMBER(SPIx);
	SPI_ENABLE_DISABLE[SPINUM](SPI_enable);

	SPI_CNFG[SPINUM] = *SPICNFG;

	//SPI PERIPHERAL ENABLE
	tempReg_CR1 |= 1 << 6 ;
	//Setting the SPI MODE
	tempReg_CR1 |= SPICNFG->DEVICE_MODE;
	//Setting COMMUNICATON MODE
	tempReg_CR1 |= SPICNFG->COMMUNICATION_MODE;
	//SETTING THE CPHA
	tempReg_CR1 |= SPICNFG->CPHA;
	//Setting the CPOL
	tempReg_CR1 |= SPICNFG->CPOL;
	//Setting Frame Format (LSB/MSB)
	tempReg_CR1 |= SPICNFG->FRAME_FORMAT;
	//Setting the data Size
	tempReg_CR1 |= SPICNFG->DATA_SIZE;
	//Setting the BaudRate Prescalar
	tempReg_CR1 |= SPICNFG->BAUDERATE_PRESCALAR;

	//Setting the NSS Configurations
	if((SPICNFG->NSS == SPI_NSS_HW_MASTER_NSS_IS_INPUT) || (SPICNFG->NSS == SPI_NSS_HW_MASTER_NSS_IS_OUTPUT) )
	{
		tempReg_CR2 |= SPICNFG->NSS ;
	}
	else
	{
		tempReg_CR1 |= SPICNFG->NSS ;
	}

	//Setting the IRQ Configurations
	if(SPICNFG->IRQ_ENABLE != SPI_IRQ_ENABLE_NONE)
	{
		tempReg_CR2 |= SPICNFG->IRQ_ENABLE ;
		//NVIC ENABLE
		SPI_NVIC_ENABLE_DISABLE[SPINUM](SPI_enable)	;

	}
	SPIx->CR1 = tempReg_CR1;
	SPIx->CR2 = tempReg_CR2;



}

//=======================================================================================
/**======================================================================================
 * @Fn				-MCAL_SPI_Deinit
 * @brief 			-DeInitializes SPI
 * @param [in]		-SPIx: where x can be (1,2.....) depending on the device used
 * @retval 			-none
 * Note				-MODULE RESET USING RCC
 *
 */

void MCAL_SPI_Deinit(SPI_TypeDef* SPIx)
{
	uint8_t SPINUM ;
	SPINUM = SPI_NUMBER(SPIx);
	SPI_ENABLE_DISABLE[SPINUM](SPI_disable);
	SPI_NVIC_ENABLE_DISABLE[SPINUM](SPI_disable);

}

/**======================================================================================
 * @Fn				-MCAL_SPI_SendData
 * @brief 			-send buffer on SPI
 * @param [in]		-SPIx: where x can be (1,2.....) depending on the device used
 * @param [in]		-TxBuffer
 * @param [in]		-polling (EN/DS)
 * @retval 			-NONE
 * Note				-MUST initialize SPI first
 *
 */
#define SPI_SR_TXE	((uint8_t)0x02)	//Tx buffer Empty
#define SPI_SR_RXNE	((uint8_t)0x01)	//Rx buffer Empty
void MCAL_SPI_Send_Data(SPI_TypeDef* SPIx , uint16_t* TxBuffer , SPI_EN_DS polling)
{

	if ( polling == SPI_enable)
	{
		//check if the TX BUFFER is empty
		while (!((SPIx->SR >> 1) & 1) );


	}
	SPIx->DR=*TxBuffer  ;







}

/**======================================================================================
 * @Fn				-MCAL_SPI_Receive_Data
 * @brief 			-Receive buffer on SPI
 * @param [in]		-SPIx: where x can be (1,2.....) depending on the device used
 * @param [in]		-RxBuffer
 * @param [in]		-polling (EN/DS)
 * @retval 			-NONE
 * Note				-MUST initialize SPI first
 *
 */


void MCAL_SPI_Receive_Data(SPI_TypeDef* SPIx , uint16_t* RxBuffer ,SPI_EN_DS polling)
{

	if (polling == SPI_enable)
	{
		//check if the RX BUFFER is not empty
		while (!( (SPIx->SR >> 0 ) & 1 ));

	}

\
	*RxBuffer = SPIx->DR  ;

}


void MCAL_SPI_Tx_Rx(SPI_TypeDef* SPIx , uint16_t* dataBuffer , SPI_EN_DS polling)
{
	//	//Transmitting
		MCAL_SPI_Send_Data(SPIx ,dataBuffer,polling);

	//Receiving
		MCAL_SPI_Receive_Data(SPIx ,dataBuffer,polling);
\
}


/**======================================================================================
 * @Fn				-MCAL_SPI_GPIO_SetPins
 * @brief 			-initialize GPIO pins
 * @param [in]		-SPIx: where x can be (1,2.....) depending on the device used
 * @retval 			-none
 * Note				-none
 */

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx)
{

	GPIO_PinConfig_t PINCNFG;



	//SPI1
	if (!SPI_NUMBER(SPIx)) //SPIx == SPI1
	{
		if (SPI_CNFG[SPI1CNFG].DEVICE_MODE == SPI_DEVICE_MODE_MASTER) //MASTER
		{

			if(SPI_CNFG[SPI1CNFG].NSS == SPI_NSS_HW_MASTER_NSS_IS_INPUT)
			{
				//NSS PIN >> FLOATING INPUT , PA4
				PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
				PINCNFG.GPIO_PinNumber		=	GPIO_PIN_4			;
				MCAL_GPIO_Init(GPIOA, &PINCNFG);
			}
			else if (SPI_CNFG[SPI1CNFG].NSS == SPI_NSS_HW_MASTER_NSS_IS_OUTPUT)
			{
				//NSS PIN >> AF_PP , PA4
				PINCNFG.GPIO_Mode 			=	GPIO_MODE_AF_OUT_PP	;
				PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
				PINCNFG.GPIO_PinNumber		=	GPIO_PIN_4			;
				MCAL_GPIO_Init(GPIOA, &PINCNFG);
			}

			//SCK PIN >> AF_PP , PA5
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_AF_OUT_PP	;
			PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_5			;
			MCAL_GPIO_Init(GPIOA, &PINCNFG);

			//MISO PIN >> FLOATING INPUT , PA6
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_6			;
			MCAL_GPIO_Init(GPIOA, &PINCNFG);

			//MOSI PIN >> AF_PP , PA7
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_AF_OUT_PP	;
			PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_7			;
			MCAL_GPIO_Init(GPIOA, &PINCNFG);



		}
		else //Slave
		{
			if(SPI_CNFG[SPI1CNFG].NSS == SPI_NSS_HW_SLAVE_NSS_IS_INPUT)
			{
				//NSS PIN >> FLOATING INPUT , PA4
				PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
				PINCNFG.GPIO_PinNumber		=	GPIO_PIN_4			;
				MCAL_GPIO_Init(GPIOA, &PINCNFG);
			}
			//SCK PIN >> FLOATING INPUT , PA5
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_5			;
			MCAL_GPIO_Init(GPIOA, &PINCNFG);

			//MISO PIN >> AF_PP , PA6
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_AF_OUT_PP	;
			PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_6			;
			MCAL_GPIO_Init(GPIOA, &PINCNFG);

			//MOSI PIN >> FLOATING INPUT , PA7
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_7			;
			MCAL_GPIO_Init(GPIOA, &PINCNFG);

		}

	}
	else //SPIx == SPI2
	{
		if (SPI_CNFG[SPI2CNFG].DEVICE_MODE == SPI_DEVICE_MODE_MASTER) //MASTER
		{

			if(SPI_CNFG[SPI2CNFG].NSS == SPI_NSS_HW_MASTER_NSS_IS_INPUT)
			{
				//NSS PIN >> FLOATING INPUT , PB12
				PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
				PINCNFG.GPIO_PinNumber		=	GPIO_PIN_12			;
				MCAL_GPIO_Init(GPIOB, &PINCNFG);
			}
			else if (SPI_CNFG[SPI2CNFG].NSS == SPI_NSS_HW_MASTER_NSS_IS_OUTPUT)
			{
				//NSS PIN >> AF_PP , PB12
				PINCNFG.GPIO_Mode 			=	GPIO_MODE_AF_OUT_PP	;
				PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
				PINCNFG.GPIO_PinNumber		=	GPIO_PIN_12			;
				MCAL_GPIO_Init(GPIOB, &PINCNFG);
			}

			//SCK PIN >> AF_PP , PB13
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_AF_OUT_PP	;
			PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_13			;
			MCAL_GPIO_Init(GPIOB, &PINCNFG);

			//MISO PIN >> FLOATING INPUT , PB14
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_14			;
			MCAL_GPIO_Init(GPIOB, &PINCNFG);

			//MOSI PIN >> AF_PP , PB15
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_AF_OUT_PP	;
			PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_15			;
			MCAL_GPIO_Init(GPIOB, &PINCNFG);



		}
		else //Slave
		{
			if(SPI_CNFG[SPI2CNFG].NSS == SPI_NSS_HW_SLAVE_NSS_IS_INPUT)
			{
				//NSS PIN >> FLOATING INPUT , PB12
				PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
				PINCNFG.GPIO_PinNumber		=	GPIO_PIN_12			;
				MCAL_GPIO_Init(GPIOB, &PINCNFG);
			}
			//SCK PIN >> FLOATING INPUT ,PB13
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_13			;
			MCAL_GPIO_Init(GPIOB, &PINCNFG);

			//MISO PIN >> AF_PP ,PB14
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_AF_OUT_PP	;
			PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_14			;
			MCAL_GPIO_Init(GPIOB, &PINCNFG);

			//MOSI PIN >> FLOATING INPUT , PB15
			PINCNFG.GPIO_Mode 			=	GPIO_MODE_FLO_IN	;
			PINCNFG.GPIO_PinNumber		=	GPIO_PIN_15			;
			MCAL_GPIO_Init(GPIOB, &PINCNFG);

		}


	}


}

//=======================================================================================
//									ISR FUNCTIONS
//=======================================================================================
void SPI1_IRQHandler(void)
{

	S_IRQ_SRC_t irq_src;
	irq_src.TXE   = ((SPI1->SR >> 1) & 1) ;
	irq_src.RXNE  = ((SPI1->SR >> 0) & 1) ;
	irq_src.ERRI  = ((SPI1->SR >> 4) & 1) ;
	SPI_CNFG[SPI1CNFG].p_IRQ_CallBAck (&irq_src);
}
void SPI2_IRQHandler(void)
{
	S_IRQ_SRC_t irq_src;
	irq_src.TXE   = ((SPI2->SR >> 1) & 1) ;
	irq_src.RXNE  = ((SPI2->SR >> 0) & 1) ;
	irq_src.ERRI  = ((SPI2->SR >> 4) & 1) ;
	SPI_CNFG[SPI2CNFG].p_IRQ_CallBAck (&irq_src);
}


//=======================================================================================




//=======================================================================================
//									STATIC FUNCTIONS IMPLEMENTATION
//=======================================================================================


static uint8_t SPI_NUMBER(SPI_TypeDef* SPIx)
{
	if(SPIx == SPI1)
	{
		return 0 ;
	}
	else //SPI2
	{
		return 1 ;
	}

}


static void SPI1_EN_DS(SPI_EN_DS choise)
{
	if (choise == SPI_enable)
	{
		RCC_SPI1_CLK_EN();
	}
	else
	{
		RCC_SPI1_RESET();
	}

}

static void SPI2_EN_DS(SPI_EN_DS choise)
{
	if (choise == SPI_enable)
	{
		RCC_SPI2_CLK_EN();
	}
	else
	{
		RCC_SPI2_RESET();
	}

}

static void SPI1_NVIC_EN_DS(SPI_EN_DS choise)
{

	if (choise == SPI_enable)
	{
		NVIC_IRQ35_SPI1_ENABLE;
	}
	else
	{
		NVIC_IRQ35_SPI1_DISABLE;
	}


}
static void SPI2_NVIC_EN_DS(SPI_EN_DS choise)
{
	if (choise == SPI_enable)
	{
		NVIC_IRQ36_SPI2_ENABLE;
	}
	else
	{
		NVIC_IRQ36_SPI2_DISABLE;
	}
}


