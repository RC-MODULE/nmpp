#include "nmtype.h"
#include "math.h"


void nmppsNormDiff_L2_32fcr(const nm32fcr *src1, const nm32fcr *src2, int num, float* pNorm)
{
    int i;
    float norm, diff;
    norm = 0;
    for(i = 0; i < num; i++) {
       diff = (src1[i].re - src2[i].re);
       diff *= diff;
       norm += diff;
       diff = (src1[i].im - src2[i].im);
       diff *= diff;
       norm += diff;
    }
    *pNorm = sqrtf(norm);
}
