 #include "nmpls.h"
#include "nmplv.h"
#include "string.h"
	// f(3) =7;
	// f(5) =6;
	// f(7) =5;
	// f(9) =4;
	// f(11)=3;
	// f(13)=2;
	// f(15)=1
	// f(17)=0
	// f(19)=7
	// f(21)=6
inline int GetDisp(int nSize)
{
	return (7-((nSize-3)/2)%8);
}


	// f(3)=3
	// f(5)=3
	// f(7)=3
	// f(9)=3
	// f(11)=3 
	// f(13)=3
	// f(15)=3
	// f(17)=3
	// f(19)=5
	// f(21)=5
	// f(23)=5
	// f(25)=5

int Sig_GetNumberOfArrays_Filter_8s8s(int nSize)
{
	return ((nSize+13)/16)*2+1;	
}


void Sig_SetDisp_Filter_8s8s(int nNumberOfArrays, int nDisp, int* pDispArray)
{
	for(int i=0;i< nNumberOfArrays; i++){
		pDispArray[i]=(i<<1)+nDisp;
	}
}


void Sig_SetWeight_Filter_8s8s(int* pWeights, int nSize, int nNumberOfArrays, nm64s* pDst)
{
	nm8s* pWeightMatrix=(nm8s*) pDst;
	VEC_Fill(pWeightMatrix,0,64*nNumberOfArrays);

	int disp=GetDisp(nSize);
	for(int i=0; i<nSize;i++){
		VEC_SetVal(pWeightMatrix,(i+disp)*8+9*0,pWeights[i]);
		VEC_SetVal(pWeightMatrix,(i+disp)*8+9*1,pWeights[i]);
		VEC_SetVal(pWeightMatrix,(i+disp)*8+9*2,pWeights[i]);
		VEC_SetVal(pWeightMatrix,(i+disp)*8+9*3,pWeights[i]);
		VEC_SetVal(pWeightMatrix,(i+disp)*8+9*4,pWeights[i]);
		VEC_SetVal(pWeightMatrix,(i+disp)*8+9*5,pWeights[i]);
		VEC_SetVal(pWeightMatrix,(i+disp)*8+9*6,pWeights[i]);
		VEC_SetVal(pWeightMatrix,(i+disp)*8+9*7,pWeights[i]);
	}
}

int SIG_SetFilter_8s8s(int* pWeights, int nSize, nm64s* pKernel)
{
#ifndef __NM__
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
#else

	int nNumberOfArrays=Sig_GetNumberOfArrays_Filter_8s8s(nSize);
	
	nm32s* pDispArray	=(nm32s*)VEC_Addr((nm32s*)pKernel,2);
	nm64s* pWeightMatrix=(nm64s*)VEC_Addr((nm32s*)pKernel,nNumberOfArrays+3);	
	
	VEC_SetVal(((nm32s*)pKernel),0,nNumberOfArrays);
	VEC_SetVal(((nm32s*)pKernel),1,nNumberOfArrays+3);
	VEC_SetVal(((nm32s*)pKernel),nNumberOfArrays+2, 0xCCCCCCCC);
	
		
	Sig_SetDisp_Filter_8s8s(nNumberOfArrays,-((nNumberOfArrays>>1)<<1),pDispArray);
	Sig_SetWeight_Filter_8s8s(pWeights, nSize, nNumberOfArrays,pWeightMatrix);
	int AllocSize=2+nNumberOfArrays+3+nNumberOfArrays*16;
	return AllocSize;
#endif	
}

int SIG_GetFilterKernelSize_8s8s(int nSize){
	int nNumberOfArrays=Sig_GetNumberOfArrays_Filter_8s8s(nSize);
	int AllocSize=2+nNumberOfArrays+3+nNumberOfArrays*16;
	return AllocSize;
}
/*
void SIG_CreateFilter_8s8s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	int nNumberOfArrays=Sig_GetNumberOfArrays_Filter_8s8s(nSize);
	int AllocSize=2+nNumberOfArrays+3+nNumberOfArrays*16;
	VEC_Malloc((nm32s**)pKernel,AllocSize,hint);
	if (*pKernel==0) return;
	SIG_SetFilter_8s8s(pWeights, nSize, *pKernel);
}

*/


//--------------------------------------------------------------------------------------------------------------
template<> CSIG_FIR<nm8s,nm8s>::CSIG_FIR(int NumWeights, void* (*malloc32_func)(unsigned),void (*free32_func)(void*)){
	pfFree32=free32_func;
	nWeights=NumWeights;
	int KernelSize=SIG_GetFilterKernelSize_8s8s(nWeights);
	pKernel=(nm64s*)malloc32_func(KernelSize);
}

template<> void* CSIG_FIR<nm8s,nm8s>::setWeights(int* pWeights){
	if (pKernel)
		SIG_SetFilter_8s8s(pWeights, nWeights, pKernel);
	return pWeights;
}
template<> void CSIG_FIR<nm8s,nm8s>::filter(nm8s* pSrcVec, nm8s* pDstVec, int nSize){
	SIG_Filter(pSrcVec,pDstVec,nSize,pKernel);
}
template<> CSIG_FIR<nm8s,nm8s>::~CSIG_FIR(){
	if (pKernel) 
		pfFree32(pKernel);
}
