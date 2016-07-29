#include	"lpc17xx.h"
#include	"Wifi_Externs.h"
#include	"Common_Lables.h"

void TIMER0_IRQHandler(void)
{
	if( TIMER_OVER )										/* MR0 interrupt generated*/
	{
		W_TxPres_State 	 = 	RST;							/* Reset */
		TIMER0_TCR 		 = 	TIMER_RESET;					/* Reset and disable timer*/
		LPC_TIM0->IR 	|= 	CLEAR_TIMER_INTERRUPT;			/* Clear interrupt*/
		NVIC->ICPR[0] 	|= 	CLEAR_TIMER0_VEC_INT;			/* Clear NVIC interrupt*/
	}
	else
	{
		;
	}
}


void Init_Timer(void)
{
	LPC_SC->PCONP 		|= 	(1<<1);							/* Power to Timer0*/
	LPC_SC->PCLKSEL0 	&= 	~((1 << 2) | (1 << 3));
	LPC_TIM0->MR0 		 = 	350000000;						/* 12 sec emulator */
	LPC_TIM0->MCR 		 = 	0x05;							/* Enable interrupt generation and stop the timer after timer counter reaches MR0*/ 
	LPC_TIM0->TCR 		 = 	0x0;							/* Disable Counter*/
	NVIC->ISER[0] 		|= 	(1 << 1); 						/* NVIC interrupt enable for Timer0*/
}


void Timer_Start(void)
{
	TIMER0_TCR 			= 	TIMER_START;
}


void Timer_Stop(void)
{
	TIMER0_TCR 			= 	TIMER_RESET;
}
