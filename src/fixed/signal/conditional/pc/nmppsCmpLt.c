    //--------------------------------------------------------------------
#include "nmplv.h"

///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLt_64s63b   (const nm64s63b* pSrcVec0, const nm64s63b* pSrcVec1, nm64s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if((signed long long)(pSrcVec0[i]-pSrcVec1[i])<0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLt_32s31b   (const nm32s31b* pSrcVec0, const nm32s31b* pSrcVec1, nm32s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if((signed int)(pSrcVec0[i]-pSrcVec1[i])<0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLt_16s15b   (const nm16s15b* pSrcVec0, const nm16s15b* pSrcVec1, nm16s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if((signed short)(pSrcVec0[i]-pSrcVec1[i])<0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;


}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLt_8s7b   (const nm8s7b* pSrcVec0, const nm8s7b* pSrcVec1, nm8s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if((signed char)(pSrcVec0[i]-pSrcVec1[i])<0)
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}

	
	