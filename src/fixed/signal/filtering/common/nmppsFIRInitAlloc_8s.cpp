#include "nmpls.h"
#include "nmpp.h"
#include "string.h"

#ifdef __cplusplus
		extern "C" {
#endif

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
__INLINE__ int GetDisp(int nSize)
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
	int i;
	for(i=0;i< nNumberOfArrays; i++){
		pDispArray[i]=(i<<1)+nDisp;
	}
}


void Sig_SetWeight_Filter_8s8s(int* pWeights, int nSize, int nNumberOfArrays, nm64s* pDst)
{
	nm8s* pWeightMatrix=(nm8s*) pDst;
	nmppsSet_8s(0, pWeightMatrix, 64*nNumberOfArrays);

	int disp=GetDisp(nSize);
	for(int i=0; i<nSize;i++){
		nmppsPut_8s(pWeightMatrix,(i+disp)*8+9*0,pWeights[i]);
		nmppsPut_8s(pWeightMatrix,(i+disp)*8+9*1,pWeights[i]);
		nmppsPut_8s(pWeightMatrix,(i+disp)*8+9*2,pWeights[i]);
		nmppsPut_8s(pWeightMatrix,(i+disp)*8+9*3,pWeights[i]);
		nmppsPut_8s(pWeightMatrix,(i+disp)*8+9*4,pWeights[i]);
		nmppsPut_8s(pWeightMatrix,(i+disp)*8+9*5,pWeights[i]);
		nmppsPut_8s(pWeightMatrix,(i+disp)*8+9*6,pWeights[i]);
		nmppsPut_8s(pWeightMatrix,(i+disp)*8+9*7,pWeights[i]);
	}
}

//int SIG_SetFilter_8s8s(int* pWeights, int nSize, nm64s* pKernel)
int nmppsFIRInit_8s(NmppsFIRState* ppState, int* pWeights, int nSize)
{
	int* pKernel=(int*)ppState;
#ifndef __NM__
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
#else

	int nNumberOfArrays=Sig_GetNumberOfArrays_Filter_8s8s(nSize);
	
	nm32s* pDispArray	=(nm32s*)nmppsAddr_32s((nm32s*)pKernel,2);
	nm64s* pWeightMatrix=(nm64s*)nmppsAddr_32s((nm32s*)pKernel,nNumberOfArrays+3);	
	
	nmppsPut_32s(((nm32s*)pKernel),0,nNumberOfArrays);
	nmppsPut_32s(((nm32s*)pKernel),1,nNumberOfArrays+3);
	nmppsPut_32s(((nm32s*)pKernel),nNumberOfArrays+2, 0xCCCCCCCC);
	
		
	Sig_SetDisp_Filter_8s8s(nNumberOfArrays,-((nNumberOfArrays>>1)<<1),pDispArray);
	Sig_SetWeight_Filter_8s8s(pWeights, nSize, nNumberOfArrays,pWeightMatrix);
	int AllocSize=2+nNumberOfArrays+3+nNumberOfArrays*16;
	return AllocSize;
#endif	
}

int nmppsFIRGetStateSize_8s(int nSize){
	int nNumberOfArrays=Sig_GetNumberOfArrays_Filter_8s8s(nSize);
	int AllocSize=2+nNumberOfArrays+3+nNumberOfArrays*16;
	return AllocSize;
}

int nmppsFIRInitAlloc_8s(NmppsFIRState** ppState, int* pTaps, int tapsLen)
{
	int stateSize=nmppsFIRGetStateSize_8s(tapsLen);
	*ppState=(void*)nmppsMalloc_32s(stateSize);
	if (*ppState){
		nmppsFIRInit_8s(*ppState, pTaps, tapsLen);
		return 0;
	}
	return -1;
}

#ifdef __cplusplus
		};
#endif