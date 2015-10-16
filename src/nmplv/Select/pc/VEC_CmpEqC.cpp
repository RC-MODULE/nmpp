    //--------------------------------------------------------------------
#include "nmplv.h"
    //--------------------------------------------------------------------
void VEC_CmpEqC(nm16u15b* pSrcVec, uint15b shCmpVal, nm16s* pDstVec, int nSize, int16b shTrueFlag)
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
void VEC_CmpEqC(nm8u7b* pSrcVec, uint7b chCmpVal, nm8s* pDstVec,int nSize, int8b chTrueFlag)
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
