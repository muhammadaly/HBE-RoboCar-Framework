/*
 * MotionEngine.h
 *
 * Created: 3/14/2013 3:36:37 PM
 *  Author: Muhammad Aly
 */ 


#ifndef MOTIONENGINE_H_
#define MOTIONENGINE_H_
#include "avr_lib.h"
#include "Robot.h"
#include "RBC_Ultra.h"

#define FORWARD	0x06	
#define BACKWARD	0x09	
#define LEFT_Turn	0x02	
#define RIGHT_Turn	0x04	
#define STOP    0x00	
#define LEFT_TurnArround	0x0A	
#define RIGHT_TurnArround	0x05	
#define RIGHT_Back_Turn	0x08	
#define LEFT_Back_Turn	0x01	
#define OBSTICAL_DETECTION_DISTANCE 50



void goForward(double distance);
void goBackward(double distance);
void turnLeft(double angle);
void turnRight(double angle);
SIGNAL(SIG_INTERRUPT2);


#endif /* MOTIONENGINE_H_ */