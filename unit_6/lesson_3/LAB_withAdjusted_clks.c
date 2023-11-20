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

//Learn-in-depth
//EtCh
//Mastering Embedded System online diploma
typedef volatile unsigned int vuint32_t;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *) (GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *) (GPIOA_BASE + 0x0c)
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_CFGR *(volatile uint32_t *)(RCC_BASE + 0x04)
#define RCC_CR *(volatile uint32_t *)(RCC_BASE + 0x00)


int main(void)
{
	// init clock for gpioA
	//Bit 2 IOPAEN: IO port A clock enable
	//Set and cleared by software.
	//0: IO port A clock disabled
	//1: IO port A clock enabled
	//Init GPIOA
	RCC_APB2ENR |= 1<<2;

	//Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	//100: HCLK divided by 2
	RCC_CFGR|= (0b100<<8);
	//Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	//101: HCLK divided by 4
	RCC_CFGR|= (0b101 << 11);
	//enable PLL
	RCC_CR |= (1<<24) ;
	//Bit 16 PLLSRC: PLL entry clock source
	//0: HSI oscillator clock / 2 selected as PLL input clock
	RCC_CFGR &= ~(1<<16) ;  //check if correct
	//Bits 21:18 PLLMUL: PLL multiplication factor x8
	// 0110: PLL input clock x 8
	RCC_CFGR |= (0b0110 << 18);
	//Bits 1:0 SW: System clock switch
	//10: PLL selected as system clock
	RCC_CFGR |= (0b10 << 0);

	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	while(1)
	{
		GPIOA_ODR = 1<<13 ;
		for (int i = 0; i < 5000; i++); // arbitrary delay
		GPIOA_ODR &= ~(1<<13) ;
		for (int i=0; i < 5000; i++); // arbitrary delay

	}
	return 0;
}
