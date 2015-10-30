    //--------------------------------------------------------------------
#include "nmplv.h"
    //--------------------------------------------------------------------
void nmppsCmpNeV_16u(nm16u15b* pSrcVec1, nm16u15b* pSrcVec2, nm16s* pDstVec, int nSize, int16b shTrueFlag)
{
    for(int i=0; i<nSize; i++)
    {
        if(pSrcVec1[i] != (unsigned short)pSrcVec2[i])
        {
            pDstVec[i] = shTrueFlag;       
        }
        else
        {
            pDstVec[i] = 0;
        }
    }
}
    //-------------------------------------------------------------------
    

void nmppsCmpNeV_8u(nm8u7b* pSrcVec1, nm8u7b* pSrcVec2, nm8s* pDstVec, int nSize, int8b chTrueFlag)
{
    for(int i=0; i<nSize; i++)
    {
        if(pSrcVec1[i] != (unsigned char)pSrcVec2[i])
        {
            pDstVec[i] = chTrueFlag;       
        }
        else
        {
            pDstVec[i] = 0;
        }
    }
}
