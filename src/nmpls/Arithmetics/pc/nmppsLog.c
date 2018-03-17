
#include "math.h"
#include "nmtype.h"

void nmppsLog_32f(const nm32f *pSrcVec, nm32f *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i] = logf(pSrcVec[i]);
	} 
	return;
}

void nmppsLog_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i] = log(pSrcVec[i]);
	} 
	return;
}

