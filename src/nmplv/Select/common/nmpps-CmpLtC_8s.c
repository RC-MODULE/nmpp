#include "time.h"
#include "nmplv.h"
#include "malloc32.h"
int nmppsCmpLtC_8s8um (const nm8s* pSrcVec,  int8b  nCmpVal, nm8s* pDstVec,  int size, struct NmppsTmpSpec *spec)
{
	struct NmppsTmpSpec localSpec;
	int alloc=0;
	if (spec==0){
		spec=&localSpec;
		spec->buffer0=nmppsMalloc_16s(size);
		spec->buffer1=nmppsMalloc_16s(size);
		if (!nmppsMallocSuccess()) return -1;
		alloc=1;
	}	
		
	if (nmppsMallocSuccess()){
		nmppsConvert_8s16s ((nm8s*)pSrcVec, (nm16s*)spec->buffer0, size);
		nmppsCmpLtC_16s15b ((nm16s*)spec->buffer0,nCmpVal,(nm16s*)spec->buffer1,size);
		nmppsConvert_16s8s ((nm16s*)spec->buffer1,pDstVec,size);
	}
	
	if (alloc){
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);
	}

	
	return 0;
}






	/*
	void nmppsCmpLtC_16s     (nm16s* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int size, Tmp2BuffSpec *spec);
	void nmppsCmpLtC_32s     (nm32s* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int size, Tmp2BuffSpec *spec);
	void nmppsCmpLtC_64s     (nm64s* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int size, Tmp2BuffSpec *spec);
	
	
int nmppsCmpLtC_8s8u (nm8s* src,  int32b  nCmpVal, nm8u* dst,  int size)
{
	Tmp2BuffSpec spec;
	
	spec.buffer0=nmppsMalloc_16s(size);
	spec.buffer1=nmppsMalloc_16s(size);
	
	if (nmppsMallocSuccess()){
		nmppsConvert_8s16s (src, (nm16s*)spec.buffer0, size);
		nmppsCmpLtC_16s15b ((nm16s*)spec.buffer0,nCmpVal,(nm16s*)spec.buffer1,size);
		nmppsConvert_16s8s ((nm16s*)spec.buffer1,(nm8s*)spec.buffer0,size);
		nmppsSubCRev_8s    ((nm8s*)spec.buffer0,0,(nm8s*)dst,size);
	}
	
	nmppsFree(spec.buffer0);
	nmppsFree(spec.buffer1);
			

	return 0;
}	*/