//------------------------------------------------------------------------
//
//  $Workfile:: sConvolution. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file   vConvolution.h
//! \author Сергей Мушкаев
//! \brief  Определение функций одномерной свертки.
//!
//! \endif
//!
//------------------------------------------------------------------------

#ifndef _SCONVOLUTION_H_INCLUDED_
#define _SCONVOLUTION_H_INCLUDED_
#include "nmtype.h"

//*****************************************************************************

    /**
    \defgroup SIG_XCorr SIG_XCorr
    \ingroup sConvolution
    \brief
        \ru Свертка двух векторов. 
        \en Two vectors convolution. 
    
		\~
    
	\f[
        DstVec_i  = \sum \limits_{j = 0}^{nKernelSize - 1} pSrcVec[i + j]  \cdot pKernel[j] 
    \f]
    
	\f[
        i = \overline{0 \ldots nSrcVecSize-nKernelSize+1}
    \f]
    
    \param	pSrcVec		
        \ru Входной вектор. 
        \en Input vec. 
		\~
    \param	pKernel		
        \ru Вектор коэффициентов окна свертки. 
        \en Vector of convolution window coefficients. 
		\~
    \param	pTmpBuf		\ru Указатель на временный буффер размера 
                            2*nKernelSize + 32 32-битных слов;\n 
                        \en Pointer to a temporary buffer sized
		\~
                            2*nKernelSize + 32 32-bit words;\n 
    \param	nKernelSize	
        \ru Размер окна свертки  [1,2,3,4...nSrcVecSize-1]. 
        \en Convolution window size.  [1,2,3,4...nSrcVecSize-1]. 
		\~
    \param	nSrcVecSize	
        \ru Размер входного вектора в элементах .Размер кратен 8,4 или 2 согласно типу данных. 
        \en Input vec size in elements. 
		\~
    \retval	pDstVec		
        \ru Результирующий вектор, размером nSrcVecSize-nKernelSize+1. после которого могут записыватсья  еще до 7 незначачих 32р слова.
        \en The result vec. 
		\~
    \note
        \ru По сути функции осушествляют фильтрацию данных окном свертки.
        \en As a matter of fact the functions filter data by means of convolution window.
        
    \par
    \xmlonly
        <testperf> 
             <param> pSrcVec </param> <values> L G </values>
             <param> pTmpBuf </param> <values> L G </values>
             <param> pKernel </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nKernelSize </param> <values> 1 2 3 </values>
             <param> nSrcVecSize </param> <values> 4 8 16 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void SIG_XCorr_32s(nm32s* pSrcVec, int nSrcVecSize,nm32s* pKernel, int nKernelSize, nm32s* pDstVec, void* pTmpBuf);
void SIG_XCorr_16s32s(nm16s* pSrcVec, int nSrcVecSize,nm32s* pKernel, int nKernelSize, nm32s* pDstVec, void* pTmpBuf);
void SIG_XCorr_8s32s(nm8s* pSrcVec,  int nSrcVecSize,nm32s* pKernel, int nKernelSize, nm32s* pDstVec, void* pTmpBuf);
    //! \}



#endif
