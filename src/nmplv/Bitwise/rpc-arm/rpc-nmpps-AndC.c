#include "rpc-host.h"
#include "nmtype.h"



void nmppsAndC_64u(
	nm64u*	Src,		// Input Buffer
	uint64b	Mask,		// Input mask
	nm64u*	Dst,		// Output Buffer
	int		Size		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	RPC_HOST_PIPI("nmppsAndC_64u",Src,Mask,Dst,Size,8);
}

void nmppsAndC_32u(
	nm32u*	Src,		// Input Buffer
	uint32b	Mask,		// Input mask
	nm32u*	Dst,		// Output Buffer
	int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	RPC_HOST_PIPI("nmppsAndC_32u",Src,Mask,Dst,Size,4);
}

void nmppsAndC_16u(
	nm16u*	Src,		// Input Buffer
	uint16b	Mask,		// Input mask
	nm16u*	Dst,		// Output Buffer
	int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	RPC_HOST_PIPI("nmppsAndC_16u",Src,Mask,Dst,Size,2);
}

void nmppsAndC_8u(
	nm8u*	Src,		// Input Buffer
	uint8b	Mask,		// Input mask
	nm8u*	Dst,		// Output Buffer
	int		Size		// size of input buffer in 3 bit elements. nSize={2,4..,n}
	)
{
	RPC_HOST_PIPI("nmppsAndC_8u",Src,Mask,Dst,Size,1);
}