#include "nmpli.h"

void* malloc32(unsigned sizeInt32 ){
#ifdef __NM__
	return malloc(sizeInt32);
#else
	return malloc(sizeInt32*4);
#endif
}

void free32(void* p){
	return free(p);
}



int main()
{

	int pFiterWindow[3*3]={ 1, 1, 1,
							1,-9, 1,
							1, 1, 1};
	int wker=3; // width of filter window 
	int hker=3;	// hweight of filter window
	unsigned crc=0;
	C_WarpImg<nm8s>  SrcImg(176,144,2,malloc32,free32);
	C_WarpImg<nm16s> DstImg(176,144,0,malloc32,free32);
	
	if (SrcImg.pWarp==0 || DstImg.pWarp==0)
		return -1;

	nmppsRandUniform_(SrcImg.pWarp, SrcImg.nWarpSize);
	CIMG_FIR<nm8s,nm16s> FIR(wker,hker,malloc32,free32);
	if (FIR.SetWeights(pFiterWindow,SrcImg.nWidth)==0)	return -1;
	FIR.Filter(SrcImg.pImg,DstImg.pImg,SrcImg.nWidth,SrcImg.nHeight);
	
	nmppsCrc_32u((nm32u*)DstImg.pImg,DstImg.nImgSize/2,&crc);						// crc 

	return crc;

	nmppsMallocCreateRoute(RANDOM, BANK0|BANK1|BANK2|BANK3,route,10);
	nmppsMallocCreateRoute(REGULAR,BANK0|BANK1|BANK2|BANK3,route,10);
	nmppsMallocSetMode(RANDOM,BANK0|BANK1|BANK2|BANK3);
	nmppsMallocSetMode(RANDOM);
	for(int i=0; i<16;i++){
		
	nmppsSetCurrentMalloc32();
		
	NMPPS_OPTIMIZE_ROUTE_BEGIN(L10,100);
		nmppsMallocRouteBegin();
		NmppsFIRState* state;
		src=nmppsMalloc_8s(size);
		dst=nmppsMalloc_16s(size);
		nmppsFIRInitAlloc_8s16s(w,h,&state);
		
		NMPPS_MALLOC_TIMER_START();
		nmppsFIR_8s16s(src,dst,size,state);
		NMPPS_MALLOC_TIMER_STOP();
		
		NMPPS_MALLOC_TIMER_RESUME();
		nmppsFIR_8s16s(src,dst,size,state);
		NMPPS_MALLOC_TIMER_STOP();
		
		nmppsFIRFree(state);
		nmppsFree(src);
		nmppsFree(dst);
		nmppsMallocRouteEnd();
	
	NMPPS_OPTIMIZE_ROUTE_BEGIN(L10);
	
	nmppsMallocGetBestRoute(route);
	nmppsMallocSetRoute(route);
	nmppsFIRInitAlloc_8s16s(w,h,malloc32,free32,&state);
	while(1){
		src=nmppsMalloc_8s(size);
		dst=nmppsMalloc_16s(size);
		nmppsFIR_8s16s(src,dst,size,state);
		nmppsFIR_8s16s(src,dst,size,state);
		nmppsFree(src);
		nmppsFree(dst);
	}		
	
	
}

