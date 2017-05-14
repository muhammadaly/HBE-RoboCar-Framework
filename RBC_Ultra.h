#ifndef _RBC_ULTRA_
#define _RBC_ULTRA_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr_lib.h"
#include "UART.h"
#include "Robot.h"


enum{SEND,CNT,RECV};




SIGNAL(SIG_OVERFLOW2);

SIGNAL(SIG_INTERRUPT0);

SIGNAL(SIG_INTERRUPT1);

void ultraSend_F();

void ultraSend_B();

u08 US_Fire_F();

u08 US_Fire_B();

#endif
