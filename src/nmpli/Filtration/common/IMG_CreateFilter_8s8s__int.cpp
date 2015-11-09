#include "nmpp.h"
#include "nmpls.h"
#include "nmpli.h"
#include <string.h>



int  Sig_GetNumberOfArrays_Filter_8s8s(int nSize);

#ifdef __NM__
void Sig_SetDisp_Filter_8s8s( int nNumberOfArrays, int nDisp,int* pDispArray);
void Sig_SetWeight_Filter_8s8s(int* pWeights, int nSize, int nNumberOfArrays, nm64s* pDst);
#endif

int IMG_SetFilter_8s8s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s* pKernel)
{
#ifdef __NM__
	int		nNumberOfArrays=Sig_GetNumberOfArrays_Filter_8s8s(nKerWidth);
	int		nDisp=-(nImgWidth>>2)*(nKerHeight>>1)-((nNumberOfArrays>>1)<<1);
	int*	pDisp=(nm32s*)nmppsAddr_32s((nm32s*)pKernel,2);
	nm64s*	pMatrix=(nm64s*)nmppsAddr_32s(pDisp,nNumberOfArrays*nKerHeight+1);

	nmppsSetInt_32s((nm32s*)pKernel,0,nNumberOfArrays*nKerHeight);
	nmppsSetInt_32s((nm32s*)pKernel,1,2+nNumberOfArrays*nKerHeight+1);
	nmppsSetInt_32s((nm32s*)pKernel,2+nNumberOfArrays*nKerHeight,0x600DBEEF);
	
	for(int y=0; y<nKerHeight; y++){
		Sig_SetDisp_Filter_8s8s( nNumberOfArrays, nDisp,pDisp);
		Sig_SetWeight_Filter_8s8s( pWeights, nKerWidth, nNumberOfArrays,pMatrix);
		pDisp+=nNumberOfArrays;
		pMatrix+=nNumberOfArrays*8;
		pWeights+=nKerWidth;
		nDisp+=(nImgWidth>>2);
	}
	
	int AllocSize=2+(nNumberOfArrays*nKerHeight*17)+1;
	return AllocSize;
#else 
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
#endif
}
/*
void IMG_CreateFilter_8s8s(int* pWeights, int nKerWidth, int nKerHeight, int nImgWidth, nm64s** pKernel, int nHint)
{
	int	nNumberOfArrays=Sig_GetNumberOfArrays_Filter_8s8s(nKerWidth);
	int AllocSize=2+(nNumberOfArrays*nKerHeight*17)+1;
	nmppsMalloc_32s((nm32s**)pKernel,AllocSize, nHint);
	if (*pKernel==0) return;
	//nmppsSet_32s((nm32s*)*pKernel, 5, 2+(nNumberOfArrays*nKerHeight*17)+1);
	IMG_SetFilter_8s8s(pWeights, nKerWidth, nKerHeight, nImgWidth, *pKernel);
}
*/
int IMG_GetFilterKernelSize32_8s8s(int nKerWidth, int nKerHeight){
	int	nNumberOfArrays=Sig_GetNumberOfArrays_Filter_8s8s(nKerWidth);
	int AllocSize=(2+(nNumberOfArrays*nKerHeight*17)+1);
	return AllocSize;
}

//--------------------------------------------------------------------------------------------------------------
template<> CIMG_FIR<nm8s,nm8s>::CIMG_FIR(int n_KerWidth, int n_KerHeight, void* (*malloc32_func)(unsigned), void (*free32_func)(void*)){
	pfFree32=free32_func;
	nKerWidth=n_KerWidth;
	nKerHeight=n_KerHeight;
	int KernelSize=IMG_GetFilterKernelSize32_8s8s( nKerWidth,  nKerHeight);
	pKernel=(nm64s*)malloc32_func(KernelSize);
}

template<> void* CIMG_FIR<nm8s,nm8s>::SetWeights(int* pWeights, int nImgWidth){
	if (pKernel)
		IMG_SetFilter_8s8s(pWeights, nKerWidth, nKerHeight, nImgWidth, pKernel);
	return pWeights;
}

template<> void CIMG_FIR<nm8s,nm8s>::Filter(nm8s* pSrcImg, nm8s* pDstImg, int nImgWidth,int nImgHeight){
	IMG_Filter(pSrcImg, pDstImg, nImgWidth, nImgHeight, pKernel);
}

template<> CIMG_FIR<nm8s,nm8s>::~CIMG_FIR(){
	if (pKernel) 
		pfFree32(pKernel);
}
