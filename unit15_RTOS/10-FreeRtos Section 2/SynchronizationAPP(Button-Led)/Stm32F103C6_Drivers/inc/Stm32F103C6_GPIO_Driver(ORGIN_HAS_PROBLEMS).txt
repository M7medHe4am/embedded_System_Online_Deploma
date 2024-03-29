/*
 * Stm32F103C6_GPIO_Driver.h
 *
 *  Created on: Dec 9, 2023
 *      Author: m7med
 */

#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_
//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct{
	uint16_t GPIO_PinNumber; // specifies the GPIO pins to be configured
							 //This parameter must be a value of @ref GPIO_PINS_define

	uint8_t	GPIO_Mode;	// specifies the GPIO MODE to be configured
						//This parameter must be a value of @ref GPIO_MODE_define


	uint8_t GPIO_Output_Speed;//specifies the speed of the selected pins
							  //This parameter must be set based on @ref GPIO_SPEED_define


}GPIO_PinConfig_t;

//=====================GLOBAL VARIABLES=============================

//GPIO_PinConfig_t pinCnfg;
//=========================================================================================



//-----------------------------
//Macros Configuration References
//-----------------------------
//@ref GPIO_PINS_define
#define GPIO_PIN_0	  (0)
#define GPIO_PIN_1	  (1)
#define GPIO_PIN_2	  (2)
#define GPIO_PIN_3	  (3)
#define GPIO_PIN_4	  (4)
#define GPIO_PIN_5	  (5)
#define GPIO_PIN_6	  (6)
#define GPIO_PIN_7	  (7)
#define GPIO_PIN_8	  (8)
#define GPIO_PIN_9	  (9)
#define GPIO_PIN_10	  (10)
#define GPIO_PIN_11	  (11)
#define GPIO_PIN_12	  (12)
#define GPIO_PIN_13	  (13)
#define GPIO_PIN_14	  (14)
#define GPIO_PIN_15	  (15)
#define GPIO_PIN_ALL  (uint16_t)0xFFFF

//@ref GPIO_MODE_define
/*In input mode (MODE[1:0]=00):
0: Analog mode
1: Floating input (reset state)
2: Input with pull-up
3: Input with pull-down
In output mode (MODE[1:0] > 00):
4: General purpose output push-pull
5: General purpose output Open-drain
6: Alternate function output Push-pull
7: Alternate function output Open-drain
8: Alternate function input
*/
//analoge mode
#define GPIO_MODE_Analog   		(0)
//input modes
#define GPIO_MODE_FLO_IN		(1)
#define GPIO_MODE_IN_PU			(2)
#define GPIO_MODE_IN_PD			(3)
//output modes
#define GPIO_MODE_OUT_PP		(4)
#define GPIO_MODE_OUT_OD		(5)
#define GPIO_MODE_AF_OUT_PP		(6)
#define GPIO_MODE_AF_OUT_OD		(7)
//AF_INPUT
#define GPIO_MODE_AF_IN 		(8)


//@ref GPIO_SPEED_define
//0: Input mode (reset state)
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.

#define GPIO_SPEED_10M	0b01
#define GPIO_SPEED_2M	0b10
#define GPIO_SPEED_50M	0b11
//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled			(1)
#define GPIO_RETURN_LOCK_ERROR				(0)






//* ===============================================
//* APIs Supported by "MCAL GPIO DRIVER"
//* ===============================================
//SET/RESET
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *pinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);
//READ
uint8_t MCAL_GPIO_ReadPIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber);
uint16_t MCAL_GPIO_ReadPORT(GPIO_TypeDef *GPIOx);
//Write
void MCAL_GPIO_WritePIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber,uint8_t value);
void MCAL_GPIO_WritePORT(GPIO_TypeDef *GPIOx,uint16_t value);
//TOGGLE
void MCAL_GPIO_TogglePIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber);
//LOCK
uint8_t MCAL_GPIO_LockPIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber);
#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */
