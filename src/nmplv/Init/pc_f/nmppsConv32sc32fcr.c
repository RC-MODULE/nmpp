#include "nmtype.h"

void nmppsConvert_32sc32fcr(nm32sc *x, nm32fc *X, int N)
{
	int i;
	for(i = 0; i < N; i++) {
		X[i].re = (float)x[i].im;
		X[i].im = (float)x[i].re;
	}
}