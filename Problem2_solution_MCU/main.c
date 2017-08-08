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

#define LITTLE_ENDIAN_CODE	0x01
#define BIG_ENDIAN_CODE		0X02
#define ERROR_CODE		0xFF


uint8_t GetMachineEndian_way1();
uint8_t GetMachineEndian_way2();

//-----------------------------------

void main(void)
{
    ClkInit();
    RTCInit();
    //WdtInit(WDT_TIMEOUT_1s02);
    asm("rim");

    vUartInit(CBR_115200, MODE_TX);
    
    LEDs_Init();
    
    uint8_t machineEndianCode1 = GetMachineEndian_way1();
    uint8_t machineEndianCode2 = GetMachineEndian_way2();
    
    if (machineEndianCode1 != machineEndianCode2)
    {
            vUartPutS("Some error happened.");    
            LED1_ON;
            LED2_ON;
            
            return;
    }
    
    switch (machineEndianCode1)
    {
    case LITTLE_ENDIAN_CODE:
            vUartPutS("Answer: Little Endian.");    
            LED1_ON;
                 
            break;
    case BIG_ENDIAN_CODE:
            vUartPutS("Answer: Big Endian.");
      
            LED2_ON;
      
            break;
    default:
            vUartPutS("Some error happened.");
        
            LED1_ON;
            LED2_ON;
      
            break;
    }   
    
    while(TRUE);
}

uint8_t GetMachineEndian_way1()
{
	uint16_t sNum = 0x0102;					//  Some random int16 number

	//  Memory 1                    Memory2
	// |****|****|                 |****|****|
	// |0x01|0x02| - big endian    |0x02|0x01| - little endian
	// |****|****|                 |****|****|

	uint8_t * aBuf = (uint8_t *)(&sNum);	//  Get pointer to girst byte of sNum
	//  Alternative code of the above command:
	/*  uint8_t *aBuf = (uint8_t*)malloc(1);//  Declare  uint8_t array
		*aBuf = (uint8_t)(sNum & 0xFF);		//  Set first element equals LSB or MSB of sNum
	*/

	if (*aBuf == 0x01)
	{//  The most significant byte is at the lowest address => big endian
		return BIG_ENDIAN_CODE;
	}
	if (*aBuf == 0x02)
	{//  The least significant byte is at the lowest address => little endian
		return LITTLE_ENDIAN_CODE;
	}

	return ERROR_CODE;						//  Some error happened
}

uint8_t GetMachineEndian_way2()
{
	uint16_t sNum;
	uint8_t * aBuf = (uint8_t*)malloc(2);
	*aBuf = 0x01;
	*(aBuf + 1) = 0x02;

	//  Memory <aBuf>  
	// |****|****|
	// |0x01|0x02|
	// |****|****|

	sNum = *(uint16_t *)aBuf;		//  Convert aBuf to __int16

	if (sNum == 0x0102)
	{//  The most significant byte is at the lowest address => big endian
		return BIG_ENDIAN_CODE;
	}
	if (sNum == 0x0201)
	{//  The least significant byte is at the lowest address => little endian
		return LITTLE_ENDIAN_CODE;
	}

	return ERROR_CODE;						//  Some error happened
}