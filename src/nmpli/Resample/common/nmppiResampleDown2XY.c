//------------------------------------------------------------------------
//
//  $Workfile:: iResampleDown2_cn.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   ResampleDown2X_C7.cpp
//! \author Павел Лукашевич
//! \brief  Функции изменения размеров изображения.
//!
//! \endif
//!
//------------------------------------------------------------------------

 #include "nmpp.h"
#include "nmpls.h"
#include "nmpli.h"
#include "nmpli/iResample.h"
//!
//! \perfinclude _nmppiResampleDown2X__FPUcPUciiPl.html
//!

void nmppiResampleDown2X_8u8u(
		nm8u7b*		pSrcImg,	// input buffer		:long Local	[h*w/8]
		nm8u7b*		pDstImg,	// output buffer	:long Global[h*w/16]
		int			nSrcWidth,	//Image width		width = [0,8,16...]
		int			nSrcHeight,	//Image height		height = [0,2,4...]
		nm64s*		pKernel
		)
{
    nmppsResampleDown2_8u8u((nm8u7b*)pSrcImg,(nm8u7b*)pDstImg,nSrcHeight*nSrcWidth,pKernel);
}

//!
//! \perfinclude _nmppiResampleDown2X__FPUsPUsiiPl.html
//!


void nmppiResampleDown2X_16u16u(
                      nm16u15b*		pSrcImg,	// input buffer		:long Local	[h*w/8]
                      nm16u15b*		pDstImg,	// output buffer	:long Global[h*w/16]
                      int				nSrcWidth,	//Image width		width = [0,8,16...]
                      int				nSrcHeight,	//Image height		height = [0,2,4...]
					  nm64s*		pKernel
                      )
{
    nmppsResampleDown2_16u16u((nm16u15b*)pSrcImg,(nm16u15b*)pDstImg,nSrcHeight*nSrcWidth,pKernel);
}


//!
//! \perfinclude _nmppiResampleDown2X__FPUcPUsiiPlPv.html
//!

void nmppiResampleDown2X_8u16u(
                      nm8u*			pSrcImg,	// input buffer		:long Local	[h*w/8]
                      nm16u*		pDstImg,	// output buffer	:long Global[h*w/16]
                      int				nSrcWidth,	//Image width		width = [0,8,16...]
                      int				nSrcHeight,	//Image height		height = [0,2,4...]
					  nm64s*		pKernel,
                      void*			pTmpBuf			// output buffer	:long Global[h*w/4]	
                      )
{
    int len = nSrcHeight*nSrcWidth;
    nmppsConvert_8s16s((nm8s*)pSrcImg,(nm16s*)pTmpBuf,len);
    nmppsResampleDown2_16u16u((nm16u15b*)pTmpBuf,(nm16u15b*)pDstImg,len,pKernel);
}

//!
//! \restr 
//!		\ru Высота должна делиться на 4.
//!     \en height should be devisable by 4.
//!
//! \perfinclude _nmppiResampleDown2Y__FPUcPUsiiPv.html
//!


void nmppiResampleDown2Y_8u16u_tmp(
		nm8u*			pSrcImg,	// input buffer		:long Local	[h*w/8]
		nm16u*			pDstImg,	// output buffer	:long Global[h*w/16]
		int				nSrcWidth,	//Image width		width = [0,8,16...]
		int				nSrcHeight,	//Image height		height = [0,2,4...]
		void*			pTmpBuf	// output buffer	:long Global[h*w/4]	
		)
{

    nmppsConvert_8s16s((nm8s*)pSrcImg,(nm16s*)pTmpBuf,nSrcHeight*nSrcWidth);
    nmppiResampleDown2Y_16u16u((nm16u15b*)pTmpBuf,(nm16u15b*)pDstImg,nSrcHeight,nSrcWidth);
}

//!
//! \restr 
//!		\ru Высота должна делиться на 4. 
//!     \en height should be devisable by 4.
//!
//! \perfinclude _nmppiResampleDown2XY__FPUcPUsiiPlPv.html
//!

void nmppiResampleDown2XY_8u16u_tmp(
                       nm8u*			pSrcImg,	// input buffer		:long Local	[h*w/8]
                       nm16u*			pDstImg,	// output buffer	:long Global[h*w/16]
                       int				nSrcWidth,	//Image width		width = [0,8,16...]
                       int				nSrcHeight,	//Image height		height = [0,2,4...]
					   	nm64s*		pKernel,
                       void*			pTmpBuf	// output buffer	:long Global[h*w/4]	
                       )
{
    nmppsConvert_8s16s((nm8s*)pSrcImg,(nm16s*)pTmpBuf,nSrcHeight*nSrcWidth);
    nmppsResampleDown2_16u16u((nm16u15b*)pTmpBuf,(nm16u15b*)pTmpBuf,nSrcHeight*nSrcWidth,pKernel);
    nmppiResampleDown2Y_16u16u((nm16u15b*)pTmpBuf,(nm16u15b*)pDstImg,nSrcHeight,(nSrcWidth/2));
}

//!
//! \restr 
//!		\ru Высота должна делиться на 8.
//!     \en height should be devisable by 8.
//!
//! \perfinclude _nmppiResampleDown2XY__FPUcPUciiPlPv.html
//!

void nmppiResampleDown2XY_8u8u_tmp(
                       nm8u7b*		pSrcImg,	// input buffer		:long Local	[h*w/8]
                       nm8u7b* 		pDstImg,	// output buffer	:long Global[h*w/16]
                       int				nSrcWidth,	//Image width		width = [0,8,16...]
                       int				nSrcHeight,	//Image height		height = [0,2,4...]
					   	nm64s*		pKernel,
                       void*			pTmpBuf	// output buffer	:long Global[h*w/4]	
                       )
{
    nmppsResampleDown2_8u8u((nm8u7b*)pSrcImg,(nm8u7b*)pTmpBuf,nSrcHeight*nSrcWidth,pKernel);
    nmppiResampleDown2Y_8u8u((nm8u7b*)pTmpBuf,(nm8u7b*)pDstImg,nSrcHeight,(nSrcWidth/2));
}

//!
//! \restr 
//!		\ru Высота должна делиться на 4. 
//!     \en height should be devisable by 4.
//!
//! \perfinclude _nmppiResampleDown2XY__FPUsPUsiiPlPv.html
//!


void nmppiResampleDown2XY_16u16u(
						nm16u15b*	pSrcImg,	// input buffer		:long Local	[h*w/8]
						nm16u15b*	pDstImg,	// output buffer	:long Global[h*w/16]
						int			nSrcWidth,	//Image width		width = [0,8,16...]
						int			nSrcHeight,	//Image height		height = [0,2,4...]
						nm64s*		pKernel,
						void*		pTmpBuf	// output buffer	:long Global[h*w/4]	
		)
{
    nmppsResampleDown2_16u16u((nm16u15b*)pSrcImg,(nm16u15b*)pTmpBuf,nSrcHeight*nSrcWidth,pKernel);
    nmppiResampleDown2Y_16u16u((nm16u15b*)pTmpBuf,(nm16u15b*)pDstImg,nSrcHeight,(nSrcWidth/2));
}

