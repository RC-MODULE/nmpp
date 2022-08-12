 #ifndef __IARITHMETICS_H
#define __IARITHMETICS_H
#ifdef ARITHM
#include "iDef.h"


//*****************************************************************************

    /**
	\internal
    \defgroup nmppiAddConvertRShiftI nmppiAddConvertRShiftI
    \ingroup iArithmetics
    \brief
        \ru Поэлементное прибавление преобразованного изображения. 
        \en Elementwise addition of the converted image. 
    
		\~
    
	\f[
        pSrcDstImg(x, y) += Convert(pSrcImg(x, y) >> nShift)
    \f]
    
	\f[ x = \overline{0 \ldots nWidth-1}, \quad 
        y = \overline{0 \ldots nHeight-1} \f]
    
    \param pSrcDstImg   
        \ru Указатель на первый элемент ROI замещаемого изображения. 
        \en Pointer on the first ROI element of the replaceable image. 
		\~
    \param nSrcDstStride \ru Межстроковое смещение для замещаемого изображения \n
                             (измеряется в 32-х разрядных словах). 
                         \en Row-to-row shift for the replaceable image \n
                             (measured in 32-bit words). 
    \param pSrcImg      
        \ru Указатель на первый элемент ROI для прибавляемого изображения. 
        \en Pointer to the first ROI element for the added image. 
		\~
    \param nSrcStride   \ru Межстроковое смещение для прибавляемого изображения \n
                            (измеряется в 32-х разрядных словах). 
                        \en Row-to-row shift for the added image \n
                             (measured in 32-bit words). 
    \param nShift       
        \ru Определяет число бит на которое предварительно сдвигается прибавляемое 
                            изображение. 
        \en Determines the number of bits for which the added image is preliminary shifted. 
		\~
    \param nWidth     
        \ru Ширина ROI (измеряется в пикселях). Кратность согласно входному типу.
        \en ROI width (measured in pixels). 
		\~
    \param nHeight    
        \ru Высота ROI (измеряется в пикселях). 
        \en ROI height (measured in pixels). 
		\~
    \return \e void
    
    \restr
    -   \ru Указатели на первый элемент ROI должны быть выровнены 
            в памяти на границу 64-х разрядного слова;
        \en Pointers to the first ROI element should be aligned
            in memory by the 64-bit word boundary;
		\~
    -   \ru Ширина ROI должна быть кратна числу пикселей результирующего изображения
            в 64-х разрядном слове;
        \en ROI width should be divisible by the number of pixels of the result image
            in a 64-bit word;
		\~
    -   \ru Межстроковые смещения должны быть кратны двум;
        \en Row-to-row shifts should be divisible by two;
		\~
    -   \ru Значение параметра nShift должно быть кратно 2.
        \en nShift parameter value should be divisible by two.
        
		\~
    \par
    \xmlonly
        <testperf> 
             <param name="pSrcImg"> im0 im1 </param>
             <param name="pSrcDstImg"> im0 im1 </param>
             <param name="nSrcStride"> 128 </param>
             <param name="nSrcDstStride"> 64 </param>
             <param name="nShift"> 2 </param>
             <param name="nHeight"> 64 </param>
             <param name="nWidth"> 64 </param>
             <size> nWidth*nHeight </size>
        </testperf>
        <testperf> 
             <param name="pSrcImg"> im0 </param>
             <param name="pSrcDstImg"> im1 </param>
             <param name="nSrcStride"> 128 </param>
             <param name="nSrcDstStride"> 64 </param>
             <param name="nShift"> 2 </param>
             <param name="nHeight"> 64 </param>
             <param name="nWidth"> 8 32 64 </param>
             <size> nWidth*nHeight </size>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppiAddConvertRShiftI(nm16s* pSrcDstImg,  int nSrcDstStride, nm32s* pSrcImg, int nSrcStride, int nShift, int nWidth, int nHeight); 
    //! \}

//*****************************************************************************

    /**
	\internal
    \defgroup nmppiSubConvertRShiftI nmppiSubConvertRShiftI
    \ingroup iArithmetics
    \brief
        \ru Поэлементное вычитание преобразованного изображения. 
        \en Elementwise subtraction of a converted image. 
    
		\~
    
	\f[
        pSrcDstImg(x, y) -= Convert(pSrcImg(x, y) >> nShift)
    \f]
    
	\f[ x = \overline{0 \ldots nWidth-1}, \quad 
        y = \overline{0 \ldots nHeight-1} \f]
    
    \param pSrcDstImg    
        \ru Указатель на первый элемент ROI для результирующего изображения. 
        \en Pointer to the first ROI element for the result image. 
		\~
    \param nSrcDstStride  \ru Межстроковое смещение для результирующего изображения
                              (измеряется в 32-х разрядных словах). 
    		              \en Row-to-row shift for the result image \n
    	                      (measured in 32-bit words). 
    \param pSrcImg       
        \ru Указатель на первый элемент ROI для вычитаемого изображения. 
        \en Pointer to the first ROI element for the deducted image. 
		\~
    \param nSrcStride \ru Межстроковое смещение для результирующего изображения
                          (измеряется в 32-х разрядных словах). 
                      \en Row-to-row shift for the result image \n
    	                  (measured in 32-bit words). 
    \param nShift     
        \ru Определяет число бит на которое предварительно сдвигается вычитаемое 
                          изображение. 
        \en Defines for how many bits the deducted image is preliminary shifted. 
		\~
    \param nWidth     
        \ru Ширина ROI (измеряется в пикселях). 
        \en ROI width (measured in pixels). 
		\~
    \param nHeight    
        \ru Высота ROI (измеряется в пикселях). 
        \en ROI height (measured in pixels). 
		\~
    \return \e void
    
    \restr
    -   \ru Указатели на первый элемент ROI должны быть выровнены 
            в памяти на границу 64-х разрядного слова;
        \en Pointers to the first ROI element should be aligned  
            in memory by the 64-bit word boundary;
		\~
    -   \ru Ширина ROI должна быть кратна числу пикселей результирующего изображения
            в 64-х разрядном слове;
        \en ROI width should be divisible by the number of pixels of the result image 
            in a 64-bit word;
		\~
    -   \ru Межстроковые смещения должны быть кратны двум;
        \en Row-to-row shifts should be divisible by two;
		\~
    -   \ru Значение параметра nShift должно быть кратно 2.
        \en nShift parameter value should be divisible by two.
    
		\~
    \par
    \xmlonly
        <testperf> 
             <param name="pSrcImg"> im0 im1 </param>
             <param name="pSrcDstImg"> im0 im1 </param>
             <param name="nSrcStride"> 128 </param>
             <param name="nSrcDstStride"> 64 </param>
             <param name="nShift"> 2 </param>
             <param name="nHeight"> 64 </param>
             <param name="nWidth"> 64 </param>
             <size> nWidth*nHeight </size>
        </testperf>
        <testperf> 
             <param name="pSrcImg"> im0 </param>
             <param name="pSrcDstImg"> im1 </param>
             <param name="nSrcStride"> 128 </param>
             <param name="nSrcDstStride"> 64 </param>
             <param name="nShift"> 2 </param>
             <param name="nHeight"> 64 </param>
             <param name="nWidth"> 8 32 64 </param>
             <size> nWidth*nHeight </size>
        </testperf>
    \endxmlonly
    */
    //! \{

void nmppiSubConvertRShiftI(nm16s * pSrcDstImg,  int nSrcDstStride,  nm32s * pSrcImg, int nSrcStride, int nShift, int nWidth, int nHeight);
    //! \}

//*****************************************************************************

    /**
	\internal
    \defgroup nmppiAdd_16s nmppiAdd_16s
    \ingroup iArithmetics
    \brief
        \ru Поэлементное сложение двух изображений. 
        \en Elementwise addition of two images. 
    
		\~
    
	\f[
        pSrcDstImg(x, y) += pSrcImg(x, y)
    \f]
    
	\f[ x = \overline{0 \ldots nWidth-1}, \quad 
        y = \overline{0 \ldots nHeight-1} \f]
    
    \param pSrcImg       
        \ru Указатель на первый элемент ROI для прибавляемого изображения. 
        \en Pointer to the first ROI element for the added image. 
		\~
    \param nSrcStride \ru Межстроковое смещение для результирующего изображения \n
                          (измеряется в 32-х разрядных словах). 
                      \en Row-to-row shift for the result image \n
                          (measured in 32-bit words). 
    \param pSrcDstImg    
        \ru Указатель на первый элемент ROI для результирующего изображения. 
        \en Pointer to the first ROI element for the result image. 
		\~
    \param nSrcDstStride \ru Межстроковое смещение для замещаемого изображения \n
                             (измеряется в 32-х разрядных словах).    
                         \en Row-to-row shift for the replaceable image \n
                             (measured in 32-bit words). 
    \param nWidth     
        \ru Ширина ROI (измеряется в пикселях). 
        \en ROI width (measured in pixels). 
		\~
    \param nHeight    
        \ru Высота ROI (измеряется в пикселях). 
        \en ROI height (measured in pixels). 
		\~
    \return \e void 
    
    \restr
        \ru
            - Указатели на первый элемент ROI должны быть выровнены 
                в памяти на границу 64-х разрядного слова; 
            - Ширина ROI должна быть кратна числу пикселей 
                в 64-х разрядном слове; 
            - Межстроковые смещения должны быть кратны двум.
        \en
            - Pointers to the first ROI element should be aligned 
                in memory by the 64-bit word boundary; 
            - ROI width should be divisible by the number of pixels 
                in a 64-bit word; 
            - Row-to-row shifts should be divisible by two. 

    \par
    \xmlonly
        <testperf> 
             <param name="pSrcImg"> im0 im1 </param>
             <param name="pSrcDstImg"> im0 im1 </param>
             <param name="nSrcStride"> 128 </param>
             <param name="nSrcDstStride"> 128 </param>
             <param name="nHeight"> 128 </param>
             <param name="nWidth"> 128 </param>
             <size> nWidth*nHeight </size>
        </testperf>
        <testperf> 
             <param name="pSrcImg"> im0 </param>
             <param name="pSrcDstImg"> im1 </param>
             <param name="nSrcStride"> 128 </param>
             <param name="nSrcDstStride"> 128 </param>
             <param name="nHeight"> 128 </param>
             <param name="nWidth"> 8 64 128 </param>
             <size> nWidth*nHeight </size>
        </testperf>
    \endxmlonly
    */
    //! \{

void nmppiAdd_16s(nm16s* pSrcDstImg, int nSrcDstStride, nm16s *pSrcImg,  int nSrcStride, int nWidth, int nHeight);
    //! \}

//*****************************************************************************

    /**
	\internal
    \defgroup nmppiSub_16s nmppiSub_16s
    \ingroup iArithmetics
    \brief
        \ru Поэлементное вычитание двух изображений. 
        \en Elementwise subtraction of two images. 
    
		\~
    
	\f[
        pSrcDstImg(x, y) -= pSrcImg(x, y)
    \f]
    
	\f[ x = \overline{0 \ldots nWidth-1}, \quad 
        y = \overline{0 \ldots nHeight-1} \f]
    
    \param pSrcImg       
        \ru Указатель на первый элемент ROI для вычитаемого изображения. 
        \en Pointer to the first ROI element for the deducted image. 
		\~
    \param nSrcStride \ru Межстроковое смещение для результирующего изображения
                          (измеряется в 32-х разрядных словах). 
                      \en Row-to-row shift for the result image \n
    	                  (measured in 32-bit words). 
    \param pSrcDstImg    
        \ru Указатель на первый элемент ROI для замещаемого изображения. 
        \en Pointer to the ROI origin for replacing image. 
		\~
    \param nSrcDstStride 
        \ru Межстроковое смещение для замещаемого изображения
                            (измеряется в 32-х разрядных словах). 
        \en Row-to-row shift for the replaceable image 
                            (measured in 32-bit words). 
		\~
    \param nWidth     
        \ru Ширина ROI (измеряется в пикселях). 
        \en ROI width (measured in pixels). 
		\~
    \param nHeight    
        \ru Высота ROI (измеряется в пикселях). 
        \en ROI height (measured in pixels). 
		\~
    \return \e void 
    
    \restr
        \ru
            - Указатели на первый элемент ROI должны быть выровнены 
                в памяти на границу 64-х разрядного слова;
            - Ширина ROI должна быть кратна числу пикселей 
                в 64-х разрядном слове; 
            - Межстроковые смещения должны быть кратны двум.
        \en 
            - Pointers to the first ROI element should be aligned  
                in memory by the 64-bit word boundary;
            - ROI width should be divisible by the number of pixels 
                in a 64-bit word; 
            - Row-to-row shifts should be divisible by two. 
    
		\~
    \par
    \xmlonly
        <testperf> 
             <param name="pSrcImg"> im0 im1 </param>
             <param name="pSrcDstImg"> im0 im1 </param>
             <param name="nSrcStride"> 128 </param>
             <param name="nSrcDstStride"> 128 </param>
             <param name="nHeight"> 128 </param>
             <param name="nWidth"> 128 </param>
             <size> nWidth*nHeight </size>
        </testperf>
        <testperf> 
             <param name="pSrcImg"> im0 </param>
             <param name="pSrcDstImg"> im1 </param>
             <param name="nSrcStride"> 128 </param>
             <param name="nSrcDstStride"> 128 </param>
             <param name="nHeight"> 128 </param>
             <param name="nWidth"> 8 64 128 </param>
             <size> nWidth*nHeight </size>
        </testperf>
    \endxmlonly
    */
    //! \{

void nmppiSub_16s(nm16s* pSrcDstImg, int nSrcDstStride, nm16s *pSrcImg, int nSrcStride,  int nWidth, int nHeight);

    //! \}

//*****************************************************************************

    /**
	\internal
    \defgroup nmppiHalfsum nmppiHalfsum
    \ingroup iArithmetics
    \brief
        \ru Поэлементное усреднение двух блоков изображений. 
        \en Elementwise halfsum of two blocks of images. 
    
		\~
    
	\f[
        pSrcDstImg(x, y) = pSrcMtr1(x, y) + pSrcMtr2(x, y) / 2
    \f]
    
	\f[ x = \overline{0 \ldots nWidth-1}, \quad 
        y = \overline{0 \ldots nHeight-1} \f]
    
    \param pSrcMtr1       
        \ru Указатель на первый элемент ROI первого изображения. 
        \en Pointer to the first ROI element of the first image. 
		\~
    \param nSrcStride1 \ru Межстроковое смещение для первого изображения
                          (измеряется в 32-х разрядных словах). 
                      \en Row-to-row shift for the first image \n
    	                  (measured in 32-bit words). 
    \param pSrcMtr2       
        \ru Указатель на первый элемент ROI второго изображения. 
        \en Pointer to the first ROI element of the second image. 
		\~
    \param nSrcStride1 \ru Межстроковое смещение для второго изображения
                          (измеряется в 32-х разрядных словах). 
                      \en Row-to-row shift for the second image \n
    	                  (measured in 32-bit words).
    \param pDstMtr       
        \ru Указатель на первый элемент ROI результата. 
        \en Pointer to the first ROI element of the result. 
		\~
    \param nDstStride \ru Межстроковое смещение для результата
                          (измеряется в 32-х разрядных словах). 
                      \en Row-to-row shift for the result \n
    	                  (measured in 32-bit words).
    \param nWidth     
        \ru Ширина ROI (измеряется в пикселях). 
        \en ROI width (measured in pixels). 
		\~
    \param nHeight    
        \ru Высота ROI (измеряется в пикселях). 
        \en ROI height (measured in pixels). 
		\~
    \return \e void 
    
    \restr
        \ru
            - Указатели на первый элемент ROI должны быть выровнены 
                в памяти на границу 64-х разрядного слова;
            - Ширина ROI должна быть кратна числу пикселей 
                в 64-х разрядном слове; 
            - Межстроковые смещения должны быть кратны двум.
        \en 
            - Pointers to the first ROI element should be aligned  
                in memory by the 64-bit word boundary;
            - ROI width should be divisible by the number of pixels 
                in a 64-bit word; 
            - Row-to-row shifts should be divisible by two. 
    
		\~
    \par
    \xmlonly
        <testperf> 
             <param name="pSrcMtr1"> im0 im1 </param>
             <param name="pSrcMtr2"> im0 im1 </param>
             <param name="pDstMtr"> im2 im3 </param>
             <param name="nSrcStride1"> 128 </param>
             <param name="nSrcStride2"> 128 </param>
             <param name="nDstStride"> 128 </param>
             <param name="nHeight"> 128 </param>
             <param name="nWidth"> 128 </param>
             <size> nWidth*nHeight </size>
        </testperf>
        <testperf> 
             <param name="pSrcMtr1"> im0 </param>
             <param name="pSrcMtr2"> im1 </param>
             <param name="pDstMtr"> im2 </param>
             <param name="nSrcStride1"> 128 </param>
             <param name="nSrcStride2"> 128 </param>
             <param name="nDstStride"> 128 </param>
             <param name="nHeight"> 128 </param>
             <param name="nWidth"> 8 64 128 </param>
             <size> nWidth*nHeight </size>
        </testperf>
    \endxmlonly
    */
    //! \{

void nmppiHalfsum(nm16s* pSrcMtr1, int nSrcStride1, nm16s* pSrcMtr2, 
        int nSrcStride2, nm16s* pDstMtr, int nDstStride,  int nWidth,int nHeight);

    //! \}


	/**
	\defgroup nmppiWAdd2I nmppiWAdd2I
	\ingroup iArithmetics
	\brief
		\ru Взвешенное суммирование двух кадров с прибавлением константы
		\en

	\~
	\param pSrcImg1
		\ru Первое исходное изображение
		\en 
	\param nMulVal1
		\ru 1-ый множитель 
		\en
	\param pSrcImg2
		\ru Второе исходное излбражение
		\en
	\param nMulVal2
		\ru 2-ой множитель
		\en
	\param nAddVal
		\ru прибавляемая константа  
		\en
	\param pDstImg
		\ru Результируюшее изображение
		\en
	\param nSize
		\ru Размер изображения в пикселях
		\en

    \par
    \xmlonly
        <testperf> 
             <param name="pSrcImg1"> im0 im1 </param>
             <param name="pSrcImg2"> im0 im1 </param>
             <param name="pDstImg"> im2 im3 </param>
             <param name="nMulVal1"> 5 </param>
             <param name="nMulVal2"> 5 </param>
             <param name="nAddVal"> 5 </param>
             <param name="nSize"> 128 </param>
             <size> nSize </size>
        </testperf>
        <testperf> 
             <param name="pSrcImg1"> im0 </param>
             <param name="pSrcImg2"> im1 </param>
             <param name="pDstImg"> im2 </param>
             <param name="nMulVal1"> 5 </param>
             <param name="nMulVal2"> 5 </param>
             <param name="nAddVal"> 5 </param>
             <param name="nSize"> 128 1024 2048 </param>
             <size> nSize </size>
        </testperf>
    \endxmlonly

	*/
	//! \{
void nmppiWAdd2I(RGB32_nm10s* pSrcImg1, int nMulVal1, RGB32_nm10s* pSrcImg2, int nMulVal2, int nAddVal, RGB32_nm10s* pDstImg, int nSize);
	//! \}


	/**
	\defgroup nmppiRsh2 nmppiRsh2
	\ingroup iArithmetics
	\brief
		\ru Беззнаковый сдвиг значений пикслелей изображения на 2 бита вправо
		\en

	\~
	\param pSrcImg
		\ru Входное изображение
		\en 
	\param pDstImg
		\ru Выходное изображение 
		\en
	\param nSize
		\ru Размер изображения в пикселях
		\en

    \par
    \xmlonly
        <testperf> 
          <param name="pSrcImg"> im0 im1 </param>
          <param name="pDstImg"> im0 im1 </param>
          <param name="nSize"> 128 </param>
          <size> nSize </size>
        </testperf>
        <testperf> 
          <param name="pSrcImg"> im0 </param>
          <param name="pDstImg"> im1 </param>
          <param name="nSize"> 8 32 128 </param>
          <size> nSize </size>
        </testperf>
    \endxmlonly
	*/
	//! \{ 
void nmppiRsh2(RGB32_nm10u* pSrcImg, RGB32_nm10u* pDstImg, int nSize);
	//! \}
#endif
#endif
