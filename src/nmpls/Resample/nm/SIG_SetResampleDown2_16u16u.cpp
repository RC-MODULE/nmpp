#include "nmtype.h"

int SIG_SetResampleDown2_16u16u(nm64s* pKernel)
{
	pKernel[0]=0x0000000000000001l;
	pKernel[1]=0x0000000000000001l;
	pKernel[2]=0x0000000000010000l;
	pKernel[3]=0x0000000000010000l;
	pKernel[4]=0x0000000100000000l;
	pKernel[5]=0x0000000100000000l;
	pKernel[6]=0x0001000000000000l;
	pKernel[7]=0x0001000000000000l;
	return 8<<1;
}