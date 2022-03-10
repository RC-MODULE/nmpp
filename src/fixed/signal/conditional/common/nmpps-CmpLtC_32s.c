#include "nmplv.h"
#include "malloc32.h"


//nt nmppsCmpLtC_32s (nm32s* pSrcVec,  int32b  nCmpVal, nm32s* pDstVec,  int nSize, Tmp2BuffSpec *pspec)
//
//	Tmp2BuffSpec s;
//	Tmp2BuffSpec* spec=&s;
//	
//	spec->buffer0=nmppsMalloc_64s(nSize);
//	spec->buffer1=nmppsMalloc_64s(nSize);
//		
//	if (nmppsMallocSuccess()){
//		nmppsConvert_32s64s (pSrcVec, (nm64s*)spec->buffer0, nSize);
//		nmppsCmpLtC_64s63b ((nm64s*)spec->buffer0,nCmpVal,(nm64s*)spec->buffer1,nSize);
//		nmppsConvert_64s32s ((nm64s*)spec->buffer1,pDstVec,nSize);
//	}
//	
//	nmppsFree(spec->buffer0);
//	nmppsFree(spec->buffer1);
//	
//	return 0;
//



int nmppsCmpLtC_32s8um (const nm32s* src,  int32b  nCmpVal, nm8u* dst,  int size, struct NmppsTmpSpec* spec)
{

	struct NmppsTmpSpec localSpec;
	int alloc=0;
	if (spec==0){
		spec=&localSpec;
		spec->buffer0=nmppsMalloc_64s(size);
		spec->buffer1=nmppsMalloc_64s(size);
		if (!nmppsMallocSuccess()) return -1;
		alloc=1;
	}	

	
	if (nmppsMallocSuccess()){
		nmppsConvert_32s64s ((nm32s*)src, (nm64s*)spec->buffer0, size);
		nmppsCmpLtC_64s63b ((nm64s*)spec->buffer0,nCmpVal,(nm64s*)spec->buffer1,size);
		nmppsConvert_64s16s ((nm64s*)spec->buffer1,(nm16s*)spec->buffer0,size);
		nmppsConvert_16s8s ((nm16s*) spec->buffer0,(nm8s*)spec->buffer1,size);
		nmppsSubCRev_8s    ((nm8s*) spec->buffer1,0,(nm8s*)dst,size);
	}
	
	if (alloc){
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);
	}

			
	
	return 0;
}