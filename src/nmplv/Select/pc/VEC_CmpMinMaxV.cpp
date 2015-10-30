//------------------------------------------------------------------------
//
//  $Workfile:: CompareMinMaxV_8s.cpp             $
//
//  Vector-processing library
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   CompareMinV_8s.asm
//! \author S. Svechnikov
//! \brief  Elementwise min/max comparision
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"

void nmppsCmpMinMaxV_32s(nm32s*  pSrcVec1, nm32s* pSrcVec2,  nm32s*  pDstMin,  nm32s*  pDstMax, int nSize)
{
   int i, t;
   for(i=0; i<nSize;i++)
   {  t=pSrcVec1[i]-pSrcVec2[i];
     if (t<0)pDstMin[i]=pSrcVec1[i];else pDstMin[i]=pSrcVec2[i];
     pDstMax[i]=pSrcVec2[i]+pSrcVec1[i]-pDstMin[i];
   }
}

void nmppsCmpMinMaxV_16s(nm16s*  pSrcVec1, nm16s* pSrcVec2,  nm16s*  pDstMin,  nm16s*  pDstMax, int nSize)
{
   int i;
   nm16s t;
   for(i=0; i<nSize;i++)
   {  t=pSrcVec1[i]-pSrcVec2[i];
      if (t<0)pDstMin[i]=pSrcVec1[i]; else pDstMin[i]=pSrcVec2[i];
      pDstMax[i]=pSrcVec1[i]+pSrcVec2[i]-pDstMin[i];
   }
}

void nmppsCmpMinMaxV_8s(nm8s*  pSrcVec1, nm8s* pSrcVec2,  nm8s*  pDstMin,  nm8s*  pDstMax, int nSize)
{
   int i;   nm8s t;
   for(i=0; i<nSize;i++)
   {  t=pSrcVec1[i]-pSrcVec2[i];
      if (t>0)pDstMin[i]=pSrcVec2[i];else pDstMin[i]=pSrcVec1[i];
      pDstMax[i]=pSrcVec1[i]+pSrcVec2[i]-pDstMin[i];         
   }
}
