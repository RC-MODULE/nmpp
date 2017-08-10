    //--------------------------------------------------------------------
#include "nmplv.h"
    //--------------------------------------------------------------------
void nmppsCmpEqC_16u15b(nm16u15b* pSrcVec, uint15b shCmpVal, nm16s* pDstVec, int nSize, int16b shTrueFlag)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	int i;
    for(i=0; i<nSize; i++)
    {
        if(pSrcVec[i] == (unsigned short)shCmpVal)
        {
            pDstVec[i] = shTrueFlag;       
        }
        else
        {
            pDstVec[i] = 0;
        }
    }

	#endif
}
    //--------------------------------------------------------------------
void nmppsCmpEqC_8u7b(nm8u7b* pSrcVec, uint7b chCmpVal, nm8s* pDstVec,int nSize, int8b chTrueFlag)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	int i;
    for(i=0; i<nSize; i++)
    {
        if(pSrcVec[i] == (unsigned char) chCmpVal)
        {
            pDstVec[i] = chTrueFlag;       
        }
        else
        {
            pDstVec[i] = 0;
        }
    }

	#endif
}

void nmppsCmpEqC_4u3b(nm4u3b* pSrcVec, uint3b chCmpVal, nm4s* pDstVec,int nSize, int4b chTrueFlag)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	nm64u uiSrc, *puiSrc = (nm64u*) pSrcVec, *puiDst = (nm64u*) pDstVec;

	int i,j;
	int iSize = nSize >>4;
    for(i=0; i<iSize; i++)
    {
		uiSrc = puiSrc[i];
		for(j=0;j<16;j++)
		{
			puiDst[i]<<=4;
			if((uiSrc>>60) == (unsigned char) chCmpVal)
			{
				puiDst[i] |= chTrueFlag & 0xf;       
			}
			else
			{
				puiDst[i] &= 0xfffffffffffffff0;
			}
			uiSrc<<=4;
		}
    }

	#endif
}
