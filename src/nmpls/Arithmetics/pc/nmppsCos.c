#include "math.h"
#include "nmtype.h"

void nmppsCos_32f(const nm32f* pSrcVec, nm32f* pDstVec, int nSize) {
	int i;
	for (i = 0; i < nSize; i++) {
		pDstVec[i] = cosf(pSrcVec[i]);
	}
}