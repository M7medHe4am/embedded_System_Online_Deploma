/*
 * US.h
 *
 *  Created on: Oct 25, 2023
 *      Author: m7med
 */

#ifndef US_H_
#define US_H_
#include "state.h"

extern void(*US_STATE)();
void US_init();
void ST_US_busy();

enum
{
	US_busy
}US_state_id;









#endif /* US_H_ */
