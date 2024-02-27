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
#include "stm32f103x6.h"
#include "Stm32F103C6_GPIO_Driver.h"
#include "Stm32F103C6_EXTI_Driver.h"
#include "Stm32F103C6_USART_Driver.h"

uint16_t ch ;

void clock_init()
{
	//GPIOA ,GPIOB & AFIO CLOCK ENABLE
	RCC_GPIOA_CLCK_EN()	;
	RCC_GPIOB_CLCK_EN()	;
	RCC_AFIO_CLK_EN()	;
}


//interrupt enable
void IRQCALLBACK(void)
{

	MCAL_USART_ReceiveData(USART1, &ch, disable);
	MCAL_USART_SendData(USART1, &ch, enable);

}

int main(void)
{
	clock_init();
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
	while (1)
	{


	}
}








