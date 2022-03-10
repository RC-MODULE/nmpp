#include "nmplv.h"
#include "malloc32.h"
int nmppsCmpNeC_8s8um (const nm8s* src,  int8b  nCmpVal, nm8u* dst,  int size, struct NmppsTmpSpec* spec)
{

	struct NmppsTmpSpec localSpec;
	int alloc=0;
	if (spec==0){
		spec=&localSpec;
		spec->buffer0=nmppsMalloc_8s(size);
		if (!spec->buffer0) return -1;
		alloc=1;
	}
		
	nmppsCmpNeC_8s  ((nm8s*)src,nCmpVal,(nm8s*)spec->buffer0,size);
	nmppsSubCRev_8s ((nm8s*)spec->buffer0,0,(nm8s*)dst,size);
	
	if (alloc){
		nmppsFree(spec->buffer0);
	}
	
	return 0;
}



