#include "rpc-host.h"
#include "nmpp.h"


///////////////////////////////////////////////////////////////////////////////
// pDstVec[i] = pSrcVec[i] & Mask 
void nmppsOrC_p64u(nm64u*	Src1,		// Input Buffer
	nm64u*	Mask,		// Input mask
	nm64u*	pDstVec,		// Output Buffer
	int		nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI("nmppsOrC_p64u",pSrcVec,pDstVec,nSize,8);
	#else


int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = Src1[i] | Mask[0];

	#endif
}

void nmppsOrC_64u(
	nm64u*	Src,		// Input Buffer
	uint64b	Mask,		// Input mask
	nm64u*	Dst,		// Output Buffer
	int		Size		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsOrC_64u",Src,Mask,Dst,Size,8);
	#else
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] | Mask;
	#endif
}

void nmppsOrC_32u(
	nm32u*	Src,		// Input Buffer
	uint32b	Mask,		// Input mask
	nm32u*	Dst,		// Output Buffer
	int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsOrC_32u",Src,Mask,Dst,Size,4);
	#else
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] | Mask;
	#endif
}

void nmppsOrC_16u(
	nm16u*	Src,		// Input Buffer
	uint16b	Mask,		// Input mask
	nm16u*	Dst,		// Output Buffer
	int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsOrC_16u",Src,Mask,Dst,Size,2);
	#else
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] | Mask;
	#endif
}

void nmppsOrC_8u(
	nm8u*	Src,		// Input Buffer
	uint8b	Mask,		// Input mask
	nm8u*	Dst,		// Output Buffer
	int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsOrC_8u",Src,Mask,Dst,Size,1);
	#else
	int i;
	for (i=0; i<Size; i++)
		Dst[i] = Src[i] | Mask;
	#endif
}