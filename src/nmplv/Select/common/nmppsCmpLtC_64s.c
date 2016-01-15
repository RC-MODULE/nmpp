#include "rpc-host.h"
#include "nmplv.h"

#include "malloc32.h"
#include "time.h"


int nmppsCmpLtC_64s (nm64s* pSrcVec,  int64b  nCmpVal, nm64s* pDstVec,  int nSize, Tmp2BuffSpec *pspec)
{
	#ifdef RPC
	RPC_HOST_PLPI("nmppsCmpLtC_64s",pSrcVec,nCmpVal,pDstVec,nSize,8);
	#else

	nmppsCmpLtC_64s63b(pSrcVec,nCmpVal,pDstVec,nSize);
	
	#endif
	
	return 0;
}

