#include	"string.h"
#include	"Common_Lables.h"
#include	"data.h"
#include	"Wifi_Externs.h"

/*
GET /input/5JXvMoorx4tgjMnqjQ02?private_key=7Ba4n881xofeYxpEYb0y&temperature=99.18&humidity=100&co2=22\r\n
Host:data.sparkfun.com\r\n\r\n
*/

void Connect_Send(uint32_t co2, uint32_t humidity, uint32_t temp)	/* prepare data to send the parameters*/
{
	uint8_t temp_str[10];
	uint8_t humidity_str[10];
	uint8_t co2_str[10];
	
	Int_To_String(temp, temp_str);
	Int_To_String(humidity, humidity_str);
	Int_To_String(co2, co2_str);
	
	Add_To_Connect_Send_Data((uint8_t *)"GET /input/");
	Add_To_Connect_Send_Data(Public_Key1);
	Add_To_Connect_Send_Data((uint8_t *)"\?private_key=");
	Add_To_Connect_Send_Data(Private_Key1);
	Add_To_Connect_Send_Data((uint8_t *)"&temperature=");
	Add_To_Connect_Send_Data(temp_str);
	Add_To_Connect_Send_Data((uint8_t *)"&humidity=");
	Add_To_Connect_Send_Data(humidity_str);
	Add_To_Connect_Send_Data((uint8_t *)"&co2=");
	Add_To_Connect_Send_Data(co2_str);
	Add_To_Connect_Send_Data((uint8_t *)"\r\nHost:data.sparkfun.com\r\n\r\n\r\n");
}
