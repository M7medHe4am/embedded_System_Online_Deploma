/*
 * LED_CNFG.h
 *
 *  Created on: Feb 24, 2024
 *      Author: m7med
 */

#ifndef INCLUDES_LED_CNFG_H_
#define INCLUDES_LED_CNFG_H_

#include "Stm32F103C6_GPIO_Driver.h"



typedef struct {
	GPIO_TypeDef* port;

	GPIO_PinConfig_t pin;



	uint8_t offStatus ;
	uint8_t status ;
}LED_t;




void LED_init( LED_t * const LED_CNFG);

uint8_t LED_getStatus(const LED_t * const LED_CNFG);

void LED_setStatus( LED_t *const LED_CNFG , uint8_t newStatus);
void LED_toggleStatus( LED_t *const LED_CNFG);


















#endif /* INCLUDES_LED_CNFG_H_ */
