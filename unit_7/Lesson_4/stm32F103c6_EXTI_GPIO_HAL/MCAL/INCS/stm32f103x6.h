/*
 * STM32F103Cx_Header.h
 *
 *  Created on: Aug 26, 2024
 *      Author: m7med
 */

#ifndef INCS_STM32F103X6_H_
#define INCS_STM32F103X6_H_



/*---------------------Includes---------------------*/
#include "stdint.h"
#include "stdlib.h"


/*--------------------------------------------------*/
/*---------------------Base addresses for Memories---------------------*/
#define SRAM_MEM_BASE    0x20000000UL
#define FLASH_MEM_BASE   0x08000000UL
#define PERIPHERALS_BASE 0x40000000UL
#define CORTEXM3_BASE    0xE0000000UL


/*---------------------------------------------------------------------*/
/*------------------Base addresses for BUS Peripherals-----------------*/
#define NVIC_BASE   0xE000E100UL

#define RCC_BASE    0x40021000UL

#define GPIOA_BASE  0x40010800UL
#define GPIOB_BASE  0x40010C00UL
#define GPIOC_BASE  0x40011000UL
#define GPIOD_BASE	0x40011400UL

#define AFIO_BASE   0x40010000UL

#define EXTI_BASE   0x40010400UL

#define USART1_BASE 0x40013800UL
#define USART2_BASE	0x40004400UL
#define USART3_BASE	0x40004800UL



#define SPI1_BASE   0x40013000UL
#define SPI2_BASE	0x40003800UL


#define I2C1_BASE   0x40005400UL
#define I2C2_BASE 	0x40005800UL





/*---------------------------------------------------------------------*/
/*------------------Peripheral register-----------------*/

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral:RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
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

}RCC_TypeDef_t;


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral:GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL  ;
	volatile uint32_t CRH  ;
	volatile uint32_t IDR  ;
	volatile uint32_t ODR  ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR  ;
	volatile uint32_t LCKR ;

}GPIO_TypeDef_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral:AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED;
	volatile uint32_t MAPR2;
}AFIO_TypeDef_t;



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral:EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t IMR ;
	volatile uint32_t EMR ;
	volatile uint32_t RTSR ;
	volatile uint32_t FTSR ;
	volatile uint32_t SWIER ;
	volatile uint32_t PR ;
}EXTI_TypeDef_t;











/*------------------------------------------------------*/
/*------------------Peripheral Instants-----------------*/
//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral:NVIC
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_ISER0 *((volatile uint32_t*)(NVIC_BASE+0x000))


#define NVIC_ISER1 *((volatile uint32_t*)(NVIC_BASE+0x004))
#define NVIC_ISER2 *((volatile uint32_t*)(NVIC_BASE+0x008))

#define NVIC_ICER0 *((volatile uint32_t*)(NVIC_BASE+0x080))
#define NVIC_ICER1 *((volatile uint32_t*)(NVIC_BASE+0x084))
#define NVIC_ICER2 *((volatile uint32_t*)(NVIC_BASE+0x088))



//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral:RCC
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC ((RCC_TypeDef_t*)RCC_BASE)


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral:GPIO
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA ((GPIO_TypeDef_t*)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef_t*)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef_t*)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef_t*)GPIOD_BASE)



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:AFIO
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO ((AFIO_TypeDef_t*)AFIO_BASE)



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:EXTI
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI ((EXTI_TypeDef_t*)EXTI_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:USART
//-*-*-*-*-*-*-*-*-*-*-*
#define USART1 ((USART_TypeDef_t*)USART1_BASE)
#define USART2 ((USART_TypeDef_t*)USART2_BASE)
#define USART3 ((USART_TypeDef_t*)USART3_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:SPI
//-*-*-*-*-*-*-*-*-*-*-*
#define SPI1 ((SPI_TypeDef_t*)SPI1_BASE)
#define SPI2 ((SPI_TypeDef_t*)SPI2_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:I2C
//-*-*-*-*-*-*-*-*-*-*-*
#define I2C1 ((I2C_TypeDef_t*)I2C1_BASE)
#define I2C2 ((I2C_TypeDef_t*)I2C2_BASE)


/*------------------------------------------------------*/
/*------------------clock Configuration  Macros-----------------*/

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral:GPIO
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA_CLCK_EN() (RCC->APB2ENR |=1<<2)
#define GPIOB_CLCK_EN() (RCC->APB2ENR |=1<<3)
#define GPIOC_CLCK_EN() (RCC->APB2ENR |=1<<4)
#define GPIOD_CLCK_EN() (RCC->APB2ENR |=1<<5)

//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA_CLCK_RESET() (RCC->APB2RSTR|=1<<2)
#define GPIOB_CLCK_RESET() (RCC->APB2RSTR |=1<<3)
#define GPIOC_CLCK_RESET() (RCC->APB2RSTR |=1<<4)
#define GPIOD_CLCK_RESET() (RCC->APB2RSTR |=1<<5)



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

#define AFIO_CLCK_EN() (RCC->APB2ENR |=1<<0)


//-*-*-*-*-*-*-*-*-*-*-*

#define AFIO_CLCK_RESET() (RCC->APB2RSTR|=1<<0)



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

//NO CLCK CONTROL >> ENABLED BY DEFAULT






/*------------------------------------------------------*/











































#endif /* INCS_STM32F103X6_H_ */
