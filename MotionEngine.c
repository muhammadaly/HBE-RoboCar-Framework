/*
 * MotionEngine.c
 *
 * Created: 3/14/2013 3:07:13 PM
 *  Author: Muhammad Aly
 */ 
#include "MotionEngine.h"


const double WheelRaduis = 42;
const double RoboCar_semidiometer =116;

void goForward(double distance) // number of steps . step = blata in robotics lap.
{
    double RPMeter    = ((distance*1000)/(2*3.14*WheelRaduis)); // number of Rotations per meter.
    u16 ETPMeter      =  (u16)RPMeter*650 ;// number of encoder ticks per meter.
	u16 current_Right_cnt=0 , current_Left_cnt=0;
	u08 m_psd_distance;
	PID_init();
	PORTA = FORWARD;
	while (current_Right_cnt < ETPMeter && current_Left_cnt < ETPMeter)	{
		m_psd_distance = GetDistancePSD();
		if(m_psd_distance < OBSTICAL_DETECTION_DISTANCE && m_psd_distance>0)
		{
			EIFR &= ~(0x04);
			break;
		}
		current_Left_cnt = PID_get_left_Encoder_count();
		current_Right_cnt = PID_get_Right_Encoder_count();
	}
	//PID_stop();
	PORTA = STOP;
}

void goBackward(double distance)
{
    double RPMeter = ((distance*1000)/(2*3.14*WheelRaduis)); // number of Rotations per meter.
    u16 ETPMeter =  (u16)RPMeter*650 ;// number of encoder ticks per meter
	u16 current_Right_cnt=0 , current_Left_cnt=0;
	PID_init();
	PORTA = BACKWARD;
	while (current_Right_cnt < ETPMeter && current_Left_cnt < ETPMeter){
		current_Left_cnt = PID_get_left_Encoder_count();
		current_Right_cnt = PID_get_Right_Encoder_count();
	}
	//PID_stop();
	PORTA = STOP;
}

void turnLeft(double angle)
{
	double RoboCar_cercumfrence = 2*3.14*RoboCar_semidiometer;
    double distance_of_wheel = (650/(2*3.14*WheelRaduis)); // number of Rotations per meter.
    u16 ETPMeter =  (u16)(distance_of_wheel*RoboCar_cercumfrence*(angle/360));// number of encoder ticks per meter
	u16 current_Right_cnt=0 , current_Left_cnt=0;
	PID_init();
	PORTA = LEFT_TurnArround;
	while (current_Right_cnt < ETPMeter && current_Left_cnt < ETPMeter){
		current_Left_cnt = PID_get_left_Encoder_count();
		current_Right_cnt = PID_get_Right_Encoder_count();
	}
	//PID_stop();
	PORTA = STOP;
}

void turnRight(double angle)
{
	double RoboCar_cercumfrence = 2*3.14*RoboCar_semidiometer;
    double distance_of_wheel = (650/(2*3.14*WheelRaduis)); // number of Rotations per meter.
    u16 ETPMeter =  (u16)(distance_of_wheel*RoboCar_cercumfrence*(angle/360));// number of encoder ticks per meter
	u16 current_Right_cnt=0 , current_Left_cnt=0;
	PID_init();
	PORTA = RIGHT_TurnArround;
	while (current_Right_cnt < ETPMeter && current_Left_cnt < ETPMeter){
		current_Left_cnt = PID_get_left_Encoder_count();
		current_Right_cnt = PID_get_Right_Encoder_count();
	}
	//PID_stop();
	PORTA = STOP;
}
SIGNAL(SIG_INTERRUPT2)
{
	cli();
	PORTA = STOP;
	sei();
}