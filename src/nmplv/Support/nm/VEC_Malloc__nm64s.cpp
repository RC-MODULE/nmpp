#include "nmplv.h"


//!
//! \perfinclude _VEC_Malloc__FPPlii.html
//!

void VEC_Malloc(nm64s** pptr, int nSize, int hint)
//nm64s* VEC_Malloc_nm64s(int nSize, int hint) 
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

