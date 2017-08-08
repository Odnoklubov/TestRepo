#include "iostm8s105c6.h"
#include "types.h"
#include "delay.h"
#include "string.h"
#include "rtc.h"
#include "clk.h"
#include "LEDs.h"
#include "helper.h"
#include "wdt.h"
#include "UartInt.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef _TYPES_H_
#include "types.h"
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))		//  Gets number of array elements

char * GetHexStringOfByteArray_Way1(uint8_t *hexArr, uint16_t sArrLen);
char * GetHexStringOfByteArray_Way2(uint8_t *hexArr, uint16_t sArrLen);
 
char *s1;
char *s2;

//-----------------------------------
void main(void)
{   
    ClkInit();
    RTCInit();
    //WdtInit(WDT_TIMEOUT_1s02);
    asm("rim");

    vUartInit(CBR_115200, MODE_TX);
    
    LEDs_Init();
    //lNumIn;
    uint8_t array[6] = { 0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6};			//  Some array

    s1 = GetHexStringOfByteArray_Way2(array, NELEMS(array));		//  First way to solve
    s2 = GetHexStringOfByteArray_Way2(array, NELEMS(array));		//  Second way to solve
    
    //printf("\"%s\"\r\n\"%s\"", s1, s2);
    //getchar();
    while(TRUE);
}


char * GetHexStringOfByteArray_Way1(uint8_t *hexArr, uint16_t sArrLen)
{
	char *outHexStr = (char *)malloc(sArrLen * 2 + 1);			//  Allocate memory for string

	for (uint8_t i = 0; i < sArrLen; i++)
	{//  Until end of array
		snprintf(outHexStr + i * 2, 2, "%02X", hexArr[i]);		//  Set hex equivalent of num to str (_snprintf)
	}

	*(outHexStr + sArrLen * 2) = '\0';							//  Set last char of string to 0

	return outHexStr;
}

char * GetHexStringOfByteArray_Way2(uint8_t *hexArr, uint16_t sArrLen)
{
	char *outHexStr = (char *)malloc(sArrLen * 2 + 1);			//  Allocate memory for string

	for (uint8_t i = 0; i < sArrLen; i++)
	{//  Until end of array
		convertHexToStr(hexArr[i],(uint8_t*) (outHexStr + i * 2), 1);				//  Set hex equivalent of num to str (_itoa)
	}

	*(outHexStr + sArrLen * 2) = '\0';							//  Set last char of string to 0

	return outHexStr;
}