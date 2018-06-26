#include "nmpp.h"

void nmppsMul_Add_32f(const nm32f* pSrcVec1, const nm32f* pSrcVec2, const nm32f* pSrcVecAdd, nm32f* pDstVec, int nSize){
	int i =0;
	for(i = 0; i<nSize;i++){
		pDstVec[i] = pSrcVec1[i]*pSrcVec2[i]+pSrcVecAdd[i];
	}	
}