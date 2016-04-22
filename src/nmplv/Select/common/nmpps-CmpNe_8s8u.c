#include "nmplv.h"
#include "malloc32.h"
int nmppsCmpNe_8s8um (nm8s* src1,nm8s* src2, nm8u* dst, int size)
{
	
	Tmp2BuffSpec spec;
	spec.buffer0=nmppsMalloc_8s(size);
		
	if (nmppsMallocSuccess()){
		nmppsCmpNe_8s   ((nm8s*)src1,(nm8s*)src2,(nm8s*)spec.buffer0,size);
		nmppsSubCRev_8s ((nm8s*)spec.buffer0,0,(nm8s*)dst,size);
	}
	
	nmppsFree(spec.buffer0);
	

	return 0;
}



