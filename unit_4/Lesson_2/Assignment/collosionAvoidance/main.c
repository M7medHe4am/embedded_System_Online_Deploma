/*
 * main.c
 *
 *  Created on: Oct 25, 2023
 *      Author: m7med
 */
#include "US.h"
#include "CA.h"
#include "DC.h"
void setup()
{

	
	//initializing.....
	US_init();
	DC_init();
	//init STATE pointers 
	US_STATE=ST_US_busy;
	CA_STATE=ST_CA_waiting;
	DC_STATE=ST_DC_idle;

}

int main()
{
	volatile int d ;
	setup();
	while (1)
	{
		//call state for each block
		US_STATE();
		CA_STATE();
		DC_STATE();

		for(d=0;d<1000;d++);//delay

	}






	return 0 ;
}
