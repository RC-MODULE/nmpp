#include "nmplv.h"
#include "malloc32.h"


int nmppsCmpNeC_32s8um (const nm32s* src,  int32b  nCmpVal, nm8u* dst,  int size,  struct NmppsTmpSpec* spec)
{
	struct NmppsTmpSpec localSpec;
	int alloc=0;
	if (spec==0){
		spec=&localSpec;
		spec->buffer0=nmppsMalloc_32s(size);
		spec->buffer1=nmppsMalloc_8s(size);
		if (!nmppsMallocSuccess()) return -1;
		alloc =1;
	}
	
	nmppsCmpNeC_32s    ((nm32s*)src,nCmpVal,(nm32s*)spec->buffer0,size);
	nmppsConvert_32s8s ((nm32s*)spec->buffer0,(nm8s*)spec->buffer1,size);
	nmppsSubCRev_8s    ((nm8s*) spec->buffer1,0,(nm8s*)dst,size);
	
	if (alloc){
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);
	}
			
	return 0;
}