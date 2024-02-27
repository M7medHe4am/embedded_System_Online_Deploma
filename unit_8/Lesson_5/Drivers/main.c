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

// Terminal <-----> USART1 : MCU1 : (SPI1 Master ) ---> (SPI2 Slave) : MCU2 :USART2 ---> Terminal2
#define MCU_ACT_AS_MASTER
//#define MCU_ACT_AS_SLAVE
#include "stm32f103x6.h"
#include "Stm32F103C6_GPIO_Driver.h"
#include "Stm32F103C6_EXTI_Driver.h"
#include "Stm32F103C6_USART_Driver.h"
#include "Stm32F103C6_SPI_Driver.h"

uint16_t ch ;

void clock_init()
{
	//GPIOA ,GPIOB & AFIO CLOCK ENABLE
	RCC_GPIOA_CLCK_EN()	;
	RCC_GPIOB_CLCK_EN()	;
	RCC_AFIO_CLK_EN()	;
}



void SPI1_IRQ_CallBack (S_IRQ_SRC_t *irq_src)
{
#ifdef MCU_ACT_AS_SLAVE
	if(irq_src->RXNE)
	{

		MCAL_SPI_Rx_Tx(SPI1, &ch, SPI_disable);
//		MCAL_SPI_Receive_Data(SPI1, &ch, SPI_disable);
		MCAL_USART_SendData(USART1, &ch, enable);
	}

#endif



}







//interrupt enable
void IRQCALLBACK(void)
{
#ifdef MCU_ACT_AS_MASTER

	MCAL_USART_ReceiveData(USART1, &ch, disable);
	MCAL_USART_SendData(USART1, &ch, enable);

	//send to SPI
	//ACTIVATING THE SLAVE SELECT
	MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN_4, 0);
	MCAL_SPI_Tx_Rx(SPI1, &ch, SPI_enable);
	MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN_4, 1);
#endif

}

int main(void)
{
	clock_init();

	//USART init
	USART_Config_t USARTCNFG ;
	USARTCNFG.baudRate 	=	USART_BAUDRATE_115200	;
	USARTCNFG.HWflowCtrl=	USART_HWFlowCtrl_NONE	;
	USARTCNFG.IRQ_ENABLE=	USART_IRQ_ENABLE_RXNE	;
	USARTCNFG.p_IRQ_CallBAck = IRQCALLBACK	;
	USARTCNFG.parity	=USART_PARITY_NONE;
	USARTCNFG.payloadLength	=	USART_PAYLOAD_8BIT;
	USARTCNFG.stopBits = USART_STOPBITS_ONE	;
	USARTCNFG.USART_Mode = USART_MODE_TX_RX;
	MCAL_USART_init(USART1, &USARTCNFG);
	MCAL_USART_GPIO_SetPins(USART1);

	//SPI1 INIT
	SPI_Config_t SPI1CNFG ;

	//COMMON CONFIGURATIONS
	SPI1CNFG.CPHA = SPI_CPHA_2ND_CLCK_TRANSITION	;
	SPI1CNFG.CPOL = SPI_CPOL_HIGH_WHEN_IDLE			;
	SPI1CNFG.DATA_SIZE	=	SPI_DATA_SIZE_8B		;
	SPI1CNFG.FRAME_FORMAT	=	SPI_FRAME_FORMAT_MSB;
	//Assume by default pclk2 = 8 MHZ
	SPI1CNFG.BAUDERATE_PRESCALAR = SPI_BAUDRATE_PRESCALAR_8	;  // 1MHZ CLOCK
	SPI1CNFG.COMMUNICATION_MODE = SPI_COMMUNICATION_MODE_2LINE_FULLDUPLEX;
#ifdef MCU_ACT_AS_MASTER
	GPIO_PinConfig_t PINCNFG;
	SPI1CNFG.DEVICE_MODE = SPI_DEVICE_MODE_MASTER ;
	SPI1CNFG.IRQ_ENABLE = SPI_IRQ_ENABLE_NONE ;
	SPI1CNFG.NSS	=	SPI_NSS_SW_SET			;		// MASTER IS ALWAYS SET BY SW
	SPI1CNFG.p_IRQ_CallBAck = NULL ;



	//Configure SS on PA4 by GPIO
	PINCNFG.GPIO_Mode 			=	GPIO_MODE_OUT_PP	;
	PINCNFG.GPIO_Output_Speed	=	GPIO_SPEED_10M		;
	PINCNFG.GPIO_PinNumber		=	GPIO_PIN_4			;
	MCAL_GPIO_Init(GPIOA, &PINCNFG);

	//Force the Slave select (HIGH) IDLE MODE
	MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN_4, 1);
	// LOOP FOREVER

#endif
#ifdef MCU_ACT_AS_SLAVE
	SPI1CNFG.DEVICE_MODE = SPI_DEVICE_MODE_SLAVE ;
	SPI1CNFG.IRQ_ENABLE = SPI_IRQ_ENABLE_RXNEIE ;
	SPI1CNFG.NSS	=	SPI_NSS_HW_SLAVE_NSS_IS_INPUT	;
	SPI1CNFG.p_IRQ_CallBAck = SPI1_IRQ_CallBack ;


#endif


	MCAL_SPI_init(SPI1, &SPI1CNFG);
	MCAL_SPI_GPIO_Set_Pins(SPI1);




	while (1)
	{


	}
}








