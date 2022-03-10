#include <math.h>
#include "nmtype.h"
void nmppsNormDiff_L2_32s(const nm32s* pSrc1, const nm32s* pSrc2, int len, float* pNorm)
{
	int i;
	int dif;
	int sum=0;
	for(i=0; i<len; i++){
		dif=pSrc1[i]-pSrc2[i];
		sum+=dif*dif;
	}
	*pNorm=sum;
	*pNorm=sqrt(*pNorm);
}