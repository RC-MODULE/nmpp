#include "time.h"
#include "nmplv.h"
#include "malloc32.h"

int nmppsMin_8sm (const nm8s* pSrcVec,  int size, int8b* pMinValue, nm16s *tmp)
{
	int alloc=0;
	if (tmp==0){
		tmp=nmppsMalloc_16s(size);
		if (tmp==0) return -1;
		alloc=1;
	}	
		
	nmppsConvert_8s16s (pSrcVec, tmp, size);
	nmppsMin_16s15b    (tmp,size,pMinValue);
	
	if (alloc){
		nmppsFree(tmp);
	}

	return 0;
}


