 #include <string.h>
#include "nmplv.h"
#include "nmpls.h"
#include "nmpli.h"



	// f(3)=3
	// f(5)=3
	// f(7)=5
	// f(9)=5
	// f(11)=7 
	//.......
static inline int GetMatrixCount(int nSize)
{
	return ((nSize+1)/4)*2+1;	
}

	// f(3)=1;
	// f(5)=0;
	// f(7)=1;
	// f(9)=0;
	// f(11)=1;
	// f(13)=0;
	// f(15)=1
	// f(17)=0

static inline int GetDisp(int nSize)
{
	return (1-((nSize-3)/2)%2);
}


//==================================
//	nSize=3
//	   [ a b c ]
//   [ a b c ]
//  -2-1 0 1 2 3 4 
//------------
//	-1	0	a
//	-2	0	0
//------------
//	1	b	c
//	0	a	b
//-------------
//	3	0	0
//	2	c	0
// pWeightMatrix:	00|0a|ab|bc|c0|00 
//===================================
// nSize=5
//	   [ a b c d e]
//   [ a b c d e]
//  -3-2-1 0 1 2 3 4 
//------------
//	-1	a	b
//	-2	0	a
//------------
//	1	c	d
//	0	b	c
//-------------
//	3	e	0
//	2	d	e
// pWeightMatrix:	0a|ab|bc|cd|de|e0 
//===================================

int IMG_SetFilter_32s32s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s* pKernel)
//int IMG_SetFilter_32s32s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, S_IMG_FilterKernel* pKernel)
{
	
#ifndef __NM__
	S_IMG_FilterKernel* psKernel=(S_IMG_FilterKernel*) pKernel;
	psKernel->nKerHeight=nKerHeight;
	psKernel->nKerWidth =nKerWidth;
	psKernel->pDispArray=0;
	psKernel->pWeightMatrix=(nm32s*)(psKernel+1);
	memcpy(psKernel->pWeightMatrix,pWeights,nKerWidth*nKerHeight*4);
	return nKerWidth*nKerHeight;
#else

	
	
	int nNumberOfArrays=GetMatrixCount(nKerWidth);
	
	
	nm32s* pDispArray	=((nm32s*)pKernel)+2;
	nm32s* pWeightMatrix=((nm32s*)pDispArray)+nKerHeight*nNumberOfArrays+1;	
	
	//------------- Init header -------------------------------------
	VEC_SetVal(((nm32s*)pKernel),0,(int)nNumberOfArrays*nKerHeight);
	VEC_SetVal(((nm32s*)pKernel),1,(int)pWeightMatrix);
	//------------- Init array of displacements ----------------------
	int disp=-nImgWidth*(nKerHeight>>1);
	for(int j=0;j< nKerHeight; j++){
		for(int i=0;i< nNumberOfArrays; i++){
			*pDispArray=(i<<1)-((nNumberOfArrays>>1)<<1)+disp;
			pDispArray++;
		}
		disp+=nImgWidth;
	}

	//------------- Init weight matrices -----------------------------
	VEC_Fill(pWeightMatrix,0,4*nNumberOfArrays*nKerHeight);
	disp=GetDisp(nKerWidth);
	for(int j=0,k=0; j<nKerHeight;j++){
		for(int i=0; i<nKerWidth;i++,k++){
			VEC_SetVal(pWeightMatrix,i*2+disp*2  ,pWeights[k]);
			VEC_SetVal(pWeightMatrix,i*2+disp*2+3,pWeights[k]);
		}
		pWeightMatrix=VEC_Addr(pWeightMatrix,4*nNumberOfArrays);
	}
	
	int AllocSize=4+nNumberOfArrays*nKerHeight+1+nNumberOfArrays*4*nKerHeight;
	return AllocSize;
#endif
}


int IMG_GetFilterKernelSize32_32s32s( int nKerWidth,  int nKerHeight){
	int nNumberOfArrays=GetMatrixCount(nKerWidth);
	int AllocSize=4+nNumberOfArrays*nKerHeight+1+nNumberOfArrays*4*nKerHeight;
	return AllocSize;
}
/*
void IMG_CreateFilter_32s32s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s** pKernel, int nHint)
{
	int nNumberOfArrays=GetMatrixCount(nKerWidth);
	int AllocSize=2+nNumberOfArrays*nKerHeight+1+nNumberOfArrays*4*nKerHeight;
	VEC_Malloc((nm32s**)pKernel,AllocSize,nHint);
	if (*pKernel==0) return;
	IMG_SetFilter_32s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, *pKernel);
}*/

//--------------------------------------------------------------------------------------------------------------
template<> CIMG_FIR<nm32s,nm32s>::CIMG_FIR(int n_KerWidth, int n_KerHeight, void* (*malloc32_func)(unsigned), void (*free32_func)(void*)){
	pfFree32=free32_func;
	nKerWidth=n_KerWidth;
	nKerHeight=n_KerHeight;
	int KernelSize=IMG_GetFilterKernelSize32_32s32s( nKerWidth,  nKerHeight);
	pKernel=(nm64s*)malloc32_func(KernelSize);
}

template<> void* CIMG_FIR<nm32s,nm32s>::SetWeights(int* pWeights, int nImgWidth){
	if (pKernel)
		IMG_SetFilter_32s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel);
	return (void*)pKernel;
}

template<> void CIMG_FIR<nm32s,nm32s>::Filter(nm32s* pSrcImg, nm32s* pDstImg, int nImgWidth,int nImgHeight){
	IMG_Filter(pSrcImg, pDstImg, nImgWidth, nImgHeight, pKernel);
}

template<> CIMG_FIR<nm32s,nm32s>::~CIMG_FIR(){
	if (pKernel) 
		pfFree32(pKernel); 
}
