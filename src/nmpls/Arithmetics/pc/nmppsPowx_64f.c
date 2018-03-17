#include "nmtype.h"
#include "math.h"

void nmppsPowx_64f(const nm64f *pSrcVec, nm64f *pDstVec, nm32u Deg, int nSize)
{
	int i;
	for(i = 0; i < nSize; i++) {
		pDstVec[i] = pow(pSrcVec[i], Deg);
	}
	return;
}

