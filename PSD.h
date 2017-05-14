/*
 * PSD.h
 *
 * Created: 09/12/2012 03:46:29 م
 *  Author: pc5
 */ 


#ifndef PSD_H_
#define PSD_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr_lib.h"

//	1)
u16 PSD_val[15]={ 954, 745, 512, 397, 331, 283, 255, 224, 200, 188, 171, 164, 151, 116, 110};
u08 PSD_cm[]=   { 5  , 10 , 15 , 20 , 25 , 30 , 35 , 45 , 50 , 55 , 60 , 65 , 70 , 75 , 80 };
	
int GetDistancePSD();



#endif /* PSD_H_ */