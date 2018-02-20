#include <stdlib.h>
void nmppsCopy_64s(const double*	pSrcVec,		// Source array
			double*	pDstVec,		// Destination array
			int			SizeInt64	// nSize of Source array in 64-bit longs; nSize=[0,1,2...]
		)
{
	int idx;
	for(idx=0;idx<SizeInt64;idx++)
		pDstVec[idx]=pSrcVec[idx];
}

void ref_nmppmCopy_64s(
		double*	SrcMtr,
			int		nSrcStride,
			double*	DstMtr,
			int		nDstStride,
			int		nHeight,
			int		nWidth)

{
	int i;
	for(i=0;i<nHeight;i++)
	{
		nmppsCopy_64s(SrcMtr,DstMtr,nWidth);
		SrcMtr+=nSrcStride;
		DstMtr+=nDstStride;
	}
}