#include "math.h"
#include "nmtype.h"

void nmppsExp_32f(const nm32f *pSrcVec, nm32f *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i] = expf(pSrcVec[i]);
	}
	return;
}

void nmppsExp_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i] = exp2(pSrcVec[i]);
	}
	return;
}
