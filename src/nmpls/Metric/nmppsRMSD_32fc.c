#include "nmpp.h"
#include "math.h"

float nmppsRMSD_32fc(const nm32fc *src1, const nm32fc *src2, int num)
{
    float RMSD;
    nmppsNormDiff_L2_32fc(src1, src2, num, &RMSD);
    RMSD = RMSD / sqrtf(num);
    return RMSD;
}
