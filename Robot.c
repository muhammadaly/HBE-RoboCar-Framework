/*
 * Robot.c
 *
 * Created: 6/15/2013 7:35:24 PM
 *  Author: Muhammad Aly
 */ 
#include "Robot.h"

void Initialize_Me()
{
	Initialize_Ports();
	Initialize_Local_Grid(LOCAL_GRID_HEIGHT,LOCAL_GRID_WIDTH);	
	Initialize_UART();
}
void change_orientation(u08 steps , u08* Position )
{
	//change orienjtation 
}
void change_Position(u08 steps , u08* Position)
{
	// change x and y.
}
void modify_Orientation(u08 Direction , u08 steps , u08* Position)
{
	switch(Direction)
	{
		case 'F':
			//change
		case 'B':
		case 'L':
		case 'R':
		default:
		break;
	}
} 

u08* Initialize_Local_Grid(u08 p_widthOfLocalGrid , u08 p_heightOfLocalGrid)
{
	u16 sizeOfLocalGrid = p_heightOfLocalGrid*p_widthOfLocalGrid;
	u08* LocalGrid  = (u08*) malloc(sizeOfLocalGrid);
	
	for(int ind = 0 ; ind < sizeOfLocalGrid ; ind ++){
		LocalGrid[ind] = UNKNOWN ;
	}
	return LocalGrid;
}

void explore_local_area(u08* LocalGrid)
{
	u08 m_distance_PSD ,m_distance_US;
	for(int step = 0 ; step <8 ; step ++)
	{
		turnRight(Exploration_Rotation_Angle-step);
		ms_delay(600);
		
		m_distance_PSD = GetDistancePSD();
		if(m_distance_PSD < Maximum_distance && m_distance_PSD > Minimum_distance){
			LocalGrid[step] = OCCUPIED ;
			F_LED_ON();
			ms_delay(300);
			F_LED_OFF();
		}
		else{
			LocalGrid[step] = OPEN ;
		}
	}
	//Stop_Timer2();	
}
void Execute_Path(u08* path , u16 Length)
{
	unsigned char Direction ;
	double distance = 0.3 ,steps;
	
	for(int i = 0 ; i < Length ; i+=2){
		
		steps = path[i];
		Direction = path[i+1] ;
		
		if(Direction == 'F'){
			goForward(steps*distance);
			ms_delay(300);
		}
		else if(Direction == 'B'){
			goBackward(steps*distance);
			ms_delay(300);
		}
		else if(Direction == 'L'){
			for(int k = 0 ; k < steps ; k++){
				turnLeft(Path_Rotation_Angle);
				ms_delay(300);
			}
		}
		else if(Direction == 'R'){
			for(int k = 0 ; k < steps ; k++){
				turnRight(Path_Rotation_Angle);
				ms_delay(300);
			}
		}	
		ms_delay(300);	
	}
		
}