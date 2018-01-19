// Software Designer: A.Brodyazhenko
// RC Module, 2018
// PC-analog for the function nmppsConvertRisc_8u32u

#include "nmtype.h"

void nmppsConvertRisc_8u32u(nm32u *x, nm32u *X, int size)
{
    int i, j;
    size = size >> 2;
    for(i = 0, j = 0; i < size; i++, j += 4) {
		X[j] = x[i] << 24;
        X[j] = X[j] >> 24;

        X[j + 1] = x[i] << 16;
        X[j + 1] = X[j + 1] >> 24;

        X[j + 2] = x[i] << 8;
        X[j + 2] = X[j + 2] >> 24;

        X[j + 3] = x[i] >> 24;
    }
}