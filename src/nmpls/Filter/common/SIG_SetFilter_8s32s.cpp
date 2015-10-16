#include "nmpls.h"
#include "nmplv.h"
#include "string.h"


//	nSize=3  nDisp=1,7,5,3 
//  nSize=5  nDisp=2,8,6,4 
//  nSize=7  nDisp=3,1,7,5 
//  nSize=9  nDisp=4,2,8,6 
//	nSize=11 nDisp=5,3,1,7 
//	nSize=13 nDisp=6,4,2,8 



inline int GetDisp0(int nSize)
{
	return ((nSize-3)/2%8+1);
}

inline int GetDisp1(int nSize)
{
	return ((nSize+9)/2)%8+1;
}

inline int GetDisp2(int nSize)
{
	return ((nSize+5)/2)%8+1;
}

inline int GetDisp3(int nSize)
{
	return ((nSize+1)/2)%8+1;
}







//==================================
//	nSize=3 nDisp=1,7,5,3 nMatrix=2,1,1,2
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
//	-5	0	0
//	-6	0	0
//	-7	0	0
//	-8	0	0
//------------	//------------	//------------	//------------
//	7	0	0	//	7	0	0	//	7	0	0	//	7	b	c
//	6	0	0	//	6	0	0	//	6	c	0	//	6	a	b
//	5	0	0	//	5	0	0	//	5	b	c	//	5	0	a
//	4	0	0	//	4	c	0	//	4	a	b	//	4	0	0
//	3	0	0	//	3	b	c	//	3	0	a	//	3	0	0
//	2	c	0	//	2	a	b	//	2	0	0	//	2	0	0
//	1	b	c	//	1	0	a	//	1	0	0	//	1	0	0
//	0	a	b	//	0	0	0	//	0	0	0	//	0	0	0
//------------	//------------	//------------	//------------
												//	15	0	0
												//	14	0	0
												//	13	0	0
												//	12	0	0
												//	11	0	0
												//	10	0	0
												//	9	0	0
												//	8	c	0
												//------------

// pWeightMatrix:	|--!00|00|00|00|00|00|00|0a!ab|bc|c0|00|00|00|00|00|--|--|
//					|--|--|--|--|--|--|--!00|0a|ab|bc|c0|00|00|00|--|--|--|--| 
//					|--|--|--|--|--!00|00|00|0a|ab|bc|c0|00|--|--|--|--|--|--|
//					|--|--|--!00|00|00|00|00|0a|ab|bc|c0|00|00|00|00|00|00|00|

//===================================
// nSize=5 nDisp=2,8,6,4 nMatrix=2,1,1,2
//	       [ a b c d e]
//	     [ a b c d e]
//	   [ a b c d e]
//   [ a b c d e]
//  -3-2-1 0 1 2 3 4 
//------------
//	-1	a	b
//	-2	0	a
//	-3	0	0
//	-4	0	0
//	-5	0	0
//	-6	0	0
//	-7	0	0
//	-8	0	0
//-------------	//------------	//------------	//------------
//	7	0	0	//		0	0	//		e	0	//		c	d
//	6	0	0	//		0	0	//		d	e	//		b	c
//	5	0	0	//		e	0	//		c	d	//		a	b
//	4	0	0	//		d	e	//		b	c	//		0	a
//	3	e	0	//		c	d	//		a	b	//		0	0
//	2	d	e	//		b	c	//		0	a	//		0	0
//	1	c	d	//		a	b	//		0	0	//		0	0
//	0	b	c	//		0	a	//		0	0	//		0	0
//------------	//------------	//------------	//------------
												//	15	0	0
												//	14	0	0
												//	13	0	0
												//	12	0	0
												//	11	0	0
												//	10	0	0
												//	9	e	0
												//	8	d	e
												//------------

// pWeightMatrix:	|--|--!00|00|00|00|00|00|0a|ab!bc|cd|de|e0|00|00|00|00!--|--|
//					|--|--|--|--|--|--|--|--!0a|ab|bc|cd|de|e0|00|00!--|--|--|--|
//					|--|--|--|--|--|--!00|00|0a|ab|bc|cd|de|e0!--|--|--|--|--|--|
//					|--|--|--|--!00|00|00|00|0a|ab|bc|cd!de|e0|00|00|00|00|00|00!
//===================================
// nSize=7 nDisp=3,1,7,5 nMatrix=2,2,2,2
//	       [ a b c d e f g]
//	     [ a b c d e f g]
//	   [ a b c d e f g]
//   [ a b c d e f g]
//    -3-2-1 0 1 2 3 4 5 6
//------------	//-----------
//	-1	b	c	//		0	a
//	-2	a	b	//		0	0
//	-3	0	a	//		0	0
//	-4	0	0	//		0	0
//	-5	0	0	//		0	0
//	-6	0	0	//		0	0
//	-7	0	0	//		0	0
//	-8	0	0	//		0	0
//-------------	//------------	//------------	//------------
//	7	0	0	//		0	0	//		f	g	//		d	e
//	6	0	0	//		0	0	//		e	f	//		c	d
//	5	0	0	//		g	0	//		d	e	//		b	c
//	4	g	0	//		e	f	//		c	d	//		a	b
//	3	f	g	//		d	e	//		b	c	//		0	a
//	2	e	f	//		c	d	//		a	b	//		0	0
//	1	d	e	//		b	c	//		0	a	//		0	0
//	0	c	d	//		a	b	//		0	0	//		0	0
//------------	//------------	//------------	//------------
								//	15	0	0	//		0	0
								//	14	0	0	//		0	0
								//	13	0	0	//		0	0
								//	12	0	0	//		0	0
								//	11	0	0	//		0	0
								//	10	0	0	//		g	0
								//	9	0	0	//		f	g
								//	8	g	0	//		e	f
								//------------	//------------
// pWeightMatrix:	
//					|--|--|--!00|00|00|00|00|0a|ab|bc!cd|de|ef|fg|g0|00|00|00!--|--|--|--|
//					|--!00|00|00|00|00|00|00|0a!ab|bc|cd|de|ef|fe|g0|00!--|--|--|--|--|--|
//					|--|--|--|--|--|--|--!00|0a|ab|bc|cd|de|ef|fe!g0|00|00|00|00|00|00|00!
//					|--|--|--|--|--!00|00|00|0a|ab|bc|cd|de!ef|fe|g0|00|00|00|00|00!--|--|
//===================================
// nSize=9 nDisp=4,2,8,6 nMatrix=2,2,2,2
//	       [ a b c d e f g h k]
//	     [ a b c d e f g h k]
//	   [ a b c d e f g h k]
//   [ a b c d e f g h k]
//    -4-3-2-1 0 1 2 3 4 5 6 7
//					|--|--|--|--!00|00|00|00|0a|ab|bc|cd!de|ef|fg|gh|hk|k0|00|00!--|--|--|
//					|--|--!00|00|00|00|00|00|0a|ab!bc|cd|de|ef|fe|gh|hk|k0!--|--|--|--|--|
//					|--|--|--|--|--|--|--|--!0a|ab|bc|cd|de|ef|fe|gh!hk|k0|00|00|00|00|00|00!
//					|--|--|--|--|--|--!00|00|0a|ab|bc|cd|de|ef!fe|gh|hk|k0|00|00|00|00|--|
//==================================
//	nSize=11 nDisp=5,3,1,7 nMatrix=2,3,3,2
//	       [ a b c d e f g h k l m]
//	     [ a b c d e f g h k l m]
//	   [ a b c d e f g h k l m]
//   [ a b c d e f g h k l m]
//    -5-4-3-2-1 0 1 2 3 4 5 6 7							 V
//					|--|--|--|--|--!00|00|00|0a|ab|bc|cd|de!ef|fg|gh|hk|kl|lm|m0|00!--|--|
//					|--|--|--!00|00|00|00|00|0a|ab|bc!cd|de|ef|fe|gh|hk|kl|lm!m0|00|00|00|00|00|00|00!
//					|--!00|00|00|00|00|00|00|0a!ab|bc|cd|de|ef|fe|gh|hk!kl|lm|m0|00|00|00|00|00!--|--|
//					|--|--|--|--|--|--|--!00|0a|ab|bc|cd|de|ef|fe!gh|hk|kl|lm|m0|00|00|00!
//==================================
//	nSize=13 nDisp=6,4,2,8 nMatrix=2,3,3,2
//	       [ a b c d e f g h k l m n o
//	     [ a b c d e f g h k l m n o
//	   [ a b c d e f g h k l m n o
//   [ a b c d e f g h k l m n o
//    -6-5-4-3-2-1 0 1 2 3 4 5 6 7	   6						 V                  21
//					|--|--|--|--|--|--!00|00|0a|ab|bc|cd|de|ef!fg|gh|hk|kl|lm|mn|no|o0!--|
//					|--|--|--|--!00|00|00|00|0a|ab|bc|cd!de|ef|fe|gh|hk|kl|lm|mn!no|o0|00|00|00|00|00!
//					|--|--!00|00|00|00|00|00|0a|ab!bc|cd|de|ef|fe|gh|hk|kl!lm|mn|no|o0|00|00|00!--|--|
//					|--|--|--|--|--|--|--|--!0a|ab|bc|cd|de|ef|fe|gh!hk|kl|lm|mn|no|o0|00!
//==================================
//	nSize=15 nDisp=7,5,3,1 nMatrix=3,3,3,3
//					|--|--|--|--|--|--|--!00|0a|ab|bc|cd|de|ef|fg!gh|hk|kl|lm|mn|no|op|p0!--
//					|--|--|--|--|--!00|00|00|0a|ab|bc|cd|de!ef|fe|gh|hk|kl|lm|mn|no!op|p0|00|00|00|00|00|00!
//					|--|--|--!00|00|00|00|00|0a|ab|bc!cd|de|ef|fe|gh|hk|kl|lm!mn|no|op|p0|00|00|00|00!--|--|
//					|--!00|00|00|00|00|00|00|0a!ab|bc|cd|de|ef|fe|gh|hk!kl|lm|mn|no|op|p0|00|00!
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
//	int: number of weight arrays (pass 2)
//	int: ar0 displacement for input array (pass 2)
//	int: addr weights array (pass 2)
//
//	int: number of weight arrays (pass 3)
//	int: ar0 displacement for input array (pass 3)
//	int: addr weights array (pass 3)
//
//	int[nNumberOfArrays]: Array of displacemnts inside pass
//
//	long[nNumberOfArrays*16/2]: weight array
// }
int SIG_SetFilter_8s32s(int* pWeights, int nSize, nm64s* pKernel)
{


#ifndef __NM__
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
#else


	int nWeightsSize=(8+nSize+1+7)*2; //Size in int32 words
	
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);
	int nDisp2=GetDisp2(nSize);
	int nDisp3=GetDisp3(nSize);

	int nNumberOfArrays0=(nSize+8+1-nDisp0+7)/8;
	int nNumberOfArrays1=(nSize+8+1-nDisp1+7)/8;
	int nNumberOfArrays2=(nSize+8+1-nDisp2+7)/8;
	int nNumberOfArrays3=(nSize+8+1-nDisp3+7)/8;
	

	int nDispArraySize  =(nSize+8+1+7)/8;
	nDispArraySize+=nDispArraySize&1;

	nm32s* pDispArray	=((nm32s*)pKernel)+12;
	nm32s* pWeightMatrix =VEC_Addr((nm32s*)pDispArray,nDispArraySize*4);	
	nm32s* pWeightMatrix0=VEC_Addr((nm32s*)pWeightMatrix,nDisp0*2);	
	nm32s* pWeightMatrix1=VEC_Addr((nm32s*)pWeightMatrix,nDisp1*2);	
	nm32s* pWeightMatrix2=VEC_Addr((nm32s*)pWeightMatrix,nDisp2*2);	
	nm32s* pWeightMatrix3=VEC_Addr((nm32s*)pWeightMatrix,nDisp3*2);	

	int nSrcDisp0=(((nSize/2)-0)+7)/8;
	int nSrcDisp1=(((nSize/2)-2)+7)/8;
	int nSrcDisp2=(((nSize/2)-4)+7)/8;
	int nSrcDisp3=(((nSize/2)-6)+7)/8;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;
	nSrcDisp2*=-2;
	nSrcDisp3*=-2;

	VEC_SetVal(((nm32s*)pKernel),0,nNumberOfArrays0);		// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),2,(int)pWeightMatrix0);	// weights for first array

	VEC_SetVal(((nm32s*)pKernel),3,nNumberOfArrays1);		// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),5,(int)pWeightMatrix1);	// weights for first array

	VEC_SetVal(((nm32s*)pKernel),6,nNumberOfArrays2);		// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),8,(int)pWeightMatrix2);	// weights for first array

	VEC_SetVal(((nm32s*)pKernel),9,nNumberOfArrays3);		// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),11,(int)pWeightMatrix3);	// weights for first array


	VEC_SetVal(((nm32s*)pKernel),1,(int)pDispArray);		// ar0 displacement for first array
	for(int i=0;i< nDispArraySize; i++){
		*pDispArray=(i<<1)+nSrcDisp0;
		pDispArray++;
	}
	VEC_SetVal(((nm32s*)pKernel),4,(int)pDispArray);			// ar0 displacement for first array
	for(int i=0;i< nDispArraySize; i++){
		*pDispArray=(i<<1)+nSrcDisp1;
		pDispArray++;
	}
	VEC_SetVal(((nm32s*)pKernel),7,(int)pDispArray);			// ar0 displacement for first array
	for(int i=0;i< nDispArraySize; i++){
		*pDispArray=(i<<1)+nSrcDisp2;
		pDispArray++;
	}
	VEC_SetVal(((nm32s*)pKernel),10,(int)pDispArray);			// ar0 displacement for first array
	for(int i=0;i< nDispArraySize; i++){
		*pDispArray=(i<<1)+nSrcDisp3;
		pDispArray++;
	}

	VEC_Fill((nm32s*)pWeightMatrix,0,nWeightsSize);

	for(int i=0; i<nSize;i++){
		VEC_SetVal(pWeightMatrix,8*2+i*2 , pWeights[i]);
		VEC_SetVal(pWeightMatrix,8*2+i*2+3,pWeights[i]);
	}
	// Total size = 12+(16+nSize)/8*4+1+(16+nSize)*2=13+(16+nSize)*5/2
	int AllocSize=12+nDispArraySize*4+nWeightsSize;
	return AllocSize;
#endif	
}

int SIG_GetFilterKernelSize_8s32s(int nSize){
	int nWeightsSize=(8+nSize+1+7)*2; //Size in int32 words
	
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);
	int nDisp2=GetDisp2(nSize);
	int nDisp3=GetDisp3(nSize);

	int nNumberOfArrays0=(nSize+8+1-nDisp0+7)/8;
	int nNumberOfArrays1=(nSize+8+1-nDisp1+7)/8;
	int nNumberOfArrays2=(nSize+8+1-nDisp2+7)/8;
	int nNumberOfArrays3=(nSize+8+1-nDisp3+7)/8;
	

	int nDispArraySize  =(nSize+8+1+7)/8;
	nDispArraySize+=nDispArraySize&1;


	int nSrcDisp0=(((nSize/2)-0)+7)/8;
	int nSrcDisp1=(((nSize/2)-2)+7)/8;
	int nSrcDisp2=(((nSize/2)-4)+7)/8;
	int nSrcDisp3=(((nSize/2)-6)+7)/8;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;
	nSrcDisp2*=-2;
	nSrcDisp3*=-2;

	// Total size = 12+(16+nSize)/8*4+1+(16+nSize)*2=13+(16+nSize)*5/2
	int AllocSize=12+nDispArraySize*4+nWeightsSize;
	return AllocSize;
}

/*
void SIG_CreateFilter_8s32s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	int nWeightsSize=(8+nSize+1+7)*2; //Size in int32 words
	int nDisp0=GetDisp0(nSize);
	int nDisp1=GetDisp1(nSize);
	int nDisp2=GetDisp2(nSize);
	int nDisp3=GetDisp3(nSize);

	int nNumberOfArrays0=(nSize+8+1-nDisp0+7)/8;
	int nNumberOfArrays1=(nSize+8+1-nDisp1+7)/8;
	int nNumberOfArrays2=(nSize+8+1-nDisp2+7)/8;
	int nNumberOfArrays3=(nSize+8+1-nDisp3+7)/8;


	int nDispArraySize  =(nSize+8+1+7)/8;
	nDispArraySize+=nDispArraySize&1;

	//nm32s* pDispArray	=((nm32s*)pKernel)+12;
	//nm32s* pWeightMatrix =VEC_Addr((nm32s*)pDispArray,nDispArraySize*4);	
	//VEC_Fill((nm32s*)pWeightMatrix,0,nWeightsSize);
	int AllocSize=12+nDispArraySize*4+nWeightsSize;
	VEC_Malloc((nm32s**)pKernel,AllocSize,hint);
	if (*pKernel==0) return;
	SIG_SetFilter_8s32s(pWeights, nSize, *pKernel);
}
*/

//--------------------------------------------------------------------------------------------------------------
template<> int CSIG_FIR<nm8s,nm32s>::init(int NumWeights, void* (*malloc32_func)(unsigned),void (*free32_func)(void*)){
	pfFree32=free32_func;
	nWeights=NumWeights;
	int KernelSize=SIG_GetFilterKernelSize_8s32s(nWeights);
	pKernel=(nm64s*)malloc32_func(KernelSize);
	return (pKernel!=0);
}

template<> CSIG_FIR<nm8s,nm32s>::CSIG_FIR(int NumWeights, void* (*malloc32_func)(unsigned),void (*free32_func)(void*)){
	init(NumWeights, malloc32_func,free32_func);
}


template<> void* CSIG_FIR<nm8s,nm32s>::setWeights(int* pWeights){
	if (pKernel)
		SIG_SetFilter_8s32s(pWeights, nWeights, pKernel);
	return pWeights;
}
template<> void CSIG_FIR<nm8s,nm32s>::filter(nm8s* pSrcVec, nm32s* pDstVec, int nSize){
	SIG_Filter(pSrcVec,pDstVec,nSize,pKernel);
}
template<> CSIG_FIR<nm8s,nm32s>::~CSIG_FIR(){
	if (pKernel) 
		pfFree32(pKernel);
}
