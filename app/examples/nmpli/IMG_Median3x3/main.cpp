 // ImgDiff.cpp : Defines the entry point for the console application.

//-------------------------------------------------------------------
#include "nmpli.h"

#define MAX_WIDTH  128 	// ������ ��������
#define MAX_HEIGHT 128 	// ������ ��������

bool malloc32error = false;

void* malloc32(unsigned sizeInt32 ){
	
#ifdef __NM__
	void* p=malloc(sizeInt32);
#else
	void* p=malloc(sizeInt32*4);
#endif
	if (p==0)
		malloc32error=true;
	return p;
}

void free32(void* p){
	return free(p);
}


int main()
{

	
	C_WarpImg<nm8u>  imSrc (MAX_WIDTH,MAX_HEIGHT,4,malloc32,free32);
	C_WarpImg<nm8u>  imDst (MAX_WIDTH,MAX_HEIGHT,4,malloc32,free32);
	C_WarpImg<nm8u>  imTmp1(MAX_WIDTH,MAX_HEIGHT,4,malloc32,free32);
	C_WarpImg<nm8u>  imTmp2(MAX_WIDTH,MAX_HEIGHT,4,malloc32,free32);
	
	if (malloc32error) 
		return -1;
	
	nmppsRandUniform_(imSrc.pWarp,imSrc.nWarpSize);
	nmppsRShiftC_(imSrc.pWarp,1,imSrc.pWarp,imSrc.nWarpSize);

	
	nmppiMedian3x3(
	  (nm8s7b*)	imSrc.pImg,
	  (nm8s7b*)	imDst.pImg,
				imSrc.nWidth,
				imSrc.nHeight,
				imTmp1.pImg,
				imTmp2.pImg);

	unsigned nCrc=0;
	nmppsCrc_(imDst.pImg,imDst.nImgSize,nCrc);	
	
	return nCrc;
}

