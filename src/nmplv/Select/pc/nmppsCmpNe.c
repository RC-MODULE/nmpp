    //--------------------------------------------------------------------
#include "nmplv.h"
    //--------------------------------------------------------------------
//void nmppsCmpNeC_16u(const nm16u15b* pSrcVec0, const nm16u15b* pSrcVec1, nm16s* pDstVec, int nSize, int16b shTrueFlag)
//{
//    int i;
//    for (i=0; i<nSize; i++)
//    {
//        if(pSrcVec0[i] != (unsigned short)shCmpVal)
//        {
//            pDstVec[i] = shTrueFlag;       
//        }
//        else
//        {
//            pDstVec[i] = 0;
//        }
//    }
//
//}
//    //--------------------------------------------------------------------
//void nmppsCmpNeC_8u(const nm8u7b* pSrcVec0, const nm8u7b* pSrcVec1, nm8s* pDstVec, int nSize, int8b chTrueFlag)
//{
//
//    
//    int i;
//    
//    for (i=0; i<nSize; i++)
//    {
//        if(pSrcVec0[i] != (unsigned char)chCmpVal)
//        {
//            pDstVec[i] = chTrueFlag;       
//        }
//        else
//        {
//            pDstVec[i] = 0;
//        }
//    }
//
//}
//    //---------------------
	

///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNe_64s   (const nm64s* pSrcVec0, const nm64s* pSrcVec1, nm64s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec0[i]!=pSrcVec1[i])
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNe_32s   (const nm32s* pSrcVec0, const nm32s* pSrcVec1, nm32s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec0[i]!=pSrcVec1[i])
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNe_16s   (const nm16s* pSrcVec0, const nm16s* pSrcVec1, nm16s* pDstVec, int nSize)
{
	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec0[i]!=pSrcVec1[i])
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpNe_8s    (const nm8s* pSrcVec0,  const nm8s* pSrcVec1, nm8s* pDstVec, int nSize)
{

	int i;
	for (i=0; i<nSize; i++)
		if(pSrcVec0[i]!=pSrcVec1[i])
			pDstVec[i] = -1;
		else
			pDstVec[i] = 0;

}

	
