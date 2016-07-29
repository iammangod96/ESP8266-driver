#include	"lpc17xx.h"
#include	"Wifi_Externs.h"
#include	"Uart_Externs.h"
#include	"Common_Lables.h"
#include	"String.h"

void TIMER1_IRQHandler(void)
{
	TIMER1_TCR = TIMER_RESET;									/* Reset and disable timer*/
	
	/* -------------------NEW MODIFICATION------------------------------- */
	
	if( Procrastinate == 'Y' )
	{
		Minute_Count	= Minute_Count + 1;
	}
	else
	{
		;
	}
	
	if( Minute_Count == MAX_MINUTES_TO_WAIT )
	{
		Procrastinate 	= 'N';
		Minute_Count 	= 0;
	}
	else
	{
		;
	}
		
	/*---------------------------------------------------------------------*/
	
	memset(Wifi_Rx_Buff, 0, WIFI_RX_BUFFER_SIZE * sizeof(Wifi_Rx_Buff[0]));
	Wifi_RxBuff_Fill_Ptr	= (uint8_t *)Wifi_RxBuff_Start_Addr;
	Wifi_RxBuff_Read_Ptr	= (uint8_t *)Wifi_RxBuff_Start_Addr;
	
	if(UART_RxBuff_Fill_Ptr	>= UART_RxBuff_Read_Ptr)
	{	
		memset(UART_Rx_Buff, 0, UART_RX_BUFFER_SIZE * sizeof(UART_Rx_Buff[0]));
		UART_RxBuff_Fill_Ptr	= (uint8_t *)UART_RxBuff_Start_Addr;
		UART_RxBuff_Read_Ptr	= (uint8_t *)UART_RxBuff_Start_Addr;
	}
	else
	{
		;
	}
	LPC_TIM1->IR 	|= CLEAR_TIMER_INTERRUPT;						/* Clear interrupt*/
	NVIC->ICPR[0] 	|= CLEAR_TIMER1_VEC_INT;						/* Clear NVIC interrupt*/
	TIMER1_TCR = TIMER_START;
	
	//call_it = 'Y';
	
	/* -------------------NEW MODIFICATION------------------------------- */
	
	if( Procrastinate == 'N' )
	{
		call_it = 'Y';
	}
	else
	{
		;
	}
	
	/*---------------------------------------------------------------------*/
}


void Init_Timer1(void)
{
	LPC_SC->PCONP |= (1<<2);						/* Power to Timer1*/
	LPC_SC->PCLKSEL0 &= ~((1 << 4) | (1 << 5));
	LPC_TIM1->PR = 99;
	LPC_TIM1->MR0 = 15000000;						/* Max count value */
	LPC_TIM1->MCR = 0x05;							/* Enable interrupt generation and reset the timer after timer counter reaches MR0*/ 
	LPC_TIM1->TCR = 0x0;							/* Disable Counter*/
	NVIC->ISER[0] |= (1 << 2); 						/* NVIC interrupt enable for Timer1*/
}


void Timer1_Start(void)
{
	TIMER1_TCR = TIMER_START;
}


void Timer1_Stop(void)
{
	TIMER1_TCR = TIMER_RESET;
}
