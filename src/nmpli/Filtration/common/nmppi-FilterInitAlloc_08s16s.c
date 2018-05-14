
//#include <string.h>
//#include "nmpp.h"
//#include "nmpls.h"
//#include "nmpls/sFiltration.h"


//#include "nmpli.h"
#include "nmpli/filter.h"
#include "nmplv/vSupport.h"
#include "nmplv/vInit.h"
#include "malloc32.h"
#include <string.h>

typedef struct SS_IMG_FilterKernel {
#ifdef __NM__
	nm32s* pDispArray;
	nm32s* pWeightMatrix;	
#else 
	nm32s* 	pDispArray;
	nm32s* 	pWeightMatrix;	
	int 	nKerWidth;
	int 	nKerHeight;
#endif
} S_IMG_FilterKernel;

//	nSize=3  nDisp=1,5 
//  nSize=5  nDisp=2,6 
//  nSize=7  nDisp=3,7 
//  nSize=9  nDisp=4,8 
//	nSize=11 nDisp=5,1 
//	nSize=13 nDisp=6,2 



static int GetDisp0(int nSize)
{
	return ((nSize-3)/2%8+1);
}

static int GetDisp1(int nSize)
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

int nmppiFilterInit_8s16s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, NmppiFilterState* pKernel)
{

#ifndef __NM__
	//((int*)pKernel)[0]=nKerWidth;
	//((int*)pKernel)[1]=nKerHeight;
	
	S_IMG_FilterKernel* psKernel=(S_IMG_FilterKernel*) pKernel;
	psKernel->nKerHeight=nKerHeight;
	psKernel->nKerWidth =nKerWidth;
	psKernel->pDispArray=0;
	psKernel->pWeightMatrix=(nm32s*)(psKernel+1);
	memcpy(psKernel->pWeightMatrix,pWeights,nKerWidth*nKerHeight*4);

	//memcpy(pKernel+1,(nm32s*)pWeights,nKerWidth*nKerHeight<<2);
	
	return nKerWidth*nKerHeight;
#else

	int nWeightsSize=(8+nKerWidth+3+7)*2; //Size of weight block in int32 words
		
	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);

	int nNumberOfArrays0=(8+nKerWidth+3-nDisp0+7)/8;
	int nNumberOfArrays1=(8+nKerWidth+3-nDisp1+7)/8;
	// Max size of disp arrays	= (nNumberOfArrays0+nNumberOfArrays1)*nKerHeight=
	//							= 2*(18+nKerWidth)/8*nKerHeight
	//							= (18+nKerWidth)*nKerHeight/4

	int nDispArraySize=(nNumberOfArrays0+nNumberOfArrays1)*nKerHeight ; // Total size of disp array segment
	nDispArraySize+=nDispArraySize&1;

	nm32s* pDispArray	=((nm32s*)pKernel)+6;
	nm16s* pWeightMatrix =(nm16s*)nmppsAddr_32s((nm32s*)pDispArray,nDispArraySize);	
	

	int nSrcDisp0=(((nKerWidth/2)-0)+7)/8;
	int nSrcDisp1=(((nKerWidth/2)-4)+7)/8;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;


	int disp;

	//-------------- Disp Matrix 0 ------------------
	disp=-(nImgWidth>>2)*(nKerHeight>>1);

	nmppsPut_32s(((nm32s*)pKernel),0,nNumberOfArrays0*nKerHeight);// Number of arrays
	nmppsPut_32s(((nm32s*)pKernel),1,(int)pDispArray);					// ar0 displacement for first array

	
	for(int j=0; j<nKerHeight; j++){
		for(int i=0; i<nNumberOfArrays0; i++){
			*pDispArray=(i<<1)+nSrcDisp0+disp;
			pDispArray++;
		}
		disp+=(nImgWidth>>2);
	}

	//-------------- Disp Matrix 1 ------------------
	disp=-(nImgWidth>>2)*(nKerHeight>>1);
	nmppsPut_32s(((nm32s*)pKernel),3, nNumberOfArrays1*nKerHeight);// Number of arrays
	nmppsPut_32s(((nm32s*)pKernel),4,(int)pDispArray);			 // ar0 displacement for first array
	
	for(int j=0; j<nKerHeight; j++){
		for(int i=0; i<nNumberOfArrays1; i++){
			*pDispArray=(i<<1)+nSrcDisp1+disp;
			pDispArray++;
		}
		disp+=(nImgWidth>>2);
	}

	//-------------- Weight Matrix initilaization ------
	// Max size of weight arrays= (nNumberOfArrays0+nNumberOfArrays1)*nKerHeight*8*4/2=
	//							= 2*(18+nKerWidth)/8*nKerHeight*16
	//							= (18+nKerWidth)*nKerHeight*4
	
	
	nmppsSet_32s((nm32s*)pWeightMatrix,0,(nNumberOfArrays0+nNumberOfArrays1)*8*2*nKerHeight);

	//-------------- Weight Matrix 0 -------------------
	nmppsPut_32s(((nm32s*)pKernel),2,((int)pWeightMatrix));	// weights for first array
	for(int j=0,k=0; j<nKerHeight; j++){
		for(int i=0; i<nKerWidth;i++,k++){
			nmppsPut_16s(pWeightMatrix,8*4+i*4	-nDisp0*2*2, pWeights[k]);
			nmppsPut_16s(pWeightMatrix,8*4+i*4+5	-nDisp0*2*2, pWeights[k]);
			nmppsPut_16s(pWeightMatrix,8*4+i*4+10 -nDisp0*2*2, pWeights[k]);
			nmppsPut_16s(pWeightMatrix,8*4+i*4+15 -nDisp0*2*2, pWeights[k]);
		}
		pWeightMatrix=nmppsAddr_16s(pWeightMatrix,nNumberOfArrays0*8*4);
	}

	//-------------- Weight Matrix 1 ------------------
	nmppsPut_32s(((nm32s*)pKernel),5,((int)pWeightMatrix));	// weights for first array
	for(int j=0,k=0; j<nKerHeight; j++){
		for(int i=0; i<nKerWidth;i++,k++){
			nmppsPut_16s(pWeightMatrix,8*4+i*4	-nDisp1*2*2, pWeights[k]);
			nmppsPut_16s(pWeightMatrix,8*4+i*4+5	-nDisp1*2*2, pWeights[k]);
			nmppsPut_16s(pWeightMatrix,8*4+i*4+10 -nDisp1*2*2, pWeights[k]);
			nmppsPut_16s(pWeightMatrix,8*4+i*4+15 -nDisp1*2*2, pWeights[k]);
		}
		pWeightMatrix=nmppsAddr_16s(pWeightMatrix,nNumberOfArrays1*8*4);
	}
	
	// Total max size = 6+(18+nKerWidth)*nKerHeight/8*2+1+(18+nKerWidth)*nKerHeight*4=
	//				  = 8+(18+nKerWidth)*nKerHeight*5/4
	
	//return 6+(18+nKerWidth)*nKerHeight*5/4;
	int AllocSize=6+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1)*8*2*nKerHeight;
	return AllocSize;
#endif
}


int static nmppiFilterGetStateSize32_8s16s(int nKerWidth, int nKerHeight){
	int nWeightsSize=(8+nKerWidth+3+7)*2; //Size of weight block in int32 words
	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);
	int nNumberOfArrays0=(8+nKerWidth+3-nDisp0+7)/8;
	int nNumberOfArrays1=(8+nKerWidth+3-nDisp1+7)/8;
	int nDispArraySize=(nNumberOfArrays0+nNumberOfArrays1)*nKerHeight + (nDispArraySize&1); // Total size of disp array segment
	int AllocSize=6+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1)*8*2*nKerHeight;
	return AllocSize;
}


//--------------------------------------------------------------------------------------------------------------
int nmppiFilterInitAlloc_8s16s(NmppiFilterState** ppState, int* pKernel, int kerWidth, int kerHeight, int imgWidth)
{
	//pfFree32=free32_func;
	//nKerWidth=n_KerWidth;
	//nKerHeight=n_KerHeight;
	int stateSize=nmppiFilterGetStateSize32_8s16s( kerWidth,  kerHeight);
	*ppState=(nm64s*)malloc32(stateSize,-1);
	if (ppState){
		nmppiFilterInit_8s16s(pKernel,kerWidth,  kerHeight, imgWidth, *ppState);
		return 0;
	}
	return -1;
}

void nmppiFilterFree(NmppiFilterState* pState){
	nmppsFree(pState);
}

