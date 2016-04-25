    //--------------------------------------------------------------------
#include "rpc/rpc-host.h"
#include "nmplv.h"

///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLtC_64s63b   (nm64s63b* pSrcVec, int64b nCmpVal, nm64s63b* pDstVec, int nSize)
{
	RPC_HOST_PIPI("nmppsCmpLtC_64s63b",pSrcVec,nCmpVal,pDstVec,nSize,8);
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLtC_32s31b   (nm32s31b* pSrcVec, int32b nCmpVal, nm32s31b* pDstVec, int nSize)
{
	RPC_HOST_PIPI("nmppsCmpLtC_32s31b",pSrcVec,nCmpVal,pDstVec,nSize,4);
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLtC_16s15b   (nm16s15b* pSrcVec, int16b nCmpVal, nm16s15b* pDstVec, int nSize)
{
	RPC_HOST_PIPI("nmppsCmpLtC_16s15b",pSrcVec,nCmpVal,pDstVec,nSize,2);
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLtC_8s7b   (nm8s7b* pSrcVec,  int8b  nCmpVal, nm8s7b* pDstVec, int nSize)
{
	RPC_HOST_PIPI("nmppsCmpLtC_8s7b",pSrcVec,nCmpVal,pDstVec,nSize,1);
}

	
	