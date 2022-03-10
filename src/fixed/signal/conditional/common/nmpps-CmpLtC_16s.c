#include "nmplv.h"
#include "malloc32.h"

//int nmppsCmpLtC_16s (nm16s* src,  int16b  nCmpVal, nm16s* dst,  int size, Tmp2BuffSpec *pspec)
//{
//	Tmp2BuffSpec s;
//	Tmp2BuffSpec* spec=&s;
//	
//	spec->buffer0=nmppsMalloc_32s(size);
//	spec->buffer1=nmppsMalloc_32s(size);
//		
//	if (nmppsMallocSuccess()){
//		nmppsConvert_16s32s (src, (nm32s*)spec->buffer0, size);
//		nmppsCmpLtC_32s31b ((nm32s*)spec->buffer0,nCmpVal,(nm32s*)spec->buffer1,size);
//		nmppsConvert_32s16s ((nm32s*)spec->buffer1,dst,size);
//	}
//	
//	nmppsFree(spec->buffer0);
//	nmppsFree(spec->buffer1);
//
//	return 0;
//}
//
int nmppsCmpLtC_16s8um (const nm16s* src,  int16b  nCmpVal, nm8u* dst,  int size, struct NmppsTmpSpec* spec)
{
	struct NmppsTmpSpec localSpec;
	int alloc=0;
	if (spec==0){
		spec=&localSpec;
		spec->buffer0=nmppsMalloc_32s(size);
		spec->buffer1=nmppsMalloc_32s(size);
		if (!nmppsMallocSuccess()) return -1;
		alloc=1;
	}	
	
	if (nmppsMallocSuccess()){
		nmppsConvert_16s32s((nm16s*)src, (nm32s*)spec->buffer0, size);
		nmppsCmpLtC_32s31b ((nm32s*)spec->buffer0,nCmpVal,(nm32s*)spec->buffer1,size);
		nmppsConvert_32s8s ((nm32s*)spec->buffer1,(nm8s*)spec->buffer0,size);
		nmppsSubCRev_8s    ((nm8s*)spec->buffer0,0,(nm8s*)dst,size);
	}
	
	if (alloc){
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);
	}
	
	return 0;
}
