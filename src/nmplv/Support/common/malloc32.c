#include <malloc.h>
#include "malloc32.h"


#ifdef __NM__
	struct NmppsMalloc32Spec nmppsMalloc32Spec = {{malloc0,malloc1,malloc2,malloc3},MALLOC32_RANDOM_ORDER,0,0,0,0,0,0,0};

#else 
	void* __malloc32(unsigned int sizeInt32){
		return malloc(sizeInt32*4);
	}
	struct NmppsMalloc32Spec nmppsMalloc32Spec = {{__malloc32,__malloc32,__malloc32,__malloc32},MALLOC32_RANDOM_ORDER,0,0,0,0,0,0,0};
#endif 

void* nmppsMalloc32(unsigned sizeInt32){
	void* buffer=0;
	static unsigned randomize=123;
	unsigned heapIndx;
	switch(nmppsMalloc32Spec.orderType){
		case(MALLOC32_FIXED_ORDER):
			heapIndx=0xF&(nmppsMalloc32Spec.fixedOrder>>(nmppsMalloc32Spec.nextFixedIndx<<2));
			if (heapIndx==0xF){
				heapIndx=0xF&nmppsMalloc32Spec.fixedOrder;
				nmppsMalloc32Spec.nextFixedIndx=1;
			}
			else 
				nmppsMalloc32Spec.nextFixedIndx++;
			buffer=nmppsMalloc32Spec.allocator[heapIndx](sizeInt32);
			break;
		case(MALLOC32_PRIOR_ORDER):
			{
				unsigned order=nmppsMalloc32Spec.priorOrder;
				while ((heapIndx=(order&0xF))!=0xF){
					buffer=nmppsMalloc32Spec.allocator[heapIndx](sizeInt32);
					if (buffer)						
						break;
					order>>=4;
				}
			}
			break;

		case(MALLOC32_RANDOM_ORDER):
			{
				unsigned mask=nmppsMalloc32Spec.randomMask;
				while (mask){
					randomize=1664525*randomize+1013904223;
					heapIndx=randomize>>30;
					if (mask&(1<<heapIndx)){
						mask^=(1<<heapIndx);
						buffer=nmppsMalloc32Spec.allocator[heapIndx](sizeInt32);
						if (buffer)
							break;
					}
				}
			}
			break;	
	}
	if (buffer) {
		nmppsMalloc32Spec.numBufAllocated++;
		nmppsMalloc32Spec.allocHistory<<=4;
		nmppsMalloc32Spec.allocHistory|=heapIndx;
	}
	else {
		nmppsMalloc32Spec.status++;
	}
	return buffer;
}

void nmppsFree32(void* buffer){
	if (buffer)
		free(buffer);
}


void nmppsMalloc32Mode(NmppsAllocation order, enum MALLOC32_MODE orderType){
	unsigned heapIndx;
	nmppsMalloc32Spec.orderType=orderType;
	switch(orderType){
		case(MALLOC32_FIXED_ORDER):
			nmppsMalloc32Spec.fixedOrder=order;
			break;
		case(MALLOC32_PRIOR_ORDER):
			nmppsMalloc32Spec.priorOrder=order;
			break;
		case(MALLOC32_RANDOM_ORDER):
			nmppsMalloc32Spec.randomMask=0;
			while ((order&0xF)!=0xF){
				nmppsMalloc32Spec.randomMask|=(1<<(order&0xF));
				order>>=4;
			}
			break;	
	}
}

int  nmppsMalloc32GetHistory(NmppsAllocation* order, int numAllocations)
{
	int i;
	unsigned long long history=nmppsMalloc32Spec.allocHistory;
	if (nmppsMalloc32Spec.numBufAllocated<numAllocations)
		return -1;
	*order=0xFULL;
	
	for(i=0; i <numAllocations; i++){
		*order<<=4;
		*order|=history&0xF;
		history>>=4;
	}

}


/*
void nmppsMalloc32ModeA(unsigned* arr, int size , int orderType){
	
}

void nmppsMalloc32HeapEnable(nmppsAllocation heapMask){
	int heapIndx;
	while ((heapIndx=(heapMask&0xF))!=0xF){
		nmppsMalloc32Mask|=1<<heapIndx;
		heapMask>>=4;
	}
}
void nmppsMalloc32HeapDisable(nmppsAllocation heapMask){
	int heapIndx;
	while ((heapIndx=(heapMask&0xFF))!=0xFF){
		nmppsMalloc32Mask&=~(1<<heapIndx);
		heapMask>>=4;
	}
}


nmppsMalloc32HeapDisable(0xF421);
*/




/*
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
*/
