#ifdef ENABLE_ASSERTE
#include <crtdbg.h>
#define ASSERTE _ASSERTE
#else
#define ASSERTE(expression)
#endif
