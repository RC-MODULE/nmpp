//------------------------------------------------------------------------
//
//  $Workfile:: FilterWxH.cp $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   Convert16_WxH.cpp
//! \author S. Mushkaev
//! \brief  Функции векторного ядра.
//! 
//! \endif
//!
//------------------------------------------------------------------------

//#include "nmpls.h"
//#include "nmpli.h"
#include "nmtype.h"
#include "nmpli/iFilter.h"
#include "nmpls/sfir.h"
void nmppiFilter_8s16s( nm8s * pSrcImg, nm16s* pDstImg, int nWidth, int nHeight, NmppiFilterState* pKernel)
{
	nmppsFIR_8s16s(pSrcImg, pDstImg, nWidth*nHeight, (NmppsFIRState*)pKernel);
}



