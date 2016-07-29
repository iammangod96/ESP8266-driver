#ifndef __uart_h
	#define __uart_h

	/* UART Rx Buffer initialization */
	
	uint8_t		UART_Rx_Buff[ UART_RX_BUFFER_SIZE ];	
	uint32_t	UART_RxBuff_Start_Addr;
	uint32_t	UART_RxBuff_End_Addr;
	uint8_t		*UART_RxBuff_Fill_Ptr;
	uint8_t		*UART_RxBuff_Read_Ptr;
	
	
	
	/* for RDA in ISR, temp variable to get byte from RBR*/
	uint8_t		UART_Ch;								
		
	
	/* UART initialization functions*/
	
			void 		Init_Uart (void);
	static 	void		UART_Vars_Init(void);
	static 	void		UART_Perpheral_Init(void);
	
	
	
	/* Delay function*/
	void Delayms (uint32_t time  );
	
	/* Interrupt Service Routine ISR for UART */
	void UART0_IRQHandler(void);
	
	
#endif
