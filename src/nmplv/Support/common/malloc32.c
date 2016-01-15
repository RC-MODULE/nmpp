#include <malloc.h>
#include "malloc32.h"

#ifdef __NM__
	__INLINE__ void* malloc32(unsigned sizeInt32) { return malloc(sizeInt32);}
#else 
	__INLINE__ void* malloc32(unsigned sizeInt32) { return malloc(sizeInt32*4);}
#endif

#ifdef __NM__
	struct NmppsMallocSpec nmppsMallocSpec = {{malloc0,malloc1,malloc2,malloc3},MALLOC32_PRIORITY_MODE,0xF,0xF3210,0,0,0,0,0,0,0,0,0xF};

#else 
	void* __malloc32(unsigned int sizeInt32){
		return malloc(sizeInt32*4);
	}
	struct NmppsMallocSpec nmppsMallocSpec = {{__malloc32,__malloc32,__malloc32,__malloc32},MALLOC32_PRIORITY_MODE,0xF,0xF3210,0,0,0,0,0,0,0,0,0xF};
#endif 

void* nmppsMalloc32(unsigned sizeInt32){
	void* buffer=0;
	static unsigned randomize=123;
	unsigned heapIndx;
	switch(nmppsMallocSpec.mode){

		case(MALLOC32_ROUTE_MODE):
			heapIndx=0xF&(nmppsMallocSpec.routeInternal>>(nmppsMallocSpec.routePos<<2));
			nmppsMallocSpec.routePos++;
			if (nmppsMallocSpec.routePos == nmppsMallocSpec.routeSize)
				nmppsMallocSpec.routePos=0;
			buffer=nmppsMallocSpec.allocator[heapIndx](sizeInt32);
			break;

		case(MALLOC32_LONG_ROUTE_MODE):
			heapIndx=0xF&(nmppsMallocSpec.route[nmppsMallocSpec.routePos>>4]>>((nmppsMallocSpec.routePos&0xF)<<2));
			if (nmppsMallocSpec.routePos++ == nmppsMallocSpec.routeSize)
				nmppsMallocSpec.routePos=0;
			buffer=nmppsMallocSpec.allocator[heapIndx](sizeInt32);
			break;

		case(MALLOC32_PRIORITY_MODE):
			{
				unsigned priority=nmppsMallocSpec.priority;
				while ((heapIndx=(priority&0xF))!=0xF){
					buffer=nmppsMallocSpec.allocator[heapIndx](sizeInt32);
					if (buffer)						
						break;
					priority>>=4;
				}
			}
			break;

		case(MALLOC32_RANDOM_MODE):
			{
				unsigned mask=nmppsMallocSpec.random;
				while (mask){
					randomize=1664525*randomize+1013904223;
					heapIndx=randomize>>30;
					if (mask&(1<<heapIndx)){
						mask^=(1<<heapIndx);
						buffer=nmppsMallocSpec.allocator[heapIndx](sizeInt32);
						if (buffer)
							break;
					}
				}
			}
			break;	
	}
	if (buffer) {
		nmppsMallocSpec.numBufAllocated++;
		nmppsMallocSpec.routeHistoryFifo<<=4;
		nmppsMallocSpec.routeHistoryFifo|=heapIndx;
		if (nmppsMallocSpec.routeHistory){
			if (nmppsMallocSpec.routeHistorySize==nmppsMallocSpec.fixedHistoryMaxSize){
				nmppsMallocSpec.status=-1;
				return buffer;
			}
			nmppsMallocSpec.routeHistory[nmppsMallocSpec.routeHistorySize>>4] |= heapIndx<<((nmppsMallocSpec.routeHistorySize&0xF)<<2);	
		}

		if (nmppsMallocSpec.fixedHistory){
			if (nmppsMallocSpec.fixedHistorySize==nmppsMallocSpec.fixedHistoryMaxSize){
				nmppsMallocSpec.status=-1;
				return buffer;
			}
			nmppsMallocSpec.fixedHistory[nmppsMallocSpec.fixedHistorySize]=buffer;
			nmppsMallocSpec.routeSize++;
		}
	}
	else {
		nmppsMallocSpec.status++;
	}
	return buffer;
}

void nmppsFree32(void* buffer){
	if (buffer)
		free(buffer);
}

void nmppsMallocSetRouteMode (fseq64 heapSeq)
{
	nmppsMallocSpec.mode = MALLOC32_ROUTE_MODE;
	nmppsMallocSpec.routeInternal=heapSeq;
	nmppsMallocSpec.routePos=0;
	nmppsMallocSpec.routeSize=0;
	while ((heapSeq&0xF)!=0xF){
		heapSeq>>=4;
		nmppsMallocSpec.routeSize++;
		if  (nmppsMallocSpec.routeSize==16)
			break;
	}
}
/*
void nmppsMalloc32SetLoFixedMode (uint64  heapSeq,  int heapCount)
{
	nmppsMalloc32Spec.mode = MALLOC32_FIXED_SEQ;
	nmppsMallocSpec.fixedOrder=heapSeq;
	nmppsMallocSpec.heapCount =heapCount;
}
void nmppsMallocSetFixedModeA(uint64* heapSeq,  int heapCount)
{
	//nmppsMallocSpec.mode = MALLOC32_FIXED_SEQA;
	//nmppsMallocSpec.fixedOrder=heapSeq;
	//nmppsMallocSpec.heapCount =heapCount;
}
*/
void nmppsMallocSetRandomMode(unsigned  heapSet,int heapCount)
{
	int i;
	int randomSize=0;
	nmppsMallocSpec.mode = MALLOC32_RANDOM_MODE;
	nmppsMallocSpec.random=0;

	for(i=0; i<heapCount; i++){
		nmppsMallocSpec.random|=(1<<(heapSet&0xF));
		heapSet>>=4;
	}
}
void nmppsMallocSetPriorityMode (uint64  heapSeq,  int heapCount)
{
	nmppsMallocSpec.mode = MALLOC32_PRIORITY_MODE;
	nmppsMallocSpec.priority=heapSeq;
}
void nmppsMallocSetDirectMode  (void** addrSeq,   int addrCount)
{
	
}
void  nmppsMallocStartAddrRec (void** addrSeq,   int maxAddrCount)
{
	
}
int  nmppsMallocStopAddrRec()
{

	return 0;
}
void nmppsMallocStartHeapRec (uint64* heapSeq,  int maxHeapCount)
{
	
}
int  nmppsMallocStopHeapRec()
{
	return 0;
}
void nmppsMallocSetBoundary (int size, int fill )
{
	
}
int  nmppsMallocCheckBoundary(void* buffer)
{
	return 0;
}
int  nmppsMallocIsErrorStatus()
{
	return nmppsMallocSpec.status;
}
int  nmppsMallocSuccess()
{
	return nmppsMallocSpec.status==0;
}

void  nmppsMallocResetStatus()
{
	nmppsMallocSpec.status=0;
}

int  nmppsMallocStatus()
{
	return nmppsMallocSpec.status;
}


int   nmppsMallocGetHistory   (fseq64*  heapSeq, int seqSize)
{
	int i;
	fifo64 history=nmppsMallocSpec.routeHistoryFifo;
	*heapSeq=0xFULL; 
	if (nmppsMallocSpec.numBufAllocated<seqSize)
		return -1;
	
	for(i=0; i <seqSize; i++){
		*heapSeq<<=4;
		*heapSeq|=history&0xF;
		history>>=4;
	}
}


/*
void nmppsMallocModeA(unsigned* arr, int size , int orderType){
	
}

void nmppsMallocHeapEnable(nmppsAllocation heapMask){
	int heapIndx;
	while ((heapIndx=(heapMask&0xF))!=0xF){
		nmppsMallocMask|=1<<heapIndx;
		heapMask>>=4;
	}
}
void nmppsMallocHeapDisable(nmppsAllocation heapMask){
	int heapIndx;
	while ((heapIndx=(heapMask&0xFF))!=0xFF){
		nmppsMallocMask&=~(1<<heapIndx);
		heapMask>>=4;
	}
}


nmppsMallocHeapDisable(0xF421);
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

nm8s*  nmppsMalloc_8s (unsigned sizeInt8) { return (nm8s*)  nmppsMalloc32((sizeInt8+7)/4);}
nm8u*  nmppsMalloc_8u (unsigned sizeInt8) { return (nm8u*)  nmppsMalloc32((sizeInt8+7)/4);}
nm16s* nmppsMalloc_16s(unsigned sizeInt16){ return (nm16s*) nmppsMalloc32((sizeInt16+3)/2);}
nm16u* nmppsMalloc_16u(unsigned sizeInt16){ return (nm16u*) nmppsMalloc32((sizeInt16+3)/2);}
nm32s* nmppsMalloc_32s(unsigned sizeInt32){ return (nm32s*) nmppsMalloc32(sizeInt32+(1&sizeInt32));}
nm32u* nmppsMalloc_32u(unsigned sizeInt32){ return (nm32u*) nmppsMalloc32(sizeInt32+(1&sizeInt32));}
nm64s* nmppsMalloc_64s(unsigned sizeInt64){ return (nm64s*) nmppsMalloc32((sizeInt64)<<1);}
nm64u* nmppsMalloc_64u(unsigned sizeInt64){ return (nm64u*) nmppsMalloc32((sizeInt64)<<1);}