#ifndef __wifi_h
	#define __wifi_h
	
	#include	"stdint.h"										/* To use uintx_t typedef for data type declarations */
	#include	"Uart_Externs.h"
	#include	"Data_Externs.h"
	#include	"Timer_Externs.h"
	
	/*------------------------------------------
		FLAGS
	--------------------------------------------*/
	
	uint32_t 	Check_To_Rst 		= 0;							/* Flag for reset function*/
	uint8_t 	complete 			= 'N';							/* Flag to check END state or posting complete*/
	uint8_t 	call_it 			= 'N';							/* Flag used in main while(1) -> when to call Start_Posting*/
	uint8_t 	Check_Response 		= 'N';							/* Flag whether to start processing responses or not*/
	uint32_t	Num_END 			= 0;							/* Count of data posting to sparkfun */
	uint8_t 	Procrastinate		= 'N';							/* Used for Count_RST */
	
	/*------------------------------------------
		STATES
	--------------------------------------------*/
	
	typedef enum { OK, NO_RESPONSE, ERR1, ERR2, ERR3, ERR4, ERR5 }ret_response;	

	typedef enum { RST, ATE1, AT, CWMODE, CWJAP, CIPSTATUS, CIPSTART, CIPSEND, SEND_DATA, END, WAIT }states;
	
	typedef enum {READY_T, INPUT_NOW_T, CLOSED_T, ERROR_T, OK_T, NOTHING_T}Response_Type;
	
	Response_Type	Type_Of_Response = NOTHING_T;
		
	states			W_TxPres_State = RST;
	states			W_TxPrev_State = RST;
	ret_response	Trans_State; 
	
	/*------------------------------------------
		BUFFERS
	--------------------------------------------*/
	
	uint8_t		Wifi_Rx_Buff[ WIFI_RX_BUFFER_SIZE ];
	uint32_t	Wifi_RxBuff_Start_Addr;
	uint32_t	Wifi_RxBuff_End_Addr;
	uint8_t		*Wifi_RxBuff_Fill_Ptr;
	uint8_t		*Wifi_RxBuff_Read_Ptr;
	
	uint8_t		Wifi_Tx_Buff[ WIFI_TX_BUFFER_SIZE ];
	uint32_t	Wifi_TxBuff_Start_Addr;
	uint32_t	Wifi_TxBuff_End_Addr;
	uint8_t		*Wifi_TxBuff_Fill_Ptr;
	uint8_t		*Wifi_TxBuff_Trans_Ptr;
	
	uint8_t		Server_Response_Buff[ SERVER_RESPONSE_BUFFER_SIZE ];
	uint32_t	Server_Response_Start_Addr;
	uint32_t	Server_Response_End_Addr;
	uint8_t		*Server_Response_Fill_Ptr;
	uint8_t		*Server_Response_Trans_Ptr;
	
	
	uint16_t	Wifi_TxCmd_TOut;
	uint16_t	Wifi_RxByte_Cnt = 0;
	
	/*------------------------------------------
		FUNCTION PROTOTYPES
	--------------------------------------------*/
	
				void 		WIFI_Main(void);
				void 		Start_Posting(void);
				states 		lookup(states Var1, ret_response Var2);
				void 		Wifi_Vars_Init(void);
			
				uint32_t 	Length_String( uint8_t *str );
				int32_t 	Find_Substring( uint8_t *str, uint8_t *sub);
				void 		Concat_Strings( uint8_t *dest, uint8_t *src);
				void 		Int_To_String( uint32_t num, uint8_t *buffer);
				void 		Init_String( uint8_t *str, uint8_t *content);
			
				void 		Add_To_Connect_Send_Data(uint8_t *data);
				void 		Store_Server_Response(void);
	static		void 		Wifi_Tx_Prep_Fun(void);
	static		void 		Wifi_Rx_Data_Fun(void);
	static		void 		Wifi_Resp_Proce_Fun(void);
	
	/*------------------------------------------
		STATE MACHINE
	--------------------------------------------*/
	
	struct trans													/* Different states during a transition process*/
	{													
		states src_state;
		ret_response trans_state;
		states dest_state;
	};

	struct trans transition_table[] = 
	{
		{RST, OK, AT}, 				{RST, ERR1, RST},
		{ATE1, OK, AT},				{ATE1, NO_RESPONSE, ATE1}, 			
		{AT, OK, CWMODE},			{AT, NO_RESPONSE, AT}, 				
		{CWMODE, OK, CWJAP}, 		{CWMODE, NO_RESPONSE, CWMODE},		
		{CWJAP, OK , CIPSTATUS},	{CWJAP, ERR1, CWJAP},				{CWJAP, ERR2,CWJAP},			{CWJAP, ERR3,CWJAP},		{CWJAP, ERR4,CWJAP}, 		
		{CIPSTATUS,ERR1,CIPSTATUS},	{CIPSTATUS, ERR2, CIPSTART},		{CIPSTATUS, ERR4, CIPSTART},	{CIPSTATUS, ERR3, CIPSEND},	{CIPSTATUS, ERR5, CWJAP},	
		{CIPSTART, OK, CIPSEND},	{CIPSTART, ERR1, CIPSTART}, 					
		{CIPSEND, OK, SEND_DATA},	{CIPSEND, ERR1, CIPSTART},			
		{SEND_DATA, OK, END}, 		{SEND_DATA, ERR1, CIPSTART},			
		{END, OK, AT},
	};
	
	/*-----------------------------------------------------
		GLOBAL VARIABLES FOR FUNCTIONS
	-----------------------------------------------------*/
	
	uint8_t 	temp_data[ TEMP_DATA_BUFFER_SIZE ];					/* For custom string concatenation function */
	uint32_t 	temp_data_cnt1;										/* For custom string concatenation function */
	uint32_t 	temp_data_cnt2;										/* For custom string concatenation function */
	
	uint32_t 	Connect_Send_Data_Cnt			= 0;				/* Index for Add_To_Connect_Send_Data() func */
	uint32_t 	ret 							= 0;				/* Used to get status or error values of some AT  commands*/
	uint32_t 	num 							= 0;				/* Used to get status or error values of some AT  commands*/
	
	uint32_t 	a = 1,		b = 1,		c = 1;						/* Parameters to be posted to sparkfun */
	uint32_t	Count_RST						= 0;				/* Number of times RST state reached */
	uint32_t	Minute_Count					= 0;				/* Used with Count_RST */
	
	/*-----------------------------------------------------*/
	
#endif
	
