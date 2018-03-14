#include "nmpls.h"
#include "nmpp.h"
#include "string.h"

#ifdef __cplusplus
		extern "C" {
#endif

void nmppsFIRFree(NmppsFIRState* pState)
{
	nmppsFree(pState);
}

#ifdef __cplusplus
		};
#endif