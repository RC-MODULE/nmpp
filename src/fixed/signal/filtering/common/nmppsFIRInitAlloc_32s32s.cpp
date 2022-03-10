#include "nmpls.h"
#include "nmpp.h"
#include "string.h"

#ifdef __cplusplus
		extern "C" {
#endif


	// f(3)=3
	// f(5)=3
	// f(7)=5
	// f(9)=5
	// f(11)=7 
	//.......
__INLINE__ int GetMatrixCount(int nSize)
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

__INLINE__ int GetDisp(int nSize)
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

int nmppsFIRInit_32s(NmppsFIRState* ppState, int* pWeights, int tapsLen)
{
	int nSize=tapsLen;
	int* pKernel=(int*)ppState;
#ifndef __NM__
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
#else

	int nNumberOfArrays=GetMatrixCount(nSize);
	
	
	nm32s* pDispArray	=((nm32s*)pKernel)+2;
	nm32s* pWeightMatrix=((nm32s*)pDispArray)+nNumberOfArrays+1;	
	
	nmppsPut_32s(((nm32s*)pKernel),0,nNumberOfArrays);
	nmppsPut_32s(((nm32s*)pKernel),1,(int)pWeightMatrix);
	
	for(int i=0;i< nNumberOfArrays; i++){
		pDispArray[i]=(i<<1)-((nNumberOfArrays>>1)<<1);
	}

	nmppsSet_32s(0,pWeightMatrix,4*nNumberOfArrays);

	int disp=GetDisp(nSize);
	for(int i=0; i<nSize;i++){
		nmppsPut_32s(pWeightMatrix,i*2+disp*2  ,pWeights[i]);
		nmppsPut_32s(pWeightMatrix,i*2+disp*2+3,pWeights[i]);
	}
//	return 2+(nSize/2+2)+(nSize/2+2)*4;
	int AllocSize=2+nNumberOfArrays+1+nNumberOfArrays*4;
	return AllocSize;
#endif	
}

int nmppsFIRGetStateSize_32s(int nSize){
	int nNumberOfArrays=GetMatrixCount(nSize);
//	return 2+(nSize/2+2)+(nSize/2+2)*4;
	int AllocSize=2+nNumberOfArrays+1+nNumberOfArrays*4;
	return AllocSize;
}

int nmppsFIRInitAlloc_32s(NmppsFIRState** ppState, int* pTaps, int tapsLen)
{
	int stateSize=nmppsFIRGetStateSize_32s(tapsLen);
	*ppState=(void*)nmppsMalloc_32s(stateSize);
	if (*ppState){
		nmppsFIRInit_32s(*ppState, pTaps, tapsLen);
		return 0;
	}
	return -1;
}


#ifdef __cplusplus
		};
#endif