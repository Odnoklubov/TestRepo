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

#define LITTLE_ENDIAN_CODE	0x01
#define BIG_ENDIAN_CODE		0X02
#define ERROR_CODE			0xFF


// TODO: reference additional headers your program requires here
uint8_t GetMachineEndian_way1();
uint8_t GetMachineEndian_way2();