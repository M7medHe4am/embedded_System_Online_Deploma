/*
 * LED_CNFG.c
 *
 *  Created on: Feb 24, 2024
 *      Author: m7med
 */

#include "LED_CNFG.h"
void LED_init( LED_t * const LED_CNFG)
{

	MCAL_GPIO_Init(LED_CNFG->port,&LED_CNFG->pin);

	MCAL_GPIO_WritePIN(LED_CNFG->port, LED_CNFG->pin.GPIO_PinNumber, LED_CNFG->offStatus);

	LED_CNFG->status = 0;

}

uint8_t LED_getStatus(const LED_t * const LED_CNFG)
{
	return LED_CNFG->status ;


}

void LED_setStatus( LED_t * const LED_CNFG , uint8_t newStatus)
{

	MCAL_GPIO_WritePIN(LED_CNFG->port, LED_CNFG->pin.GPIO_PinNumber, (newStatus != LED_CNFG->offStatus)) ;
	LED_CNFG->status = newStatus ;

}

void LED_toggleStatus( LED_t *const LED_CNFG)
{

	MCAL_GPIO_TogglePIN(LED_CNFG->port, LED_CNFG->pin.GPIO_PinNumber);

	LED_CNFG->status = (!LED_CNFG->status);



}






















