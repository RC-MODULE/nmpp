#include "nmpls.h"
#include "nmplv.h"
#include "string.h"

// nSize=3  nDisp=1,3 nMatrix=2
// nSize=5  nDisp=2,4 nMatrix=2
// nSize=7  nDisp=3,1 nMatrix=3
// nSize=9  nDisp=4,2 nMatrix=3
// nSize=11 nDisp=1,3 nMatrix=4
// nSize=13 nDisp=2,4 nMatrix=4

inline int GetMatrixCount(int nSize)
{
	return (nSize+5)/4;	
}

inline int GetDisp0(int nSize)
{
	return ((nSize-3)/2%4+1);
}

inline int GetDisp1(int nSize)
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

int SIG_SetFilter_16s32s(int* pWeights, int nSize, nm64s* pKernel)
{

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
	nmppsSetInt_32s(((nm32s*)pKernel),2,(int)pWeightMatrix0);	// weights for first array
	nmppsSetInt_32s(((nm32s*)pKernel),5,(int)pWeightMatrix1);	// weights for first array

	int nSrcDisp0=(((nSize/2)-0)+3)/4;
	int nSrcDisp1=(((nSize/2)-2)+3)/4;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;

	nmppsSetInt_32s(((nm32s*)pKernel),0,(int)nNumberOfArrays0);		// Number of arrays
	nmppsSetInt_32s(((nm32s*)pKernel),1,(int)pDispArray);			// ar0 displacement for first array
	for(int i=0;i< nNumberOfArrays0; i++){
		*pDispArray=(i<<1)+nSrcDisp0;
		pDispArray++;
	}

	nmppsSetInt_32s(((nm32s*)pKernel),3,(int)nNumberOfArrays1);		// Number of arrays
	nmppsSetInt_32s(((nm32s*)pKernel),4,(int)pDispArray);			// ar0 displacement for first array
	for(int i=0; i< nNumberOfArrays1; i++){
		*pDispArray=(i<<1)+nSrcDisp1;
		pDispArray++;
	}
	
	nmppsSet_32s((nm32s*)pWeightMatrix,0,nWeightsSize);

	for(int i=0; i<nSize; i++){
		nmppsSetInt_32s(pWeightMatrix,4*2+i*2 , pWeights[i]);
		nmppsSetInt_32s(pWeightMatrix,4*2+i*2+3,pWeights[i]);
	}

	// Total size = 6+(8+nSize)*2/4+1+(8+nSize)*2=
	//			  = 8+(8+nSize)*5/2
	int AllocSize=6+nDispArraySize+nWeightsSize;
	return AllocSize;
#endif
}
int SIG_GetFilterKernelSize_16s32s(int nSize){

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
/*
void SIG_CreateFilter_16s32s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	int nWeightsSize=(4+nSize+1+3)*2; //Size in int32 words
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);
	int nNumberOfArrays0=(4+nSize+1-nDisp0+3)/4;
	int nNumberOfArrays1=(4+nSize+1-nDisp1+3)/4;
	int nDispArraySize=(4+nSize+1+3)*2/4;
	nDispArraySize+=nDispArraySize&1;

	//nm32s* pDispArray	=((nm32s*)pKernel)+6;
	//nm32s* pWeightMatrix =nmppsAddr_32s((nm32s*)pDispArray,nDispArraySize);	
	//nmppsSet_32s((nm32s*)pWeightMatrix,0,nWeightsSize);

	int AllocSize=6+nDispArraySize+nWeightsSize;
	nmppsMalloc_32s((nm32s**)pKernel,AllocSize,hint);
	if (*pKernel==0) return;
	SIG_SetFilter_16s32s(pWeights, nSize, *pKernel);
}
*/



template<> int CSIG_FIR<nm16s,nm32s>::init(int NumWeights, void* (*malloc32_func)(unsigned),void (*free32_func)(void*)){
	init(NumWeights, malloc32_func,free32_func);
	pfFree32=free32_func;
	nWeights=NumWeights;
	int KernelSize=SIG_GetFilterKernelSize_16s32s(nWeights);
	pKernel=(nm64s*)malloc32_func(KernelSize);
	return (pKernel!=0);
}

template<> CSIG_FIR<nm16s,nm32s>::CSIG_FIR(int NumWeights, void* (*malloc32_func)(unsigned),void (*free32_func)(void*)){
	init(NumWeights, malloc32_func,free32_func);
}


template<> void* CSIG_FIR<nm16s,nm32s>::setWeights(int* pWeights){
	if (pWeights)
		SIG_SetFilter_16s32s(pWeights, nWeights, pKernel);
	return pWeights;
}
template<> void CSIG_FIR<nm16s,nm32s>::filter(nm16s* pSrcVec, nm32s* pDstVec, int nSize){
	SIG_Filter(pSrcVec,pDstVec,nSize,pKernel);
}
template<> CSIG_FIR<nm16s,nm32s>::~CSIG_FIR(){
	if (pKernel) 
		pfFree32(pKernel);
}


