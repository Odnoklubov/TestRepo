// Problem3_solution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int _tmain(int argc, _TCHAR* argv[])
{
	uint64_t lNumIn = 0xA1B2C3D4E5F60718ULL;			//  Input number - one ending
	uint64_t lNumOut = RotateEndianOrder(lNumIn);		//  Output - another ending

	printf("In:  %llx\r\nOut: %llx\r\n", lNumIn, lNumOut);
	
	//  But if it is not possible to use uint64 numbers (like in IAR compiler for STM8S for example - uint32 maximum):
	struct uint64 lNumIn_struct;						//  Special structure for uint64 numbers
	lNumIn_struct.LSB = 0xE5F60718;						//  Least significant 4 bytes uint32
	lNumIn_struct.MSB = 0xA1B2C3D4;						//  Most significant 4 bytes uint32

	printf("Struct in:  %x%x\r\n", lNumIn_struct.MSB, lNumIn_struct.LSB);

	lNumIn_struct = RotateEndianOrder_struct(lNumIn_struct);			//  Make another bytes order of uint64
	printf("Struct out: %x%x", lNumIn_struct.MSB, lNumIn_struct.LSB);	//  Print result

	getchar();

	return 0;
}

uint64_t RotateEndianOrder(uint64_t lNum)
{
	//  Rotate number using shift
	return	((lNum & 0xFF00000000000000) >> 56) | ((lNum & 0x00FF000000000000) >> 40) |
			((lNum & 0x0000FF0000000000) >> 24) | ((lNum & 0x000000FF00000000) >> 8)  |
			((lNum & 0x00000000FF000000) << 8)  | ((lNum & 0x0000000000FF0000) << 24) |
			((lNum & 0x000000000000FF00) << 40) | ((lNum & 0x00000000000000FF) << 56) ;
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