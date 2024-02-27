/*
 * Stm32F103C6_SPI_Driver.h
 *
 *  Created on: Jan 9, 2024
 *      Author: m7med
 */

#ifndef INC_STM32F103C6_SPI_DRIVER_H_
#define INC_STM32F103C6_SPI_DRIVER_H_


//=======================================================================================
//									INCLUDES
//=======================================================================================

#include "stm32f103x6.h"
#include "Stm32F103C6_GPIO_Driver.h"

//=======================================================================================



//=======================================================================================
//									CONFIGURATIONS STRUCTURES
//=======================================================================================

typedef struct
{
	uint8_t TXE  	 : 1 ;		//Tx buffer empty IRQ
	uint8_t RXNE 	 : 1 ;		//Rx buffer not empty IRQ
	uint8_t ERRI 	 : 1 ;		//Error IRQ
	uint8_t RESERVED : 5 ;


}S_IRQ_SRC_t;






typedef struct
{
	uint16_t DEVICE_MODE				;					//specifies the SPI MODE ( MASTER/SLAVE)
														//This parameter must be set based on @ref SPI_DEVICE_MODE_DEFINE

	uint16_t COMMUNICATION_MODE		;					//specifies the SPI COMMUNCATION  MODE (BI/UNi DIRECTION -)
														//This parameter must be set based on @ref SPI_COMMUNICATION_MODE_DEFINE

	uint16_t CPHA					;   				//specifies the SPI CLOCK PHASE
														//This parameter must be set based on @ref SPI_CPHA_DEFINE

	uint16_t CPOL					;   				//specifies the SPI CLOCK POLARITY
														//This parameter must be set based on @ref SPI_CPOL_DEFINE

	uint16_t FRAME_FORMAT			; 					//specifies the SPI FRAME FORMAT ( LSB/MSB)
														//This parameter must be set based on @ref SPI_FRAME_FORMAT_DEFINE

	uint16_t DATA_SIZE				;					//specifies the SPI DATA SIZE (8bit/16bit)
														//This parameter must be set based on @ref SPI_DATA_SIZE_DEFINE

	uint16_t	BAUDERATE_PRESCALAR	 	;					//specifies the SPI BAUD RATE PRESCALARE
														//This parameter must be set based on @ref SPI_BAUDRATE_PRESCALAR_DEFINE

	uint16_t	NSS						;					//specifies the SPI NSS CONFIGURATIONS
														//This parameter must be set based on @ref SPI_NSS_DEFINE

	uint16_t IRQ_ENABLE				;					//specifies the SPI INTERRUPT ( ENABLE / DISABLE )
														//This parameter must be set based on @ref SPI_IRQ_ENABLE_DEFINE

	void(* p_IRQ_CallBAck)(S_IRQ_SRC_t* irq_src)	;		//set the C function which will be Called once the IRQ HAPPENS

}SPI_Config_t;



//=======================================================================================
//									TYPED DEFINED ENUMS
//=======================================================================================

typedef enum
{
	SPI_enable,
	SPI_disable
}SPI_EN_DS;




//=======================================================================================

//=======================================================================================
//									@ref MACROS
//=======================================================================================



//@ref SPI_MODE_DEFINE
// SPI->CR1
#define SPI_DEVICE_MODE_MASTER											(1<<2)
#define SPI_DEVICE_MODE_SLAVE											(0)


//@ref SPI_COMMUNICATION_MODE_DEFINE
// SPI->CR1
//2LINES
#define SPI_COMMUNICATION_MODE_2LINE_FULLDUPLEX					(0)
#define SPI_COMMUNICATION_MODE_2LINE_RX_ONLY					(1 << 10)
//1LINE
#define SPI_COMMUNICATION_MODE_1LINE_RX_ONLY					(1<<15)
#define SPI_COMMUNICATION_MODE_1LINE_TX_ONLY					((1<<15) | (1<<14))


//@ref SPI_CPHA_DEFINE
// SPI->CR1
#define SPI_CPHA_1ST_CLCK_TRANSITION 	(0)
#define SPI_CPHA_2ND_CLCK_TRANSITION	(1<<0)


//@ref SPI_CPOL_DEFINE
// SPI->CR1
#define SPI_CPOL_LOW_WHEN_IDLE		 	(0)
#define SPI_CPOL_HIGH_WHEN_IDLE			(1<<1)

//@ref SPI_FRAME_FORMAT_DEFINE
// SPI->CR1
#define SPI_FRAME_FORMAT_MSB			(0)
#define SPI_FRAME_FORMAT_LSB			(1<<7)


//@ref SPI_DATA_SIZE_DEFINE
// SPI->CR1

#define SPI_DATA_SIZE_8B				(0)
#define SPI_DATA_SIZE_16B				(1<<11)

//@ref SPI_BAUDRATE_PRESCALAR_DEFINE
// SPI->CR1
#define SPI_BAUDRATE_PRESCALAR_2		(0)
#define SPI_BAUDRATE_PRESCALAR_4		(1<<3)
#define SPI_BAUDRATE_PRESCALAR_8		(2<<3)
#define SPI_BAUDRATE_PRESCALAR_16		(3<<3)
#define SPI_BAUDRATE_PRESCALAR_32		(4<<3)
#define SPI_BAUDRATE_PRESCALAR_64		(5<<3)
#define SPI_BAUDRATE_PRESCALAR_128		(6<<3)
#define SPI_BAUDRATE_PRESCALAR_256		(7<<3)


//@ref SPI_NSS_DEFINE

//if SLAVE >> SPI->CR1
//if MASTER >> SPI->CR2

//NSS Driven by  HW
//MASTER
#define SPI_NSS_HW_MASTER_NSS_IS_OUTPUT	 (1<<2)    				//>> CR2 << SSM = 0 >> HW SELECT , SSOE = 1 >> NSS IS OUTPUT  ( MSTR MUST = 1 ; )
																//( NSS IS ALWAYS LOW WHEN THE MASTER STARTS AND DIVEN HIGH WHEN IT IS DISABLED

#define SPI_NSS_HW_MASTER_NSS_IS_INPUT	 (0)				    //>> CR2 <<SSM = 0 >> HW SELEC , SSOE = 0 >> NSS IS INPUT (multimaster capability)

//SLAVE
#define SPI_NSS_HW_SLAVE_NSS_IS_INPUT	 (0)					//>> CR1 << SSM = 0 >> HW SELEC , SSOE = 0 >> NSS IS INPUT (CLASSICAL HW SLAVE MODE )

//NSS Driven by SW (master OR slave )
#define SPI_NSS_SW_RESET				 (1<<9)					//>> CR1 << slave is SW SSM = 1  >> SW SELECT , SSI is the bit to drive the salve  >> CR1
#define SPI_NSS_SW_SET					 ((1<<9)|(1<<8))		//>> CR1 << slave is SW SSM = 1  >> SW SELECT , SSI is the bit to drive the salve

//@ref SPI_IRQ_ENABLE_DEFINE
// SPI->CR2

#define SPI_IRQ_ENABLE_NONE				(0)
#define SPI_IRQ_ENABLE_TXEIE			(1<<7)
#define SPI_IRQ_ENABLE_RXNEIE			(1<<6)
#define SPI_IRQ_ENABLE_ERRIE			(1<<5)


//=======================================================================================
//=======================================================================================
//						APIs Supported by "MCAL SPI DRIVER "
//=======================================================================================

void MCAL_SPI_init(SPI_TypeDef* SPIx,SPI_Config_t* SPICNFG);
void MCAL_SPI_Deinit(SPI_TypeDef* SPIx);
void MCAL_SPI_Send_Data(SPI_TypeDef* SPIx , uint16_t* TxBuffer , SPI_EN_DS polling);
void MCAL_SPI_Receive_Data(SPI_TypeDef* SPIx , uint16_t* RxBuffer ,SPI_EN_DS polling);
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx);
void MCAL_SPI_Tx_Rx(SPI_TypeDef* SPIx , uint16_t* dataBuffer , SPI_EN_DS polling);


//=======================================================================================


#endif /* INC_STM32F103C6_SPI_DRIVER_H_ */
