#include "nmplv.h"
#include "malloc32.h"


int nmppsCmpNeC_32s8u (nm32s* src,  int32b  nCmpVal, nm8u* dst,  int size)
{
	Tmp2BuffSpec spec;
	
	spec.buffer0=nmppsMalloc_32s(size);
	spec.buffer1=nmppsMalloc_8s(size);
	
	if (nmppsMallocSuccess()){
		nmppsCmpNeC_32s    ((nm32s*)src,nCmpVal,(nm32s*)spec.buffer0,size);
		nmppsConvert_32s8s ((nm32s*)spec.buffer0,(nm8s*)spec.buffer1,size);
		nmppsSubCRev_8s    ((nm8s*) spec.buffer1,0,(nm8s*)dst,size);
	}
	
	nmppsFree(spec.buffer0);
	nmppsFree(spec.buffer1);
			
	return 0;
}