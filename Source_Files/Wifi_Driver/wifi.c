#include	"string.h"
#include	"lpc17xx.h"	//for testing

#include	"Common_Lables.h"

/* used stdio for sprintf to convert integer into string in Func_CIPSEND()*/
#include	"wifi.h"

/*------------------------------------------
		STRING FUNCTIONS
--------------------------------------------*/

uint32_t Length_String( uint8_t *str )
{
	uint32_t size = 0;
	if( str[size] == '\0')
	{
		return 0;
	}
	else
	{
		while( str[size] != 0)
		{
			size++;
		}
		return size;
	}
}

/*------------------------------------------------------*/

int32_t Find_Substring( uint8_t *str, uint8_t *sub)
{
	
	int32_t 	i_str = 0, 				i_sub = 0;
	uint32_t 	n = Length_String(str), m = Length_String(sub);
	if(n == 0 || m == 0) 
	{
		return -2;				/* Function not applicable*/
	}
	else
	{
		for( i_str = 0; i_str < n; i_str++)
		{
			for( i_sub = 0; (i_sub < m) && (i_str + i_sub < n); i_sub++ )
			{
				if (str[i_str + i_sub] != sub[i_sub]) 
				{
					break;
				}
				else
				{
					;
				}
			}
			
			if (i_sub == m) 
			{
				return i_str;	/* Substring location*/
			}
			else
			{
				;
			}
		}
		
		return -1;				/* Substring not present*/
	}
}

uint8_t Equal_Checker(uint32_t i, uint8_t* str1, uint8_t* str2)
{
	uint32_t k;
	uint32_t n = Length_String(str1), m = Length_String(str2);
	for(k = 0; (k < m) && (( k + i ) < n); k++)
	{
			if(str2[k] != str1[i+k])
			{
				return 'N';
			}
			else
			{
				;
			}
	}
	if( (k < m) || (( k + i ) < n) )
	{
		return 'N';
	}
	else
	{
		return 'Y';
	}
}



int32_t Find_Response( uint8_t* str )
{
	int32_t 	i_str 	= 0;
	uint32_t 	n 		= Length_String(str);
	uint8_t		found	= 'N';
	if( n == 0 )
	{
		return -2;
	}
	else
	{
		for(i_str=0; i_str < n;i_str++)
		{
			switch(str[i_str])
			{
				case 'r':
					if( Equal_Checker(i_str, str, (uint8_t*)"ready\r\n") == 'Y')
					{
						Type_Of_Response = READY_T;
						found = 'Y';
					}
					else
					{
						;
					}
					break;
				case '>':
					Type_Of_Response = INPUT_NOW_T;
					found = 'Y';
					
					break;
				case 'C':
					if( Equal_Checker(i_str, str, (uint8_t*)"CLOSED\r\n") == 'Y')
					{
						Type_Of_Response = CLOSED_T;
						found = 'Y';
					}
					else
					{
						;
					}
					break;
				case 'E':
					if( Equal_Checker(i_str, str, (uint8_t*)"ERROR\r\n") == 'Y')
					{
						Type_Of_Response = ERROR_T;
						found = 'Y';
					}
					else
					{
						;
					}
					break;
				case 'O':
					if( Equal_Checker(i_str, str, (uint8_t*)"OK\r\n") == 'Y')
					{
						Type_Of_Response = OK_T;
						found = 'Y';
					}
					else
					{
						;
					}
					break;
				default:
					;
			} /* end of switch*/
			if( found == 'Y' )
			{
				return 1;
			}
			else
			{
				;
			}
		}/* end of for*/
		Type_Of_Response = NOTHING_T;
		return -1; /*Not equal*/
	}/* end of else*/
}/* end of Find_Response function*/

/*------------------------------------------------------*/

void Init_String( uint8_t *str, uint8_t *content)
{
	uint32_t cnt = 0;
	for(cnt = 0; content[cnt] != '\0'; cnt++)
	{
		str[cnt] = content[cnt];
	}
	str[cnt] = '\0';
	
}

/*------------------------------------------------------*/

void Int_To_String( uint32_t num, uint8_t *buffer)
{
	uint32_t d 					= 1;
	uint32_t digit 				= 0;
	uint32_t buffer_index 		= 0;
	
	while((num / d) >= 10)
	{
		d = d * 10;
	}
	
	while(d != 0)
	{
		digit 	= num / d;
		num 	= num % d;
		d 		= d / 10;
		
		buffer[ buffer_index++ ] = digit + '0';
	}
	buffer[ buffer_index ] = '\0';
	
}

/*-----------------------------------------------------*/

void Concat_Strings( uint8_t *dest, uint8_t *src)
{
	for(temp_data_cnt1 = 0; dest[temp_data_cnt1] != '\0'; temp_data_cnt1++)
	{
		;
	}
					
	for(temp_data_cnt2 = 0; src[temp_data_cnt2] != '\0'; temp_data_cnt2++)
	{	
		dest[temp_data_cnt1 + temp_data_cnt2] = src[temp_data_cnt2];
	}
	
	dest[temp_data_cnt1 + temp_data_cnt2] = '\0';
}


/*------------------------------------------
		BUFFERS INITIALISATION
--------------------------------------------*/

void Wifi_Vars_Init(void)
{	
	Wifi_RxBuff_Start_Addr	= (uint32_t)&Wifi_Rx_Buff[0];
	Wifi_RxBuff_End_Addr	= (uint32_t)&Wifi_Rx_Buff[ WIFI_RX_BUFFER_SIZE ];
	Wifi_RxBuff_Fill_Ptr	= (uint8_t *)Wifi_RxBuff_Start_Addr;
	Wifi_RxBuff_Read_Ptr	= (uint8_t *)Wifi_RxBuff_Start_Addr;
	
	Wifi_TxBuff_Start_Addr	= (uint32_t)&Wifi_Tx_Buff[0];
	Wifi_TxBuff_End_Addr	= (uint32_t)&Wifi_Tx_Buff[ WIFI_TX_BUFFER_SIZE ];
	Wifi_TxBuff_Fill_Ptr	= (uint8_t *)Wifi_TxBuff_Start_Addr;
	Wifi_TxBuff_Trans_Ptr	= (uint8_t *)Wifi_TxBuff_Start_Addr;
	
	Server_Response_Start_Addr	= (uint32_t)&Server_Response_Buff[0];
	Server_Response_End_Addr	= (uint32_t)&Server_Response_Buff[ SERVER_RESPONSE_BUFFER_SIZE ];
	Server_Response_Fill_Ptr	= (uint8_t *)Server_Response_Start_Addr;
	Server_Response_Trans_Ptr	= (uint8_t *)Server_Response_Start_Addr;
	
}



void Store_Server_Response(void)
{
	uint32_t index_response 			= 0;
	uint32_t response_end 				= 0;
	index_response 						= Find_Substring(Wifi_Rx_Buff, (uint8_t*)"+IPD");
	response_end 						= Find_Substring(Wifi_Rx_Buff, (uint8_t*)"CLOSED");
	
	for( ; index_response < response_end; index_response++)
	{
		if( Server_Response_Fill_Ptr 	!= (uint8_t*)Server_Response_End_Addr)
		{
			*Server_Response_Fill_Ptr++ = Wifi_Rx_Buff[index_response];
		}
		else
		{
			;
		}
	}
}
/*------------------------------------------
		PREPARE CONNECT_SEND_DATA
--------------------------------------------*/

void Add_To_Connect_Send_Data(uint8_t *data)
{
	uint32_t loop_var 		= 0;
	uint32_t loop_var_const = Connect_Send_Data_Cnt;
		
	while(data[loop_var] != 0x00)
	{
		Connect_Send_Data[loop_var + loop_var_const]	= data[loop_var];
		Connect_Send_Data_Cnt 							= Connect_Send_Data_Cnt + 1u;
		loop_var										= (loop_var + 1u);
	}
}

/*------------------------------------------
		STATE MACHINE MAIN CALLS
--------------------------------------------*/

void WIFI_Main(void)
{
	Wifi_Tx_Prep_Fun( );
	Wifi_Rx_Data_Fun( );
	Wifi_Resp_Proce_Fun( );
}

void Start_Posting(void)
{
	while(1)
	{
		if(complete == 'Y')
		{
			complete = 'N';
			break;
		}
		else
		{
			WIFI_Main();
		}
	}
	
	return;
}

states lookup(states Var1, ret_response Var2)
{
	uint32_t Count = 0;
	uint32_t Size_Transition_Table = sizeof(transition_table) / sizeof(transition_table[0]);
	
	for(Count = 0; Count < Size_Transition_Table; Count++)
	{
		if((transition_table[Count].src_state == Var1) && (transition_table[Count].trans_state == Var2))
		{
			return transition_table[Count].dest_state;
		}
		else
		{
			;
		}
	}
	return AT;
}

/*-----------------------------------------------------*/

static void Wifi_Tx_Prep_Fun(void)
{
	switch(W_TxPres_State)
	{
		case RST:
		{			
					Count_RST		= Count_RST + 1;
					if( Count_RST	>=	MAX_RST_ALLOWED )
					{
						Procrastinate = 'Y';
					}
					else
					{
						;
					}
					Send_Data_To_UART0((uint8_t* )"AT+RST\r\n");
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
		}
		break;
		
		case AT:
		{
					Send_Data_To_UART0((uint8_t* )"AT\r\n");
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Timer_Start();
		}
		break;
		
		case ATE1:
		{
					Send_Data_To_UART0((uint8_t* )"ATE1\r\n");
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Timer_Start();
		}
		break;
		
		case CWMODE:
		{
					Send_Data_To_UART0((uint8_t* )"AT+CWMODE=1\r\n");
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Timer_Start();
		}
		break;
		
		case CWJAP:
		{
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Send_Data_To_UART0((uint8_t* )"AT+CWJAP=\"EFF-WIFI\",\"eff@ronics\"\r\n");
					Timer_Start();
		}
		break;
		
		case CIPSTATUS:
		{
					Send_Data_To_UART0((uint8_t* )"AT+CIPSTATUS\r\n");
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Timer_Start();
		}
		break;
		
		case CIPSTART:
		{
					
					Init_String(temp_data, (uint8_t*)"AT+CIPSTART=");
					Concat_Strings(temp_data,Connect_To_Data);
					
					Send_Data_To_UART0(temp_data);
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Timer_Start();
		}
		break;
		
		case CIPSEND:
		{
					
					uint8_t buffer_char_Func_CIPSEND[10];
					Int_To_String(Length_String(Connect_Send_Data), buffer_char_Func_CIPSEND);
														
					memset(temp_data, 0, TEMP_DATA_BUFFER_SIZE * sizeof(temp_data[0]));
					
					Init_String(temp_data, (uint8_t*)"AT+CIPSEND=");
					Concat_Strings(temp_data, buffer_char_Func_CIPSEND);
					Concat_Strings(temp_data, (uint8_t*)"\r\n");
															
					Send_Data_To_UART0(temp_data);
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Timer_Start();
		}
		break;
		
		case SEND_DATA:
		{
					Send_Data_To_UART0((uint8_t* ) Connect_Send_Data);
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Timer_Start();
		}
		break;
		
		case END:
		{
					Num_END++;
					W_TxPrev_State	= W_TxPres_State;
					W_TxPres_State	= WAIT;
					Connect_Send_Data_Cnt = 0;
					
		}
		break;
		
		case WAIT:
		{
			;
		}
		break;
		
		default:
		{
			;
		}
		break;
	}
	
	UART0_IER_REG 			&= ~( THRE_ENABLE_PIN );							/* disable Tx interrupt*/
	memset(Wifi_Tx_Buff, 0, WIFI_TX_BUFFER_SIZE * sizeof(Wifi_Tx_Buff[0]));
	Wifi_TxBuff_Fill_Ptr	= (uint8_t *)Wifi_TxBuff_Start_Addr;
	Wifi_TxBuff_Trans_Ptr	= (uint8_t *)Wifi_TxBuff_Start_Addr;
	return;
}

/*-----------------------------------------------------*/

static void Wifi_Rx_Data_Fun(void)
{
	while(UART_RxBuff_Read_Ptr < UART_RxBuff_Fill_Ptr)	
	{		
		*Wifi_RxBuff_Fill_Ptr++			= *UART_RxBuff_Read_Ptr++;
		Wifi_RxByte_Cnt					= (Wifi_RxByte_Cnt + 1u);	
	}
	
	return;
}

/*-----------------------------------------------------*/

static void Wifi_Resp_Proce_Fun(void)
{
// 	if( ( Find_Substring(Wifi_Rx_Buff, (uint8_t*)"ready\r\n") >= 0) || ( Find_Substring( Wifi_Rx_Buff, (uint8_t*)">") >= 0) || ( Find_Substring( Wifi_Rx_Buff, (uint8_t*)"CLOSED\r\n" ) >= 0 ) || ( Find_Substring( Wifi_Rx_Buff, (uint8_t*)"ERROR\r\n") >= 0) || ( Find_Substring( Wifi_Rx_Buff, (uint8_t*)"OK\r\n" ) >= 0 ) )
// 	{
// 		Check_Response = 'Y';
// 	}
// 	else
// 	{
// 		;
// 	}
		if(Find_Response(Wifi_Rx_Buff) == 1)
		{
			Check_Response = 'Y';
		}
		else
		{
			;
		}
	

	if(Check_Response == 'Y')
	{
		switch(W_TxPrev_State)
		{
			case RST:
						if( Type_Of_Response == READY_T )
						{
							Trans_State = OK;
						}
						else 
						{
							Trans_State = ERR1;
						}
						
						break;
						
			case ATE1:
						if( Type_Of_Response == OK_T )
						{
							Trans_State = OK;
						}
						else 
						{
							Trans_State = NO_RESPONSE;
						}
						
						break;
				
			case AT:
						if( Type_Of_Response == OK_T )
						{
							Trans_State = OK;
						}
						else 
						{
							Trans_State = NO_RESPONSE;
						}
						
						break;
				
			case CWMODE:
						if( Type_Of_Response == OK_T )
						{
							Trans_State = OK;
						}
						else 
						{
							Trans_State = NO_RESPONSE;
						}
						
						break;
				
			case CWJAP:
						if( Find_Substring( Wifi_Rx_Buff, (uint8_t* )"WIFI CONNECTED") >= 0)
						{
							if( Type_Of_Response == OK_T )
							{
								Trans_State = OK;
							}
							else
							{
								;
							}
								
						}
						else
						{
							
							ret = Find_Substring( Wifi_Rx_Buff, (uint8_t*)"+CWJAP:" );
							num = Wifi_Rx_Buff[ ret + 7 ] - '0';
							
							switch(num)
							{
								case 2:										/* wrong password*/
									Trans_State = ERR2;
									break;
								case 3:										/* cannot find AP*/
									Trans_State = ERR3;
									break;
								case 1:										/* timeout*/
									Trans_State = ERR1;
									break;
								case 4:										/* connectoin fail*/
									Trans_State = ERR4;
									break;
								default:
									;
							}
									
						}
						
						break;
						
			case CIPSTATUS:
						if( Type_Of_Response == OK_T )
						{
							ret = Find_Substring( Wifi_Rx_Buff, (uint8_t*)"STATUS:");
							num = Wifi_Rx_Buff[ ret + 7 ] - '0';
							
							switch(num)
							{
								case 2:										/*Got IP address*/
									Trans_State = ERR2;
									break;
								case 3:										/*Connected to server*/
									Trans_State = ERR3;
									break;
								case 4:										/*failed connection*/
									Trans_State = ERR4;
									break;
								case 5:										/*WIFI connection failed go to CWJAP*/
									Trans_State = ERR5;
									break;
								default:
									Trans_State = ERR1;
									
							}
								
						}
						else 
						{
							Trans_State = ERR1;
						}
						
						break;	
			
			case CIPSTART:
						if( Type_Of_Response == OK_T )
						{
							Trans_State = OK;
						}
						else 
						{
							Trans_State = ERR1;
 						}
						
			
						break;
						
			case CIPSEND:
						if( Type_Of_Response == INPUT_NOW_T)
						{
							Trans_State = OK;
						}
						else 
						{
							Trans_State = ERR1;
						}
						
						break;
			
			case SEND_DATA:
						if( Type_Of_Response == OK_T )
						{
							Trans_State = OK;
						}
						else 
						{
							Trans_State = ERR1;
						}
						
						break;
			
			case WAIT:
						break;
			
			case END:
						Store_Server_Response();
						Trans_State = OK;
						complete 		= 'Y';
						call_it 		= 'N'; 			
						break;
			default:
						;
		
		} /* end of switch */
		
		W_TxPres_State = lookup( W_TxPrev_State, Trans_State );
		Timer_Stop();
		
		if(W_TxPrev_State != SEND_DATA)
		{
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
		}
		else
		{
			memset(Server_Response_Buff, 0, SERVER_RESPONSE_BUFFER_SIZE * sizeof(Server_Response_Buff[0]));
			Server_Response_Fill_Ptr	= (uint8_t *)Server_Response_Start_Addr;
			Server_Response_Trans_Ptr	= (uint8_t *)Server_Response_Start_Addr;
		}
		
		Check_Response = 'N';
		return;
	
	} /* end of if Y */
	else
	{
		;
	}
	
	if(W_TxPres_State == WAIT)
	{
		return;
	}
	else
	{
		;
	}
	
} /*end of Wifi_Resp_Proce_Fun() */


/*-----------------------------------------------------*/
/*-----------------------------------------------------*/

