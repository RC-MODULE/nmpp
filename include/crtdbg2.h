#ifdef ENABLE_ASSERTE
#ifndef __NM__
#include <crtdbg.h>
#else 
#define _ASSERTE
#endif

#define ASSERTE _ASSERTE
#else
#define ASSERTE(expression)
#endif
