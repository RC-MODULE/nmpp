 // ImgDiff.cpp : Defines the entry point for the console application.

//-------------------------------------------------------------------
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
	C_WarpImg<nm32s> DstImg(176,144,0,malloc32,free32);
	
	if (SrcImg.pWarp==0 || DstImg.pWarp==0)
		return -1;

	nmppsRand_(SrcImg.pWarp, SrcImg.nWarpSize);
	CIMG_FIR<nm8s,nm32s> FIR(wker,hker,malloc32,free32);
	if (FIR.SetWeights(pFiterWindow,SrcImg.nWidth)==0)	return -1;
	FIR.Filter(SrcImg.pImg,DstImg.pImg,SrcImg.nWidth,SrcImg.nHeight);
	
	nmppsCrc_32u((nm32u*)DstImg.pImg,DstImg.nImgSize/2,crc);						// crc 

	return crc;

}

