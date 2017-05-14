/*
 * PSD.c
 *
 * Created: 09/12/2012 01:45:50 م
 *  Author: pc5
 */ 
/*************************************************************************
	HBE - RoboCAR PSD control example

	Operation:
		If on the front of RoboCAR the obstacle is within 20cm, lights LED.
	
	Source explanation(PSD.c) :
		1)	look-up-table(LUT) of PSD Sensor value.

		2)	PSD sensors are connected in 0 pin of port F.
			
		3)	AD converter value and LUT compares.

		4)	Uses a formality and calculates a distance, and stores the value in dist.
		
		5)	If on the front of RoboCAR the obstacle is within 20cm, lights LED.

	

*************************************************************************/
#include "PSD.h"


int GetDistancePSD()
{	
	u16 Dist=0;
	u08 i,j;
	u16 tmp_val;
	u08 tmp_cm;
	u08 tmp;
	Dist = ADC_Convert(0x00);		

	for(i=0,j=0;i<15;i++){
		if(Dist<PSD_val[i])
			j=i;
		else
			break;		
	}				
				
	tmp_cm = PSD_cm[i]-PSD_cm[j];
	tmp_val = PSD_val[j]-PSD_val[i];
		
	tmp = tmp_val/tmp_cm ;
	Dist = ((PSD_val[j]-Dist)/tmp)+PSD_cm[j];
		
	return Dist;
}

