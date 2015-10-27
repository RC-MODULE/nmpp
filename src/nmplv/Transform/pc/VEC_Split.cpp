#include "nmplv.h"
void VEC_Split(v4nm16s* pSrcVec, nm16s** pDst4Vec, int nSize)
{
	for(int i=0; i<nSize; i++){
		((short*)pDst4Vec[0])[i]=((short*)(pSrcVec+i))[0];
		((short*)pDst4Vec[1])[i]=((short*)(pSrcVec+i))[1];
		((short*)pDst4Vec[2])[i]=((short*)(pSrcVec+i))[2];
		((short*)pDst4Vec[3])[i]=((short*)(pSrcVec+i))[3];
	}
}



