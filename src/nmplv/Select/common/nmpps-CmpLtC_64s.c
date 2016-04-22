#include "nmplv.h"
#include "malloc32.h"

int nmppsCmpLtC_64s (nm64s* pSrcVec,  int64b  nCmpVal, nm64s* pDstVec,  int nSize, Tmp2BuffSpec *pspec)
{

	nmppsCmpLtC_64s63b(pSrcVec,nCmpVal,pDstVec,nSize);
	
	return 0;
}


int nmppsCmpLtC_64s8u (nm64s* src,  int64b  nCmpVal, nm8u* dst,  int size)
{
	Tmp2BuffSpec spec;
	
	spec.buffer0=nmppsMalloc_64s(size);
	spec.buffer1=nmppsMalloc_64s(size);
	
	if (nmppsMallocSuccess()){
		nmppsCmpLtC_64s63b ((nm64s*)src,nCmpVal,(nm64s*)spec.buffer0,size);
		nmppsConvert_64s16s((nm64s*)spec.buffer0,(nm16s*)spec.buffer1,size);
		nmppsConvert_16s8s ((nm16s*)spec.buffer1,(nm8s*)spec.buffer0,size);
		nmppsSubCRev_8s    ((nm8s*) spec.buffer0,0,(nm8s*)dst,size);
	}
	nmppsFree(spec.buffer1);		
	nmppsFree(spec.buffer0);		
		
			
	return 0;
}