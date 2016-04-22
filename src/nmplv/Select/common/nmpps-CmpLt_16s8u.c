#include "nmplv.h"
#include "malloc32.h"


int nmppsCmpLt_16s8um (nm16s* src1, nm16s* src2, nm8u* dst,  int size)
{
	Tmp2BuffSpec spec;
		
	spec.buffer0=nmppsMalloc_32s(size);
	spec.buffer1=nmppsMalloc_32s(size);
	
	if (nmppsMallocSuccess()){
		nmppsConvert_16s32s  ((nm16s*)src1,(nm32s*)spec.buffer0,size);
		nmppsConvert_16s32s  ((nm16s*)src2,(nm32s*)spec.buffer1,size);
		nmppsCmpLt_32s       ((nm32s*)spec.buffer0,(nm32s*)spec.buffer1,(nm32s*)spec.buffer1,size);
		nmppsConvert_32s8s   ((nm32s*)spec.buffer1,(nm8s*) spec.buffer0,size);
		nmppsSubCRev_8s      ((nm8s*)spec.buffer0,0,(nm8s*)dst,size);
	}
	
	
	nmppsFree(spec.buffer0);
	nmppsFree(spec.buffer1);
	
	return 0;
}
