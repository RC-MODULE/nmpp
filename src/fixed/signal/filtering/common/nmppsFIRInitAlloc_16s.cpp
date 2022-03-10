#include "nmpls.h"
#include "nmpp.h"
#include "string.h"

#ifdef __cplusplus
		extern "C" {
#endif

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

__INLINE__ int GetMatrixCount(int nSize)
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

__INLINE__ int GetDisp(int nSize)
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


int nmppsFIRInit_16s(NmppsFIRState* ppState, int* pWeights, int tapsLen)
{
	int nWeights=tapsLen;
	int* pKernel=(int*)ppState;
	
#if defined(__NM__)
	int nNumberOfArrays=GetMatrixCount(tapsLen);


	nm32s* pDispArray	=((nm32s*)pKernel)+2;
	nm16s* pWeightMatrix=(nm16s*)nmppsAddr_32s((nm32s*)pKernel,nNumberOfArrays+3);	

	nmppsPut_32s(((nm32s*)pKernel),0,(int)nNumberOfArrays);
	nmppsPut_32s(((nm32s*)pKernel),1,(int)pWeightMatrix);

	for(int i=0;i< nNumberOfArrays; i++){
		pDispArray[i]=(i<<1)-((nNumberOfArrays>>1)<<1);
	}

	nmppsSet_16s(0,pWeightMatrix,16*nNumberOfArrays);

	int disp=GetDisp(nWeights);
	for(int i=0; i<nWeights;i++){
		nmppsPut_16s(pWeightMatrix,(i+disp)*4+5*0,pWeights[i]);
		nmppsPut_16s(pWeightMatrix,(i+disp)*4+5*1,pWeights[i]);
		nmppsPut_16s(pWeightMatrix,(i+disp)*4+5*2,pWeights[i]);
		nmppsPut_16s(pWeightMatrix,(i+disp)*4+5*3,pWeights[i]);
	}
	int AllocSize=2+nNumberOfArrays+3+nNumberOfArrays*16/2;
	return AllocSize;	
#else 
	pKernel[0]=nWeights;
	memcpy(pKernel+1,pWeights,nWeights<<2);
	return nWeights;
#endif
	
}

int nmppsFIRGetStateSize_16s(int tapsLen){
	int nSize=tapsLen;
	int nNumberOfArrays=GetMatrixCount(nSize);
	int AllocSize=2+nNumberOfArrays+3+nNumberOfArrays*16/2;
	return AllocSize;
}

int nmppsFIRInitAlloc_16s(NmppsFIRState** ppState, int* pTaps, int tapsLen)
{
	int stateSize=nmppsFIRGetStateSize_16s(tapsLen);
	*ppState=(void*)nmppsMalloc_32s(stateSize);
	if (*ppState){
		nmppsFIRInit_16s(*ppState, pTaps, tapsLen);
		return 0;
	}
	return -1;
}


#ifdef __cplusplus
		};
#endif