
#ifndef	__Uart_Externs___H
	#define	__Uart_Externs___H
		extern void Init_Uart(void);
		extern void Send_Data_To_UART0(uint8_t *send_data);
		
		extern 	uint8_t		UART_Rx_Buff[1200];
		extern	uint32_t	UART_RxBuff_Start_Addr;
		extern	uint32_t	UART_RxBuff_End_Addr;
		extern	uint8_t		*UART_RxBuff_Fill_Ptr;
		extern	uint8_t		*UART_RxBuff_Read_Ptr;
#endif
