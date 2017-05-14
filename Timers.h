/*
 * Timers.h
 *
 * Created: 6/15/2013 7:51:03 PM
 *  Author: Muhammad Aly
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include "avr/io.h"

void Initialize_Timer0();
void Stop_Timer0();

void Initialize_Timer1();
void Stop_Timer1();

void Initialize_Timer2();
void Stop_Timer2();


#endif /* TIMERS_H_ */