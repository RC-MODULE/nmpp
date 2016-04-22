#include "nmplv.h"
#include "malloc32.h"

int nmppsCmpLt_32s8um (nm32s* src1, nm32s* src2, nm8u* dst,  int size)
{
	Tmp2BuffSpec spec;
	
	spec.buffer0=nmppsMalloc_64s(size);
	spec.buffer1=nmppsMalloc_64s(size);
		
	if (nmppsMallocSuccess()){
		nmppsConvert_32s64s  ((nm32s*)src1,(nm64s*)spec.buffer0,size);
		nmppsConvert_32s64s  ((nm32s*)src2,(nm64s*)spec.buffer1,size);
		nmppsCmpLt_64s       ((nm64s*)spec.buffer0,(nm64s*)spec.buffer1,(nm64s*)spec.buffer1,size);
		nmppsConvert_64s16s  ((nm64s*)spec.buffer1,(nm16s*) spec.buffer0,size);
		nmppsConvert_16s8s   ((nm16s*)spec.buffer0,(nm8s*) spec.buffer1,size);
		nmppsSubCRev_8s      ((nm8s*)spec.buffer1,0,(nm8s*)dst,size);
	}
	
	nmppsFree(spec.buffer0);
	nmppsFree(spec.buffer1);
	
	return 0;
}