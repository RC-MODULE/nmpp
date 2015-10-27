#include "nmplv.h"
//#include "crtdbg.h"
/*
void VEC_ClipArshCnv_AddC_Ext(v16nm16s* pSrcVec, v16nm32s* pnClipFactor, v16nm32s* pnShift,v16nm4s* pnAdd, v16nm4s* pDstVec,int nSize)
{
	nm16s pClipPos[16];
	nm16s pClipNeg[16];
	nm16s pAdd[16];
	for(int i=0;i<16;i++)
	{
		pClipPos[i]=(1<<VEC_GetVal(pnClipFactor->data,i))-1;
		pClipNeg[i]=-pClipPos[i]-1;
		pAdd[i]=VEC_GetVal((nm16s*)pnAdd,i);
	}

	for(int i=0;i<nSize;i++,pSrcVec++,pDstVec++)
	{
		for(int k=0;k<16;k++)
		{
			int nSrc=VEC_GetVal(pSrcVec->data,k);
			if (nSrc>pClipPos[k])
				nSrc=pClipPos[k];
			else
				if (nSrc<pClipNeg[k])
					nSrc=pClipNeg[k];
			nSrc>>=VEC_GetVal(pnShift->data,k);
			nSrc+=pAdd[k];
			//ASSERTE(nSrc<8);
			//ASSERTE(nSrc>=-8);
			VEC_SetVal(pDstVec->data,k,nSrc);
		}
	}
}*/