#include "nmplv.h"
#include "malloc32.h"
int nmppsCmpLt_8s8um (const nm8s* src1,const nm8s* src2, nm8u* dst, int size, struct NmppsTmpSpec* spec )
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

		
	nmppsConvert_8s16s   ((nm8s*)src1,(nm16s*)spec->buffer0,size);
	nmppsConvert_8s16s   ((nm8s*)src2,(nm16s*)spec->buffer1,size);
	nmppsCmpLt_16s       ((nm16s*)spec->buffer0,(nm16s*)spec->buffer1,(nm16s*)spec->buffer1,size);
	nmppsConvert_16s8s   ((nm16s*)spec->buffer1,(nm8s*)spec->buffer0,size);
	nmppsSubCRev_8s      ((nm8s*)spec->buffer0,0,(nm8s*)dst,size);
	
	if (alloc){
		nmppsFree(spec->buffer1);
		nmppsFree(spec->buffer0);
	}
		
	
	return 0;
}



