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

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))		//  Gets number of array elements


// TODO: reference additional headers your program requires here
char * GetHexStringOfByteArray_Way1(uint8_t *hexArr, uint16_t sArrLen);
char * GetHexStringOfByteArray_Way2(uint8_t *hexArr, uint16_t sArrLen);