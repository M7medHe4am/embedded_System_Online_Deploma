/*
 * DC.c
 *
 *  Created on: Oct 25, 2023
 *      Author: m7med
 */

#include "DC.h"
int DC_speed = 0;
void (*DC_STATE)();
void DC_init()
{
	//init DC_Drivers

	printf("DC_init\n");

}

void sendSpeed(int s )
{
	DC_speed =s ;
	printf("CA ----- Speed = %d ------> DC\n",DC_speed);
	DC_STATE=ST_DC_busy;


}

void ST_DC_idle()
{
	//state name
	DC_state_id=DC_idle;
	//state action
	//call PWM to make speed = DC_speed
	printf("DC_idle state :  Speed = %d\n",DC_speed);

}

void ST_DC_busy()
{
	DC_state_id=DC_busy;
	DC_STATE=ST_DC_idle;
	printf("DC_busy state :  Speed = %d\n",DC_speed);

}
