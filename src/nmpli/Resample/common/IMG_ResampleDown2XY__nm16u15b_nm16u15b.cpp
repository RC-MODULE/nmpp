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

 #include "nmplv.h"
#include "nmpls.h"
#include "nmpli.h"
//!
//! \perfinclude _IMG_ResampleDown2X__FPUcPUciiPl.html
//!

void IMG_ResampleDown2X(
		nm8u7b*		pSrcImg,	// input buffer		:long Local	[h*w/8]
		nm8u7b*		pDstImg,	// output buffer	:long Global[h*w/16]
		int			nSrcWidth,	//Image width		width = [0,8,16...]
		int			nSrcHeight,	//Image height		height = [0,2,4...]
		nm64s*		pKernel
		)
{
    SIG_ResampleDown2((nm8u7b*)pSrcImg,(nm8u7b*)pDstImg,nSrcHeight*nSrcWidth,pKernel);
}

//!
//! \perfinclude _IMG_ResampleDown2X__FPUsPUsiiPl.html
//!


void IMG_ResampleDown2X(
                      nm16u15b*		pSrcImg,	// input buffer		:long Local	[h*w/8]
                      nm16u15b*		pDstImg,	// output buffer	:long Global[h*w/16]
                      int				nSrcWidth,	//Image width		width = [0,8,16...]
                      int				nSrcHeight,	//Image height		height = [0,2,4...]
					  nm64s*		pKernel
                      )
{
    SIG_ResampleDown2((nm16u15b*)pSrcImg,(nm16u15b*)pDstImg,nSrcHeight*nSrcWidth,pKernel);
}


//!
//! \perfinclude _IMG_ResampleDown2X__FPUcPUsiiPlPv.html
//!

void IMG_ResampleDown2X(
                      nm8u*			pSrcImg,	// input buffer		:long Local	[h*w/8]
                      nm16u*		pDstImg,	// output buffer	:long Global[h*w/16]
                      int				nSrcWidth,	//Image width		width = [0,8,16...]
                      int				nSrcHeight,	//Image height		height = [0,2,4...]
					  nm64s*		pKernel,
                      void*			pTmpBuf			// output buffer	:long Global[h*w/4]	
                      )
{
    int len = nSrcHeight*nSrcWidth;
    nmppsCnv_8s16s((nm8s*)pSrcImg,(nm16s*)pTmpBuf,len);
    SIG_ResampleDown2((nm16u15b*)pTmpBuf,(nm16u15b*)pDstImg,len,pKernel);
}

//!
//! \restr 
//!		\ru Высота должна делиться на 4.
//!     \en height should be devisable by 4.
//!
//! \perfinclude _IMG_ResampleDown2Y__FPUcPUsiiPv.html
//!


void IMG_ResampleDown2Y(
		nm8u*			pSrcImg,	// input buffer		:long Local	[h*w/8]
		nm16u*			pDstImg,	// output buffer	:long Global[h*w/16]
		int				nSrcWidth,	//Image width		width = [0,8,16...]
		int				nSrcHeight,	//Image height		height = [0,2,4...]
		void*			pTmpBuf	// output buffer	:long Global[h*w/4]	
		)
{

    nmppsCnv_8s16s((nm8s*)pSrcImg,(nm16s*)pTmpBuf,nSrcHeight*nSrcWidth);
    IMG_ResampleDown2Y((nm16u15b*)pTmpBuf,(nm16u15b*)pDstImg,nSrcHeight,nSrcWidth);
}

//!
//! \restr 
//!		\ru Высота должна делиться на 4. 
//!     \en height should be devisable by 4.
//!
//! \perfinclude _IMG_ResampleDown2XY__FPUcPUsiiPlPv.html
//!

void IMG_ResampleDown2XY(
                       nm8u*			pSrcImg,	// input buffer		:long Local	[h*w/8]
                       nm16u*			pDstImg,	// output buffer	:long Global[h*w/16]
                       int				nSrcWidth,	//Image width		width = [0,8,16...]
                       int				nSrcHeight,	//Image height		height = [0,2,4...]
					   	nm64s*		pKernel,
                       void*			pTmpBuf	// output buffer	:long Global[h*w/4]	
                       )
{
    nmppsCnv_8s16s((nm8s*)pSrcImg,(nm16s*)pTmpBuf,nSrcHeight*nSrcWidth);
    SIG_ResampleDown2((nm16u15b*)pTmpBuf,(nm16u15b*)pTmpBuf,nSrcHeight*nSrcWidth,pKernel);
    IMG_ResampleDown2Y((nm16u15b*)pTmpBuf,(nm16u15b*)pDstImg,nSrcHeight,(nSrcWidth/2));
}

//!
//! \restr 
//!		\ru Высота должна делиться на 8.
//!     \en height should be devisable by 8.
//!
//! \perfinclude _IMG_ResampleDown2XY__FPUcPUciiPlPv.html
//!

void IMG_ResampleDown2XY(
                       nm8u7b*		pSrcImg,	// input buffer		:long Local	[h*w/8]
                       nm8u7b* 		pDstImg,	// output buffer	:long Global[h*w/16]
                       int				nSrcWidth,	//Image width		width = [0,8,16...]
                       int				nSrcHeight,	//Image height		height = [0,2,4...]
					   	nm64s*		pKernel,
                       void*			pTmpBuf	// output buffer	:long Global[h*w/4]	
                       )
{
    SIG_ResampleDown2((nm8u7b*)pSrcImg,(nm8u7b*)pTmpBuf,nSrcHeight*nSrcWidth,pKernel);
    IMG_ResampleDown2Y((nm8u7b*)pTmpBuf,(nm8u7b*)pDstImg,nSrcHeight,(nSrcWidth/2));
}

//!
//! \restr 
//!		\ru Высота должна делиться на 4. 
//!     \en height should be devisable by 4.
//!
//! \perfinclude _IMG_ResampleDown2XY__FPUsPUsiiPlPv.html
//!


void IMG_ResampleDown2XY(
						nm16u15b*	pSrcImg,	// input buffer		:long Local	[h*w/8]
						nm16u15b*	pDstImg,	// output buffer	:long Global[h*w/16]
						int			nSrcWidth,	//Image width		width = [0,8,16...]
						int			nSrcHeight,	//Image height		height = [0,2,4...]
						nm64s*		pKernel,
						void*		pTmpBuf	// output buffer	:long Global[h*w/4]	
		)
{
    SIG_ResampleDown2((nm16u15b*)pSrcImg,(nm16u15b*)pTmpBuf,nSrcHeight*nSrcWidth,pKernel);
    IMG_ResampleDown2Y((nm16u15b*)pTmpBuf,(nm16u15b*)pDstImg,nSrcHeight,(nSrcWidth/2));
}

