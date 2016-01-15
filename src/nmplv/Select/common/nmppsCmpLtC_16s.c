#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"


int nmppsCmpLtC_16s (nm16s* pSrcVec,  int16b  nCmpVal, nm16s* pDstVec,  int nSize, Tmp2BuffSpec *pspec)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpLtC_16s",pSrcVec,nCmpVal,pDstVec,nSize,2);
	#else

	Tmp2BuffSpec s;
	Tmp2BuffSpec* spec=&s;
	
	spec->buffer0=nmppsMalloc_32s(nSize);
	spec->buffer1=nmppsMalloc_32s(nSize);
		
	if (nmppsMallocSuccess()){
		nmppsConvert_16s32s (pSrcVec, (nm32s*)spec->buffer0, nSize);
		nmppsCmpLtC_32s31b ((nm32s*)spec->buffer0,nCmpVal,(nm32s*)spec->buffer1,nSize);
		nmppsConvert_32s16s ((nm32s*)spec->buffer1,pDstVec,nSize);
	}
	
	nmppsFree(spec->buffer0);
	nmppsFree(spec->buffer1);
	
	#endif
	
	return 0;
}
