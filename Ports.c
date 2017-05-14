/*
 * Ports.c
 *
 * Created: 6/15/2013 7:52:29 PM
 *  Author: Muhammad Aly
 */ 
#include "avr/io.h"

void Initialize_Ports()
{
	DDRA = 0x0F; 
	PORTA = 0x00;
	
	DDRB = 0xFF;
	PORTB = 0x00;
		
	DDRC = 0x00; 
	PORTC =0x00; 
	
	DDRE	|=	0x1C; 
	PORTE	|=	0x18;
		
	DDRD	|=	0xc0; 
	PORTD	|=	0xc0;

	DDRF	=	0x00;
	PORTF	=	0x00;	
	
	DDRG = 0xff;
	
	// External Interupts.
	EICRA	|=0x2a;  
	EIMSK	|=0x07;   
	EIFR	|=0x07;  
}