#include "nmpls.h"
#include "nmpp.h"

void nmppsCreateResampleDown2_16u16u(nm64s** pKernel, int nHint)
{
	*pKernel=nmppsMalloc_64s(16);
	nmppsSetResampleDown2_16u16u(*pKernel);
}
