    //--------------------------------------------------------------------
#include "nmplv.h"
    //--------------------------------------------------------------------
void nmppsCmpEqC_16u(nm16u15b* pSrcVec, uint15b shCmpVal, nm16s* pDstVec, int nSize, int16b shTrueFlag)
{
    for(int i=0; i<nSize; i++)
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
}
    //--------------------------------------------------------------------
void nmppsCmpEqC_8u(nm8u7b* pSrcVec, uint7b chCmpVal, nm8s* pDstVec,int nSize, int8b chTrueFlag)
{
    for(int i=0; i<nSize; i++)
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
}
