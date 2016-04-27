    //--------------------------------------------------------------------
#include "rpc/rpc-host.h"
#include "nmplv.h"
	




///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_64s   (nm64s* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int nSize)
{
	RPC_HOST_PLPI("nmppsCmpNeC_64s",pSrcVec,nCmpVal,pDstVec,nSize,8,8);
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_32s   (nm32s* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int nSize)
{
	RPC_HOST_PIPI("nmppsCmpNeC_32s",pSrcVec,nCmpVal,pDstVec,nSize,4);
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_16s   (nm16s* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int nSize)
{
	RPC_HOST_PIPI("nmppsCmpNeC_16s",pSrcVec,nCmpVal,pDstVec,nSize,2);
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNeC_8s    (nm8s* pSrcVec,  int8b  nCmpVal, nm8s* pDstVec, int nSize)
{
	RPC_HOST_PIPI("nmppsCmpNeC_8s",pSrcVec,nCmpVal,pDstVec,nSize,1);
}

	
