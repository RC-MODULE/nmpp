#include "nmpp.h"

void nmppsMulC_Add_32fcr(nm32fcr* pSrcVec1, nm32fcr* pSrcVec2, nm32fcr* pDstVec, float C, int nSize){
	for(int i = 0; i<nSize;i++){
		pDstVec[i].im = pSrcVec1[i].im*C+pSrcVec2[i].im;
		pDstVec[i].re = pSrcVec1[i].re*C+pSrcVec2[i].re;
	}	
}