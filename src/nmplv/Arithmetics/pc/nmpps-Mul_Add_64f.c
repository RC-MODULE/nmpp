#include "nmpp.h"

void nmppsMul_Add_64f(const nm64f* pSrcVec1, const nm64f* pSrcVec2, const nm64f* pSrcVecAdd, nm64f* pDstVec, int nSize){
	int i =0;
	for(i = 0; i<nSize;i++){
		pDstVec[i] = pSrcVec1[i]*pSrcVec2[i]+pSrcVecAdd[i];
	}	
}