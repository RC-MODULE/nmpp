#include "nmpp.h"


//!
//! \perfinclude _nmppsMalloc__FPPlii_.html
//!

void nmppsMalloc_64s(nm64s** pptr, int nSize, int hint)
//nm64s* nmppsMalloc_nm64s_(int nSize, int hint) 
{
    //if (hint == MEM_GLOBAL)
    //    *pptr = (nm64s*)malloc2(nSize<<1);
    //else 
	//	*pptr = (nm64s*)malloc1(nSize<<1);

	if (hint == HEAP0)
        *pptr = (nm64s*)malloc0(nSize<<1);
    else if (hint== HEAP1)
		*pptr = (nm64s*)malloc1(nSize<<1);
	else if (hint== HEAP2)
		*pptr = (nm64s*)malloc2(nSize<<1);
	else if (hint== HEAP3)
		*pptr = (nm64s*)malloc3(nSize<<1);

}

