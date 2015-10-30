//------------------------------------------------------------------------
//
//  $Workfile:: nmppsDivC__nm64sc_nm64sc.cpp             $
//
//  nmplv
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      Date:: 27.06.2005
//
//! \if file_doc
//!
//! \file   nmppsDivC__nm64sc_nm64sc.cpp
//! \author Sergey V. Vaganov esq.
//! \brief  <Brief Description>
//!
//! \endif
//!
//------------------------------------------------------------------------



#include "nmtype.h"
void nmppsDivC(nm64sc *pSrcVec, nm64sc *pDstVec, int nSize, nm64sc *pnDivisor)
{
	int i;
	if(!pnDivisor->im)
	{
		for(i=0;i<nSize;i++)
		{
			pDstVec[i].re = pSrcVec[i].re/pnDivisor->re;
			pDstVec[i].im = pSrcVec[i].im/pnDivisor->re;
		}
	}
	else
	{
		nm64s d;
		d = pnDivisor->re * pnDivisor->re + pnDivisor->im * pnDivisor->im;
		for(i=0;i<nSize;i++)
		{
			pDstVec[i].re = (pSrcVec[i].re*pnDivisor->re+pSrcVec[i].im*pnDivisor->im)/d;
			pDstVec[i].im = (pSrcVec[i].im*pnDivisor->re-pSrcVec[i].re*pnDivisor->im)/d;
		}
	}
}
