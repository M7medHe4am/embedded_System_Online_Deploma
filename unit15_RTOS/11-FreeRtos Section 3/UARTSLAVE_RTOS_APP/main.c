/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */




#include "stdint.h"
#include "string.h"
#include "Stm32F103C6_GPIO_Driver.h"
#include "Stm32F103C6_USART_Driver.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"


//=================================GLOBAL VARIABLES==============================//

char volatile CMD ;
char PString1[15] ;
char PString2[15] ;



//===============================================================================//

//==============================SLAVE CALLBACK FUNCTION =========================//

void SlaveCallBack(void) ;


//===============================================================================//


//==============================TASKS PROTOTYPES==============================//
void vSlaveTask(void *par);

//===========================================================================//

//==============================TASKS HANDLERS==============================//
xTaskHandle xSlaveHandle = NULL ;
//===========================================================================//

//==============================QUEUE HANDLERS==============================//
QueueHandle_t xQueueHandel = NULL ;
//===========================================================================//

//==============================INITIALIZING HW==============================//

void CLCK_init(void)
{
	RCC_GPIOC_CLCK_EN() ;
	RCC_GPIOA_CLCK_EN() ;
	RCC_AFIO_CLK_EN()   ;

}

void HW_init(void)
{
	//============================USART2 INIT============================//
	//PA2 -> Tx
	//PA3 -> Rx
	//PA0 -> CTS
	//PA1 -> RTS
	USART_Config_t UARTCNFG ;
	UARTCNFG.USART_Mode     = USART_MODE_TX_RX      ;
	UARTCNFG.baudRate       = USART_BAUDRATE_115200 ;
	UARTCNFG.payloadLength  = USART_PAYLOAD_8BIT    ;
	UARTCNFG.parity         = USART_PARITY_NONE     ;
	UARTCNFG.stopBits       = USART_STOPBITS_ONE    ;
	UARTCNFG.HWflowCtrl     = USART_HWFlowCtrl_NONE ;
	UARTCNFG.IRQ_ENABLE     = USART_IRQ_ENABLE_RXNE ;
	UARTCNFG.p_IRQ_CallBAck = SlaveCallBack         ;
	MCAL_USART_init(USART2, &UARTCNFG) ;
	MCAL_USART_GPIO_SetPins(USART2)    ;

	//==================================================================//

	//===========================LED PIN INIT===========================//
	//LED PIN AS OUTPUT  >> PC13
	GPIO_PinConfig_t LEDCNFG ;
	LEDCNFG.GPIO_Mode         = GPIO_MODE_OUT_PP ;
	LEDCNFG.GPIO_PinNumber    = GPIO_PIN_13      ;
	LEDCNFG.GPIO_Output_Speed = GPIO_SPEED_10M   ;
	MCAL_GPIO_Init(GPIOC, &LEDCNFG) ;
	MCAL_GPIO_WritePIN(GPIOC, GPIO_PIN_13, 0) ;

	//==================================================================//


}

//===========================================================================//



int main(void)
{

	CLCK_init();
	HW_init()  ;

	//===========================TASK CREATE===========================//

	xTaskCreate(vSlaveTask, "vSlaveTask", configMINIMAL_STACK_SIZE, NULL , 0, xSlaveHandle) ;

	//==================================================================//

	//===========================QUEUE CREATE===========================//
	xQueueHandel = xQueueCreate(10 , sizeof(uint8_t)) ;
	//==================================================================//

	//=========================SCHEDULER START=========================//
	vTaskStartScheduler() ;
	//=================================================================//

	while(1)
	{

	}
	return 0 ;
}







//=========================TASK IMPLEMENTATION=========================//



void vSlaveTask(void *par)
{


	char CMDREC = 0 ;
	uint8_t i = 0 ;
	strcpy(PString2 , "\nLEDOFF\n" ) ;

	strcpy(PString1 , "\nLEDON\n" ) ;

	while(1)
	{
		xQueueReceive(xQueueHandel, &CMDREC, (TickType_t)5) ;

		if(CMDREC == 'T')
		{

			MCAL_GPIO_WritePIN(GPIOC, GPIO_PIN_13, 1) ;
			for (i=0 ; i < 15 ; i++)
			{
				MCAL_USART_SendData(USART2, (PString1 + i), enable) ;
			}

			CMDREC = 0 ;
		}
		else if(CMDREC == 'F' )
		{
			MCAL_GPIO_WritePIN(GPIOC, GPIO_PIN_13, 0) ;
			for (i = 0 ; i < 15 ; i++)
			{
				MCAL_USART_SendData(USART2, (PString2 + i), enable) ;
			}

			CMDREC = 0 ;

		}
	}


}

//==================================================================================//


//=========================CALLBACK FUNCTION IMPLEMENTATION=========================//


void SlaveCallBack(void)
{
	MCAL_USART_ReceiveData(USART2, &CMD, disable)  ;
	MCAL_USART_SendData(USART2, &CMD, enable)      ;
	xQueueSend(xQueueHandel ,&CMD , (TickType_t)5) ;


}

//==================================================================================//
