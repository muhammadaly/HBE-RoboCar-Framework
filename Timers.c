/*
 * Timers.c
 *
 * Created: 6/15/2013 7:50:07 PM
 *  Author: Muhammad Aly
 */ 
#include "Timers.h"

void Initialize_Timer0()
{
	TCCR0 = 0x02;
	
	TCNT0 = 0xFF-92;
	
	TIMSK |= 0x01;
	TIFR  |= 0x01; 
}
void Stop_Timer0()
{
	TCCR0 &= ~(0xFF);
	TCNT0 = 0x00;
	TIMSK &= ~(0x01);
	TIFR  &= ~(0x01);
}

void Initialize_Timer1()
{
	TCCR1A = 0xA3; // COMA = 10 COMB = 10 WaveGenrationMode = 0011 COMC = 00
	TCCR1B = 0x02; // CS = 010
	TCCR1C = 0x00;
	
	TCNT1 = 0x0000;
	
	OCR1A =  0x0000;
	OCR1B =  0x0000;
}
void Stop_Timer1()
{
	TCCR1A &= ~(0xFF);
	TCCR1B &= ~(0xFF);
	TCCR1C &= 0x00;
	
	TCNT1 = 0x0000;
	OCR1A =  0x0000;
	OCR1B =  0x0000;
}

void Initialize_Timer2()
{
	TCCR2	=	0x02;	
	TCNT2	=	0xff - 10;		
	TIMSK	|=	(1 << TOIE2);	
	TIFR	|=	(1 << TOV2);

}
void Stop_Timer2()
{
	TCCR2   &=  ~(0xFF);	
	TCNT2	=	0x00;	
	TIMSK	&=	~(1 << TOIE2);	
	TIFR	&=	~(1 << TOV2);
}