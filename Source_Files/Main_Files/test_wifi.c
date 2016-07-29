#include "LPC17xx.H"
#include "string.h"
#include	"Common_Lables.h"

#include	"Uart_Externs.h"
#include	"Wifi_Externs.h"
#include	"Data_Externs.h"
#include	"Timer_Externs.h"
#include	"Timer1_Externs.h"


int main( void )
{	
	Init_Timer1();								/* TIMER1 initialisation*/
 	Init_Timer();								/* TIMER0 initialisation*/
 	Wifi_Vars_Init();							/* WIFI buffers initialisation*/
	Init_Uart();								/* UART initialisation */
 	
	Connect_Send(a, b, c);						/* For sparkfun data posting format CO2, Humd, Temp*/
	
	Timer1_Stop();								/* Restart Timer1*/
	Timer1_Start();	
 	
	Start_Posting();							/* Start posting data to server*/
	
	while(1)
	{
		if (call_it == 'Y')						/* if TIMER1 interrupt*/
		{
			memset(Connect_Send_Data, 0, CONNECT_SEND_DATA_SIZE * sizeof(Connect_Send_Data[0]));
			Connect_Send(++a, ++b, ++c);
			Start_Posting();
		}
		else
		{
			;
		}
	}	
}
