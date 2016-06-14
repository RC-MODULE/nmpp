#include "time.h"
#include "nmplv.h"
#include "malloc32.h"

int nmppsMax_16sm (const nm16s* pSrcVec,  int size, int16b* pMaxValue, nm32s *tmp)
{
	int alloc=0;
	if (tmp==0){
		tmp=nmppsMalloc_32s(size);
		if (tmp==0) return -1;
		alloc=1;
	}	
		
	nmppsConvert_16s32s (pSrcVec, tmp, size);
	nmppsMax_32s31b    (tmp,size,pMaxValue);
	
	if (alloc){
		nmppsFree(tmp);
	}

	return 0;
}


