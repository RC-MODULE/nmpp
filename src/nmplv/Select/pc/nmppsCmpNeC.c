    //--------------------------------------------------------------------
#include "rpc-host.h"
#include "nmplv.h"
    //--------------------------------------------------------------------
void nmppsCmpNeC_16u(nm16u15b* pSrcVec, uint15b shCmpVal, nm16s* pDstVec, int nSize, int16b shTrueFlag)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

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

	#endif
}
    //--------------------------------------------------------------------
void nmppsCmpNeC_8u(nm8u7b* pSrcVec, uint7b chCmpVal, nm8s* pDstVec, int nSize, int8b chTrueFlag)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

    
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

	#endif
}
    //---------------------
	

	




///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_64s   (nm64s* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpNeC_64s",pSrcVec,nCmpVal,pDstVec,nSize,8);
	#else

	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=nCmpVal)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_32s   (nm32s* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpNeC_32s",pSrcVec,nCmpVal,pDstVec,nSize,4);
	#else

	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=nCmpVal)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_16s   (nm16s* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpNeC_16s",pSrcVec,nCmpVal,pDstVec,nSize,2);
	#else

	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=nCmpVal)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_8s    (nm8s* pSrcVec,  int8b  nCmpVal, nm8s* pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpNeC_8s",pSrcVec,nCmpVal,pDstVec,nSize,1);
	#else

	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec[i]!=nCmpVal)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

	#endif
}

	
