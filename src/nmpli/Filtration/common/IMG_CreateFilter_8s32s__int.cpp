#include <string.h>
#include "nmplv.h"
#include "nmpls.h"
#include "nmpli.h"



//	nSize=3  nDisp=1,7,5,3 
//  nSize=5  nDisp=2,8,6,4 
//  nSize=7  nDisp=3,1,7,5 
//  nSize=9  nDisp=4,2,8,6 
//	nSize=11 nDisp=5,3,1,7 
//	nSize=13 nDisp=6,4,2,8 



static inline int GetDisp0(int nSize)
{
	return ((nSize-3)/2%8+1);
}

static inline int GetDisp1(int nSize)
{
	return ((nSize+9)/2)%8+1;
}

static inline int GetDisp2(int nSize)
{
	return ((nSize+5)/2)%8+1;
}

static inline int GetDisp3(int nSize)
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

int IMG_SetFilter_8s32s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s* pKernel)
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

	int nWeightsSize=(8+nKerWidth+1+7)*2; //Size in int32 words
	
	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);
	int nDisp2=GetDisp2(nKerWidth);
	int nDisp3=GetDisp3(nKerWidth);

	int nNumberOfArrays0=(nKerWidth+8+1-nDisp0+7)/8;
	int nNumberOfArrays1=(nKerWidth+8+1-nDisp1+7)/8;
	int nNumberOfArrays2=(nKerWidth+8+1-nDisp2+7)/8;
	int nNumberOfArrays3=(nKerWidth+8+1-nDisp3+7)/8;
	
	int nDispArraySize  =(nKerWidth+8+1+7)*4*nKerHeight/8;
	nDispArraySize+=nDispArraySize&1;
	

	nm32s* pDispArray	=((nm32s*)pKernel)+12;
	nm32s* pWeightMatrix =VEC_Addr((nm32s*)pDispArray,nDispArraySize);	

	int nSrcDisp0=(((nKerWidth/2)-0)+7)/8;
	int nSrcDisp1=(((nKerWidth/2)-2)+7)/8;
	int nSrcDisp2=(((nKerWidth/2)-4)+7)/8;
	int nSrcDisp3=(((nKerWidth/2)-6)+7)/8;

	nSrcDisp0*=-2;
	nSrcDisp1*=-2;
	nSrcDisp2*=-2;
	nSrcDisp3*=-2;

	// Max size of disp arrays	= (nNumberOfArrays0+nNumberOfArrays1+nNumberOfArrays2+nNumberOfArrays3)*nKerHeight=
	//							= 4*(16+nKerWidth)/8*nKerHeight
	//							= (16+nKerWidth)*nKerHeight/2

	int disp;

	//-------------- Disp Matrix 0 ------------------
	VEC_SetVal(((nm32s*)pKernel),0,nNumberOfArrays0*nKerHeight);// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),1,(int)pDispArray);	
	disp=-(nImgWidth>>2)*(nKerHeight>>1);
	for(int j=0; j< nKerHeight; j++){
		for(int i=0; i< nNumberOfArrays0; i++){
			*pDispArray=(i<<1)+disp+nSrcDisp0;
			pDispArray++;
		}
		disp+=(nImgWidth>>2);
	}

	//-------------- Disp Matrix 1 ------------------
	VEC_SetVal(((nm32s*)pKernel),3,nNumberOfArrays1*nKerHeight);// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),4,(int)pDispArray);	
	disp=-(nImgWidth>>2)*(nKerHeight>>1);
	for(int j=0; j< nKerHeight; j++){
		for(int i=0; i< nNumberOfArrays1; i++){
			*pDispArray=(i<<1)+disp+nSrcDisp1;
			pDispArray++;
		}
		disp+=(nImgWidth>>2);
	}

	//-------------- Disp Matrix 2 ------------------
	VEC_SetVal(((nm32s*)pKernel),6,nNumberOfArrays2*nKerHeight);// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),7,(int)pDispArray);	
	disp=-(nImgWidth>>2)*(nKerHeight>>1);
	for(int j=0; j< nKerHeight; j++){
		for(int i=0; i< nNumberOfArrays2; i++){
			*pDispArray=(i<<1)+disp+nSrcDisp2;
			pDispArray++;
		}
		disp+=(nImgWidth>>2);
	}

	//-------------- Disp Matrix 3 ------------------
	VEC_SetVal(((nm32s*)pKernel),9,nNumberOfArrays3*nKerHeight);// Number of arrays
	VEC_SetVal(((nm32s*)pKernel),10,(int)pDispArray);	
	disp=-(nImgWidth>>2)*(nKerHeight>>1);
	for(int j=0; j< nKerHeight; j++){
		for(int i=0; i< nNumberOfArrays3; i++){
			*pDispArray=(i<<1)+disp+nSrcDisp3;
			pDispArray++;
		}
		disp+=(nImgWidth>>2);
	}
	
	//-------------- Weight Matrix initilaization ------
	// Max size of weight arrays= nNumberOfArrays0*nKerHeight*4=
	//							= (16+nKerWidth)/8*nKerHeight*8*2*4=
	//							= (16+nKerWidth)*nKerHeight*8


	VEC_Fill((nm32s*)pWeightMatrix,0,(nNumberOfArrays0+nNumberOfArrays1+nNumberOfArrays2+nNumberOfArrays3)*nKerHeight*8*2);
	
	VEC_SetVal(((nm32s*)pKernel),2,(int)pWeightMatrix);		// weights for first array
	for(int j=0,k=0; j<nKerHeight; j++){
		for(int i=0; i<nKerWidth; i++,k++){
			VEC_SetVal(pWeightMatrix,8*2+i*2	-nDisp0*2, pWeights[k]);
			VEC_SetVal(pWeightMatrix,8*2+i*2+3	-nDisp0*2, pWeights[k]);
		}
		pWeightMatrix=VEC_Addr(pWeightMatrix,nNumberOfArrays0*8*2);
	}

	VEC_SetVal(((nm32s*)pKernel),5,(int)pWeightMatrix);		// weights for first array
	for(int j=0,k=0; j<nKerHeight; j++){
		for(int i=0; i<nKerWidth; i++,k++){
			VEC_SetVal(pWeightMatrix,8*2+i*2	-nDisp1*2, pWeights[k]);
			VEC_SetVal(pWeightMatrix,8*2+i*2+3	-nDisp1*2, pWeights[k]);
		}
		pWeightMatrix=VEC_Addr(pWeightMatrix,nNumberOfArrays1*8*2);
	}
	
	VEC_SetVal(((nm32s*)pKernel),8,(int)pWeightMatrix);		// weights for first array
	for(int j=0,k=0; j<nKerHeight; j++){
		for(int i=0; i<nKerWidth; i++,k++){
			VEC_SetVal(pWeightMatrix,8*2+i*2	-nDisp2*2, pWeights[k]);
			VEC_SetVal(pWeightMatrix,8*2+i*2+3	-nDisp2*2, pWeights[k]);
		}
		pWeightMatrix=VEC_Addr(pWeightMatrix,nNumberOfArrays2*8*2);
	}
	
	VEC_SetVal(((nm32s*)pKernel),11,(int)pWeightMatrix);		// weights for first array
	for(int j=0,k=0; j<nKerHeight; j++){
		for(int i=0; i<nKerWidth; i++,k++){
			VEC_SetVal(pWeightMatrix,8*2+i*2	-nDisp3*2, pWeights[k]);
			VEC_SetVal(pWeightMatrix,8*2+i*2+3	-nDisp3*2, pWeights[k]);
		}
		pWeightMatrix=VEC_Addr(pWeightMatrix,nNumberOfArrays3*8*2);
	}

	// Total size = 12+1+(16+nKerWidth)*nKerHeight/2+(16+nKerWidth)*nKerHeight*8
	//			  = 14+(16+nKerWidth)*nKerHeight*17/8;
	
	int AllocSize=12+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1+nNumberOfArrays2+nNumberOfArrays3)*nKerHeight*8*2;
	return AllocSize;
#endif	

}
/*
void IMG_CreateFilter_8s32s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s** pKernel, int nHint)
{
	//VEC_Malloc((nm32s**)pKernel,14+(16+nKerWidth)*nKerHeight*17/8,nHint);
	int nWeightsSize=(8+nKerWidth+1+7)*2; //Size in int32 words

	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);
	int nDisp2=GetDisp2(nKerWidth);
	int nDisp3=GetDisp3(nKerWidth);

	int nNumberOfArrays0=(nKerWidth+8+1-nDisp0+7)/8;
	int nNumberOfArrays1=(nKerWidth+8+1-nDisp1+7)/8;
	int nNumberOfArrays2=(nKerWidth+8+1-nDisp2+7)/8;
	int nNumberOfArrays3=(nKerWidth+8+1-nDisp3+7)/8;

	int nDispArraySize  =(nKerWidth+8+1+7)*4*nKerHeight/8;
	nDispArraySize+=nDispArraySize&1;


	nm32s* pDispArray	=((nm32s*)pKernel)+12;
	nm32s* pWeightMatrix =VEC_Addr((nm32s*)pDispArray,nDispArraySize);	
	
	int AllocSize=12+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1+nNumberOfArrays2+nNumberOfArrays3)*nKerHeight*8*2;
	VEC_Malloc((nm32s**)pKernel,AllocSize,nHint);
	if (*pKernel==0) return;
	//VEC_Fill((nm32s*)*pKernel,5,AllocSize);



	IMG_SetFilter_8s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, *pKernel);
}
*/

int IMG_GetFilterKernelSize32_8s32s(int nKerWidth, int nKerHeight)
{
/*
	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);
	int nDisp2=GetDisp2(nKerWidth);
	int nDisp3=GetDisp3(nKerWidth);

	int nNumberOfArrays0=(nKerWidth+8+1-nDisp0+7)/8;
	int nNumberOfArrays1=(nKerWidth+8+1-nDisp1+7)/8;
	int nNumberOfArrays2=(nKerWidth+8+1-nDisp2+7)/8;
	int nNumberOfArrays3=(nKerWidth+8+1-nDisp3+7)/8;

	int nDispArraySize  =(nKerWidth+8+1+7)*4*nKerHeight/8;
	nDispArraySize+=nDispArraySize&1;

	int AllocSize=12+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1+nNumberOfArrays2+nNumberOfArrays3)*nKerHeight*8*2;
	return AllocSize;
*/

	int nWeightsSize=(8+nKerWidth+1+7)*2; //Size in int32 words
	
	int nDisp0=GetDisp0(nKerWidth);
	int nDisp1=GetDisp1(nKerWidth);
	int nDisp2=GetDisp2(nKerWidth);
	int nDisp3=GetDisp3(nKerWidth);

	int nNumberOfArrays0=(nKerWidth+8+1-nDisp0+7)/8;
	int nNumberOfArrays1=(nKerWidth+8+1-nDisp1+7)/8;
	int nNumberOfArrays2=(nKerWidth+8+1-nDisp2+7)/8;
	int nNumberOfArrays3=(nKerWidth+8+1-nDisp3+7)/8;
	
	int nDispArraySize  =(nKerWidth+8+1+7)*4*nKerHeight/8;
	nDispArraySize+=nDispArraySize&1;
	

	//nm32s* pDispArray	=((nm32s*)pKernel)+12;
	//nm32s* pWeightMatrix =VEC_Addr((nm32s*)pDispArray,nDispArraySize);	


	int AllocSize=12+nDispArraySize+(nNumberOfArrays0+nNumberOfArrays1+nNumberOfArrays2+nNumberOfArrays3)*nKerHeight*8*2;
	return AllocSize;
}

//--------------------------------------------------------------------------------------------------------------
template<> CIMG_FIR<nm8s,nm32s>::CIMG_FIR(int n_KerWidth, int n_KerHeight, void* (*malloc32_func)(unsigned), void (*free32_func)(void*)){
	pfFree32=free32_func;
	nKerWidth=n_KerWidth;
	nKerHeight=n_KerHeight;
	int KernelSize=IMG_GetFilterKernelSize32_8s32s( nKerWidth,  nKerHeight);
	pKernel=(nm64s*)malloc32_func(KernelSize);
}

template<> void* CIMG_FIR<nm8s,nm32s>::SetWeights(int* pWeights, int nImgWidth){
	if (pKernel)
		IMG_SetFilter_8s32s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel);
	return (void*)pKernel;
}

template<> void CIMG_FIR<nm8s,nm32s>::Filter(nm8s* pSrcImg, nm32s* pDstImg, int nImgWidth,int nImgHeight){
	IMG_Filter(pSrcImg, pDstImg, nImgWidth, nImgHeight, pKernel);
}

template<> CIMG_FIR<nm8s,nm32s>::~CIMG_FIR(){
	if (pKernel) 
		pfFree32(pKernel); 
}



