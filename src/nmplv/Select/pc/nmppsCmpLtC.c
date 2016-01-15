    //--------------------------------------------------------------------
#include "rpc-host.h"
#include "nmplv.h"

	




	



///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLtC_64s63b   (nm64s63b* pSrcVec, int64b nCmpVal, nm64s63b* pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpLtC_64s63b",pSrcVec,nCmpVal,pDstVec,nSize,8);
	#else

	int i;
	for (i=0; i<nSize; i++)
		if((signed long long)(pSrcVec[i]-nCmpVal)<0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLtC_32s31b   (nm32s31b* pSrcVec, int32b nCmpVal, nm32s31b* pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpLtC_32s31b",pSrcVec,nCmpVal,pDstVec,nSize,4);
	#else

	int i;
	for (i=0; i<nSize; i++)
		if((signed int)(pSrcVec[i]-nCmpVal)<0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLtC_16s15b   (nm16s15b* pSrcVec, int16b nCmpVal, nm16s15b* pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpLtC_16s15b",pSrcVec,nCmpVal,pDstVec,nSize,2);
	#else

	int i;
	for (i=0; i<nSize; i++)
		if((signed short)(pSrcVec[i]-nCmpVal)<0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLtC_8s7b   (nm8s7b* pSrcVec,  int8b  nCmpVal, nm8s7b* pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpLtC_8s7b",pSrcVec,nCmpVal,pDstVec,nSize,1);
	#else

	int i;
	for (i=0; i<nSize; i++)
		if((signed char)(pSrcVec[i]-nCmpVal)<0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

	#endif
}

	
	