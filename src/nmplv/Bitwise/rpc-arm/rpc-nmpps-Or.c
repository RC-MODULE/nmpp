#include "rpc-host.h"
#include "nmtype.h"

///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] & Src2[i];
void nmppsOr_64u(
	nm64u*	Src1,		// Input Buffer
	nm64u*	Src2,		// Input Buffer
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PPPI("nmppsOr_64u",Src1,Src2,pDstVec,nSize,8);
}

void nmppsOr_32u(
	nm32u*	Src1,		// Input Buffer
	nm32u*	Src2,		// Input Buffer
	nm32u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PPPI("nmppsOr_32u",Src1,Src2,pDstVec,nSize,4);
}


void nmppsOr_16u(
	nm16u*	Src1,		// Input Buffer
	nm16u*	Src2,		// Input Buffer
	nm16u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PPPI("nmppsOr_16u",Src1,Src2,pDstVec,nSize,2);
}


void nmppsOr_8u(
	nm8u*	Src1,		// Input Buffer
	nm8u*	Src2,		// Input Buffer
	nm8u*	pDstVec,	// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PPPI("nmppsOr_8u",Src1,Src2,pDstVec,nSize,1);
}


