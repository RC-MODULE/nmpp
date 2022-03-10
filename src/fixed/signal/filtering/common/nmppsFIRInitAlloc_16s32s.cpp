#include "nmpls.h"
#include "nmpp.h"
#include "string.h"

#ifdef __cplusplus
		extern "C" {
#endif
// nSize=3  nDisp=1,3 nMatrix=2
// nSize=5  nDisp=2,4 nMatrix=2
// nSize=7  nDisp=3,1 nMatrix=3
// nSize=9  nDisp=4,2 nMatrix=3
// nSize=11 nDisp=1,3 nMatrix=4
// nSize=13 nDisp=2,4 nMatrix=4

__INLINE__ int GetMatrixCount(int nSize)
{
	return (nSize+5)/4;	
}

__INLINE__ int GetDisp0(int nSize)
{
	return ((nSize-3)/2%4+1);
}

__INLINE__ int GetDisp1(int nSize)
{
	return ((nSize+1)/2)%4+1;
}



//==================================
//	nSize=3 nDisp=1,3 nMatrix=2
//	       [ a b c ]
//	     [ a b c ]
//	   [ a b c ]
//   [ a b c ]
//  -2-1 0 1 2 3 4 
//------------
//	-1	0	a
//	-2	0	0
//	-3	0	0
//	-4	0	0
//------------	//------------
//	3	0	0	//	3	b	c
//	2	c	0	//	2	a	b
//	1	b	c	//	1	0	a
//	0	a	b	//	0	0	0
//------------	//------------
//	7	0	0	//	7	0	0
//	6	0	0	//	6	0	0
//	5	0	0	//	5	0	0
//	4	0	0	//	4	c	0
//------------	//------------
// pWeightMatrix:  |--|00|00|00|0a|ab|bc|c0|00|00|00|00|00|
//                 |--|--|--|00|0a|ab|bc|c0|00|00|00| 
//===================================
// nSize=5 nDisp=2,4 nMatrix=2
//	       [ a b c d e]
//	     [ a b c d e]
//	   [ a b c d e]
//   [ a b c d e]
//  -3-2-1 0 1 2 3 4 
//------------	//------------
//	-1	a	b	//	-1	0	0
//	-2	0	a	//	-2	0	0
//	-3	0	0	//	-3	0	0
//	-4	0	0	//	-4	0	0
//------------	//------------
//	3	e	0	//	3	c	d
//	2	d	e	//	2	b	c
//	1	c	d	//	1	a	b
//	0	b	c	//	0	0	a
//------------	//------------
//	7	0	0	//	7	0	0
//	6	0	0	//	6	0	0
//	5	0	0	//	5	e	0
//	4	0	0	//	4	d	e
//------------	//------------
// pWeightMatrix:	|--|--|00|00|0a|ab|bc|cd|de|e0|
//    		        |--|--|--|--|0a|ab|bc|cd|de|e0|00|00| 
//===================================
// nSize=7 nDisp=3,1 nMatrix=3
//	       [ a b c d e f g]
//	     [ a b c d e f g]
//	   [ a b c d e f g]
//   [ a b c d e f g]
//    -3-2-1 0 1 2 3 4 
//------------	//------------
//	-1	b	c	//	-1	0	a
//	-2	a	b	//	-2	0	0
//	-3	0	a	//	-3	0	0
//	-4	0	0	//	-4	0	0
//-----------	//-----------
//	3	f	g	//	3	d	e
//	2	e	f	//	2	c	d
//	1	d	e	//	1	b	c
//	0	c	d	//	0	a	b
//-----------	//-----------
//	7	0	0	//	7	0	0
//	6	0	0	//	6	g	0
//	5	0	0	//	5	f	g
//	4	g	0	//	4	e	f
//------------	//------------
// pWeightMatrix:|--|--|--|00|0a|ab|bc|cd|de|e0|fg|g0|00|00|00|
//			     |--|00|00|00|0a|ab|bc|cd|de|e0|fg|g0|00| 
//===================================
// nSize=9 nDisp=4,2 nMatrix=3
//	       [ a b c d e f g h k]
//	     [ a b c d e f g h k]
//	   [ a b c d e f g h k]
//   [ a b c d e f g h k]
//    -4-3-2-1 0 1 2 3 4 5 6 7
//------------	//------------
//	-1	b	c	//	-1	0	a
//	-2	a	b	//	-2	0	0
//	-3	0	a	//	-3	0	0
//	-4	0	0	//	-4	0	0
//-----------	//-----------
//	3	f	g	//	3	d	e
//	2	e	f	//	2	c	d
//	1	d	e	//	1	b	c
//	0	c	d	//	0	a	b
//-----------	//-----------
//	7	0	0	//	7	0	0
//	6	0	0	//	6	g	0
//	5	0	0	//	5	f	g
//	4	g	0	//	4	e	f
//------------	//------------
// pWeightMatrix: |--|--|--|--|0a|ab|bc|cd|de|ef|fg|gh|hk|k0|00|00|
//			      |--|--|00|00|0a|ab|bc|cd|de|ef|fg|gh|hk|k0|
//==================================
//	nSize=11 nDisp=1,3 nMatrix=4
//	       [ a b c d e f g h k l m]
//	     [ a b c d e f g h k l m]
//	   [ a b c d e f g h k l m]
//   [ a b c d e f g h k l m]
//    -5-4-3-2-1 0 1 2 3 4 5 6 7
//------------
//	-5	0	a
//	-6	0	0
//	-7	0	0
//	-8	0	0
//------------
//	-1	d	e
//	-2	c	d
//	-3	b	c
//	-4	a	b
//------------	//------------
//	3	h	k	//	3	b	c
//	2	g	h	//	2	a	b
//	1	f	g	//	1	0	a
//	0	e	f	//	0	0	0
//------------	//------------
//	7	0	0	//	7	0	0
//	6	m	0	//	6	0	0
//	5	l	m	//	5	0	0
//	4	k	l	//	4	c	0
//------------	//------------
// pWeightMatrix:	|--|00|00|00|0a|ab|bc|cd|de|ef|fg|gh|hk|kl|lm|m0|00|
//			        |--|--|00|00|0a|ab|bc|cd|de|ef|fg|gh|hk|kl|lm|m0|00|00|

int nmppsFIRInit_16s32s(NmppsFIRState* ppState, int* pWeights, int tapsLen)
{
	int nSize=tapsLen;
	int* pKernel=(int*)ppState;
#ifndef __NM__
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
#else



	int nWeightsSize=(4+nSize+1+3)*2; //Size in int32 words
	
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);
	
	int nNumberOfArrays0=(4+nSize+1-nDisp0+3)/4;
	int nNumberOfArrays1=(4+nSize+1-nDisp1+3)/4;
	int nDispArraySize=(4+nSize+1+3)*2/4;
	nDispArraySize+=nDispArraySize&1;


	nm32s* pDispArray	=((nm32s*)pKernel)+6;
	nm32s* pWeightMatrix =nmppsAddr_32s((nm32s*)pDispArray,nDispArraySize);	
	nm32s* pWeightMatrix0=nmppsAddr_32s((nm32s*)pWeightMatrix,nDisp0*2);	
	nm32s* pWeightMatrix1=nmppsAddr_32s((nm32s*)pWeightMatrix,nDisp1*2);	
	nmppsPut_32s(((nm32s*)pKernel),2,(int)pWeightMatrix0);	// weights for first array
	nmppsPut_32s(((nm32s*)pKernel),5,(int)pWeightMatrix1);	// weights for first array

	int nSrcDisp0=(((nSize/2)-0)+3)/4;
	int nSrcDisp1=(((nSize/2)-2)+3)/4;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;

	nmppsPut_32s(((nm32s*)pKernel),0,(int)nNumberOfArrays0);		// Number of arrays
	nmppsPut_32s(((nm32s*)pKernel),1,(int)pDispArray);			// ar0 displacement for first array
	for(int i=0;i< nNumberOfArrays0; i++){
		*pDispArray=(i<<1)+nSrcDisp0;
		pDispArray++;
	}

	nmppsPut_32s(((nm32s*)pKernel),3,(int)nNumberOfArrays1);		// Number of arrays
	nmppsPut_32s(((nm32s*)pKernel),4,(int)pDispArray);			// ar0 displacement for first array
	for(int i=0; i< nNumberOfArrays1; i++){
		*pDispArray=(i<<1)+nSrcDisp1;
		pDispArray++;
	}
	
	nmppsSet_32s(0,(nm32s*)pWeightMatrix,nWeightsSize);

	for(int i=0; i<nSize; i++){
		nmppsPut_32s(pWeightMatrix,4*2+i*2 , pWeights[i]);
		nmppsPut_32s(pWeightMatrix,4*2+i*2+3,pWeights[i]);
	}

	// Total size = 6+(8+nSize)*2/4+1+(8+nSize)*2=
	//			  = 8+(8+nSize)*5/2
	int AllocSize=6+nDispArraySize+nWeightsSize;
	return AllocSize;
#endif
}
int nmppsFIRGetStateSize_16s32s(int nSize){

	int nWeightsSize=(4+nSize+1+3)*2; //Size in int32 words
	
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);
	
	int nNumberOfArrays0=(4+nSize+1-nDisp0+3)/4;
	int nNumberOfArrays1=(4+nSize+1-nDisp1+3)/4;
	int nDispArraySize=(4+nSize+1+3)*2/4;
	nDispArraySize+=nDispArraySize&1;

	// Total size = 6+(8+nSize)*2/4+1+(8+nSize)*2=
	//			  = 8+(8+nSize)*5/2
	int AllocSize=6+nDispArraySize+nWeightsSize;
	return AllocSize;
}

int nmppsFIRInitAlloc_16s32s(NmppsFIRState** ppState, int* pTaps, int tapsLen)
{
	int stateSize=nmppsFIRGetStateSize_16s32s(tapsLen);
	*ppState=(void*)nmppsMalloc_32s(stateSize);
	if (*ppState){
		nmppsFIRInit_16s32s(*ppState, pTaps, tapsLen);
		return 0;
	}
	return -1;
}


#ifdef __cplusplus
		};
#endif