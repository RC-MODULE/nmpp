#include "nmpp.h"

///////////////////////////////////////////////////////////////////////////////
// Dst[i] = Src1[i] & Src2[i];
void nmppsAnd_64u(
const	nm64u*	Src1,		// Input Buffer
const	nm64u*	Src2,		// Input Buffer
		nm64u*	Dst,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		Dst[i] = Src1[i] & Src2[i];
}

void nmppsAnd_32u(
const	nm32u*	Src1,		// Input Buffer
const	nm32u*	Src2,		// Input Buffer
		nm32u*	Dst,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		Dst[i] = Src1[i] & Src2[i];
}


void nmppsAnd_16u(
const	nm16u*	Src1,		// Input Buffer
const	nm16u*	Src2,		// Input Buffer
		nm16u*	Dst,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		Dst[i] = Src1[i] & Src2[i];
}


void nmppsAnd_8u(
const	nm8u*	Src1,		// Input Buffer
const	nm8u*	Src2,		// Input Buffer
		nm8u*	Dst,	// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		Dst[i] = Src1[i] & Src2[i];
}

void nmppsAnd_4u(
const	nm4u*	Src1,		// Input Buffer
const	nm4u*	Src2,		// Input Buffer
		nm4u*	Dst,	// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i,iSize = nSize>>4;
	unsigned long long int *puiSrc1 = (nm64u*)Src1, *puiSrc2 = (nm64u*)Src2;
	unsigned long long int *puiDst  = (nm64u*)Dst;
	for (i=0; i<iSize; i++)
		puiDst[i] = puiSrc1[i] & puiSrc2[i];
}


