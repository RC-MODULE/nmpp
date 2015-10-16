#include "nmplv.h"
void VEC_ClipCnv_AddC(nm16s* pSrcVec, int nClipFactor, int8b nAddValue,nm8s* pDstVec, int nSize, nm64u* weights)
{
	int	ClipPos=(1<<nClipFactor)-1;	
	int ClipNeg=-ClipPos-1;
	
	for(int i=0;i<nSize;i++,pSrcVec++,pDstVec++)
	{
		int x=*pSrcVec;
		if (x>ClipPos)
			x=ClipPos;
		else if (x<ClipNeg)
			x=ClipNeg;
		x+=nAddValue;
		*pDstVec=x;
	}
	
}

extern "C" {
	nm64u VEC_TBL_Diagonal_01h_G[8];
};
//nm64u VEC_TBL_Diagonal_01h_G[1];