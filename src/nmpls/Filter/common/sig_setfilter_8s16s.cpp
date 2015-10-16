#include "nmpls.h"
#include "nmplv.h"
#include "string.h"

//	nSize=3  nDisp=1,5 
//  nSize=5  nDisp=2,6 
//  nSize=7  nDisp=3,7 
//  nSize=9  nDisp=4,8 
//	nSize=11 nDisp=5,1 
//	nSize=13 nDisp=6,2 



inline int GetDisp0(int nSize)
{
	return ((nSize-3)/2%8+1);
}

inline int GetDisp1(int nSize)
{
	return ((nSize+5)/2)%8+1;
}




//==================================
//	nSize=3 nDisp=1,5 nMatrix=2,1,1,2
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
//	-5	0	0	0	0
//	-6	0	0	0	0
//	-7	0	0	0	0
//	-8	0	0	0	0
//----------------------//----------------------
//	7	0	0	0	0	//	7	b	c	0	0	
//	6	0	0	0	0	//	6	a	b	c	0	
//	5	0	0	0	0	//	5	0	a	b	c	
//	4	c	0	0	0	//	4	0	0	a	b	
//	3	b	c	0	0	//	3	0	0	0	a	
//	2	a	b	c	0	//	2	0	0	0	0	
//	1	0	a	b	c	//	1	0	0	0	0	
//	0	0	0	a	b	//	0	0	0	0	0	
//----------------------//----------------------
						//	15	0	0	0	0
						//	14	0	0	0	0
						//	13	0	0	0	0
						//	12	0	0	0	0
						//	11	0	0	0	0
						//	10	0	0	0	0
						//	9	0	0	0	0
						//	8	c	0	0	0
						//------------

// pWeightMatrix:	|----!0000|0000|0000|0000|0000|0000|0000|000a!00ab|0abc|abc0|bc00|c000|0000|0000|0000|
//					|----|----|----|----|----!0000|0000|0000|000a|00ab|0abc|abc0|bc00!c000|0000|0000|0000|0000|0000|0000|0000|
//
//===================================
// nSize=5 nDisp=2,6 
//	       [ a b c d e]
//	     [ a b c d e]
//	   [ a b c d e]
//   [ a b c d e]
//  -3-2-1 0 1 2 3 4 
//------------
//	-1	0	0	a	b
//	-2	0	0	0	a
//	-3	0	0	0	0
//	-4	0	0	0	0
//	-5	0	0	0	0
//	-6	0	0	0	0
//	-7	0	0	0	0
//	-8	0	0	0	0
//---------------------	//------------------------
//	7	0	0	0	0	//		c	d	e	0	//	
//	6	0	0	0	0	//		b	c	d	e	//	
//	5	e	0	0	0	//		a	b	c	d	//	
//	4	d	e	0	0	//		0	a	b	c	//	
//	3	c	d	e	0	//		0	0	a	b	//	
//	2	b	c	d	e	//		0	0	0	a	//	
//	1	a	b	c	d	//		0	0	0	0	//	
//	0	0	a	b	c	//		0	0	0	0	//	
//---------------------	//------------------------
						//	15	0	0	0	0
						//	14	0	0	0	0
						//	13	0	0	0	0
						//	12	0	0	0	0
						//	11	0	0	0	0
						//	10	0	0	0	0
						//	9	e	0	0	0
						//	8	d	e	0	0
						//----------------------
// pWeightMatrix:	|----|----!0000|0000|0000|0000|0000|0000|000a|00ab!0abc|abcd|bcde|cde0|de00|e000|0000|
//					|----|----|----|----|----|----!0000|0000|000a|00ab|0abc|abcd|bcde|cde0!de00|e000|0000|0000|0000|0000|0000|----|----|----|
//
//===================================
// nSize=7 nDisp=3,7
//	       [ a b c d e f g]
//	     [ a b c d e f g]
//	   [ a b c d e f g]
//   [ a b c d e f g]
//    -3-2-1 0 1 2 3 4 5 6
//-----------------------
//	-1	0	a	b	c	//	
//	-2	0	0	a	b	//	
//	-3	0	0	0	a	//	
//	-4	0	0	0	0	//	
//	-5	0	0	0	0	//	
//	-6	0	0	0	0	//	
//	-7	0	0	0	0	//	
//	-8	0	0	0	0	//	
//---------------------	//------------------------
//	7	0	0	0	0	//		d	e	f	g	//	
//	6	0	0	0	0	//		c	d	e	f	//	
//	5	g	0	0	0	//		b	c	d	e	//	
//	4	e	f	g	0	//		a	b	c	d	//	
//	3	d	e	f	g	//		0	a	b	c	//	
//	2	c	d	e	f	//		0	0	a	b	//	
//	1	b	c	d	e	//		0	0	0	a	//	
//	0	a	b	c	d	//		0	0	0	0	//	
//---------------------	//------------------------
						//	15	0	0	0	0	//	
						//	14	0	0	0	0	//	
						//	13	0	0	0	0	//	
						//	12	0	0	0	0	//	
						//	11	0	0	0	0	//	
						//	10	g	0	0	0	//	
						//	9	f	g	0	0	//	
						//	8	e	f	g	0	//	
						//------------------------

//===================================
// nSize=9 nDisp=4,8
//	       [ a b c d e f g h k]
//	     [ a b c d e f g h k]
//	   [ a b c d e f g h k]
//   [ a b c d e f g h k]
//    -4-3-2-1 0 1 2 3 4 5 6 7
//==================================
//	nSize=11 nDisp=5,1
//	       [ a b c d e f g h k l m]
//	     [ a b c d e f g h k l m]
//	   [ a b c d e f g h k l m]
//   [ a b c d e f g h k l m]
//    -5-4-3-2-1 0 1 2 3 4 5 6 7							 
//==================================
//	nSize=13 nDisp=6,2
//	       [ a b c d e f g h k l m n o
//	     [ a b c d e f g h k l m n o
//	   [ a b c d e f g h k l m n o
//   [ a b c d e f g h k l m n o
//    -6-5-4-3-2-1 0 1 2 3 4 5 6 7	  
//==================================
//	nSize=15 nDisp=7,3
//
// pKernel Structure
// {
//
//	int: number of weight arrays (pass 0)
//	int: ar0 displacement for input array (pass 0)
//	int: addr of weights array (pass 0)
//
//	int: number of weight arrays (pass 1)
//	int: ar0 displacement for input array (pass 1)
//	int: addr weights array (pass 1)
//
//	int[nNumberOfArrays]: Array of displacemnts inside pass
//
//	long[nNumberOfArrays*16/2]: weight array
// }
//int SIG_SetFilter_8s16s(int* pWeights, int nSize, nm64s* pKernel)
//{
//	
//	int nWeightsSize=(8+nSize+3+7)*2; //Size in int32 words
//		
//	int nDisp0=GetDisp0(nSize);
//	int nDisp1=GetDisp1(nSize);
//
//	int nNumberOfArrays0=(8+nSize+3-nDisp0+7)/8;
//	int nNumberOfArrays1=(8+nSize+3-nDisp1+7)/8;
//	int nDispArraySize=(8+nSize+3+7)/8;
//	nDispArraySize+=nDispArraySize&1;
//
//	nm32s* pDispArray	=((nm32s*)pKernel)+6;
//	nm16s* pWeightMatrix =(nm16s*)VEC_Addr((nm32s*)pDispArray,nDispArraySize);	
//	nm16s* pWeightMatrix0=(nm16s*)VEC_Addr((nm32s*)pWeightMatrix,nDisp0*2);	
//	nm16s* pWeightMatrix1=(nm16s*)VEC_Addr((nm32s*)pWeightMatrix,nDisp1*2);	
//
//	nDisp0=(((nSize/2)-0)+7)/8;
//	nDisp1=(((nSize/2)-4)+7)/8;
//
//	nDisp0*=-2;
//	nDisp1*=-2;
//
//	VEC_SetVal(((nm32s*)pKernel),0, nNumberOfArrays0);		// Number of arrays
//	VEC_SetVal(((nm32s*)pKernel),1,(int)nDisp0);			// ar0 displacement for first array
//	VEC_SetVal(((nm32s*)pKernel),2,(int)pWeightMatrix0);	// weights for first array
//
//	VEC_SetVal(((nm32s*)pKernel),3, nNumberOfArrays1);		// Number of arrays
//	VEC_SetVal(((nm32s*)pKernel),4,(int)nDisp1);			// ar0 displacement for first array
//	VEC_SetVal(((nm32s*)pKernel),5,(int)pWeightMatrix1);	// weights for first array
//
//	for(int i=0;i< nDispArraySize; i++){
//		pDispArray[i]=i<<1;
//	}
//
//	VEC_Fill((nm32s*)pWeightMatrix,0,nWeightsSize);
//
//	for(int i=0; i<nSize;i++){
//		VEC_SetVal(pWeightMatrix,8*4+i*4 ,	 pWeights[i]);
//		VEC_SetVal(pWeightMatrix,8*4+i*4+5,	 pWeights[i]);
//		VEC_SetVal(pWeightMatrix,8*4+i*4+10 , pWeights[i]);
//		VEC_SetVal(pWeightMatrix,8*4+i*4+15 , pWeights[i]);
//	}
//	return 6+(18+nSize)/8+1+(18+nSize)*2;
//}

int SIG_SetFilter_8s16s(int* pWeights, int nSize, nm64s* pKernel)
{
#ifndef __NM__
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
#else

	int nWeightsSize=(8+nSize+3+7)*2; //Size in int32 words
		
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);

	int nNumberOfArrays0=(8+nSize+3-nDisp0+7)/8;
	int nNumberOfArrays1=(8+nSize+3-nDisp1+7)/8;

	int nDispArraySize=nNumberOfArrays0+nNumberOfArrays1;
	nDispArraySize+=nDispArraySize&1;

	nm32s* pDispArray	=((nm32s*)pKernel)+6;
	nm16s* pWeightMatrix =(nm16s*)VEC_Addr((nm32s*)pDispArray,nDispArraySize);	
	nm16s* pWeightMatrix0=(nm16s*)VEC_Addr((nm32s*)pWeightMatrix,nDisp0*2);	
	nm16s* pWeightMatrix1=(nm16s*)VEC_Addr((nm32s*)pWeightMatrix,nDisp1*2);	
	VEC_SetVal(((nm32s*)pKernel),0,(int) nNumberOfArrays0);		// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),2,(int) pWeightMatrix0);		// weights for first array
	VEC_SetVal(((nm32s*)pKernel),3,(int) nNumberOfArrays1);		// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),5,(int) pWeightMatrix1);		// weights for first array

	int nSrcDisp0=(((nSize/2)-0)+7)/8;
	int nSrcDisp1=(((nSize/2)-4)+7)/8;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;

	//----------- Disp array 0 --------------------
	VEC_SetVal(((nm32s*)pKernel),1,(int)pDispArray);	
	for(int i=0;i< nNumberOfArrays0; i++){
		*pDispArray=(i<<1)+nSrcDisp0;
		pDispArray++;
	}
	//----------- Disp array 1 --------------------
	VEC_SetVal(((nm32s*)pKernel),4,(int)pDispArray);	
	for(int i=0;i< nNumberOfArrays1; i++){
		*pDispArray=(i<<1)+nSrcDisp1;
		pDispArray++;
	}
	
	VEC_Fill((nm32s*)pWeightMatrix,0,nWeightsSize);

	//----------- Weight array 0,1 ----------------
	for(int i=0; i<nSize;i++){
		VEC_SetVal(pWeightMatrix,8*4+i*4 ,	 pWeights[i]);
		VEC_SetVal(pWeightMatrix,8*4+i*4+5,	 pWeights[i]);
		VEC_SetVal(pWeightMatrix,8*4+i*4+10 , pWeights[i]);
		VEC_SetVal(pWeightMatrix,8*4+i*4+15 , pWeights[i]);
	}
	// Total size	= 6+(18+nSize)/8*2+1+(18+nSize)*2=
	//				= 7+(18+nSize)*5/4
	int AllocSize=6+nDispArraySize+nWeightsSize;
	return AllocSize;
#endif
}

int SIG_GetFilterKernelSize_8s16s(int nSize){
	int nWeightsSize=(8+nSize+3+7)*2; //Size in int32 words
		
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);

	int nNumberOfArrays0=(8+nSize+3-nDisp0+7)/8;
	int nNumberOfArrays1=(8+nSize+3-nDisp1+7)/8;

	int nDispArraySize=nNumberOfArrays0+nNumberOfArrays1;
	nDispArraySize+=nDispArraySize&1;

	int nSrcDisp0=(((nSize/2)-0)+7)/8;
	int nSrcDisp1=(((nSize/2)-4)+7)/8;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;

	int AllocSize=6+nDispArraySize+nWeightsSize;
	return AllocSize;
}

/*
int SIG_GetFilterKernelSize_8s16s(int nSize)
{
	// pKernal
	//  .....
	//  pDispArray+6
	//  .....
	//  pWeightMatrix
	//  ...
	//  pWeightMatrix0
	//  ...
	//  pWeightMatrix1
	//  ...
	
	
	int nWeightsSize=(8+nSize+3+7)*2; //Size in int32 words
		
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);

	int nNumberOfArrays0=(8+nSize+3-nDisp0+7)/8;
	int nNumberOfArrays1=(8+nSize+3-nDisp1+7)/8;

	int nDispArraySize=nNumberOfArrays0+nNumberOfArrays1;
	nDispArraySize+=nDispArraySize&1;

	nm32s* pDispArray	=((nm32s*)pKernel)+6;
	nm16s* pWeightMatrix =(nm16s*)VEC_Addr((nm32s*)pDispArray,nDispArraySize);	
	nm16s* pWeightMatrix0=(nm16s*)VEC_Addr((nm32s*)pWeightMatrix,nDisp0*2);	
	nm16s* pWeightMatrix1=(nm16s*)VEC_Addr((nm32s*)pWeightMatrix,nDisp1*2);	
	//VEC_SetVal(((nm32s*)pKernel),0,(int) nNumberOfArrays0);		// Number of arrays
	//VEC_SetVal(((nm32s*)pKernel),2,(int) pWeightMatrix0);		// weights for first array
	//VEC_SetVal(((nm32s*)pKernel),3,(int) nNumberOfArrays1);		// Number of arrays
	//VEC_SetVal(((nm32s*)pKernel),5,(int) pWeightMatrix1);		// weights for first array

	int nSrcDisp0=(((nSize/2)-0)+7)/8;
	int nSrcDisp1=(((nSize/2)-4)+7)/8;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;

	//----------- Disp array 0 --------------------
	//VEC_SetVal(((nm32s*)pKernel),1,(int)pDispArray);	
	for(int i=0;i< nNumberOfArrays0; i++){
		//*pDispArray=(i<<1)+nSrcDisp0;
		pDispArray++;
	}
	//----------- Disp array 1 --------------------
	//VEC_SetVal(((nm32s*)pKernel),4,(int)pDispArray);	
	for(int i=0;i< nNumberOfArrays1; i++){
		//*pDispArray=(i<<1)+nSrcDisp1;
		pDispArray++;
	}
	
	//VEC_Fill((nm32s*)pWeightMatrix,0,nWeightsSize);

	//----------- Weight array 0,1 ----------------
	
	for(int i=0; i<nSize;i++){
		//VEC_SetVal(pWeightMatrix,8*4+i*4 ,	 pWeights[i]);
		//VEC_SetVal(pWeightMatrix,8*4+i*4+5,	 pWeights[i]);
		//VEC_SetVal(pWeightMatrix,8*4+i*4+10 , pWeights[i]);
		//VEC_SetVal(pWeightMatrix,8*4+i*4+15 , pWeights[i]);
	}
	// Total size	= 6+(18+nSize)/8*2+1+(18+nSize)*2=
	//				= 7+(18+nSize)*5/4
	int AllocSize=(int)VEC_Addr(VEC_SetVal(pWeightMatrix,8*4+i*4+15)-(int)pKernel;
	return AllocSize;
#endif
}
*/
/*
void SIG_CreateFilter_8s16s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	int nWeightsSize=(8+nSize+3+7)*2; //Size in int32 words
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);
	int nNumberOfArrays0=(8+nSize+3-nDisp0+7)/8;
	int nNumberOfArrays1=(8+nSize+3-nDisp1+7)/8;
	int nDispArraySize=nNumberOfArrays0+nNumberOfArrays1;
	nDispArraySize+=nDispArraySize&1;
	int AllocSize=6+nDispArraySize+nWeightsSize;
	VEC_Malloc((nm32s**)pKernel,AllocSize,hint);
	if (*pKernel==0) return;
	//VEC_Fill((nm32s*)*pKernel,5,AllocSize);
	SIG_SetFilter_8s16s(pWeights, nSize, *pKernel);
}
*/

//--------------------------------------------------------------------------------------------------------------

template<> int CSIG_FIR<nm8s,nm16s>::init(int NumWeights, void* (*malloc32_func)(unsigned),void (*free32_func)(void*)){
	pfFree32=free32_func;
	nWeights=NumWeights;
	int KernelSize=SIG_GetFilterKernelSize_8s16s(nWeights);
	pKernel=(nm64s*)malloc32_func(KernelSize);
	return (pKernel!=0);
}
template<> CSIG_FIR<nm8s,nm16s>::CSIG_FIR(int NumWeights, void* (*malloc32_func)(unsigned),void (*free32_func)(void*)){
	init(NumWeights, malloc32_func, free32_func);
}


template<> void* CSIG_FIR<nm8s,nm16s>::setWeights(int* pWeights){
	if (pKernel)
		SIG_SetFilter_8s16s(pWeights, nWeights, pKernel);
	return pWeights;
}
template<> void CSIG_FIR<nm8s,nm16s>::filter(nm8s* pSrcVec, nm16s* pDstVec, int nSize){
	SIG_Filter(pSrcVec,pDstVec,nSize,pKernel);
}
template<> CSIG_FIR<nm8s,nm16s>::~CSIG_FIR(){
	if (pKernel) 
		pfFree32(pKernel);
}
