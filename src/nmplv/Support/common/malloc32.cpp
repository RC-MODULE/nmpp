#include <malloc.h>
#include "malloc32.h"

void* malloc32(unsigned size_int32 )
{
#ifdef __NM__
	return malloc(size_int32); 
#else
	return malloc(size_int32*4);
#endif
}

void* malloc32 (unsigned size_int32, unsigned bank_mask)
{
#ifdef __NM__
	void* p;
	if (bank_mask&HEAP_0){
		p= malloc0(size_int32);	// Memory allocation in heap0 
		if (p) return p;
	}
	if (bank_mask&HEAP_1){
		p= malloc1(size_int32);  // Memory allocation in heap1
		if (p) return p;
	}
	if (bank_mask&HEAP_2){
		p= malloc2(size_int32);	// Memory allocation in heap2
		if (p) return p;
	}
	if (bank_mask&HEAP_3){
		p= malloc3(size_int32);	// Memory allocation in heap3
		if (p) return p;
	}
	return 0;
#else
	return malloc(size_int32*4);
#endif	
}

void free32(void* p)
{
	free(p);
}

