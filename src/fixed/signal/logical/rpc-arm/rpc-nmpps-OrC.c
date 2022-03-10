#include "rpc-host.h"
#include "nmtype.h"



void nmppsOrC_64u(
const 	nm64u*	Src,		// Input Buffer
		uint64b	Mask,		// Input mask
		nm64u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PIPI("nmppsOrC_64u",Src,Mask,Dst,Size,8);
}

void nmppsOrC_32u(
const 	nm32u*	Src,		// Input Buffer
		uint32b	Mask,		// Input mask
		nm32u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	RPC_HOST_PIPI("nmppsOrC_32u",Src,Mask,Dst,Size,4);
}

void nmppsOrC_16u(
const 	nm16u*	Src,		// Input Buffer
		uint16b	Mask,		// Input mask
		nm16u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	RPC_HOST_PIPI("nmppsOrC_16u",Src,Mask,Dst,Size,2);
}

void nmppsOrC_8u(
const 	nm8u*	Src,		// Input Buffer
		uint8b	Mask,		// Input mask
		nm8u*	Dst,		// Output Buffer
		int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	RPC_HOST_PIPI("nmppsOrC_8u",Src,Mask,Dst,Size,1);
}