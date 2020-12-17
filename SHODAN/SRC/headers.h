#ifndef HEADERS_H
#define HEADERS_H

//debug
#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#include "crtdbg.h"
#endif

//std
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdarg.h"
#include "ctype.h"
#include "math.h"
#include "float.h"
#include "string.h"
#include "time.h"

/************/
/* COMPILER */
/************/
#if defined(_MSC_VER)
#include "../SDL2/VS/INCLUDE/SDL.h"
#endif

#if defined(__MINGW32__)
#include "../SDL2/MINGW/INCLUDE/SDL.h"
#endif

#if defined(__unix__)
#include "SDL2/SDL.h"
#endif

#endif