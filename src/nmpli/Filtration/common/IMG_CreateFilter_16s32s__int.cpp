 #include <string.h>
#include "nmpp.h"
#include "nmpls.h"
#include "nmpli.h"



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

int nmppiSetFilter_16s32s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s* pKernel)
{
#ifndef __NM__
	S_nmppiFilterKernel* psKernel=(S_nmppiFilterKernel*) pKernel;
	psKernel->nKerWidth=nKerWidth;
	psKernel->nKerHeight=nKerHeight;
	psKernel->pDispArray=0;
	psKernel->pWeightMatrix=(nm32s*)(psKernel+1);	
	memcpy(psKernel->pWeightMatrix,(nm32s*)pWeights,nKerWidth*nKerHeight*4);
	//((int*)pKernel)[0]=nKerWidth;
	//((int*)pKernel)[1]=nKerHeight;
	//memcpy(pKernel+1,(nm32s*)pWeights,nKerWidth*nKerHeight<<2);
	return nKerWidth*nKerHeight;
#else



	int nWeightsSize=(4+nKerWidth+1+3)*2; //Size in int32 words
	
	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);
	
	int nNumberOfArrays0=(4+nKerWidth+1-nDisp0+3)/4;
	int nNumberOfArrays1=(4+nKerWidth+1-nDisp1+3)/4;
	int nDispArraySize=(4+nKerWidth+1+3)*nKerHeight*2/4;
	nDispArraySize+=nDispArraySize&1;

	nm32s* pDispArray	=((nm32s*)pKernel)+6;
	nm32s* pWeightMatrix =nmppsAddr_32s((nm32s*)pDispArray,nDispArraySize);	

	int nSrcDisp0=(((nKerWidth/2)-0)+3)/4;
	int nSrcDisp1=(((nKerWidth/2)-2)+3)/4;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;

	// Max size of disp arrays	= (nNumberOfArrays0+nNumberOfArrays1)*nKerHeight=
	//							= 2*(8+nKerWidth)/4*nKerHeight
	//							= (8+nKerWidth)*nKerHeight/2

	int disp;
	//-------------- Disp Matrix 0 ------------------
	disp=-(nImgWidth>>1)*(nKerHeight>>1);
	nmppsPut_32s(((nm32s*)pKernel),0,(int)nNumberOfArrays0*nKerHeight);		// Number of arrays
	nmppsPut_32s(((nm32s*)pKernel),1,(int)pDispArray);						// ar0 displacement for first array
	for(int j=0; j<nKerHeight; j++){
		for(int i=0; i< nNumberOfArrays0; i++){
			*pDispArray=(i<<1)+disp+nSrcDisp0;
			pDispArray++;
		}
		disp+=(nImgWidth>>1);
	}
	//-------------- Disp Matrix 1 ------------------
	disp=-(nImgWidth>>1)*(nKerHeight>>1);
	nmppsPut_32s(((nm32s*)pKernel),3,(int)nNumberOfArrays1*nKerHeight);		// Number of arrays
	nmppsPut_32s(((nm32s*)pKernel),4,(int)pDispArray);						// ar0 displacement for first array

	for(int j=0; j<nKerHeight; j++){
		for(int i=0; i< nNumberOfArrays1; i++){
			*pDispArray=(i<<1)+disp+nSrcDisp1;
			pDispArray++;
		}
		disp+=(nImgWidth>>1);
	}

	//-------------- Weight Matrix initilaization ------
	// Max size of weight arrays= nNumberOfArrays0*4*2+nNumberOfArrays1*4*2=
	//							= (8+nKerWidth)*2*nKerHeight*2=
	//							= (8+nKerWidth)*nKerHeight*4

	nmppsSet_32s((nm32s*)pWeightMatrix,0,(nNumberOfArrays0+nNumberOfArrays1)*nKerHeight*4*2);

	//-------------- Weight Matrix 0 -------------------
	nmppsPut_32s(((nm32s*)pKernel),2,((int)pWeightMatrix));	// weights for first array
	for(int j=0,k=0; j<nKerHeight; j++ ){
		for(int i=0; i<nKerWidth; i++,k++){
			nmppsPut_32s(pWeightMatrix,4*2+i*2  -nDisp0*2,pWeights[k]);
			nmppsPut_32s(pWeightMatrix,4*2+i*2+3-nDisp0*2,pWeights[k]);
		}
		pWeightMatrix=nmppsAddr_32s(pWeightMatrix,nNumberOfArrays0*4*2);
	}

	//-------------- Weight Matrix 1 -------------------
	nmppsPut_32s(((nm32s*)pKernel),5,((int)pWeightMatrix));	// weights for first array
	for(int j=0,k=0; j<nKerHeight; j++ ){
		for(int i=0; i<nKerWidth; i++,k++){
			nmppsPut_32s(pWeightMatrix,4*2+i*2  -nDisp1*2,pWeights[k]);
			nmppsPut_32s(pWeightMatrix,4*2+i*2+3-nDisp1*2,pWeights[k]);
		}
		pWeightMatrix=nmppsAddr_32s(pWeightMatrix,nNumberOfArrays1*4*2);
	}

	// Total max size = 6+(8+nKerWidth)*nKerHeight/2+1+(8+nKerWidth)*nKerHeight*4=
	//				  = 8+(8+nKerWidth)*nKerHeight*9/4
	//return 8+(8+nKerWidth)*nKerHeight*9/4;
	int AllocSize=6+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1)*nKerHeight*4*2;
	return AllocSize;
#endif	
}
/*
void nmppiCreateFilter_16s32s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s** pKernel, int nHint)
{
	int nWeightsSize=(4+nKerWidth+1+3)*2; //Size in int32 words

	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);

	int nNumberOfArrays0=(4+nKerWidth+1-nDisp0+3)/4;
	int nNumberOfArrays1=(4+nKerWidth+1-nDisp1+3)/4;
	int nDispArraySize=(4+nKerWidth+1+3)*nKerHeight*2/4;
	nDispArraySize+=nDispArraySize&1;

	//nm32s* pDispArray	=((nm32s*)pKernel)+6;
	//nm32s* pWeightMatrix =nmppsAddr_32s((nm32s*)pDispArray,nDispArraySize);	
	//nmppsSet_32s((nm32s*)pWeightMatrix,0,(nNumberOfArrays0+nNumberOfArrays1)*nKerHeight*4*2);


	int AllocSize=6+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1)*nKerHeight*4*2;
	nmppsMalloc_32s((nm32s**)pKernel, AllocSize,nHint);
	if (*pKernel==0) return;
	//nmppsSet_32s((nm32s*)*pKernel,5,AllocSize);
	nmppiSetFilter_16s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, *pKernel);
}*/

int nmppiGetFilterKernelSize32_16s32s(int nKerWidth, int nKerHeight)
{
	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);

	int nNumberOfArrays0=(4+nKerWidth+1-nDisp0+3)/4;
	int nNumberOfArrays1=(4+nKerWidth+1-nDisp1+3)/4;
	int nDispArraySize=(4+nKerWidth+1+3)*nKerHeight*2/4;
	nDispArraySize+=nDispArraySize&1;


	int AllocSize=6+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1)*nKerHeight*4*2;
	return AllocSize;
}


/*
//--------------------------------------------------------------------------------------------------------------
template<> CnmppiFIR<nm16s,nm32s>::CnmppiFIR(int n_KerWidth, int n_KerHeight, void* (*malloc32_func)(unsigned), void (*free32_func)(void*)){
	pfFree32=free32_func;
	nKerWidth=n_KerWidth;
	nKerHeight=n_KerHeight;
	int KernelSize=nmppiGetFilterKernelSize32_16s32s( nKerWidth,  nKerHeight);
	pKernel=(nm64s*)malloc32_func(KernelSize);
}

template<> void* CnmppiFIR<nm16s,nm32s>::SetWeights(int* pWeights, int nImgWidth){
	if (pKernel)
		nmppiSetFilter_16s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel);
	return (void*)pKernel;
}

template<> void CnmppiFIR<nm16s,nm32s>::Filter(nm16s* pSrcImg, nm32s* pDstImg, int nImgWidth,int nImgHeight){
	nmppiFilter(pSrcImg, pDstImg, nImgWidth, nImgHeight, pKernel);
}

template<> CnmppiFIR<nm16s,nm32s>::~CnmppiFIR(){
	if (pKernel) 
		pfFree32(pKernel); 
}

*/