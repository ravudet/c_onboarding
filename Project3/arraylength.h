#pragma once

// NOTE: no private header file for macros because these are all hard dependencies; there are no macro "prototypes" that you define in the public header only

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

#ifdef __cplusplus
}
#endif