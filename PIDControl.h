/*
 * PIDControl.h
 *
 * Created: 2/6/2013 10:27:23 AM
 *  Author: Muhammad Aly
 */ 
#ifndef PIDCONTROL_H_
#define PIDCONTROL_H_

#include "avr/io.h"
#include "avr/interrupt.h"
#include "avr_lib.h"

#define ONE_ROTATE 650
#define is_Left_Encoder_HIGH() (PINA & 0x40)
#define is_Right_Encoder_HIGH() (PINA & 0x10)


#define  Left_PWM(x) (OCR1B = x)
#define  Right_PWM(x) (OCR1A = x)
#define kp_R 0.5
#define ki_R 0.1
#define kd_R 0.05

#define kp_L 0.5
#define ki_L 0.1
#define kd_L 0.05

#define RPM 110
#define RPM_value ( (u16) (RPM * (ONE_ROTATE/120) ) ) // number of rotations per 0.5 sec



enum{HIGH=1 , LOW=0};

u16 Right_cnt = 0;
u16 Left_cnt = 0;

u16 past_Right_cnt = 0;
u16 past_Left_cnt = 0;

u08 R_flag = HIGH;
u08 L_flag = HIGH;

s16 pwm_value_R = 0;
s16 pwm_value_L = 0;
s16 pwm_value_O = 0;


void PID_init();
void Count_Pulse();
void Change_Speed();
void PID_stop();
u16 PID_get_left_Encoder_count();
u16 PID_get_Right_Encoder_count();

#endif /* PIDCONTROL_H_ */