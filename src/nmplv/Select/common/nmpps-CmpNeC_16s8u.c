#include "nmplv.h"
#include "malloc32.h"

int nmppsCmpNeC_16s8u (nm16s* src,  int16b  nCmpVal, nm8u* dst,  int size)
{
	Tmp2BuffSpec spec;
	
	spec.buffer0=nmppsMalloc_16s(size);
	spec.buffer1=nmppsMalloc_8s(size);
			
	if (nmppsMallocSuccess()){
		nmppsCmpNeC_16s    ((nm16s*)src,nCmpVal,(nm16s*) spec.buffer0,size);
		nmppsConvert_16s8s ((nm16s*)spec.buffer0,(nm8s*)spec.buffer1,size);
		nmppsSubCRev_8s    ((nm8s*)spec.buffer1,0,(nm8s*)dst,size);
	}
	
	nmppsFree(spec.buffer0);
	nmppsFree(spec.buffer1);


	return 0;
}
