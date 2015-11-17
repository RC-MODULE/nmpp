#include <malloc.h>
#include "malloc32.h"


#ifdef __NM__
	struct NmppsMalloc32Spec nmppsMalloc32Spec = {{malloc0,malloc1,malloc2,malloc3},MALLOC32_PRIORITY_MODE,0xF,0xF3210,0,0,0,0,0,0,0,0,0xF};

#else 
	void* __malloc32(unsigned int sizeInt32){
		return malloc(sizeInt32*4);
	}
	struct NmppsMalloc32Spec nmppsMalloc32Spec = {{__malloc32,__malloc32,__malloc32,__malloc32},MALLOC32_PRIORITY_MODE,0xF,0xF3210,0,0,0,0,0,0,0,0,0xF};
#endif 

void* nmppsMalloc32(unsigned sizeInt32){
	void* buffer=0;
	static unsigned randomize=123;
	unsigned heapIndx;
	switch(nmppsMalloc32Spec.mode){

		case(MALLOC32_ROUTE_MODE):
			heapIndx=0xF&(nmppsMalloc32Spec.routeInternal>>(nmppsMalloc32Spec.routePos<<2));
			nmppsMalloc32Spec.routePos++;
			if (nmppsMalloc32Spec.routePos == nmppsMalloc32Spec.routeSize)
				nmppsMalloc32Spec.routePos=0;
			buffer=nmppsMalloc32Spec.allocator[heapIndx](sizeInt32);
			break;

		case(MALLOC32_LONG_ROUTE_MODE):
			heapIndx=0xF&(nmppsMalloc32Spec.route[nmppsMalloc32Spec.routePos>>4]>>((nmppsMalloc32Spec.routePos&0xF)<<2));
			if (nmppsMalloc32Spec.routePos++ == nmppsMalloc32Spec.routeSize)
				nmppsMalloc32Spec.routePos=0;
			buffer=nmppsMalloc32Spec.allocator[heapIndx](sizeInt32);
			break;

		case(MALLOC32_PRIORITY_MODE):
			{
				unsigned priority=nmppsMalloc32Spec.priority;
				while ((heapIndx=(priority&0xF))!=0xF){
					buffer=nmppsMalloc32Spec.allocator[heapIndx](sizeInt32);
					if (buffer)						
						break;
					priority>>=4;
				}
			}
			break;

		case(MALLOC32_RANDOM_MODE):
			{
				unsigned mask=nmppsMalloc32Spec.random;
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
		nmppsMalloc32Spec.routeHistoryFifo<<=4;
		nmppsMalloc32Spec.routeHistoryFifo|=heapIndx;
		if (nmppsMalloc32Spec.routeHistory){
			if (nmppsMalloc32Spec.routeHistorySize==nmppsMalloc32Spec.fixedHistoryMaxSize){
				nmppsMalloc32Spec.status=-1;
				return buffer;
			}
			nmppsMalloc32Spec.routeHistory[nmppsMalloc32Spec.routeHistorySize>>4] |= heapIndx<<((nmppsMalloc32Spec.routeHistorySize&0xF)<<2);	
		}

		if (nmppsMalloc32Spec.fixedHistory){
			if (nmppsMalloc32Spec.fixedHistorySize==nmppsMalloc32Spec.fixedHistoryMaxSize){
				nmppsMalloc32Spec.status=-1;
				return buffer;
			}
			nmppsMalloc32Spec.fixedHistory[nmppsMalloc32Spec.fixedHistorySize]=buffer;
			nmppsMalloc32Spec.routeSize++;
		}
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

void nmppsMalloc32SetRouteMode (fseq64 heapSeq)
{
	nmppsMalloc32Spec.mode = MALLOC32_ROUTE_MODE;
	nmppsMalloc32Spec.routeInternal=heapSeq;
	nmppsMalloc32Spec.routePos=0;
	nmppsMalloc32Spec.routeSize=0;
	while ((heapSeq&0xF)!=0xF){
		heapSeq>>=4;
		nmppsMalloc32Spec.routeSize++;
		if  (nmppsMalloc32Spec.routeSize==16)
			break;
	}
}
/*
void nmppsMalloc32SetLoFixedMode (uint64  heapSeq,  int heapCount)
{
	nmppsMalloc32Spec.mode = MALLOC32_FIXED_SEQ;
	nmppsMalloc32Spec.fixedOrder=heapSeq;
	nmppsMalloc32Spec.heapCount =heapCount;
}
void nmppsMalloc32SetFixedModeA(uint64* heapSeq,  int heapCount)
{
	//nmppsMalloc32Spec.mode = MALLOC32_FIXED_SEQA;
	//nmppsMalloc32Spec.fixedOrder=heapSeq;
	//nmppsMalloc32Spec.heapCount =heapCount;
}
*/
void nmppsMalloc32SetRandomMode(unsigned  heapSet,int heapCount)
{
	int i;
	int randomSize=0;
	nmppsMalloc32Spec.mode = MALLOC32_RANDOM_MODE;
	nmppsMalloc32Spec.random=0;

	for(i=0; i<heapCount; i++){
		nmppsMalloc32Spec.random|=(1<<(heapSet&0xF));
		heapSet>>=4;
	}
}
void nmppsMalloc32SetPriorityMode (uint64  heapSeq,  int heapCount)
{
	nmppsMalloc32Spec.mode = MALLOC32_PRIORITY_MODE;
	nmppsMalloc32Spec.priority=heapSeq;
}
void nmppsMalloc32SetDirectMode  (void** addrSeq,   int addrCount)
{
	
}
void  nmppsMalloc32StartAddrRec (void** addrSeq,   int maxAddrCount)
{
	
}
int  nmppsMalloc32StopAddrRec()
{

	return 0;
}
void nmppsMalloc32StartHeapRec (uint64* heapSeq,  int maxHeapCount)
{
	
}
int  nmppsMalloc32StopHeapRec()
{
	return 0;
}
void nmppsMalloc32SetBoundary (int size, int fill )
{
	
}
int  nmppsMalloc32CheckBoundary(void* buffer)
{
	return 0;
}
int  nmppsMalloc32IsErrorStatus()
{
	return nmppsMalloc32Spec.status;
}
void  nmppsMalloc32ResetStatus()
{
	nmppsMalloc32Spec.status=0;
}


int   nmppsMalloc32GetHistory   (fseq64*  heapSeq, int seqSize)
{
	int i;
	fifo64 history=nmppsMalloc32Spec.routeHistoryFifo;
	*heapSeq=0xFULL; 
	if (nmppsMalloc32Spec.numBufAllocated<seqSize)
		return -1;
	
	for(i=0; i <seqSize; i++){
		*heapSeq<<=4;
		*heapSeq|=history&0xF;
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
