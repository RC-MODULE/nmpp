#include "nmpls.h"
#include "nmpp.h"

void nmppsCreateResampleDown2_8u8u(nm64s** pKernel, int nHint)
{
	*pKernel=nmppsMalloc_64s(16);
	nmppsSetResampleDown2_8u8u(*pKernel);
}
