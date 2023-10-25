/*
 * CA.h
 *
 *  Created on: Oct 25, 2023
 *      Author: m7med
 */

#ifndef CA_H_
#define CA_H_
#include "state.h"
//STATE pointer
extern void (*CA_STATE)();


//defining states
enum
{
	CA_waiting,
	CA_driving
}CA_state_id;
//declare state functions
void ST_CA_waiting();
void ST_CA_driving();



#endif /* CA_H_ */
