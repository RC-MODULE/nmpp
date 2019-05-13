#include "nmpli.h"

 /*
void nmppiRShiftConvert( nm32s* pSrcImg, int nSrcStride, nm16s* pDstImg,  int nSrcDstStride, int nShift,
								 int nWidth, int nHeight)
{
	int sstep=nSrcStride;
	int dstep=nSrcDstStride<<1;
	int i, j;
	for(j=0; j<nHeight; j++)
		for(i=0; i<nWidth; i++)
			((nm16s*)pDstImg)[dstep*j+i]=(nm16s)(pSrcImg[sstep*j+i]>>nShift);
}
*/

void nmppiConvert(RGB32_nm8u* pSrcImg, RGB32_nm10u* pDstImg, int nSize)
{
    int *pnSrc = (int*)pSrcImg;
    int *pnDst = (int*)pDstImg;

    for(int i=0; i<nSize; i++)
    {
        pnDst[i] = (pnSrc[i] & 0xFF) | ((pnSrc[i] & 0xFF00) << 2) | 
                ((pnSrc[i] & 0xFF0000) << 4);
    }
}

void nmppiConvert(RGB32_nm10u* pSrcImg, RGB32_nm8u* pDstImg, int nSize)
{
    int *pnSrc = (int*)pSrcImg;
    int *pnDst = (int*)pDstImg;

    for(int i=0; i<nSize; i++)
    {
        pnDst[i] = (pnSrc[i] & 0xFF) | ((pnSrc[i] & 0x3FC00) >> 2) | 
                ((pnSrc[i] & 0xFF00000) >> 4);
    }
}

void nmppiGrayToRGB242424242424242424(nm8u* pSrcImg, RGB24_nm8u* pDstImg, int nSize)
{
	for(int i=0;i<nSize;i++,pDstImg++,pSrcImg++)
	{
		pDstImg->nB=*pSrcImg;
		pDstImg->nG=*pSrcImg;
		pDstImg->nR=*pSrcImg;
	}
}