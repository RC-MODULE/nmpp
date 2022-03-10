#include "nmpp.h"
#include "math.h"

float nmppsRMSD_32fcr(const nm32fcr *src1, const nm32fcr *src2, int num)
{
    float RMSD;
    nmppsNormDiff_L2_32fcr(src1, src2, num, &RMSD);
    RMSD = RMSD / sqrtf(num);
    return RMSD;
}
