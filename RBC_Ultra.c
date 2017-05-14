#include"RBC_Ultra.h"

u08 US_flag_F=SEND;
u08 US_flag_B=SEND;

u08 US_F_cnt=0;
u08 US_F_c10=0;
u08 US_F_c100=0;
u08 US_F_c1000=0;

u08 US_B_cnt=0;
u08 US_B_c10=0;
u08 US_B_c100=0;
u08 US_B_c1000=0;

u16 US_F_Data = 0;
u16 US_B_Data = 0;

u16 US_F_tmp = 0;
u16 US_B_tmp = 0;

void Initialize_US()
{
	Initialize_Timer2();
}


SIGNAL(SIG_OVERFLOW2) 
{
  
	cli();

  TCNT2	=	0xff - 10;	 //10us
	
	if(US_flag_F==CNT){
		US_F_cnt++;	
		if(US_F_cnt==10){
			US_F_c10++;
			US_F_cnt=0;
		}

		if(US_F_c10==10){
			US_F_c100++;
			US_F_c10=0;
		}

		if(US_F_c100==10){
			US_F_c1000++;
			US_F_c100=0;
		}

		if(US_F_c1000>=9){
		
			US_F_cnt=US_F_c10=US_F_c100=US_F_c1000=0;
		}				

	} //end if
	else {
		US_F_cnt=US_F_c10=0,US_F_c100=0,US_F_c1000=0;
	
	}
	
	if(US_flag_B==CNT){
		US_B_cnt++;	
		if(US_B_cnt==10){
			US_B_c10++;
			US_B_cnt=0;
		}

		if(US_B_c10==10){
			US_B_c100++;US_B_c10=0;
		}

		if(US_B_c100==10){
			US_B_c1000++;US_B_c100=0;
		}

		if(US_B_c1000>=9){		
			US_B_cnt=US_B_c10=0,US_B_c100=0,US_B_c1000=0;
		}				

	} 
	else {
		US_B_cnt=US_B_c10=0,US_B_c100=0,US_B_c1000=0;
	}
	sei();
}


SIGNAL(SIG_INTERRUPT0)
{
	cli();
	static u08 my_cnt = 0;

	if(US_flag_F==CNT){
		my_cnt++;
		if(my_cnt>20){
			US_F_Data = ((US_F_c1000*1000)+ (US_F_c100*100)+(US_F_c10*10)+US_F_cnt);
		
            // 03689 = (10.85 * 34000) / 1000000 ;
			// 6.8   = (200   * 34 )   / 1000000 ; 
			US_F_Data = (u16)((US_F_Data*0.3689)+6.8);		
			US_F_Data /=2;

			US_F_tmp = US_F_Data;
			US_flag_F=RECV;
		
			my_cnt = 0;			
		}
}
	sei();
}


SIGNAL(SIG_INTERRUPT1){
	cli();
	static u08 my_cnt = 0;

	if(US_flag_B==CNT){
		my_cnt++;
		if(my_cnt>20){
			US_B_Data = ((US_B_c1000*1000)+ (US_B_c100*100)+(US_B_c10*10)+US_B_cnt);
			/*US_B_Data/=3;
			US_B_Data=US_B_Data-(US_B_Data/5);*/
			US_B_Data = (u16)((US_B_Data*0.3689)+6.8);		
			US_B_Data /=2;

			US_B_tmp = US_B_Data;
			US_flag_B=RECV;
			my_cnt = 0;	
			}
		}
	sei();
}


void print_data(u08 mode){

	putch_u1('z');
	
	if(mode!=0){		

		putch_u1(( US_F_Data/1000 )+'0');	
		putch_u1(( (US_F_Data/100)%10 )+'0');	
		putch_u1(( (US_F_Data/10)%10 )+'0');	
		putch_u1(( US_F_Data%10 )+'0');	
	}
	else{
		putch_u1('0');	
		putch_u1('0');	
		putch_u1('0');	
		putch_u1('0');	
	}
	US_F_Data=0;
	US_flag_F=RECV;

}

void print_data2(u08 mode){


	putch_u1('x');
	
	if(mode!=0){
		
		
		putch_u1(( US_B_Data/1000 )+'0');	
		putch_u1(( (US_B_Data/100)%10 )+'0');	
		putch_u1(( (US_B_Data/10)%10 )+'0');	
		putch_u1(( US_B_Data%10 )+'0');	
	}

	else{
		putch_u1('0');	
		putch_u1('0');	
		putch_u1('0');	
		putch_u1('0');	
	}
	US_B_Data=0;
	US_flag_B=RECV;
	
}

void ultraSend_F(){
	u08 i;
	
	PORTD	&=	~(0x40);
		
	for(i=0;i<9;i++){
	
		PORTE &= ~0x18;	
		PORTE |=0x08 ;
		
		us_delay(11);
		
		PORTE &= ~0x18;	
		PORTE |=0x10 ;
		
		us_delay(11);	
	}
	PORTD	|=	(0x40);
	
	US_flag_F=CNT;

	
}


void ultraSend_B(){
	u08 i;	
	
	PORTD	&=	~(0x80);
	for(i=0;i<9;i++){
		PORTE &= ~0x18;	
		PORTE	|=0x08;
		us_delay(11);
		PORTE &= ~0x18;	
		PORTE	|=0x10;
		us_delay(11);	
	}
	PORTD	|=	(0x80);	

	US_flag_B=CNT;	
	
}

u08 US_Fire_F(){
		
		for(int ind = 0 ; ind < 10 ; ind++){
			cli();
				ultraSend_F();						  				
			sei();
			Initialize_Timer2();
			ms_delay(24); // time to receive for 8 m.
			Stop_Timer2();
		
			if(US_flag_F==RECV){
				BEEP_ON();
			ms_delay(500);
			BEEP_OFF();
			ms_delay(500);	
				return US_F_Data;
			 }
		}	
		return 0;
}


u08 US_Fire_B(){
		
		for(int ind = 0 ; ind < 10 ; ind++){
			cli();
				ultraSend_B();						  				
			sei();
					
			ms_delay(24); // time to receive for 8 m.
		
			if(US_flag_B==RECV){

				return US_B_Data;
			 }
		}		
		return 0;
}
