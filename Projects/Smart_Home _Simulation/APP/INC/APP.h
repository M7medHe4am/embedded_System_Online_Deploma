/*
 * APP.h
 *
 *  Created on: Feb 5, 2024
 *      Author: m7med
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "stm32f103x6.h"
#include "Stm32F103C6_GPIO_Driver.h"
#include "lcd.h"
#include "keypad.h"
#include "LED_CNFG.h"
#define LED1 GPIO_PIN_13
#define LED2 GPIO_PIN_14
#define LED3 GPIO_PIN_10
#define LED4 GPIO_PIN_11
#define LED5 GPIO_PIN_12
#define LED6 GPIO_PIN_13
#define LED7 GPIO_PIN_14
#define LED8 GPIO_PIN_15





void changeStatus(uint8_t);
void Pin_call(uint8_t pinRead);
void GPIO_CNFG(void);
void HAL_init(void);
void clock_init(void);






#endif /* INC_APP_H_ */
