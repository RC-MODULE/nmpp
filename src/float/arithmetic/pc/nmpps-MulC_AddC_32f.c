#include "nmtype.h"

void nmppsMulC_AddC_32f(const nm32f* pSrcVec, float nMulC, float nAddC, nm32f* pDstVec, int nSize){
	int i;
	for(i = 0; i < nSize; i++){
		pDstVec[i] = pSrcVec[i] * nMulC + nAddC;
	}
}
