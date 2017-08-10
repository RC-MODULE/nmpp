#include "nmpp.h"


///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = pSrcVec[i] & Mask 
void nmppsAndC_p64u(nm64u*	Src1,		// Input Buffer
		nm64u*	Mask,		// Input mask
		nm64u*	pDstVec,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] & Mask[0];
}

void nmppsAndC_64u(
const 	nm64u*	Src,		// Input Buffer
		uint64b	Mask,		// Input mask
		nm64u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] & Mask;
}

void nmppsAndC_32u(
const 	nm32u*	Src,		// Input Buffer
		uint32b	Mask,		// Input mask
		nm32u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] & Mask;
}

void nmppsAndC_16u(
const 	nm16u*	Src,		// Input Buffer
		uint16b	Mask,		// Input mask
		nm16u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] & Mask;
}

void nmppsAndC_8u(
const 	nm8u*	Src,		// Input Buffer
		uint8b	Mask,		// Input mask
		nm8u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] & Mask;
}

/*void nmppsAndC_4u(
const 	nm4u*	Src,		// Input Buffer
		uint4b	Mask,		// Input mask
		nm4u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	int i,j;
	int iSize = Size>>4;
	Mask &= 0xf;
	long long lMask = Mask & 0xf;
	lMask |= lMask << 4;
	lMask |= lMask << 8;
	lMask |= lMask << 16;
	lMask |= lMask << 32;
	long long int *puiSrc = (nm64u*)Src, *puiDst = (nm64u*)Dst;
	for (i=0; i<iSize; i++)
		puiDst[i] = puiSrc[i] & lMask;
}*/