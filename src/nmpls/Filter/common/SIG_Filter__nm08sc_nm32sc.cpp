
#include "nmplv.h"
#include "nmpls.h"

/*
void SIG_Filter(nm8s* pSrcRe, nm8s* pSrcIm, nm32s* pDstRe, nm32s* pDstIm, int nSize, nm64s* pKernel, nm32s* pTmp0, nm32s* pTmp1)
{
	nm64s* pKernelRe=(nm64s*)((nm32s*)pKernel)[0];
	nm64s* pKernelIm=(nm64s*)((nm32s*)pKernel)[1];
	
	SIG_Filter(pSrcRe, pTmp0, nSize, pKernelRe);
	SIG_Filter(pSrcIm, pTmp1, nSize, pKernelIm);
	nmppsSub(pTmp0,pTmp1,pDstRe,nSize);
	
	SIG_Filter(pSrcIm, pTmp0, nSize, pKernelRe);
	SIG_Filter(pSrcRe, pTmp1, nSize, pKernelIm);
	nmppsAdd(pTmp0,pTmp1,pDstRe,nSize);
	
}






void SIG_CreateFilter_8s32s(nm32sc* pWeights, int nSize, nm64s** pKernel, int hint)
{
	nm32s* pWeightsRe;
	nm32s* pWeightsIm;
	int nKerSize=13+(16+nSize)*5/2;
	nKerSize+=1;
	nKerSize&=~1;
	VEC_Malloc((nm32s**)pKernel,2*nKerSize+2,hint);
	VEC_Malloc(&pWeightsRe, nSize, MEM_GLOBAL);
	VEC_Malloc(&pWeightsIm, nSize, MEM_GLOBAL);
	for(int i=0; i<nSize; i++){
		pWeightsRe[i]=pWeights[i].re;
		pWeightsIm[i]=pWeights[i].im;
	}
	nm32s* pKer=(int*)*pKernel;
	nm64s* pKernelRe=(nm64s*)(pKer+2);
	nm64s* pKernelIm=(nm64s*)(pKer+2+nKerSize);
	pKer[0]=(int)pKernelRe;
	pKer[1]=(int)pKernelIm;
	SIG_SetFilter_8s32s(pWeightsRe, nSize, pKernelRe);
	SIG_SetFilter_8s32s(pWeightsIm, nSize, pKernelIm);
	VEC_Free(pWeightsIm);
	VEC_Free(pWeightsRe);
}
*/
