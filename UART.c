/*
 * UART.c
 *
 * Created: 07/04/2013 04:13:15 م
 *  Author: pc5
 */ 
#include "avr_lib.h"
#include "UART.h"
#include "Utilities.h"

void Initialize_UART()
{
	init_UART0(UART_115200); // 115200 bps in 7.3728
	m_sendBuffer        = (unsigned char*) malloc(MAX_DATA_SIZE);
	m_receiveBuffer     = (unsigned char*) malloc(MAX_DATA_SIZE);
	m_newCommand        = (unsigned char*) malloc(MAX_DATA_SIZE);
	m_newData           = (unsigned char*) malloc(MAX_DATA_SIZE);
	m_receiveBufferInd  = 0;
	m_sendBufferInd     = 0;
}
void sendbytes(unsigned char* data)
{
	int i=0;
	while(data[i] != '\0')
		putch_u0(data[i++]);
	putch_u0('\n');
}
void init_UART1(u08 bps)  
{

      DDRD &= 0xFB;
	  DDRD |= 0x08;


     UCSR1A=0x00;
     UCSR1B=0x98;  // enable the RXIE and TXIE Interrupts .  
     UCSR1C=0x06;  // make the character size = 8 bit .

     UBRR1H=0x00;
     UBRR1L=bps;   

}
void init_UART0(u08 bps)   
{

    DDRE &= ~0x01;
	DDRE |= 0x02;  


     UCSR0A=0x00;
     UCSR0B=0x98; // enable the RXIE and TXIE Interrupts .
     UCSR0C=0x06; // make the character size = 8 bit .

     UBRR0H=0x00;
     UBRR0L=bps;   

}
u08 getch_u1(){

	unsigned char data;

	while((UCSR1A & 0x80)==0); // check RXC bit 

	data=UDR1;

	UCSR1A	|=	0x80;

	return data;
}

void putch_u1(unsigned char data)
{
	while((UCSR1A & 0x20)==0x00); // check UDRE bit
	UDR1=data;
  
	UCSR1A |= 0x20;       
}

u08 getch_u0(){

	unsigned char data;

	while((UCSR0A & 0x80)==0);

	data=UDR0;

	UCSR0A	|=	0x80;

	return data;
}

void putch_u0(unsigned char data)
{
	while((UCSR0A & 0x20)==0x00);
	UDR0=data;
  
	UCSR0A |= 0x20;         // إ¬¸®¾î UDRE0
}

void uart1_Str(char *str){
	u08 i=0;
	while(str[i]!='\0')
		putch_u1(str[i++]);
}

void uart0_Str(char *str){
	u08 i=0;
	while(str[i]!='\0')
		putch_u0(str[i++]);
}
SIGNAL(USART0_RX_vect)
{
	cli();
	BEEP_ON();
	ms_delay(100);
	BEEP_OFF();
	ms_delay(100);	
	m_receiveBuffer[m_receiveBufferInd]=UDR0;
	UCSR0A	|=	(1<<RXC0);
	if(m_receiveBuffer[m_receiveBufferInd] == '$' ){
		for(u08 ind = 0; ind <= m_receiveBufferInd ; ind++ ){
			m_newData[ind] = m_receiveBuffer[ind];			
		}
		m_receiveBufferInd = 0;
		Split_Data(m_newData);
	}
	if(m_receiveBuffer[m_receiveBufferInd] == '#' ){
		for(u08 ind = 0; ind <= m_receiveBufferInd ; ind++ ){
			m_newCommand[ind] = m_receiveBuffer[ind];			
		}
		m_receiveBufferInd = 0;
		Split_Command(m_newCommand);
	}
	else{
		m_receiveBufferInd++;
	}
	sei();
}