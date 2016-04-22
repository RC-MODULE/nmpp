#include "nmplv.h"
#include "malloc32.h"

int nmppsCmpLt_64s8um (nm64s* src1,nm64s* src2, nm8u* dst,  int size)
{
	Tmp2BuffSpec s;
	Tmp2BuffSpec* spec=&s;
	
	spec->buffer0=nmppsMalloc_64s(size);
	spec->buffer1=nmppsMalloc_16s(size);
	
	if (nmppsMallocSuccess()){
		nmppsCmpLt_64s    ((nm64s*)src1,(nm64s*)src2, (nm64s*)spec->buffer0,size);
		nmppsConvert_64s16s((nm64s*)spec->buffer0,  (nm16s*)spec->buffer1,size);
		nmppsConvert_16s8s ((nm16s*)spec->buffer1,  (nm8s*) spec->buffer0,size);
		nmppsSubCRev_8s    ((nm8s*) spec->buffer0,0,(nm8s*) dst,size);
	}
	nmppsFree(spec->buffer1);		
	nmppsFree(spec->buffer0);		
		

	return 0;
}