#pragma once

// NOTE: no private header file for macros because these are all hard dependencies; there are no macro "prototypes" that you define in the public header only

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))