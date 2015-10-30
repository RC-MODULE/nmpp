#include <string.h>
#include "nmplv.h"
#include "nmpls.h"
#include "nmpli.h"




	// f(3)=3
	// f(5)=3
	// f(7)=3
	// f(9)=3
	// f(11)=5 
	// f(13)=5
	// f(15)=5
	// f(17)=5
	// f(19)=7
	// f(21)=7
	// f(23)=7
	// f(25)=7

static inline int GetMatrixCount(int nSize)
{
	return ((nSize+5)/8)*2+1;	
}


	// f(3)=3;
	// f(5)=2;
	// f(7)=1;
	// f(9)=0;
	// f(11)=3;
	// f(13)=2;
	// f(15)=1
	// f(17)=0

static inline int GetDisp(int nSize)
{
	return (3-((nSize-3)/2)%4);
}
//3	0	0	0
//5	2	1	1
//7	4	2	2
//9	6   3	3
//11 8	4	0
//13 10	5	1
//15 12	6	2
//19	15	3
//21	19	0

//==================================
//	nSize=3
//	       [ a b c ]
//	     [ a b c ]
//	   [ a b c ]
//   [ a b c ]
//  -2-1 0 1 2 3 4 
//------------
//	-1	0	0	0	a
//	-2	0	0	0	0
//	-3	0	0	0	0
//	-4	0	0	0	0
//-------------------
//	3	b	c	0	0
//	2	a	b	c	0
//	1	0	a	b	c
//	0	0	0	a	b
//-------------------
//  7	0	0	0	0
//	6	0	0	0	0
//	5	0	0	0	0
//	4	c	0	0	0
//
// pWeightMatrix:	|0000|0000|0000|000a|00ab|0abc|abc0|bc00|c000|0000|0000|0000|
//===================================
// nSize=5
//	         [ a b c d e]
//	       [ a b c d e]
//	     [ a b c d e]
//	   [ a b c d e]
//   [ a b c d e]
//  -3-2-1 0 1 2 3 4 
//-------------------
//	-1	0	0	a	b
//	-2	0	0	0	a
//	-3	0	0	0	0
//	-4	0	0	0	0
//-------------------
//	3	c	d	e	0
//	2	b	c	d	e
//	1	a	b	c	d
//	0	0	a	b	c
//-------------------
//  7	0	0	0	0
//	6	0	0	0	0
//	5	e	0	0	0
//	4	d	e	0	0
// pWeightMatrix:	0000|0000|000a|00ab|0abc|abcd|bcde|cde0|de00|e000|0000|0000|
//===================================
// nSize=7
//	         [ a b c d e f g]
//	       [ a b c d e f g]
//	     [ a b c d e f g]
//	   [ a b c d e f g]
//   [ a b c d e f g]
//  -4-3-2-1 0 1 2 3 4 
//-------------------
//	-1	0	a	b	c
//	-2	0	0	a	b
//	-3	0	0	0	a
//	-4	0	0	0	0
//-------------------
//	3	d	e	f	g
//	2	c	d	e	f
//	1	b	c	d	e
//	0	a	b	c	d
//-------------------
//  7	0	0	0	0
//	6	g	0	0	0
//	5	f	g	0	0
//	4	e	f	g	0
// pWeightMatrix:	0000|000a|00ab|0abc|abcd|bcde|cde0|de00|e000|0000|0000|0000|
//===================================

int IMG_SetFilter_16s16s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s* pKernel)
{
	
#ifndef __NM__
	//((int*)pKernel)[0]=nKerWidth;
	//((int*)pKernel)[1]=nKerHeight;
	//memcpy(pKernel+1,(nm32s*)pWeights,nKerWidth*nKerHeight<<2);
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
	nm16s* pWeightMatrix=(nm16s*)nmppsAddr_32s((nm32s*)pDispArray,nKerHeight*nNumberOfArrays+1);	
	
	nmppsSetInt_32s(((nm32s*)pKernel),0,(int)nNumberOfArrays*nKerHeight);
	nmppsSetInt_32s(((nm32s*)pKernel),1,(int)pWeightMatrix);
	
	int disp=-(nImgWidth>>1)*(nKerHeight>>1);
	for(int j=0; j<nKerHeight; j++){
		for(int i=0; i<nNumberOfArrays; i++){
			*pDispArray=(i<<1)-((nNumberOfArrays>>1)<<1)+disp;
			pDispArray++;
		}
		disp+=(nImgWidth>>1);
	}
	
	nmppsSet_16s(pWeightMatrix,0,16*nNumberOfArrays*nKerHeight);
	
	disp=GetDisp(nKerWidth);
	for(int j=0,k=0; j<nKerHeight; j++){
		for(int i=0; i<nKerWidth; i++,k++){
			nmppsSetInt_16s(pWeightMatrix,(i+disp)*4+5*0,pWeights[k]);
			nmppsSetInt_16s(pWeightMatrix,(i+disp)*4+5*1,pWeights[k]);
			nmppsSetInt_16s(pWeightMatrix,(i+disp)*4+5*2,pWeights[k]);
			nmppsSetInt_16s(pWeightMatrix,(i+disp)*4+5*3,pWeights[k]);
		}
		pWeightMatrix=nmppsAddr_16s(pWeightMatrix,nNumberOfArrays*16);
	}

	//return 2+nKerHeight*nNumberOfArrays+1+nKerHeight*nNumberOfArrays*8;
	int AllocSize=2+nKerHeight*nNumberOfArrays+1+nKerHeight*nNumberOfArrays*8;
	return AllocSize;
#endif	

}
/*
void IMG_CreateFilter_16s16s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s** pKernel, int nHint)
{
	int nNumberOfArrays=GetMatrixCount(nKerWidth);
	int AllocSize=2+nKerHeight*nNumberOfArrays+1+nKerHeight*nNumberOfArrays*8;
	nmppsMalloc_32s((nm32s**)pKernel,AllocSize,nHint);
	if (*pKernel==0) return;
	IMG_SetFilter_16s16s(pWeights, nKerWidth, nKerHeight, nImgWidth, *pKernel);
}*/

int IMG_GetFilterKernelSize32_16s16s(int nKerWidth, int nKerHeight)
{
	int nNumberOfArrays=GetMatrixCount(nKerWidth);
	int AllocSize=2+nKerHeight*nNumberOfArrays+1+nKerHeight*nNumberOfArrays*8;
	return AllocSize;
}




//--------------------------------------------------------------------------------------------------------------
template<> CIMG_FIR<nm16s,nm16s>::CIMG_FIR(int n_KerWidth, int n_KerHeight, void* (*malloc32_func)(unsigned), void (*free32_func)(void*)){
	pfFree32=free32_func;
	nKerWidth=n_KerWidth;
	nKerHeight=n_KerHeight;
	int KernelSize=IMG_GetFilterKernelSize32_16s16s( nKerWidth,  nKerHeight);
	pKernel=(nm64s*)malloc32_func(KernelSize);
}

template<> void* CIMG_FIR<nm16s,nm16s>::SetWeights(int* pWeights, int nImgWidth){
	if (pKernel)
		IMG_SetFilter_16s16s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel);
	return pWeights;
}

template<> void CIMG_FIR<nm16s,nm16s>::Filter(nm16s* pSrcImg, nm16s* pDstImg, int nImgWidth,int nImgHeight){
	IMG_Filter(pSrcImg, pDstImg, nImgWidth, nImgHeight, pKernel);
}

template<> CIMG_FIR<nm16s,nm16s>::~CIMG_FIR(){
	if (pKernel) 
		pfFree32(pKernel);
}
