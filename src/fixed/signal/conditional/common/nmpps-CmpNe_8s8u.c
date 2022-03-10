#include "nmplv.h"
#include "malloc32.h"
int nmppsCmpNe_8s8um (const nm8s* src1, const nm8s* src2, nm8u* dst, int size,  struct NmppsTmpSpec *spec)
{
	struct NmppsTmpSpec localSpec;
	int alloc=0;
	if (spec==0){
		spec=&localSpec;
		spec->buffer0=nmppsMalloc_8s(size);
		if (!nmppsMallocSuccess()) return -1;
		alloc=1;
	}	
		
	nmppsCmpNe_8s   ((nm8s*)src1,(nm8s*)src2,(nm8s*)spec->buffer0,size);
	nmppsSubCRev_8s ((nm8s*)spec->buffer0,0,(nm8s*)dst,size);
	
	if (alloc){
		nmppsFree(spec->buffer0);
	}

	
	return 0;
}



