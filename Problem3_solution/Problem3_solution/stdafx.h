// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned _int64 uint64_t;

struct uint64
{
	uint32_t MSB;
	uint32_t LSB;
};



// TODO: reference additional headers your program requires here
uint64_t RotateEndianOrder(uint64_t lNum);
struct uint64 RotateEndianOrder_struct(struct uint64 lNum);