/*
 * DC.h
 *
 *  Created on: Oct 25, 2023
 *      Author: m7med
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"

enum
{
	DC_idle,
	DC_busy

}DC_state_id;


extern void (*DC_STATE)();

void DC_init();
void ST_DC_idle();
void ST_DC_busy();




#endif /* DC_H_ */
