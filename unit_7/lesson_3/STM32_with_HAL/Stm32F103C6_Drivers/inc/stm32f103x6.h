/*
 * stm32f103x6.h
 *
 *  Created on: Dec 9, 2023
 *      Author: m7med
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_


//-----------------------------
//Includes
//-----------------------------

#include "stdint.h"
#include "stdlib.h"
//====================================================================
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define SRAM_MERMORY_BASE					0x20000000UL
#define FLASH_MERMORY_BASE					0x08000000UL
#define SYSTEM_MERMORY_BASE					0x1FFFF000UL
#define Peripherals_BASE					0x40000000UL
#define CortexM3_internal_Peripherals_BASE	0xE0000000UL

//====================================================================


//-----------------------------
//Base addresses for AHB BUS Peripherals
//-----------------------------
//RCC
#define RCC_BASE	0x40021000UL
//-----------------------------
//Base addresses for APB2 BUS Peripherals
//-----------------------------
//GPIO
//A,B fully included in LQFP48 package
#define GPIOA_BASE	0x40010800UL
#define GPIOB_BASE	0x40010C00UL
//C,D partially included in LQFP48 package
#define GPIOC_BASE	0x40011000UL
#define GPIOD_BASE	0x40011400UL
//E NOT included in LQFP48 package
#define GPIOE_BASE	0x40011800UL

//EXTI
#define EXTI_BASE	0x40010400UL
//AFIO
#define AFIO_BASE	0x40010000UL
//====================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED;
	volatile uint32_t MAPR2;
}AFIO_TypeDef;
//========================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:GPIO
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef*)GPIOE_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:RCC
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC ((RCC_TypeDef*)RCC_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:AFIO
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO ((AFIO_TypeDef*)AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:EXTI
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI ((EXTI_TypeDef*)EXTI_BASE)


//========================================================
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA_CLCK_EN() (RCC->APB2ENR |=1<<2)
#define GPIOB_CLCK_EN() (RCC->APB2ENR |=1<<3)
#define GPIOC_CLCK_EN() (RCC->APB2ENR |=1<<4)
#define GPIOD_CLCK_EN() (RCC->APB2ENR |=1<<5)
#define GPIOE_CLCK_EN() (RCC->APB2ENR |=1<<6)
//AFIO
#define RCC_AFIO_CLK_EN() (RCC->AP2ENR |= 1<<0)

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*


#endif /* INC_STM32F103X6_H_ */
