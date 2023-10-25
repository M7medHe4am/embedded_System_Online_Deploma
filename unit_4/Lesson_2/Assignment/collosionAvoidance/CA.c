/*
 * CA.c
 *
 *  Created on: Oct 25, 2023
 *      Author: m7med
 */

#include "CA.h"

int CA_distance = 0;
int CA_speed = 0 ;
int threshold=50;
//STATE pointer
void (*CA_STATE)();

void sendDistance(int d)
{
	CA_distance =d;
	//eventCheck
	(CA_distance>50)?(CA_STATE=ST_CA_driving):(CA_STATE=ST_CA_waiting);
	printf("US ----- distance = %d ------> CA\n",CA_distance);


}


//Definitions
void ST_CA_waiting()
{
	//state name
	CA_state_id = CA_waiting;
	CA_speed=0;
	sendSpeed(CA_speed);
	printf("CA_waiting State distance = %d , Speed = %d \n",CA_distance,CA_speed);
}
void ST_CA_driving()
{
	//state name
	CA_state_id = CA_driving;
		CA_speed=30;
		sendSpeed(CA_speed);
		printf("CA_waiting State distance = %d , Speed = %d \n",CA_distance,CA_speed);

}
