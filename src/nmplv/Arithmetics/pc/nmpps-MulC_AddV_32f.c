#include "nmtype.h"

void nmppsMulC_AddV_32f(const nm32f* pSrcVec1, const nm32f* pSrcVec2, nm32f* pDstVec, float C, int nSize){
	int i;
	for(i = 0; i < nSize; i++){
		pDstVec[i] = pSrcVec1[i] * C + pSrcVec2[i];
	}
}
