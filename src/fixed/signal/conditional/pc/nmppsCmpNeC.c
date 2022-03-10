    //--------------------------------------------------------------------
#include "nmplv.h"
    //--------------------------------------------------------------------
void nmppsCmpNeC_16u(nm16u15b* pSrcVec, uint15b shCmpVal, nm16s* pDstVec, int nSize, int16b shTrueFlag)
{
    int i;
    for (i=0; i<nSize; i++)
    {
        if(pSrcVec[i] != (unsigned short)shCmpVal)
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
void nmppsCmpNeC_8u(nm8u7b* pSrcVec, uint7b chCmpVal, nm8s* pDstVec, int nSize, int8b chTrueFlag)
{

    
    int i;
    
    for (i=0; i<nSize; i++)
    {
        if(pSrcVec[i] != (unsigned char)chCmpVal)
        {
            pDstVec[i] = chTrueFlag;       
        }
        else
        {
            pDstVec[i] = 0;
        }
    }

}
    //---------------------
	

	




///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_64s   (const nm64s* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=nCmpVal)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_32s   (const nm32s* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=nCmpVal)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_16s   (const nm16s* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=nCmpVal)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_8s    (const nm8s* pSrcVec,  int8b  nCmpVal, nm8s* pDstVec, int nSize)
{

	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=nCmpVal)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}

	
