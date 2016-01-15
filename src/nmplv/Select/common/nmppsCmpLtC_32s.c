#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"


int nmppsCmpLtC_32s (nm32s* pSrcVec,  int32b  nCmpVal, nm32s* pDstVec,  int nSize, Tmp2BuffSpec *pspec)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpLtC_32s",pSrcVec,nCmpVal,pDstVec,nSize,4);
	#else

	Tmp2BuffSpec s;
	Tmp2BuffSpec* spec=&s;
	
	spec->buffer0=nmppsMalloc_64s(nSize);
	spec->buffer1=nmppsMalloc_64s(nSize);
		
	if (nmppsMallocSuccess()){
		nmppsConvert_32s64s (pSrcVec, (nm64s*)spec->buffer0, nSize);
		nmppsCmpLtC_64s63b ((nm64s*)spec->buffer0,nCmpVal,(nm64s*)spec->buffer1,nSize);
		nmppsConvert_16s32s ((nm16s*)spec->buffer1,pDstVec,nSize);
	}
	
	nmppsFree(spec->buffer0);
	nmppsFree(spec->buffer1);
	
	#endif
	
	return 0;
}
