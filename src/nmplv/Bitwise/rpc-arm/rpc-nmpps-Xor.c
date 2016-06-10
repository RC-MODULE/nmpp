#include "rpc-host.h"
#include "nmtype.h"

///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = Src1[i] & Src2[i];
void nmppsXor_64u(
const	nm64u*	Src1,		// Input Buffer
const	nm64u*	Src2,		// Input Buffer
		nm64u*	pDstVec,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PPPI("nmppsXor_64u",Src1,Src2,pDstVec,nSize,8);
}

void nmppsXor_32u(
const	nm32u*	Src1,		// Input Buffer
const	nm32u*	Src2,		// Input Buffer
		nm32u*	pDstVec,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PPPI("nmppsXor_32u",Src1,Src2,pDstVec,nSize,4);
}


void nmppsXor_16u(
const	nm16u*	Src1,		// Input Buffer
const	nm16u*	Src2,		// Input Buffer
		nm16u*	pDstVec,		// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PPPI("nmppsXor_16u",Src1,Src2,pDstVec,nSize,2);
}


void nmppsXor_8u(
const	nm8u*	Src1,		// Input Buffer
const	nm8u*	Src2,		// Input Buffer
		nm8u*	pDstVec,	// Output Buffer
		int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PPPI("nmppsXor_8u",Src1,Src2,pDstVec,nSize,1);
}


