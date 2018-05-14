#include "nmpp.h"

void nmppsMulC_Add_32fcr(nm32fcr* pSrcVec1, nm32fcr* pSrcVec2, nm32fcr* pDstVec, float C, int nSize){
	for(int i = 0; i<nSize;i++){
		dst[i].im = src1[i].im*C+src2[i].im;
		dst[i].re = src1[i].re*C+src2[i].re;
	}	
}