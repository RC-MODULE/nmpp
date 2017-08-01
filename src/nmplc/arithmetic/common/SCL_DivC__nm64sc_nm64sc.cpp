//------------------------------------------------------------------------
//
//  $Workfile:: nmppcDivC__nm64sc_nm64sc.cpp             $
//
//  nmplc
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.5 $      Date:: 27.06.2005
//
//! \if file_doc
//!
//! \file   nmppcDivC__nm64sc_nm64sc.cpp
//! \author Sergey V. Vaganov esq.
//! \brief  <Brief Description>
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"

void nmppcDivC(nm64sc *pnSrcA, nm64s *pnSrcB, nm64sc *Dst)
{
	Dst->re = pnSrcA->re/ *pnSrcB;
	Dst->im = pnSrcA->im/ *pnSrcB;
}
