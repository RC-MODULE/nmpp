#include "nmpli.h"

void nmppiAddI(nm16s* pSrcDstImg, int nSrcDstStride, nm16s *pSrcImg,  int nSrcStride, int nWidth, int nHeight)
{
	int sstep=nSrcStride<<1;
	int dstep=nSrcDstStride<<1;
	int i, j;
	for(j=0; j<nHeight; j++)
		for(i=0; i<nWidth; i++)
			((short*)pSrcDstImg)[dstep*j+i]+=((short*)pSrcImg)[sstep*j+i];

}

void nmppiSubI(nm16s* pSrcDstImg, int nSrcDstStride, nm16s *pSrcImg, int nSrcStride,  int nWidth, int nHeight)
{
	int sstep=nSrcStride<<1;
	int dstep=nSrcDstStride<<1;
	int i, j;
	for(j=0; j<nHeight; j++)
		for(i=0; i<nWidth; i++)
		{
			int p1=(int)((short*)pSrcDstImg)[dstep*j+i];
			int p2=(int)((short*)pSrcImg)[sstep*j+i];
			((short*)pSrcDstImg)[dstep*j+i]=(short)(p1-p2);
		}
}

void nmppiAddCnvArshI(nm16s* pSrcDstImg,  int nSrcDstStride,  nm32s* pSrcImg, int nSrcStride, int nShift, int nWidth, int nHeight)
{
	int sstep=nSrcStride;
	int dstep=nSrcDstStride<<1;
	int i, j;
	for(j=0; j<nHeight; j++)
		for(i=0; i<nWidth; i++)
			((short*)pSrcDstImg)[dstep*j+i]+=((short)(pSrcImg[sstep*j+i]>>nShift));
}

void nmppiSubCnvArshI(nm16s * pSrcDstImg,  int nSrcDstStride, nm32s * pSrcImg, int nSrcStride, int nShift, int nWidth, int nHeight)
{
	int sstep=nSrcStride;
	int dstep=nSrcDstStride<<1;
	int i, j;
	for(j=0; j<nHeight; j++)
		for(i=0; i<nWidth; i++)
			((short*)pSrcDstImg)[dstep*j+i]-=((short)(pSrcImg[sstep*j+i]>>nShift));
}

void nmppiHalfsum(nm16s* pSrcMtr1, int nSrcStride1, nm16s* pSrcMtr2, 
        int nSrcStride2, nm16s* pDstMtr, int nDstStride, int nWidth, int nHeight)
{
    int i, j;
    short *pshSrc1 = (short*)pSrcMtr1;
    short *pshSrc2 = (short*)pSrcMtr2;
    short *pshDst = (short*)pSrcMtr1;
    nSrcStride1 <<= 1;
    nSrcStride2 <<= 1;
    nDstStride <<= 1;

    for(i=0; i<nHeight; i++)
    {
        pshSrc1 += nSrcStride1;
        pshSrc2 += nSrcStride2;
        pshDst += nDstStride;
        for(j=0; j<nWidth; j++)
        {
            pshDst[j] = (short)(pshSrc1[j] + pshSrc2[j]) / 2;
        }
    }
}
/*
void nmppiHalfsumM32x8(nm16u15b* pSrcMtr1, int nSrcStride1, nm16u15b* pSrcMtr2, 
        int nSrcStride2, nm16u15b* pDstMtr, int nDstStride)
{
    int i, j;
    short *pshSrc1 = (short*)pSrcMtr1;
    short *pshSrc2 = (short*)pSrcMtr2;
    short *pshDst = (short*)pSrcMtr1;
    nSrcStride1 <<= 1;
    nSrcStride2 <<= 1;
    nDstStride <<= 1;

    for(i=0; i<8; i++)
    {
        pshSrc1 += nSrcStride1;
        pshSrc2 += nSrcStride2;
        pshDst += nDstStride;
        for(j=0; j<32; j++)
        {
            pshDst[j] = (unsigned short)(pshSrc1[j] + pshSrc2[j]) / 2;
        }
    }
}*/