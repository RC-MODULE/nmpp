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

#include "nmpls.h"
#include "nmpli.h"


void nmppiFilter( nm8s * pSrcImg, nm32s* pDstImg, int nWidth, int nHeight, nm64s* pKernel)
{
	//SIG_Filter(pSrcImg, pDstImg, nWidth*nHeight, pKernel);
	nmppsFIR_8s32s(pSrcImg, pDstImg, nWidth*nHeight, pKernel);
	
}


