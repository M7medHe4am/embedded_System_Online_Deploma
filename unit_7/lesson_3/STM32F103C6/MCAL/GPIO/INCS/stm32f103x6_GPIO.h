/*
 * STM32F103Cx.h
 *
 *  Created on: Aug 26, 2024
 *      Author: m7med
 */

#ifndef GPIO_INCS_STM32F103X6_GPIO_H_
#define GPIO_INCS_STM32F103X6_GPIO_H_


/*---------------------Includes---------------------*/

#include "../../INCS/stm32f103x6.h"

/*--------------------------------------------------*/

/*---------------------GPIOConfigs---------------------*/
typedef struct
{

	volatile uint8_t GPIO_PinNumber ;		// specifies the GPIO pins to be configured
	                                        //This parameter must be a value of @ref GPIO_PINS_define

	volatile uint8_t GPIO_Mode ;			// specifies the GPIO MODE to be configured
											//This parameter must be a value of @ref GPIO_MODE_define`

	volatile uint8_t GPIO_Speed ;			//specifies the speed of the selected pins
											//This parameter must be set based on @ref GPIO_SPEED_define


}GPIO_PinConfig_t;





//@ref GPIO_PINS_define
#define GPIO_PIN_0	  0
#define GPIO_PIN_1	  4
#define GPIO_PIN_2	  8
#define GPIO_PIN_3	  12
#define GPIO_PIN_4	  16
#define GPIO_PIN_5	  20
#define GPIO_PIN_6	  24
#define GPIO_PIN_7	  28
#define GPIO_PIN_8	  32
#define GPIO_PIN_9	  36
#define GPIO_PIN_10	  40
#define GPIO_PIN_11	  44
#define GPIO_PIN_12	  48
#define GPIO_PIN_13	  52
#define GPIO_PIN_14	  56
#define GPIO_PIN_15	  60








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
#define GPIO_MODE_IN_Analog 0b0000
//input modes
#define GPIO_MODE_IN_FLO  	0b0100
#define GPIO_MODE_IN_PU   	0b1000
#define GPIO_MODE_IN_PD	  	0b1000
//output modes
#define GPIO_MODE_OUT_PP    0b0000
#define GPIO_MODE_OUT_OD    0b0100
#define GPIO_MODE_OUT_AF_PP	0b1000
#define GPIO_MODE_OUT_AF_OD	0b1100

//@ref GPIO_SPEED_define
//0: Input mode (reset state)
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.

#define GPIO_SPEED_10M		0b01
#define GPIO_SPEED_2M		0b10
#define GPIO_SPEED_50M		0b11










//* ===============================================
//* APIs Supported by "MCAL GPIO DRIVER"
//* ===============================================
void MCAL_GPIO_init(GPIO_TypeDef_t* GPIOx ,GPIO_PinConfig_t* PinConfig);
uint8_t MCAL_GPIO_ReadPIN(GPIO_TypeDef_t* GPIOx , uint8_t PinNumber);
uint16_t MCAL_GPIO_ReadPORT(GPIO_TypeDef_t* GPIOx);
void MCAL_GPIO_WritePIN(GPIO_TypeDef_t* GPIOx ,uint8_t PinNumber , uint8_t value);
void MCAL_GPIO_WritePORT(GPIO_TypeDef_t* GPIOx , uint16_t value);
void MCAL_GPIO_TogglePIN(GPIO_TypeDef_t* GPIOx , uint8_t PinNumber);
/*--------------------------------------------------*/

#endif /* GPIO_INCS_STM32F103X6_GPIO_H_ */
