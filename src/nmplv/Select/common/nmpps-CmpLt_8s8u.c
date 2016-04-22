#include "nmplv.h"
#include "malloc32.h"
int nmppsCmpLt_8s8um (nm8s* src1,nm8s* src2, nm8u* dst, int size)
{
	
	Tmp2BuffSpec spec;
	spec.buffer0=nmppsMalloc_16s(16);
	spec.buffer1=nmppsMalloc_16s(16);
	
		
	if (nmppsMallocSuccess()){
		nmppsConvert_8s16s   ((nm8s*)src1,(nm16s*)spec.buffer0,size);
		nmppsConvert_8s16s   ((nm8s*)src2,(nm16s*)spec.buffer1,size);
		nmppsCmpLt_16s       ((nm16s*)spec.buffer0,(nm16s*)spec.buffer1,(nm16s*)spec.buffer1,size);
		nmppsConvert_16s8s   ((nm16s*)spec.buffer1,(nm8s*)spec.buffer0,size);
		nmppsSubCRev_8s      ((nm8s*)spec.buffer0,0,(nm8s*)dst,size);
	}
	nmppsFree(spec.buffer1);
	nmppsFree(spec.buffer0);
		
	
	return 0;
}



