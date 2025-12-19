#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

enum substringError
{
	substringError_BUG = 1,
	substringError_ENOMEM,
};
enum substringError substring(const char string[], const int endIndex, char* substringPointer[]);

bool substrcmp(const char x[], const int xStart, const char y[], const int yStart, const int length);