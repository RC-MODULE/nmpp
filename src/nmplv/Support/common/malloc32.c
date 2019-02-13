#include <malloc.h>
#include "malloc32.h"
#include "nmplv/vSupport.h"
#include "nmplv/vInit.h"
#include "nmplv/vBitwise.h"


//#ifdef __NM__
//	__INLINE__ void* malloc32(unsigned sizeInt32) { return malloc(sizeInt32);}
//#else 
//	__INLINE__ void* malloc32(unsigned sizeInt32) { return malloc(sizeInt32*4);}
//#endif

#ifdef __NM__
	struct NmppsMallocSpec nmppsMallocSpec = {{malloc0,   malloc1,   malloc2,   malloc3},   MALLOC32_RING_MODE,0xF,0xF3210,0,0,0,0,0,0,0,0,0,1};

#else 
	void* __malloc32(unsigned int sizeInt32){
		return malloc(sizeInt32*4);
	}
	struct NmppsMallocSpec nmppsMallocSpec = {{__malloc32,__malloc32,__malloc32,__malloc32},MALLOC32_RING_MODE,0xF,0xF3210,0,0,0,0,0,0,0,0,0xF,1};
#endif 

int nmppsMallocBorder32=0;
/*
void* nmppsMalloc32(unsigned sizeInt32){
	int* buffer=0;
	//static unsigned randomize=123;
	unsigned heapIndx,i;
	
	
	switch(nmppsMallocSpec.mode){
		case(MALLOC32_HISTORY_MODE):
		{
			buffer=(int*)nmppsMallocSpec.allocHistory[nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS];
			if (buffer){
				nmppsMallocSpec.routePos++;
				return buffer;
			}
			if (buffer==0){
				nmppsMallocSpec.routePos=1;
				buffer=(int*)nmppsMallocSpec.allocHistory[0];
				return buffer;
			}
		}
		//case(MALLOC32_ROUTE_MODE):
		//	heapIndx=0xF&(nmppsMallocSpec.routeInternal>>(nmppsMallocSpec.routePos<<2));
		//	nmppsMallocSpec.routePos++;
		//	if (nmppsMallocSpec.routePos == nmppsMallocSpec.routeSize)
		//		nmppsMallocSpec.routePos=0;
		//	buffer=((int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32+2*nmppsMallocBorder32))+nmppsMallocBorder32;
		//	break;
 		case(MALLOC32_RING_MODE):
 			heapIndx=nmppsGet_4u((nm4u*)nmppsMallocSpec.route, (nmppsMallocSpec.routePos-1)&NMPPS_MALLOC_MAX_POS);
 			for(i =0; i<4; i++){
 				heapIndx++;
 				heapIndx&=3;
 				buffer=(int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32);
 				if (buffer){
 					nmppsPut_4u((nm4u*)nmppsMallocSpec.route, nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS, heapIndx);
 					break;
 				}
 			}
 			break;

		

		//case(MALLOC32_HISTORY_MODE):
		//	//if (nmppsMallocSpec.routePos==nmppsMallocSpec.routeSize)
		//	//	return 0;
		//	buffer=(int*)nmppsMallocSpec.allocHistory[nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS];
		//	nmppsMallocSpec.routePos++;
		//	return buffer;
			

		case(MALLOC32_ROUTE_MODE):
			nmppsMallocTimerStop();
			sizeInt32+= nmppsMallocBorder32<<1;

			heapIndx=nmppsGet_4u((nm4u*)nmppsMallocSpec.route, nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS);
			if (heapIndx==0xf){
				nmppsMallocSpec.routePos=0;
				heapIndx=nmppsMallocSpec.route[0]&0xf;
				nmppsMallocSpec.firstPass=0;
			}
				
			buffer=(int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32);
			if (buffer)
				break;
			for(;heapIndx<4;heapIndx++){
				buffer=(int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32);
				if (buffer){
					break;
				}
			}
			nmppsPut_4u((nm4u*)nmppsMallocSpec.route, nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS, heapIndx&3);
			break;

		case(MALLOC32_PRIORITY_MODE):
			{
				unsigned priority=nmppsMallocSpec.priority;
				nmppsMallocTimerStop();
				sizeInt32+= nmppsMallocBorder32<<1;
				while ((heapIndx=(priority&0xF))!=0xF){
					buffer=((int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32+2*nmppsMallocBorder32))+nmppsMallocBorder32;
					if (buffer)						
						break;
					priority>>=4;
				}
			}
			break;

		//case(MALLOC32_RANDOM_MODE):
		//	{
		//		unsigned mask=nmppsMallocSpec.random;
		//		while (mask){
		//			randomize=1664525*randomize+1013904223;
		//			heapIndx=randomize>>30;
		//			if (mask&(1<<heapIndx)){
		//				mask^=(1<<heapIndx);
		//				buffer=((int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32+2*nmppsMallocBorder32))+nmppsMallocBorder32;
		//				if (buffer)
		//					break;
		//			}
		//		}
		//	}
		//	break;	
	}
	if (buffer){
		nmppsMallocSpec.routePos++;
		buffer+=nmppsMallocBorder32;
		nmppsMallocSpec.allocHistory[nmppsMallocSpec.allocHistoryPos&NMPPS_MALLOC_MAX_POS]=buffer;
		nmppsMallocSpec.allocHistoryPos++;
	}
	else {
		nmppsMallocSpec.status++;
	}
	nmppsMallocTimerResume();
	return buffer;
}
*/
void* nmppsMalloc32(unsigned sizeInt32) {
	int* buffer = 0;
	//static unsigned randomize=123;
	unsigned heapIndx, i;


	switch (nmppsMallocSpec.mode) {
	case(MALLOC32_HISTORY_MODE):
	{
		buffer = (int*)nmppsMallocSpec.allocHistory[nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS];
		if (buffer) {
			nmppsMallocSpec.routePos++;
			return buffer;
		}
		if (buffer == 0) {
			nmppsMallocSpec.routePos = 1;
			buffer = (int*)nmppsMallocSpec.allocHistory[0];
			return buffer;
		}
	}
	//case(MALLOC32_ROUTE_MODE):
	//	heapIndx=0xF&(nmppsMallocSpec.routeInternal>>(nmppsMallocSpec.routePos<<2));
	//	nmppsMallocSpec.routePos++;
	//	if (nmppsMallocSpec.routePos == nmppsMallocSpec.routeSize)
	//		nmppsMallocSpec.routePos=0;
	//	buffer=((int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32+2*nmppsMallocBorder32))+nmppsMallocBorder32;
	//	break;
	case(MALLOC32_RING_MODE):
		heapIndx = nmppsGet_4u((nm4u*)nmppsMallocSpec.route, (nmppsMallocSpec.routePos - 1)&NMPPS_MALLOC_MAX_POS);
		for (i = 0; i<4; i++) {
			heapIndx++;
			heapIndx &= 3;
			buffer = (int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32);
			if (buffer) {
				nmppsPut_4u((nm4u*)nmppsMallocSpec.route, nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS, heapIndx);
				break;
			}
		}
		break;



		//case(MALLOC32_HISTORY_MODE):
		//	//if (nmppsMallocSpec.routePos==nmppsMallocSpec.routeSize)
		//	//	return 0;
		//	buffer=(int*)nmppsMallocSpec.allocHistory[nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS];
		//	nmppsMallocSpec.routePos++;
		//	return buffer;


	case(MALLOC32_ROUTE_MODE):
		//nmppsMallocTimerStop();
		//sizeInt32 += nmppsMallocBorder32 << 1;
		//printf("-----\n");
		heapIndx = nmppsGet_4u((nm4u*)nmppsMallocSpec.route, nmppsMallocSpec.routePos & NMPPS_MALLOC_MAX_POS);
		if (heapIndx == 0xf) {
			nmppsMallocSpec.routePos = 0;
			heapIndx = nmppsMallocSpec.route[0] & 0xf;
			//nmppsMallocSpec.firstPass = 0;
		}

		buffer = (int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32);
		//if (buffer) {
		//	nmppsMallocSpec.routePos++;
		//	return buffer;
		//}
			//break;
		//for (; heapIndx<4; heapIndx++) {
		//	buffer = (int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32);
		//	if (buffer) {
		//		break;
		//	}
		//}
		//nmppsPut_4u((nm4u*)nmppsMallocSpec.route, nmppsMallocSpec.routePos&NMPPS_MALLOC_MAX_POS, heapIndx & 3);
		break;

	case(MALLOC32_PRIORITY_MODE):
	{
		unsigned priority = nmppsMallocSpec.priority;
		nmppsMallocTimerStop();
		sizeInt32 += nmppsMallocBorder32 << 1;
		while ((heapIndx = (priority & 0xF)) != 0xF) {
			buffer = ((int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32 + 2 * nmppsMallocBorder32)) + nmppsMallocBorder32;
			if (buffer)
				break;
			priority >>= 4;
		}
	}
	break;

	//case(MALLOC32_RANDOM_MODE):
	//	{
	//		unsigned mask=nmppsMallocSpec.random;
	//		while (mask){
	//			randomize=1664525*randomize+1013904223;
	//			heapIndx=randomize>>30;
	//			if (mask&(1<<heapIndx)){
	//				mask^=(1<<heapIndx);
	//				buffer=((int*)nmppsMallocSpec.allocator[heapIndx](sizeInt32+2*nmppsMallocBorder32))+nmppsMallocBorder32;
	//				if (buffer)
	//					break;
	//			}
	//		}
	//	}
	//	break;	
	}
	if (buffer) {
		nmppsMallocSpec.routePos++;
		//buffer += nmppsMallocBorder32;
		//nmppsMallocSpec.allocHistory[nmppsMallocSpec.allocHistoryPos&NMPPS_MALLOC_MAX_POS] = buffer;
		//nmppsMallocSpec.allocHistoryPos++;
	}
	else {
		nmppsMallocSpec.status++;
	}
	//nmppsMallocTimerResume();
	return buffer;
}

void nmppsFree(void* buffer){
	if (nmppsMallocSpec.mode==MALLOC32_HISTORY_MODE)
		return;
	nmppsMallocTimerStop();
	
	if (buffer){
		int* realBuf=(int*)buffer-nmppsMallocBorder32;
		free(realBuf);
		nmppsMallocSpec.freeHistory[nmppsMallocSpec.freeHistoryPos&NMPPS_MALLOC_MAX_POS]=realBuf;
		nmppsMallocSpec.freeHistoryPos++;
	}
	nmppsMallocTimerResume();
}
void nmppsFree32(void* ptr) {
	nmppsFree((void*)ptr);
}

int nmppsMallocWipe(){
	int allocIndx;
	int freeIndx;
	void* buffer;
	if (nmppsMallocSpec.allocHistoryPos>=NMPPS_MALLOC_MAX_POS || nmppsMallocSpec.freeHistoryPos>=NMPPS_MALLOC_MAX_POS){
		nmppsMallocSpec.status = -2;
		return -2;
	}
	if (nmppsMallocSpec.freeHistoryPos<nmppsMallocSpec.allocHistoryPos){
		for(allocIndx=0; allocIndx<nmppsMallocSpec.allocHistoryPos; allocIndx++){
			buffer=nmppsMallocSpec.allocHistory[allocIndx];
			for(freeIndx=0; freeIndx<nmppsMallocSpec.freeHistoryPos; freeIndx++){
				if (buffer==nmppsMallocSpec.freeHistory[freeIndx]){
					nmppsMallocSpec.freeHistory[freeIndx]=0;
					buffer=0;
					break;
				}
			}
			if (buffer)
				free(buffer);
		}
	}
	nmppsMallocSpec.status = 0;
	nmppsMallocSpec.freeHistoryPos = 0;
	nmppsMallocSpec.allocHistoryPos = 0;
	//nmppsMallocSpec.routePos = 0; because Increment breaks
}

	  
void  nmppsMallocSetRingMode  ()
{
	nmppsMallocResetPos();
	nmppsMallocSpec.mode = MALLOC32_RING_MODE;
}
void nmppsMallocSetRouteMode ()
{
	nmppsMallocResetPos();
	nmppsMallocSpec.mode = MALLOC32_ROUTE_MODE;
}

//void nmppsMallocSetRoute(uint64 routeLSBStart,int routeSize)
//{
//	nmppsMallocSpec.route[0]=seq;
//	nmppsMallocSpec.route[1]=0xFF;
//	nmppsMallocSpec.firstPass=1;
//	nmppsMallocSetRouteMode();
//}

void nmppsMallocSetRoute16(uint64 seq)
{
	nmppsMallocSpec.route[0]=seq;
	nmppsMallocSpec.route[1]=0xFF;
	nmppsMallocSpec.firstPass=1;
	nmppsMallocSetRouteMode();
}


void  nmppsMallocSetHistoryMode()
{
	nmppsMallocSpec.mode=MALLOC32_HISTORY_MODE;
}
int nmppsMallocResetPos(){
	if (nmppsMallocSpec.allocHistoryPos!=nmppsMallocSpec.freeHistoryPos){
		nmppsMallocSpec.status = -3;
		return -3;
	}
	nmppsMallocSpec.routePos=0;
	nmppsMallocSpec.freeHistoryPos=0;
	nmppsMallocSpec.allocHistoryPos=0;
	return 0;
}



//int nmppsMallocBetterRoute()
//{
//	if (nmppsMallocSpec.time<nmppsMallocSpec.timeBest){
//		nmppsMallocSpec.timeBest=nmppsMallocSpec.time;	
//		nmppsCopy_64u( (nm64u*)nmppsMallocSpec.route, (nm64u*)nmppsMallocSpec.bestRoute, NMPPS_MALLOC_LIMIT>>4);
//		return 1;
//	}
//	else 
//		return 0;
//}
//void nmppsMallocSetBestRoute(int historyEnable)
//{
//	//static int call=0;
//	//if (call==0 || historyEnable==0 )
//		nmppsCopy_64u((nm64u*)nmppsMallocSpec.bestRoute,(nm64u*)nmppsMallocSpec.route,   NMPPS_MALLOC_LIMIT>>4);
//	//else 
//	//	nmppsMallocSetHistoryMode();
//	//call++;
//}
//void nmppsMallocRandomRoute(){
//	nmppsRandUniform_64u(nmppsMallocSpec.route,NMPPS_MALLOC_LIMIT/16);
//	nmppsAndC_32u((nm32u*)nmppsMallocSpec.route,0x33333333,(nm32u*)nmppsMallocSpec.route,NMPPS_MALLOC_LIMIT/8);
//	nmppsMallocSpec.route[NMPPS_MALLOC_LIMIT/16-1]|=0xF000000000000000l;
//}

void nmppsMallocGetRoute16(fseq64* route){
	route=nmppsMallocSpec.route;
	nmppsPut_4u((nm4u*)route,nmppsMallocSpec.routePos,0xF);
}	
int nmppsMallocIncrementRoute0()
{
	int routeIndx;
	int heapIndx;

	for (routeIndx=(nmppsMallocSpec.routePos-1)&NMPPS_MALLOC_MAX_POS; routeIndx>=0; routeIndx--){
		heapIndx=nmppsGet_4u((nm4u*)nmppsMallocSpec.route, routeIndx);
		heapIndx++;
		if (heapIndx<4){
			nmppsPut_4u((nm4u*)nmppsMallocSpec.route,routeIndx,heapIndx);
			break;
		}
		heapIndx=0;
		nmppsPut_4u((nm4u*)nmppsMallocSpec.route,routeIndx,heapIndx);
		if (routeIndx==0 && heapIndx==0)
			return -1;

	}
	return 0;
}

int nmppsMallocIncrementRoute(int routeLength,int heapMask)
{
	int routePos;
	int routeIndx;
	int heapIndx;
	int carry = 0;
	int minHeapIndx=0;
	int maxHeapIndx=31;
	int mask=heapMask;
	
	nmppsMallocSpec.status = 0;
	nmppsMallocSpec.routePos = 0;
	// search low "1" bit 
	while (mask&1==0){
		mask>>=1;
		minHeapIndx++;
	}
	// search high "1" bit 
	mask=heapMask;
	while (mask&0x80000000==0){
		mask<<=1;
		maxHeapIndx--;
	}
	
	for (routePos = 0; routePos < routeLength; routePos++) {
		heapIndx = nmppsGet_4u((nm4u*)nmppsMallocSpec.route, routePos);
				
		if (heapIndx >= maxHeapIndx) {
			nmppsPut_4u((nm4u*)nmppsMallocSpec.route, routePos, minHeapIndx);
			carry = 1;
		}
		else {
			do{
				heapIndx++;
			} while ((heapMask>>heapIndx)&1==0);
			nmppsPut_4u((nm4u*)nmppsMallocSpec.route, routePos, heapIndx);
			carry = 0;
			return 1;
		}
		if (carry == 0)
			break;		
	}
	return 0; // exit with flag of route reset.
}
	
/*
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
}*/
int  nmppsMallocSuccess()
{
	return nmppsMallocSpec.status==0;
}

int  nmppsMallocFail()
{
	return nmppsMallocSpec.status!=0;
}

void  nmppsMallocResetStatus()
{
	nmppsMallocSpec.status=0;
}

int  nmppsMallocStatus()
{
	return nmppsMallocSpec.status;
}

/*
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

void  nmppsMallocSetBoundary32 (int size32 )
{
	nmppsMallocBorder32=size32;
}

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
*/
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
nm1*    nmppsMalloc_1  (unsigned sizeInt1) { return (nm1*)    nmppsMalloc32((sizeInt1+63)/64*2);}
nm2s*   nmppsMalloc_2s (unsigned sizeInt2) { return (nm2s*)   nmppsMalloc32((sizeInt2+31)/32*2);}
nm2u*   nmppsMalloc_2u (unsigned sizeInt2) { return (nm2u*)   nmppsMalloc32((sizeInt2+31)/32*2);}
nm4s*   nmppsMalloc_4s (unsigned sizeInt4) { return (nm4s*)   nmppsMalloc32((sizeInt4+15)/16*2);}
nm4u*   nmppsMalloc_4u (unsigned sizeInt4) { return (nm4u*)   nmppsMalloc32((sizeInt4+15)/16*2);}
nm8s*   nmppsMalloc_8s (unsigned sizeInt8) { return (nm8s*)   nmppsMalloc32((sizeInt8+7)/8*2);}
nm8u*   nmppsMalloc_8u (unsigned sizeInt8) { return (nm8u*)   nmppsMalloc32((sizeInt8+7)/8*2);}
nm16s*  nmppsMalloc_16s(unsigned sizeInt16){ return (nm16s*)  nmppsMalloc32((sizeInt16+3)/4*2);}
nm16u*  nmppsMalloc_16u(unsigned sizeInt16){ return (nm16u*)  nmppsMalloc32((sizeInt16+3)/4*2);}
nm32s*  nmppsMalloc_32s(unsigned sizeInt32){ return (nm32s*)  nmppsMalloc32(sizeInt32+(1&sizeInt32));}
float*  nmppsMalloc_32f(unsigned size)     { return (float*)  nmppsMalloc32(size);}
double* nmppsMalloc_64f(unsigned size)     { return (double*) nmppsMalloc32(size<<1);}
nm32sc* nmppsMalloc_32sc(unsigned size)    { return (nm32sc*) nmppsMalloc32(size<<1);}
nm32fc* nmppsMalloc_32fc(unsigned size)    { return (nm32fc*) nmppsMalloc32(size<<1);}
nm32fcr* nmppsMalloc_32fcr(unsigned size)  { return (nm32fcr*) nmppsMalloc32(size<<1);}
nm32u*  nmppsMalloc_32u(unsigned sizeInt32){ return (nm32u*)  nmppsMalloc32(sizeInt32+(1&sizeInt32));}
nm64s*  nmppsMalloc_64s(unsigned sizeInt64){ return (nm64s*)  nmppsMalloc32((sizeInt64)<<1);}
nm64u*  nmppsMalloc_64u(unsigned sizeInt64){ return (nm64u*)  nmppsMalloc32((sizeInt64)<<1);}




nm8s*  nmppsMallocFrame_8s (unsigned sizeInt8 , unsigned boundaryInt8 , NmppsFrame_8s * pFrame){return (nm8s* )nmppsMallocFrame_64u((sizeInt8+ 7)>>3,(boundaryInt8+ 7)>>3,(NmppsFrame_64u*)pFrame);}
nm8u*  nmppsMallocFrame_8u (unsigned sizeInt8 , unsigned boundaryInt8 , NmppsFrame_8u * pFrame){return (nm8u* )nmppsMallocFrame_64u((sizeInt8+ 7)>>3,(boundaryInt8+ 7)>>3,(NmppsFrame_64u*)pFrame);}
nm16s* nmppsMallocFrame_16s(unsigned sizeInt16, unsigned boundaryInt16, NmppsFrame_16s* pFrame){return (nm16s*)nmppsMallocFrame_64u((sizeInt16+3)>>2,(boundaryInt16+3)>>2,(NmppsFrame_64u*)pFrame);}
nm16u* nmppsMallocFrame_16u(unsigned sizeInt16, unsigned boundaryInt16, NmppsFrame_16u* pFrame){return (nm16u*)nmppsMallocFrame_64u((sizeInt16+3)>>2,(boundaryInt16+3)>>2,(NmppsFrame_64u*)pFrame);}
nm32s* nmppsMallocFrame_32s(unsigned sizeInt32, unsigned boundaryInt32, NmppsFrame_32s* pFrame){return (nm32s*)nmppsMallocFrame_64u((sizeInt32+1)>>1,(boundaryInt32+1)>>1,(NmppsFrame_64u*)pFrame);}
nm32u* nmppsMallocFrame_32u(unsigned sizeInt32, unsigned boundaryInt32, NmppsFrame_32u* pFrame){return (nm32u*)nmppsMallocFrame_64u((sizeInt32+1)>>1,(boundaryInt32+1)>>1,(NmppsFrame_64u*)pFrame);}
nm64s* nmppsMallocFrame_64s(unsigned sizeInt64, unsigned boundaryInt64, NmppsFrame_64s* pFrame){return (nm64s*)nmppsMallocFrame_64u(sizeInt64,boundaryInt64,(NmppsFrame_64u*)pFrame);}
nm64u* nmppsMallocFrame_64u(unsigned sizeInt64, unsigned boundaryInt64, NmppsFrame_64u* pFrame){      
	pFrame->pull=nmppsMalloc32(sizeInt64*2+boundaryInt64*4);
	pFrame->data=(nm64u*)pFrame->pull;
	if (pFrame->pull)
		pFrame->data+=boundaryInt64;
	return pFrame->data;
}
void   nmppsFreeFrame(void* buffer){
	if (((NmppsFrame_64u*)buffer)->pull)
		free(((NmppsFrame_64u*)buffer)->pull);
}