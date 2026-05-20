#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

enum substringError
{
	substringError_BUG = 1,
	substringError_ENOMEM,
};
enum substringError substring(const char string[], const int endIndex, char* substringPointer[]);

bool substrcmp(const char x[], const int xStart, const char y[], const int yStart, const int length);

#ifdef __cplusplus
}
#endif