//------------------------------------------------------------------------
//
//  $Workfile:: iResample. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   iResample.h
//! \author Сергей Мушкаев
//! \brief  Изменение размера изображения.
//!
//! \endif
//!
//------------------------------------------------------------------------

#ifndef _I_Resample_H_INCLUDED_
#define _I_Resample_H_INCLUDED_

//#include "nmpls.h"


#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************

    /**
	\internal
    \defgroup nmppiResampleDown2X nmppiResampleDown2X
    \ingroup iResample
    \brief
        \ru Уменьшение ширины изображения вдвое. 
        \en Image width reduction by factor 2. 
    
		\~
    
	\f[
        pDst(x,y) = \frac{1}{2} \left( pSrcImg(2*x, y) + pSrcImg(2*x+1, y) \right)
    \f]
    
    \ru Значение пикселя для выходного изображения получаются 
        в результате усреднения значений для соседних пикселей входного 
        изображения. 
    \en Pixel value for output image results from averaging 
        values from neighbour pixels on the input image. 

		\~
		\~
    \param pSrcImg		
        \ru Исходное изображение. 
        \en Input image. 
		\~
    \param pTmpBuf      
        \ru Временный буфер размера 2*nSrcWidth*nSrcHeight. 
        \en Temporary buffer with size 2*nSrcWidth*nSrcHeight. 
		\~
    \param nSrcWidth		
        \ru Ширина изображения; 
        \en Image width; 
		\~
    \param nSrcHeight		
        \ru Высота изображения. 
        \en Image height. 

		\~
    \retval pDst		
        \ru Результирующее изображение; 
        \en Output image. 

		\~
    \restr 
        \ru Высота должна быть четным числом.
        \en nSrcHeight should be an even number.
    
		\~
    \note 
        \ru Для того чтобы избежать переполнения при усреднении,
              динамический диапазон исходного изображения должен
              принадлежать диапазону, определенному типом. 
        \en To avoid data overflow dynamic range of source
              image should be in interval defined by type. 
    
		\~
    \par
    \xmlonly
        <testperf> 
             <param name="pSrcImg"> im0 im1 </param>
             <param name="pDstImg"> im0 im1 </param>
             <param name="pTmpBuf"> im2 im3 </param>
             <param name="nSrcHeight"> 128 </param>
             <param name="nSrcWidth"> 128 </param>
             <size> nSrcHeight*nSrcWidth </size>
        </testperf>
        <testperf> 
             <param name="pSrcImg"> im0 </param>
             <param name="pDstImg"> im1 </param>
             <param name="pTmpBuf"> im2 </param>
             <param name="nSrcHeight"> 128 </param>
             <param name="nSrcWidth"> 8 32 128 </param>
             <size> nSrcHeight*nSrcWidth </size>
        </testperf>
    \endxmlonly
    */
    //! \{
//void nmppiResampleDown2X_8u8u(nm8u7b* pSrcImg, nm8u7b* pDstImg, int nSrcWidth, int nSrcHeight) ;
void nmppiResampleDown2X_8u8u(nm8u7b* pSrcImg, nm8u7b* pDstImg, int nSrcWidth, int nSrcHeight,nm64s*pKernel) ;
//void nmppiResampleDown2X_16u16u(nm16u15b* pSrcImg, nm16u15b* pDstImg, int nSrcWidth, int nSrcHeight);
void nmppiResampleDown2X_16u16u(nm16u15b* pSrcImg, nm16u15b* pDstImg, int nSrcWidth, int nSrcHeight, nm64s* pKernel);
//void nmppiResampleDown2X_8u16u(nm8u* pSrcImg, nm16u* pDstImg, int nSrcWidth, int nSrcHeight, void* pTmpBuf);
    //! \}

//*****************************************************************************

    /**
	\internal
    \defgroup nmppiResampleDown2Y nmppiResampleDown2Y
    \ingroup iResample
    \brief
        \ru Уменьшение высоты изображения вдвое. 
        \en Image height reduction by factor 2. 
    
		\~
    
	\f[
        pDst(x,y) = \frac{1}{2} \left( pSrcImg(x, 2*y) + pSrcImg(x, 2*y+1) \right)
    \f]
    
    \ru Значение пикселя для выходного изображения получаются 
        в результате усреднения значений для соседних пикселей входного 
        изображения. 
    \en Pixel value for output image results from averaging 
        values from neighbour pixels on the input image. 

		\~
		\~
    \param pSrcImg		
        \ru Исходное изображение. 
        \en Input image. 
		\~
    \param pTmpBuf      
        \ru Временный буфер размера 2*nSrcWidth*nSrcHeight. 
        \en Temporary buffer with size 2*nSrcWidth*nSrcHeight. 
		\~
    \param nSrcWidth		
        \ru Ширина изображения; 
        \en Image width; 
		\~
    \param nSrcHeight		
        \ru Высота изображения. 
        \en Image height. 

		\~
    \retval	pDst		
        \ru Результирующее изображение; 
        \en Output image. 

		\~
    \restr 
        \ru Высота должна быть четным числом. 
        \en nSrcHeight should be an even number. 

		\~
    \note \ru Для того чтобы избежать переполнения при усреднении,
              динамический диапазон исходного изображения должен
              принадлежать диапазону, определенному типом. 
          \en To avoid data overflow dynamic range of source
              image should be in interval defined by type. 

		\~
    \par
    \xmlonly
        <testperf> 
             <param name="pSrcImg"> im0 im1 </param>
             <param name="pDstImg"> im0 im1 </param>
             <param name="pTmpBuf"> im2 im3 </param>
             <param name="nSrcHeight"> 128 </param>
             <param name="nSrcWidth"> 8 32 128 </param>
             <size> nSrcHeight*nSrcWidth </size>
        </testperf>
        <testperf> 
             <param name="pSrcImg"> im0 </param>
             <param name="pDstImg"> im1 </param>
             <param name="pTmpBuf"> im2 </param>
             <param name="nSrcHeight"> 128 </param>
             <param name="nSrcWidth"> 128 </param>
             <size> nSrcHeight*nSrcWidth </size>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppiResampleDown2Y_8u8u (nm8u7b* pSrcImg, nm8u7b* pDstImg, int nSrcWidth, int nSrcHeight);
void nmppiResampleDown2Y_16u16u(nm16u15b* pSrcImg, nm16u15b* pDstImg, int nSrcWidth, int nSrcHeight);
void nmppiResampleDown2Y_8u16u_tmp(nm8u* pSrcImg, nm16u* pDstImg, int nSrcWidth, int nSrcHeight, void* pTmpBuf);
    //! \}

//*****************************************************************************

    /**
	\internal
    \defgroup nmppiResampleDown2XY nmppiResampleDown2XY
    \ingroup iResample
    \brief
        \ru Уменьшение размеров изображения вдвое. 
        \en Image size reduction by factor 2. 
    
		\~
    
	\f[
        pDst(x,y) = \frac{1}{4} \sum_{k=0}^1 \sum_{l=0}^1 pSrcImg(2*x+k, 2*y+l)
    \f]
    
    \ru Значение пикселя для выходного изображения получаются 
        в результате усреднения значений для соседних пикселей входного 
        изображения. 
    \en Pixel value for output image results from averaging 
        values from neighbour pixels on the input image. 

		\~
		\~
    \param pSrcImg		
        \ru Исходное изображение. 
        \en Input image. 
		\~
    \param pTmpBuf      
        \ru Временный буфер размера 2*nSrcWidth*nSrcHeight. 
        \en Temporary buffer with size 2*nSrcWidth*nSrcHeight. 
		\~
    \param nSrcWidth		
        \ru Ширина изображения; 
        \en Image width; 
		\~
    \param nSrcHeight		
        \ru Высота изображения. 
        \en Image height. 

		\~
    \retval pDst		
        \ru Результирующее изображение; 
        \en Output image. 

		\~
    \restr 
        \ru Высота должна быть четным числом. 
        \en nSrcHeight should be an even number. 

		\~
    \note \ru Для того чтобы избежать переполнения при усреднении,
              динамический диапазон исходного изображения должен
              принадлежать диапазону, определенному типом. 
          \en To avoid data overflow dynamic range of source
              image should be in interval defined by type. 
		\~
    \par
    \xmlonly
        <testperf> 
             <param name="pSrcImg"> im0 im1 </param>
             <param name="pDstImg"> im0 im1 </param>
             <param name="pTmpBuf"> im2 im3 </param>
             <param name="nSrcHeight"> 128 </param>
             <param name="nSrcWidth"> 128 </param>
             <size> nSrcHeight*nSrcWidth </size>
        </testperf>
        <testperf> 
             <param name="pSrcImg"> im0 </param>
             <param name="pDstImg"> im1 </param>
             <param name="pTmpBuf"> im2 </param>
             <param name="nSrcHeight"> 128 </param>
             <param name="nSrcWidth"> 8 32 128 </param>
             <size> nSrcHeight*nSrcWidth </size>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppiResampleDown2XY_8u8u(nm8u7b* pSrcImg, nm8u7b* pDstImg, int nSrcWidth, int nSrcHeight, void* pTmpBuf);
//void nmppiResampleDown2XY_16u16u(nm16u15b* pSrcImg, nm16u15b* pDstImg, int nSrcWidth, int nSrcHeight, void* pTmpBuf);
//void nmppiResampleDown2XY_8u16u(nm8u* pSrcImg, nm16u* pDstImg, int nSrcWidth, int nSrcHeight, void* pTmpBuf);
    //! \}

//void nmppiVResample3div2_RShift0(nm16s* pSrcImg, int nWidth, int nHeight, nm16s* pDstImg);


//__INLINE__ void nmppiCreateResampleDown2X_8u8u(nm64s**	pKernel, int nHint)	{	nmppsCreateResampleDown2_8u8u(pKernel,nHint);}
//__INLINE__ void nmppiCreateResampleDown2X_8u16u(nm64s** pKernel, int nHint)	{	nmppsCreateResampleDown2_16u16u(pKernel,nHint);}
//__INLINE__ void nmppiCreateResampleDown2X_16u16u(nm64s** pKernel, int nHint)	{	nmppsCreateResampleDown2_16u16u(pKernel,nHint);}
//__INLINE__ void nmppiCreateResampleDown2Y_8u16u(nm64s** pKernel, int nHint)	{   nmppsCreateResampleDown2_16u16u(pKernel,nHint);}
//__INLINE__ void nmppiCreateResampleDown2XY_8u16u(nm64s**	 pKernel, int nHint){   nmppsCreateResampleDown2_16u16u(pKernel,nHint);}
//__INLINE__ void nmppiCreateResampleDown2XY_8u8u(nm64s** pKernel, int nHint)	{   nmppsCreateResampleDown2_8u8u(pKernel,nHint);}
//__INLINE__ void nmppiCreateResampleDown2XY_16u16u(nm64s** pKernel,int nHint)	{   nmppsCreateResampleDown2_16u16u(pKernel,nHint);}

#ifdef __cplusplus
		};
#endif

#endif // _I_Resample_H_INCLUDED_