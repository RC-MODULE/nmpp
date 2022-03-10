#include "nmpp.h"


///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = pSrcVec[i] & Mask 
void nmppsOrC_p64u(nm64u*	Src1,		// Input Buffer
const 	nm64u*	Mask,		// Input mask
		nm64u*	pDstVec,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
			)
{

int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Mask[0];
}

void nmppsOrC_64u(
const 	nm64u*	Src,		// Input Buffer
		uint64b	Mask,		// Input mask
		nm64u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] | Mask;
}

void nmppsOrC_32u(
const 	nm32u*	Src,		// Input Buffer
		uint32b	Mask,		// Input mask
		nm32u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] | Mask;
}

void nmppsOrC_16u(
const 	nm16u*	Src,		// Input Buffer
		uint16b	Mask,		// Input mask
		nm16u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] | Mask;
}

void nmppsOrC_8u(
const 	nm8u*	Src,		// Input Buffer
		uint8b	Mask,		// Input mask
		nm8u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] | Mask;
}