#include "nmplv.h"
//#include "crtdbg.h"
/*
void nmppsClipArshCnv_AddC_Ext_(v16nm16s* pSrcVec, v16nm32s* pnClipFactor, v16nm32s* pnShift,v16nm4s* pnAdd, v16nm4s* pDstVec,int nSize)
{
	nm16s pClipPos[16];
	nm16s pClipNeg[16];
	nm16s pAdd[16];
	for(int i=0;i<16;i++)
	{
		pClipPos[i]=(1<<nmppsGetVal_(pnClipFactor->data,i))-1;
		pClipNeg[i]=-pClipPos[i]-1;
		pAdd[i]=nmppsGet_16s((nm16s*)pnAdd,i);
	}

	for(int i=0;i<nSize;i++,pSrcVec++,pDstVec++)
	{
		for(int k=0;k<16;k++)
		{
			int nSrc=nmppsGetVal_(pSrcVec->data,k);
			if (nSrc>pClipPos[k])
				nSrc=pClipPos[k];
			else
				if (nSrc<pClipNeg[k])
					nSrc=pClipNeg[k];
			nSrc>>=nmppsGetVal_(pnShift->data,k);
			nSrc+=pAdd[k];
			//ASSERTE(nSrc<8);
			//ASSERTE(nSrc>=-8);
			nmppsSetInt_(pDstVec->data,k,nSrc);
		}
	}
}*/