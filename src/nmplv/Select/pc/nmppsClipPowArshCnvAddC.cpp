#include "nmplv.h"
//#include "crtdbg.h"
/*
void nmppsClipArshCnv_AddC_Ext(v16nm16s* pSrcVec, v16nm32s* pnClipFactor, v16nm32s* pnShift,v16nm4s* pnAdd, v16nm4s* pDstVec,int nSize)
{
	nm16s pClipPos[16];
	nm16s pClipNeg[16];
	nm16s pAdd[16];
	int i;
	for (i=0;i<16;i++)
	{
		pClipPos[i]=(1<<nmppsGet_32s((nm32s*)pnClipFactor->data,i))-1;
		pClipNeg[i]=-pClipPos[i]-1;
		pAdd[i]=nmppsGet_16s((nm16s*)pnAdd,i);
	}

	int i;

	for (i=0;i<nSize;i++,pSrcVec++,pDstVec++)
	{
		for(int k=0;k<16;k++)
		{
			int nSrc=nmppsGet_16s((nm16s*)pSrcVec->vec,k);
			if (nSrc>pClipPos[k])
				nSrc=pClipPos[k];
			else
				if (nSrc<pClipNeg[k])
					nSrc=pClipNeg[k];
			nSrc>>=nmppsGet_16s((nm32s*)pnShift->vec,k);
			nSrc+=pAdd[k];
			//ASSERTE(nSrc<8);
			//ASSERTE(nSrc>=-8);
			nmppsPut_16s(pDstVec->data,k,nSrc);
		}
	}
}
*/