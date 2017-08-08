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

#define LITTLE_ENDIAN_CODE	0x01
#define BIG_ENDIAN_CODE		0X02
#define ERROR_CODE		0xFF

//  It is not possible to use uint64 numbers in IAR compiler for STM8S for example - uint32 maximum:
struct uint64 
{
    uint32_t MSB;
    uint32_t LSB;
};

struct uint64 RotateEndianOrder_struct(struct uint64 lNum);
 
//-----------------------------------
void main(void)
{
    char str[80]; 
    struct uint64 lNumIn;
   
    ClkInit();
    RTCInit();
    //WdtInit(WDT_TIMEOUT_1s02);
    asm("rim");

    vUartInit(CBR_115200, MODE_TX);
    
    LEDs_Init();
    //lNumIn;
    lNumIn.LSB = 0xE5F60718;			
    lNumIn.MSB = 0xA1B2C3D4; 
    
    lNumIn = RotateEndianOrder_struct(lNumIn);

    snprintf(str, 80, "%lx%lx\r\n", lNumIn.MSB, lNumIn.LSB);
    vUartPutS(str);
    while(TRUE);
}


struct uint64 RotateEndianOrder_struct(struct uint64 lNum)
{
    uint8_t *cNumArr = (uint8_t*)&lNum;		//  Set pointer to struct start byte
    uint8_t cTemp = 0;
    for (uint8_t i = 0; i < 4; i++)
    {//  Change bytes order
        cTemp = cNumArr[i];
        cNumArr[i] = cNumArr[7 - i];
        cNumArr[7 - i] = cTemp;
    }
    
    return lNum;
}