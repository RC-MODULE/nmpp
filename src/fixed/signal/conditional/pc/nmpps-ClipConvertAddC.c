#include "nmplv.h"
void nmppsClipConvertAddC_16s8s(nm16s* pSrcVec, int nClipFactor, int8b nAddValue,nm8s* pDstVec, int nSize, NmppsWeightState* pState)
{
	int	ClipPos=(1<<nClipFactor)-1;	
	int ClipNeg=-ClipPos-1;
	int i,x;
	for(i=0;i<nSize;i++,pSrcVec++,pDstVec++)
	{
		x=*pSrcVec;
		if (x>ClipPos)
			x=ClipPos;
		else if (x<ClipNeg)
			x=ClipNeg;
		x+=nAddValue;
		*pDstVec=x;
	}
	
}
