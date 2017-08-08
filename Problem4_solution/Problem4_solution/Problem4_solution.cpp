// Problem4_solution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	uint8_t array[6] = { 0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6};			//  Some array

	char *s1 = GetHexStringOfByteArray_Way2(array, NELEMS(array));		//  First way to solve
	char *s2 = GetHexStringOfByteArray_Way2(array, NELEMS(array));		//  Second way to solve

	printf("\"%s\"\r\n\"%s\"", s1, s2);
	getchar();

	return 0;
}

char * GetHexStringOfByteArray_Way1(uint8_t *hexArr, uint16_t sArrLen)
{
	char *outHexStr = (char *)malloc(sArrLen * 2 + 1);			//  Allocate memory for string

	for (uint8_t i = 0; i < sArrLen; i++)
	{//  Until end of array
		_snprintf(outHexStr + i * 2, 2, "%02X", hexArr[i]);		//  Set hex equivalent of num to str (_snprintf)
	}

	*(outHexStr + sArrLen * 2) = '\0';							//  Set last char of string to 0

	return outHexStr;
}

char * GetHexStringOfByteArray_Way2(uint8_t *hexArr, uint16_t sArrLen)
{
	char *outHexStr = (char *)malloc(sArrLen * 2 + 1);			//  Allocate memory for string

	for (uint8_t i = 0; i < sArrLen; i++)
	{//  Until end of array
		_itoa(hexArr[i], outHexStr + i * 2, 16);				//  Set hex equivalent of num to str (_itoa)
	}

	*(outHexStr + sArrLen * 2) = '\0';							//  Set last char of string to 0

	return outHexStr;
}