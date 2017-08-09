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


uint8_t ChangedWithoutOperators_Way1(uint8_t st);
uint8_t ChangedWithoutOperators_Way2(uint8_t st);

//-----------------------------------
void main(void)
{
    char str[80]; 
   
    ClkInit();
    RTCInit();
    //WdtInit(WDT_TIMEOUT_1s02);
    asm("rim");

    vUartInit(CBR_115200, MODE_TX);
    
    LEDs_Init();
    
    //  The solution consist two functions - two way of code changing
    uint8_t st = 0;
    uint8_t res1, res2;
    
    res1 = ChangedWithoutOperators_Way1(st);
    res2 = ChangedWithoutOperators_Way2(st);

    snprintf(str, 80, "st == %d\r\nres1 = %d\r\nres2 = %d\r\n", st, res1, res2);
    vUartPutS(str);             //  Transmit to UART - trace
    
    while(TRUE);
}

uint8_t ChangedWithoutOperators_Way1(uint8_t st)
{
	const uint8_t arr[7] = { 26, 65, 234, 31, 25, 25, 25 };         //  Change 'switch' to byte array
	uint8_t result;

	result = arr[st];

	return result;
}

uint8_t ChangedWithoutOperators_Way2(uint8_t st)
{
	const char arr[8] = "\x1a\x41\xea\x1f\x19\x19\x19";             //  Change 'switch' to string
	uint8_t result;

	result = arr[st];

	return result;
}