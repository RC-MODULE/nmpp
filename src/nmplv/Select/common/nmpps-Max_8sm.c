#include "time.h"
#include "nmplv.h"
#include "malloc32.h"

int nmppsMax_8sm (const nm8s* pSrcVec,  int size, int8b* pMaxValue, nm16s* tmp)
{
	int alloc=0;
	if (tmp==0){
		tmp=nmppsMalloc_16s(size);
		if (tmp==0) return -1;
		alloc=1;
	}	
		
	nmppsConvert_8s16s (pSrcVec, tmp, size);
	nmppsMax_16s15b    (tmp,size,pMaxValue);
	
	if (alloc){
		nmppsFree(tmp);
	}

	return 0;
}


