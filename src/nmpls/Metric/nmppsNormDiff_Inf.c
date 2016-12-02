#include <math.h>
#include "nmtype.h"
void nmppsNormDiff_Inf_32s(const nm32s* pSrc1, const nm32s* pSrc2, int len, float* pNorm)
{
	int i;
	int dif;
	int max=0;
	for(i=0; i<len; i++){
		dif=pSrc1[i]-pSrc2[i];
		if (dif<0)
			dif=-dif;
		if (max<dif)
			max=dif;
	}
	*pNorm=max;
}