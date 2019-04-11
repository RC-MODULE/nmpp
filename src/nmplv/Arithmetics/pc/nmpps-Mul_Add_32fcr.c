#include "nmtype.h"

void nmppsMul_Add_32fcr(const nm32fcr* pSrcVec1, const nm32fcr* pSrcVec2, const nm32fcr* pSrcVecAdd, nm32fcr* pDstVec, int nSize){
	int i =0;
	for(i = 0; i<nSize;i++){
		pDstVec[i].im = (pSrcVec1[i].re*pSrcVec2[i].im + pSrcVec1[i].im*pSrcVec2[i].re)+pSrcVecAdd[i].im;
		pDstVec[i].re = (pSrcVec1[i].re*pSrcVec2[i].re - pSrcVec1[i].im*pSrcVec2[i].im)+pSrcVecAdd[i].re;
	}	
}