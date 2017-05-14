
#include "PIDControl.h"

u16 PID_get_left_Encoder_count()
{
	return Left_cnt;
}
u16 PID_get_Right_Encoder_count()
{
	return Right_cnt;
}
void PID_init()
{
	Initialize_Timer1();
	Initialize_Timer0();
	Left_cnt = 0;
	Right_cnt = 0; 
 
	past_Right_cnt = 0;
	past_Left_cnt = 0;

	R_flag = HIGH;
    L_flag = HIGH;

	pwm_value_R = 0;
	pwm_value_L = 0;
	pwm_value_O = 0;
}

void PID_stop()
{
	Stop_Timer1();
	Stop_Timer0();
}

void Count_Pulse(){
	
	// Right Motor
	if(is_Right_Encoder_HIGH()){
		if(R_flag == HIGH){
			Right_cnt++;
			R_flag = LOW;
		}
	}
	else{
		R_flag = HIGH;
	}
	
	// Left Motor
	if(is_Left_Encoder_HIGH()){
		if(L_flag == HIGH){
			Left_cnt++;
			L_flag = LOW;
		}
	}
	else{
		L_flag = HIGH;
	}
}

void Change_Speed(){
	
	static s16 R_pre_err = 0;
	static s16 R_cur_err = 0;
	static u16 R_cur_cnt = 0;
	static s16 R_dt_err = 0;
	static s16 R_err_sum = 0;
	
	static s16 L_pre_err = 0;
	static s16 L_cur_err = 0;
	static u16 L_cur_cnt = 0;
	static s16 L_dt_err = 0;
	static s16 L_err_sum = 0;
	
	R_pre_err = R_cur_err;
	R_cur_cnt = Right_cnt - past_Right_cnt;
	past_Right_cnt = Right_cnt;
	R_cur_err = RPM_value - R_cur_cnt;
	R_err_sum += R_cur_err;
	R_dt_err = R_cur_err - R_pre_err; 
	
	pwm_value_R += (R_cur_err * kp_R)+(R_err_sum * ki_R)+(R_dt_err* kd_R);
	
	if(pwm_value_R > 0x03FF)pwm_value_R = 0x03FF;
	if(pwm_value_R < 0)pwm_value_R = 0;
	
	L_pre_err       = L_cur_err;
	L_cur_cnt       = Left_cnt - past_Left_cnt;
	past_Left_cnt   = Left_cnt;
	L_cur_err       = RPM_value - L_cur_cnt;
	L_err_sum       += L_cur_err;
	L_dt_err        = L_cur_err - L_pre_err; 
	
	pwm_value_L     += (L_cur_err * kp_L)+(L_err_sum * ki_L)+(L_dt_err*kd_L);
	
	if(pwm_value_L > 0x03FF)pwm_value_L = 0x03FF;
	if(pwm_value_L < 0)pwm_value_L = 0;
	
	pwm_value_O = (pwm_value_R + pwm_value_L)/2;
	
	Left_PWM(pwm_value_O);
	Right_PWM(pwm_value_O);
}
SIGNAL(SIG_OVERFLOW0)
{
	cli();
	static u16 timer_cnt1 = 0;
	TCNT0 = 0xFF-92;
	Count_Pulse();
	timer_cnt1++;
	if(timer_cnt1 >= 5000){
		timer_cnt1=0;
		Change_Speed();
	}			
	sei();
}