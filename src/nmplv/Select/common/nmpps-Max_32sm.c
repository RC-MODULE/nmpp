#include "time.h"
#include "nmplv.h"
#include "malloc32.h"

int nmppsMax_32sm (const nm32s* pSrcVec,  int size, int32b* pMaxValue, nm64s* tmp)
{
	int alloc=0;
	int64b max;
	if (tmp==0){
		tmp=nmppsMalloc_64s(size);
		if (tmp==0) return -1;
		alloc=1;
	}	
		
	nmppsConvert_32s64s (pSrcVec, tmp, size);
	nmppsMax_64s63b    (tmp,size,&max);
	*pMaxValue=max;
	
	if (alloc){
		nmppsFree(tmp);
	}

	return 0;
}


