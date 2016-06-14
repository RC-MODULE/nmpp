#include "time.h"
#include "nmplv.h"
#include "malloc32.h"

int nmppsMin_32sm (const nm32s* pSrcVec,  int size, int32b* pMinValue, nm64s* tmp)
{
	int64b min;
	int alloc=0;
	if (tmp==0){
		tmp=nmppsMalloc_64s(size);
		if (tmp==0) return -1;
		alloc=1;
	}	
		
	nmppsConvert_32s64s (pSrcVec, tmp, size);
	nmppsMin_64s63b    (tmp,size,&min);
	*pMinValue=min;
	
	if (alloc){
		nmppsFree(tmp);
	}

	return 0;
}


