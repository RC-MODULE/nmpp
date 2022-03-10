#include "nmpli.h"

int  nmppiCompareGtC (nm16s *pSrcImg, int nSrcStride, nm16s *pDst, 
										 int nDstStride, nm16s *pThreshold, int nWidth, int nHeight)
{
	int x, y, i, sstep, dstep;
	sstep=nSrcStride<<1;
	dstep=nDstStride<<1;

	for(y=0; y<nHeight; y++)
		for(x=0; x<nWidth; x+=4)
			for(i=0; i<4; i++)
				pDst[dstep*y+(x+i)]=(pSrcImg[sstep*y+(x+i)]>pThreshold[i])?0x00FF:0x0000;

	return 0;
}

