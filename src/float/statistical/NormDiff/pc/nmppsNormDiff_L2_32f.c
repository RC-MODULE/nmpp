#include "math.h"

//extern "C" {
void nmppsNormDiff_L2_32f(const float* pSrc1, const float* pSrc2, int len, float* pNorm)
{
	int i;
	int dif;
	int sum=0;
	for(i=0; i<len; i++){
		dif=pSrc1[i]-pSrc2[i];
		sum+=dif*dif;
	}
	*pNorm=sqrtf(sum);
}
//};