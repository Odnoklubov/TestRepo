// Problem3_solution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	uint64_t lNumIn = 0xA1B2C3D4E5F60718ULL;			//  Input number - one ending
	uint64_t lNumOut = RotateEndianOrder(lNumIn);		//  Output - another ending

	printf("In:  %llx\r\nOut: %llx", lNumIn, lNumOut);
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