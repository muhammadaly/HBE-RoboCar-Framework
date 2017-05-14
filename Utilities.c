/*
 * Utilities.c
 *
 * Created: 6/15/2013 4:35:14 PM
 *  Author: Muhammad Aly
 */ 
#include "Utilities.h"
int Convert_From_String_To_Int(unsigned char* p_number)
{
	int	m_number =0, ind = MAX_NUMBER_OF_DIGITS ,factor =1;
	while (ind != -1)
	{
		if(p_number[ind] <='9' && p_number[ind] >='0')
		{
			m_number+=(p_number[ind]-'0')*factor ;
			factor*=10; 
		}
		ind--;
	}
	return m_number;
}
u08 Compare_Two_Strings(unsigned char* first , unsigned char* second)
{
	int ind = 0;
	while(second[ind] >= 'A' && second[ind] <='Z'&& first[ind] >= 'A' && first[ind] <='Z')
	{
		if(second[ind]!=first[ind])
			return 0;
		ind++;
	}
	return 1;
}