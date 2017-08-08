// Problem2_solution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	uint8_t machineEndianCode1 = GetMachineEndian_way1();
	uint8_t machineEndianCode2 = GetMachineEndian_way2();

	if (machineEndianCode1 != machineEndianCode2)
	{
		printf("Some error happened.");
		getchar();
		return 0;
	}

	switch (machineEndianCode1)
	{
	case LITTLE_ENDIAN_CODE:
		printf("Answer: Little Endian.");
		getchar();
		break;
	case BIG_ENDIAN_CODE:
		printf("Answer: Big Endian.");
		getchar();
		break;
	default:
		printf("Some error happened.");
		getchar();
		break;
	}

	return 0;
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

	sNum = *(__int16 *)aBuf;		//  Convert aBuf to __int16

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