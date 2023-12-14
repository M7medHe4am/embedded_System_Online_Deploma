/*
 * utils.h
 *
 * Created: 11/29/2023 6:19:54 AM
 *  Author: m7med
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define setBit(reg,bit) (reg |= (1<<bit))
#define clearBit(reg,bit) (reg &= ~(1<<bit))
#define readBit(reg,bit) ((reg & (1<<bit))>>bit)
//#define readBit(reg,bit) ((reg>>bit)&1)
#define toggleBit(reg,bit) (reg ^= (1<<bit))

#endif /* UTILS_H_ */