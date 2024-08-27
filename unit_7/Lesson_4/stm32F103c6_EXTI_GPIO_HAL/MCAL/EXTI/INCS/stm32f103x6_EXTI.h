/*
 * stm32f103x6_EXTI.h
 *
 *  Created on: Aug 27, 2024
 *      Author: m7med
 */

#ifndef EXTI_INCS_STM32F103X6_EXTI_H_
#define EXTI_INCS_STM32F103X6_EXTI_H_

/*---------------------Includes---------------------*/

#include "../../INCS/stm32f103x6.h"
#include "../../GPIO/INCS/stm32f103x6_GPIO.h"
/*--------------------------------------------------*/

//NOTE
//USER MUST ENABLE CLOCK FOR GPIO , AFIO used using APIS from  the device header file


//Configuration structure

typedef struct
{
	volatile uint8_t EXTI_Line ;
//	volatile uint8_t* EXTI_PORT ;
	volatile uint8_t EXTI_Direction ;
	volatile uint8_t EXTI_Speed ;
	volatile uint8_t EXTI_Mode ;
	volatile uint8_t EXTI_Edge ;
	void(*P_CallBack)(void) ;

}EXTI_PinConfig_t;


typedef enum
{
	Enable ,
	Disable

}NVIC_status_t;


//CONFIG GPIO
//CONFIG AFIO
//Config EXTI
//Config NVIC

#define EXTI0			GPIO_PIN_0
#define EXTI1			GPIO_PIN_1
#define EXTI2			GPIO_PIN_2
#define EXTI3			GPIO_PIN_3
#define EXTI4			GPIO_PIN_4
#define EXTI5			GPIO_PIN_5
#define EXTI6			GPIO_PIN_6
#define EXTI7			GPIO_PIN_7
#define EXTI8			GPIO_PIN_8
#define EXTI9			GPIO_PIN_9
#define EXTI10			GPIO_PIN_10
#define EXTI11			GPIO_PIN_11
#define EXTI12			GPIO_PIN_12
#define EXTI13			GPIO_PIN_13
#define EXTI14			GPIO_PIN_14
#define EXTI15			GPIO_PIN_15





//input modes
#define EXTI_MODE_IN_FLO GPIO_MODE_IN_FLO

//output modes
#define EXTI_MODE_OUT_AF_PP GPIO_MODE_OUT_AF_PP
#define EXTI_MODE_OUT_AF_OD GPIO_MODE_OUT_AF_OD


#define EXTI_Direction_INPUT	INPUT
#define EXTI_Direction_OUTPUT	OUTPUT


#define EXTI_SPEED_10M GPIO_SPEED_10M
#define EXTI_SPEED_2M GPIO_SPEED_2M
#define EXTI_SPEED_50M GPIO_SPEED_50M


#define EXTI_RISING			0
#define EXTI_FALLING		1
#define EXTI_RI_FA			2









void MCAL_EXTI_init(EXTI_PinConfig_t* EXTIx,GPIO_TypeDef_t* GPIOx);
void MCAL_EXTI_Deinit(uint8_t EXTIx,GPIO_TypeDef_t* GPIOx);


















#endif /* EXTI_INCS_STM32F103X6_EXTI_H_ */
