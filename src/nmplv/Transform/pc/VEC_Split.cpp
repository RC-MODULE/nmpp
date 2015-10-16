#include "nmplv.h"
void VEC_Split(v4nm16s* pSrcVec, nm16s** pDst4Vec, int nSize)
{
	for(int i=0; i<nSize; i++){
		pDst4Vec[0][i]=((nm16s*)pSrcVec[i].data)[0];
		pDst4Vec[1][i]=((nm16s*)pSrcVec[i].data)[1];
		pDst4Vec[2][i]=((nm16s*)pSrcVec[i].data)[2];
		pDst4Vec[3][i]=((nm16s*)pSrcVec[i].data)[3];
	}
}



