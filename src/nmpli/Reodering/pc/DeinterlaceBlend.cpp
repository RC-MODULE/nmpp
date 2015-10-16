#include "nmplv.h"
void IMG_DeinterlaceBlend(nm8u* pSrcEven, nm8u* pSrcOdd, int nSrcWidth, int nSrcHeight, nm8u* pDst)
{
	int i, j, IndDst; // i - string index, j - column index
	
	nm32u* pSrcEven32	= (nm32u*) pSrcEven;
	nm32u* pSrcOdd32	= (nm32u*) pSrcOdd;
	nm32u* pDst32		= (nm32u*) pDst;

	for (i = 0; i <= 2 * nSrcHeight - 1; i++)
		for (j = 0; j <= nSrcWidth/4 - 1; j++) {
			IndDst = i * nSrcWidth/4 + j;
			pDst32[IndDst] = (i % 2 == 0) ? pSrcEven32[(i / 2)*nSrcWidth/4 + j] : pSrcOdd32[((i-1)/2)*nSrcWidth/4 + j];
		}
};