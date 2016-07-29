#include	"lpc17xx.h"
#include	"string.h"

#include	"Common_Lables.h"

#include	"Wifi_Externs.h"
#include	"Data_Externs.h"
#include	"uart.h"

/*------------------------------------------
		UART INTERRUPT SERVICE ROUTINE 
--------------------------------------------*/

void UART0_IRQHandler(void)									/* Interrupt Service Routine (ISR)*/
{
	uint8_t val = INTERRUPT_TYPE;							/* Identifying the type of Interrupt*/
	
	
	if( TX_DATA_INTERRUPT )									/* Checking for THRE*/
	{
		uint32_t	loop_var;
		
		for(loop_var = 0; loop_var < UART_TX_BUFF_SIZE; loop_var = (loop_var + 1u))
		{
			if(Wifi_TxBuff_Trans_Ptr != Wifi_TxBuff_Fill_Ptr)
			{
				UART0_TX_REG	= *Wifi_TxBuff_Trans_Ptr++;
			}
			else
			{
				loop_var		= UART_TX_BUFF_SIZE;
			}
		}
		Delayms(1);
	}
	else
	{
		;
	}
		
		
	if( RECEIVE_DATA_INTERRUPT )						/* Checking for Receive Data interrupt (RDA)*/
	{  
		while( RECEIVER_DATA_READY )					/* Check if Receiver Data Ready (RDR)*/
		{
			UART_Ch			= UART0_RX_DATA;			/* Storing received bytes*/
			
			if(UART_RxBuff_Fill_Ptr <= (uint8_t *)UART_RxBuff_End_Addr)
			{
				*UART_RxBuff_Fill_Ptr++		= UART_Ch;
			}
			else
			{
				;
			}
		}
	}
	else
	{
		;
	}
	
}//end of ISR

/*------------------------------------------
		UART INITIALISATION
--------------------------------------------*/

void Init_Uart(void)									/* initialise UART0*/
{
	UART_Vars_Init();
	UART_Perpheral_Init();		
}


static void UART_Vars_Init(void)
{
	UART_RxBuff_Start_Addr	= (uint32_t)&UART_Rx_Buff[0];
	UART_RxBuff_End_Addr	= (uint32_t)&UART_Rx_Buff[ UART_RX_BUFFER_SIZE ];
	UART_RxBuff_Fill_Ptr	= (uint8_t *)UART_RxBuff_Start_Addr;
	UART_RxBuff_Read_Ptr	= (uint8_t *)UART_RxBuff_Start_Addr;
}


static void UART_Perpheral_Init(void)
{
	LPC_SC->PCONP 		|= 	(1<<3);							/* power control for peripherals*/
	LPC_SC->PCLKSEL0 	&= 	~((1<<6)|(1<<7));				/* selecting UART0 peripheral clock*/
	
	LPC_PINCON->PINSEL0 |= 	(1<<4)|(1<<6); 					/* selecting UART0 from the multiplexed pins*/
	LPC_PINCON->PINSEL0 &= 	~((1<<5)|(1<<7));
	
	LPC_UART0->FCR 		|= 	(1<<0)|(1<<1)|(1<<2); 			/* enable FIFO and reset Tx and Rx FIFO*/
	
	LPC_UART0->LCR 		= 	0x83; 							/* 8bit word length, 1 stop bit, disable parity,enable DLAB*/
	
	
	LPC_UART0->FDR 		&= 	~(0X01<<0);						/* set MulVal = 1, DivAddVal = 0*/
	LPC_UART0->FDR 		&= 	~((1<<5)|(1<<6)|(1<<7));
	LPC_UART0->FDR 		|= 	(1<<4);
	
	LPC_UART0->DLL 		= 	14;								/* 163->9600,14->115200 */
	LPC_UART0->DLM 		= 	0;
	LPC_UART0->LCR 		&= 	~(1<<7); 						/* CLEAR DLAB*/
	
	UART0_IER_REG 		|= 	(1<<0);							/* enable Rx Interrupt*/
	//LPC_UART0->IER 	|= 	(1<<1);
	UART0_IER_REG 		&= 	~(1<<1);						/* disable Tx interrupt	*/
	NVIC->ISER[0] 		|= 	(1 << UART0_VECT_INTR_NUM);		/* enable vector interrupts for UART0*/
}

/*------------------------------------------
		DELAY FUNCTION
--------------------------------------------*/

void Delayms (uint32_t time  )
{	
	while( time > 0 )
	{   
		uint32_t i = 500000; 								/* i is local counter */
		while (i>0)
		{
			i--;
		}
		time--;
	}
}

/*------------------------------------------
		TX FUNCTION
--------------------------------------------*/

void Send_Data_To_UART0(uint8_t* send_data)
{
	
	uint32_t temp  = 0;
	uint32_t size_temp = 0;
	while(send_data[temp] != '\0' )
	{
		if(Wifi_TxBuff_Fill_Ptr != (uint8_t *)Wifi_TxBuff_End_Addr)
		{
			*Wifi_TxBuff_Fill_Ptr++ = send_data[temp++];
		}
		else
		{
			;
		}
	}
	
	size_temp = temp;
	
	for(temp = 0;temp < UART_TX_BUFF_SIZE; temp++)
	{
		if(Wifi_TxBuff_Trans_Ptr != Wifi_TxBuff_Fill_Ptr)
		{
			UART0_TX_REG	= *Wifi_TxBuff_Trans_Ptr++;
		}
		else
		{
			;
		}
	}
	
	Delayms(1);
	
	if(size_temp > UART_TX_BUFF_SIZE)
	{
		UART0_IER_REG |= THRE_ENABLE_PIN;
	}
	else
	{
		;
	}
	
	return;
}

/*----------------------------------------------*/
/*----------------------------------------------*/
