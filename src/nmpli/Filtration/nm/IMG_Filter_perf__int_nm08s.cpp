#include "nmpls.h"
#include "nmpli.h"
#include "time.h"
#include "nmpli.h"


//!
//! \perfinclude _IMG_Filter_perf__FPiiiPiPiiiPl.html
//!

void IMG_Filter_perf(int* pWeights, int nKerWidth, int nKerHeight, nm32s* pSrcVec, nm32s* pDstVec, int nImgWidth, int nImgHeight, nm64s* pKernel)
{
	IMG_SetFilter_32s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel); 
	clock_t t0,t1;	
	t0=clock();
	IMG_Filter(pSrcVec, pDstVec, nImgWidth, nImgHeight,pKernel);
	t1=clock();
	exit((int)(100.*(t1-t0)/(nImgWidth*nImgHeight)));
}




//!
//! \perfinclude _IMG_Filter_perf__FPiiiPSsPiiiPl.html
//!

void IMG_Filter_perf(int* pWeights, int nKerWidth, int nKerHeight,  nm16s* pSrcVec, nm32s* pDstVec, int nImgWidth, int nImgHeight, nm64s* pKernel)
{
	IMG_SetFilter_16s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel); 
	clock_t t0,t1;	
	t0=clock();
	IMG_Filter(pSrcVec, pDstVec, nImgWidth, nImgHeight,pKernel);
	t1=clock();
	exit((int)(100.*(t1-t0)/(nImgWidth*nImgHeight)));

}



//!
//! \perfinclude _IMG_Filter_perf__FPiiiPSsPSsiiPl.html
//!

void IMG_Filter_perf(int* pWeights, int nKerWidth, int nKerHeight,  nm16s* pSrcVec, nm16s* pDstVec, int nImgWidth, int nImgHeight, nm64s* pKernel)
{
	IMG_SetFilter_16s16s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel); 
	clock_t t0,t1;	
	t0=clock();
	IMG_Filter(pSrcVec, pDstVec, nImgWidth, nImgHeight,pKernel);
	t1=clock();
	exit((int)(100.*(t1-t0)/(nImgWidth*nImgHeight)));
}



//!
//! \perfinclude _IMG_Filter_perf__FPiiiPcPiiiPl.html
//!

void IMG_Filter_perf(int* pWeights, int nKerWidth, int nKerHeight,  nm8s* pSrcVec, nm32s* pDstVec, int nImgWidth, int nImgHeight, nm64s* pKernel)
{
	IMG_SetFilter_8s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel); 
	clock_t t0,t1;	
	t0=clock();
	IMG_Filter(pSrcVec, pDstVec, nImgWidth, nImgHeight,pKernel);
	t1=clock();
	exit((int)(100.*(t1-t0)/(nImgWidth*nImgHeight)));
}


//!
//! \perfinclude _IMG_Filter_perf__FPiiiPcPSsiiPl.html
//!

void IMG_Filter_perf(int* pWeights, int nKerWidth, int nKerHeight,  nm8s* pSrcVec, nm16s* pDstVec, int nImgWidth, int nImgHeight, nm64s* pKernel)
{
	IMG_SetFilter_8s16s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel); 
	clock_t t0,t1;	
	t0=clock();
	IMG_Filter(pSrcVec, pDstVec, nImgWidth, nImgHeight,pKernel);
	t1=clock();
	exit((int)(100.*(t1-t0)/(nImgWidth*nImgHeight)));
}


//!
//! \perfinclude _IMG_Filter_perf__FPiiiPcPciiPl.html
//!

void IMG_Filter_perf(int* pWeights, int nKerWidth, int nKerHeight,  nm8s* pSrcVec, nm8s* pDstVec, int nImgWidth, int nImgHeight, nm64s* pKernel)
{
	IMG_SetFilter_8s8s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel); 
	clock_t t0,t1;	
	t0=clock();
	IMG_Filter(pSrcVec, pDstVec, nImgWidth, nImgHeight,pKernel);
	t1=clock();
	exit((int)(100.*(t1-t0)/(nImgWidth*nImgHeight)));
}