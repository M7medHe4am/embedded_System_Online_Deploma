/*
 * Stm32F103C6_USART_Driver.h
 *
 *  Created on: Dec 27, 2023
 *      Author: m7med
 */

#ifndef INC_STM32F103C6_USART_DRIVER_H_
#define INC_STM32F103C6_USART_DRIVER_H_


//=======================================================================================
//									INCLUDES
//=======================================================================================

#include "stm32f103x6.h"
#include "Stm32F103C6_RCC_Driver.h"
#include "Stm32F103C6_GPIO_Driver.h"

//=======================================================================================
//=======================================================================================
//									TYPED DEFINED STRUCTURES
//=======================================================================================

typedef struct
{
	uint8_t		USART_Mode			;		//specifies Tx/Rx Enable/Disable
											//This parameter must be set based on @ref USART_MODE_DEFINE

	uint32_t 	baudRate			;		//CONFIGURES BAUDRATE Value
											//this parameter must be set based on @ref USART_BAUDRATE_DEFINE

	uint8_t 	payloadLength		; 		//specefies PAYLOAD LENGTH
											//this parameter must be set based on @ref USART_PAYLOAD_DEFINE

	uint8_t		parity				;		//specefies Parity
											//this parameter must be set based on //@ref USART_PARITY_DEFINE

	uint8_t		stopBits			;		//Specefies stopbits number
											//this parameter must be set based on //@ref USART_STOPBITS_DEFINE

	uint8_t		HWflowCtrl			;		//Specefies whether the HW flow control is EN/DS
											//this parameter must be set based on //@ref USART_HWFLOWCTRL_DEFINE

	uint8_t		IRQ_ENABLE			;		//ENABLE or DISABLE USART IRQ TX/Rx
											//this parameter must be set based on //@ref USART_IRQ_ENABLE_DEFINE

	void(* p_IRQ_CallBAck)(void)	;		//set the C function which will be Called once the IRQ HAPPENS


}USART_Config_t;


//=======================================================================================
//									TYPED DEFINED ENUMS
//=======================================================================================



typedef enum
{
	enable,
	disable
}EN_DS_CHOISE;






//=======================================================================================
//									REFRENCE MACROS
//=======================================================================================

//@ref USART_MODE_DEFINE
#define USART_MODE_TX								(uint32_t)(1<<3)
#define USART_MODE_RX								(uint32_t)(1<<2)
#define USART_MODE_TX_RX							(uint32_t)((1<<2) | (1<<3))

//@ref USART_BAUDRATE_DEFINE

#define USART_BAUDRATE_2400							2400
#define USART_BAUDRATE_9600							9600
#define USART_BAUDRATE_19200						19200
#define USART_BAUDRATE_57600						57600
#define USART_BAUDRATE_115200						115200
#define USART_BAUDRATE_230400						230400
#define USART_BAUDRATE_460800						460800
#define USART_BAUDRATE_921600						921600
#define USART_BAUDRATE_2250000						2250000
#define USART_BAUDRATE_4500000						4500000

//@ref USART_PAYLOAD_DEFINE
#define USART_PAYLOAD_8BIT							(uint32_t)(0)
#define USART_PAYLOAD_9BIT							(uint32_t)(1<<12)

//@ref USART_PARITY_DEFINE

#define USART_PARITY_NONE							(uint32_t)(0)
#define USART_PARITY_EVEN							(uint32_t)(1<<10)
#define USART_PARITY_ODD							(uint32_t)((1<<10) | (1<<9))

//@ref USART_STOPBITS_DEFINE

#define USART_STOPBITS_ONE							(uint32_t)(0)
#define USART_STOPBITS_HALF							(uint32_t)(1<<12)
#define USART_STOPBITS_TWO							(uint32_t)(1<<13)
#define USART_STOPBITS_ONE_HALF						(uint32_t)((1<<12) | (1<<13))


//@ref USART_HWFLOWCTRL_DEFINE

#define USART_HWFlowCtrl_NONE						(uint32_t)(0)
#define USART_HWFlowCtrl_RTS						(uint32_t)(1<<8)
#define USART_HWFlowCtrl_CTS						(uint32_t)(1<<9)
#define USART_HWFlowCtrl_RTS_CTS					(uint32_t)((1<<8) | (1<<9))

//@ref USART_IRQ_ENABLE_DEFINE
#define USART_IRQ_ENABLE_NONE						(uint32_t)(0)
#define USART_IRQ_ENABLE_TXE						(uint32_t)(1<<7)
#define USART_IRQ_ENABLE_TC							(uint32_t)(1<<6)
#define USART_IRQ_ENABLE_RXNE						(uint32_t)(1<<5)
#define USART_IRQ_ENABLE_PE							(uint32_t)(1<<8)


//=======================================================================================
//
//=======================================================================================














//=======================================================================================
//=======================================================================================
//						APIs Supported by "MCAL USART DRIVER "
//=======================================================================================

void MCAL_USART_init(USART_TypeDef* USARTx, USART_Config_t* USART_Config);
void MCAL_USART_Deinit(USART_TypeDef* USARTx);
void MCAL_USART_SendData(USART_TypeDef* USARTx,uint16_t* pTxBuffer,EN_DS_CHOISE polling );
void MCAL_USART_WAIT_TC(USART_TypeDef* USARTx);
void MCAL_USART_ReceiveData(USART_TypeDef* USARTx,uint16_t* pRxBuffer,EN_DS_CHOISE polling  );
void MCAL_USART_GPIO_SetPins(USART_TypeDef* USARTx);


//=======================================================================================
















#endif /* INC_STM32F103C6_USART_DRIVER_H_ */
