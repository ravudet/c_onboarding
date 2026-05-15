#pragma once

#include "directories.h"

#if defined _WIN32
#include <direct.h>
#elif defined __linux__
#include <sys/stat.h>
#include <unistd.h>
#endif

#include <errno.h>
#include <stdlib.h>

#include "errors.h"
#include "strs.h"
