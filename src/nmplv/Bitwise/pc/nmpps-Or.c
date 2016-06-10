#include "nmpp.h"

///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] & Src2[i];
void nmppsOr_64u(
const	nm64u*	Src1,		// Input Buffer
const	nm64u*	Src2,		// Input Buffer
		nm64u*	pDstVec,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Src2[i];
}

void nmppsOr_32u(
const	nm32u*	Src1,		// Input Buffer
const	nm32u*	Src2,		// Input Buffer
		nm32u*	pDstVec,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Src2[i];

}


void nmppsOr_16u(
const	nm16u*	Src1,		// Input Buffer
const	nm16u*	Src2,		// Input Buffer
		nm16u*	pDstVec,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Src2[i];
}


void nmppsOr_8u(
const	nm8u*	Src1,		// Input Buffer
const	nm8u*	Src2,		// Input Buffer
		nm8u*	pDstVec,	// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Src2[i];
}


