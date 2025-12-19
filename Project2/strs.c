#include "strs.h"

bool substrcmp(const char x[], const int xStart, const char y[], const int yStart, const int length)
{
	return memcmp(x + xStart, y + yStart, length) == 0;
}