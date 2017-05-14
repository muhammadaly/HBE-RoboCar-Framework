/*
 * UART.h
 *
 * Created: 07/04/2013 04:19:21 م
 *  Author: pc5
 */ 


#ifndef UART_H_
#define UART_H_

#include "avr_lib.h"
#include "Robot.h"
#define MAX_DATA_SIZE          40
#define COMMAND_SIGNATURE_SIZE 3
#define PARAMETER_MAX_SIZE     10
#define UART_115200	3

unsigned char* m_sendBuffer ;
unsigned char* m_receiveBuffer ;
unsigned char* m_newCommand ;
unsigned char* m_newData;
static u08 m_receiveBufferInd;
static u08 m_sendBufferInd ;

void Initialize_UART();
u08 getbytes(unsigned char *data);
void sendbytes(unsigned char* data);
void uart0_Str(char *str);
void uart1_Str(char *str);
void putch_u0(unsigned char data);
u08 getch_u0();
void putch_u1(unsigned char data);
u08 getch_u1();
void init_UART0(u08 bps);
void init_UART1(u08 bps);
SIGNAL(USART1_RX_vect);
void Enable_Sending();
#endif /* UART_H_ */