// Problem1_solution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//  The solution consist two functions - two way of code changing
	uint8_t st = 0;
	uint8_t res1, res2;

	res1 = ChangedWithoutOperators_Way1(st);
	res2 = ChangedWithoutOperators_Way2(st);

	printf("st == %d\r\nres1 = %d\r\nres2 = %d\r\n", st, res1, res2);
	getchar();

	return 0;
}

uint8_t ChangedWithoutOperators_Way1(uint8_t st)
{
	const uint8_t arr[7] = { 26, 65, 234, 31, 25, 25, 25 };				//  Change 'switch' to byte array
	uint8_t result;

	result = arr[st];

	return result;
}

uint8_t ChangedWithoutOperators_Way2(uint8_t st)
{
	const char arr[8] = "\x1a\x41\xea\x1f\x19\x19\x19";					//  Change 'switch' to byte array
	uint8_t result;

	result = arr[st];

	return result;
}