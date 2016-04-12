#include "malloc32.h"
#include "nmtype.h"
#include "nmpp.h"
#include "string.h"

#ifdef __NM__
extern nm64u VEC_TBL_Diagonal_01h_G[8];		
#endif

void nmppsClipConvertAddCInitAlloc_16s8s(NmppsWeightState** ppState)
{
	*ppState=nmppsMalloc_64u(8);
	#ifdef __NM__
	memcpy(*ppState,VEC_TBL_Diagonal_01h_G,16);
	#endif
}
void nmppsClipConvertAddCFree(NmppsWeightState* pState)
{
	if (pState)
		nmppsFree(pState);
}
