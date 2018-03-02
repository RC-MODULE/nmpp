#include "nmplv.h"
extern "C" {
void nmppsClipRShiftConvertAddC_32s8s( nm32s* pSrcVec, int nClipFactor, int nShift, int8b nAddValue,nm8s* pDstVec, int nSize)
{
	int i;
	int	ClipPos=(1<<nClipFactor)-1;	
	int ClipNeg=-ClipPos-1;
	
	for(i=0;i<nSize;i++,pSrcVec++,pDstVec++)
	{
		int x=*pSrcVec;
		if (x>ClipPos)
			x=ClipPos;
		else if (x<ClipNeg)
			x=ClipNeg;
		x>>=nShift;
		x+=nAddValue;
		*pDstVec=x;
	}
	
}
};