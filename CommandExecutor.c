/*
 * CommandExecutor.c
 *
 * Created: 6/15/2013 5:03:07 PM
 *  Author: Muhammad Aly
 */ 
#include "UART.h"
#include "CommandExecutor.h"
#include "CommandExecuterErrors.h"



u08 Start_Robot(unsigned char** p_ArrayOfParameters,u08 p_numberOfParameters)
{
	m_positionX = (u08) Convert_From_String_To_Int(p_ArrayOfParameters[0]);
	m_positionY = (u08) Convert_From_String_To_Int(p_ArrayOfParameters[1]);
	
	// send "RDY"
	// send "GRD"
	
}
u08 VeriFying_Sending(unsigned char** p_ArrayOfParameters,u08 p_numberOfParameters)
{	
	u08* m_localGrid = malloc(LOCAL_GRID_HEIGHT*LOCAL_GRID_WIDTH);
	explore_local_area(m_localGrid);
	// send the local grid 
}
u08 Send_Path_Request(unsigned char** p_ArrayOfParameters,u08 p_numberOfParameters)
{	
	// send path Request .
}
u08 Stop_Session(unsigned char** p_ArrayOfParameters,u08 p_numberOfParameters)
{	
	// send Fin.
}
u08 Apply_Path_Sent(unsigned char** p_path,u08 p_Length)
{
	u08* m_path = (u08*) malloc(p_Length);
	for(int ind = 0 ; ind < p_Length ; ind+=2)
	{
		m_path[ind] = (u08)Convert_From_String_To_Int(p_path[ind]);
		m_path[ind+1] = p_path[ind+1][0];
	}
	Execute_Path(m_path , p_Length);
}
u08 Split_Command(unsigned char* Command)
{
	u08 ind = 0 , m_tempInd,m_parameterInd  = 0 ,m_numberOfParameters = 0;
	unsigned char* m_CommandSignature       = (unsigned char*) malloc(COMMAND_SIGNATURE_SIZE);
	unsigned char* m_parameter              = (unsigned char*) malloc(PARAMETER_MAX_SIZE);
	unsigned char** m_ArrayOfParameters     = (char**)malloc(PARAMETER_MAX_SIZE);
	
	while (Command[ind] != ' ' && Command[ind] != '#')
	{
		m_CommandSignature[ind] = Command[ind];
		ind++;
	}
	while (Command[ind++] != '#')
	{
	    m_tempInd = ind;
		while(Command[ind] !=',' && Command[ind] != '#')
		{
			m_parameter[ind-m_tempInd] = Command[ind];
			ind++;			
		}
		
		m_ArrayOfParameters[m_numberOfParameters] = (unsigned char*)malloc(MAX_NUMBER_OF_DIGITS);
		memcpy(m_ArrayOfParameters[m_numberOfParameters],m_parameter,MAX_NUMBER_OF_DIGITS);
		m_numberOfParameters++;
	}
	Execute_Command(m_CommandSignature,m_ArrayOfParameters,m_numberOfParameters);
	return COMMAND_EXECUTE_SUCCESS;
}
u08 Split_Data(unsigned char* Data)
{	
	u08 ind = 0 , m_tempInd,m_numberOfParameters  = 0 ;
	unsigned char* m_CommandSignature       = (unsigned char*) malloc(COMMAND_SIGNATURE_SIZE);
	unsigned char* m_parameter              = (unsigned char*) malloc(PARAMETER_MAX_SIZE);
	unsigned char** m_ArrayOfParameters                = (char**)malloc(PARAMETER_MAX_SIZE);
	while (Data[ind] != ' ' && Data[ind] != '$')
	{
		m_CommandSignature[ind] = Data[ind];
		ind++;
	}
	while (Data[ind++] != '$')
	{
	    m_tempInd = ind;
		while(Data[ind] !=',' && Data[ind] != '$')
		{
			m_parameter[ind-m_tempInd] = Data[ind];
			ind++;			
		}
		m_ArrayOfParameters[m_numberOfParameters] = (char*)malloc(MAX_NUMBER_OF_DIGITS);
		memcpy(m_ArrayOfParameters[m_numberOfParameters],m_parameter,MAX_NUMBER_OF_DIGITS);
		m_numberOfParameters++;

	}
	Process_Data(m_CommandSignature,m_ArrayOfParameters,m_numberOfParameters);
	return COMMAND_EXECUTE_SUCCESS;
}

u08 Execute_Command(unsigned char* p_CommandSignature , unsigned char** p_ArrayOfParameter , int p_NumberOfParameters)
{
		if(Compare_Two_Strings( p_CommandSignature , (unsigned char*)"CTS"))
			Command_Function = &VeriFying_Sending;
		else if(Compare_Two_Strings( p_CommandSignature , (unsigned char*)"UPD"))
			Command_Function = &Send_Path_Request;
		else if(Compare_Two_Strings( p_CommandSignature , (unsigned char*)"STP"))
			Command_Function = &Stop_Session;		
		else if(Compare_Two_Strings( p_CommandSignature , (unsigned char*)"STR"))
			Command_Function = &Start_Robot;
		else
			return NO_SUCH_COMMAND_ERROR;	

		if(Command_Function(p_ArrayOfParameter , p_NumberOfParameters))
			return COMMAND_EXECUTE_SUCCESS;
		else
			return COMMAND_EXECUTE_FAIL;

		
}
u08 Process_Data(unsigned char* p_CommandSignature , unsigned char** Data , u08 p_NumberOfData)
{
	if(Compare_Two_Strings( p_CommandSignature , (unsigned char*)"PTH"))
		Data_Function = &Apply_Path_Sent;		
	else
		return NO_SUCH_COMMAND_ERROR;	
	if(Data_Function(Data , p_NumberOfData))
			return COMMAND_EXECUTE_SUCCESS;
		else
			return COMMAND_EXECUTE_FAIL;
}