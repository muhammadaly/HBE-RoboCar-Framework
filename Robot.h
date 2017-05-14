/*
 * Robot.h
 *
 * Created: 6/15/2013 7:41:31 PM
 *  Author: Muhammad Aly
 */ 

#include "avr/io.h"
#include "avr/interrupt.h"
#include "avr_lib.h"
#include "Timers.h"
#include "MotionEngine.h"
#include "RBC_Ultra.h"
#include "UART.h"

#ifndef ROBOT_H_
#define ROBOT_H_


#define    Exploration_Rotation_Angle           45
#define    Path_Rotation_Angle           90
#define    Maximum_distance         40
#define    Minimum_distance         10
		   				         
#define    OCCUPIED                 2
#define    UNKNOWN                  1
#define    OPEN                     0

#define LOCAL_GRID_WIDTH              5
#define LOCAL_GRID_HEIGHT             5

#define F_LED	0x04 
#define B_LED 0x08

#define F_LED_ON()	(PORTB |= F_LED)
#define F_LED_OFF()	(PORTB &= ~F_LED)

#define B_LED_ON()	(PORTB |= B_LED)
#define B_LED_OFF()	(PORTB &= ~B_LED)


#define BEEP_ON()	(PORTE |= 0x04)
#define BEEP_OFF()	(PORTE &= ~0x04)

static u08 m_positionX=0,m_positionY=0;

void Initialize_Me();
void explore_local_area   (u08* LocalGrid);
u08* Initialize_Local_Grid(u08 p_widthOfLocalGrid , u08 p_heightOfLocalGrid);
void Execute_Path(u08* Path , u16 Length);

#endif /* ROBOT_H_ */