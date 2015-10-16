#include "nmplv.h"


void VEC_Malloc(nm64s** pptr, int nSize, int hint)
//nm64s* VEC_Malloc_nm64s(int size, int hint) 
{
    __int64* ptr =(__int64*) malloc(nSize*8);
//    return (nm64s*) ptr;
		*pptr=(nm64s*) ptr;
}

