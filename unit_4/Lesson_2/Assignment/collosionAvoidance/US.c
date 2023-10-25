/*
 * US.c
 *
 *  Created on: Oct 25, 2023
 *      Author: m7med
 */
#include "US.h"


int  getDistance_random(int l , int r , int count);



int US_distance = 0;
void(*US_STATE)();


void US_init()
{
	//init US drivers
	printf("US_init\n");
}





void ST_US_busy()
{
	US_state_id=US_busy;
	US_distance = getDistance_random(45,55,1);
	sendDistance(US_distance);
	US_STATE=ST_US_busy;
}



int  getDistance_random(int l , int r , int count) // l=low r=max(range)
{
	int i;
	for(i=0 ;i<count ; i++)
	{
		int rand_num = (rand() % (r-1+1)) + 1 ;

		return rand_num;

	}

}
