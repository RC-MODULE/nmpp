    //--------------------------------------------------------------------
#include "nmplv.h"
    //--------------------------------------------------------------------
void nmppsCmpEqV_16u(nm16u15b* pSrcVec1, nm16u15b* pSrcVec2, nm16s* pDstVec, int nSize, int16b shTrueFlag)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

    int i;
    for (i=0; i<nSize; i++)
    {
        if(pSrcVec1[i] == pSrcVec2[i])
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
void nmppsCmpEqV_8u(nm8u7b* pSrcVec1, nm8u7b* pSrcVec2, nm8s* pDstVec, int nSize, int8b chTrueFlag)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

    int i;
    for (i=0; i<nSize; i++)
    {
        if(pSrcVec1[i] == pSrcVec2[i])
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
    //--------------------------------------------------------------------
