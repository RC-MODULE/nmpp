#include "time.h"
#include "nmplv.h"
#include "malloc32.h"

int nmppsMin_16sm (const nm16s* pSrcVec,  int size, int16b* pMinValue, nm32s *tmp)
{
	int alloc=0;
	if (tmp==0){
		tmp=nmppsMalloc_32s(size);
		if (tmp==0) return -1;
		alloc=1;
	}	
		
	nmppsConvert_16s32s (pSrcVec, tmp, size);
	nmppsMin_32s31b    (tmp,size,pMinValue);
	
	if (alloc){
		nmppsFree(tmp);
	}

	return 0;
}


