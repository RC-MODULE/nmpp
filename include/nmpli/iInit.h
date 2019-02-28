#ifndef __ICONVERT_H
#define __ICONVERT_H

//#include "iCellTexture.h"
#include "iDef.h"

// #ifdef __cplusplus
// 		extern "C" {
// #endif

//*****************************************************************************

    /**
	\internal
    \defgroup nmppiRShiftConvert nmppiRShiftConvert
    \ingroup iInit
    \brief
        \ru Преобразование типов для элементов изображения.
        \en Conversion of types for image elements.

		\~

	\f[
        pDst(x,y) = Convert(pSrcImg(x,y) >> nShift)
    \f]

	\f[ x = \overline{0 \ldots nWidth-1}, \quad
        y = \overline{0 \ldots nHeight-1}
    \f]

    \ru Функция преобразует тип элементов путем отсечения верхних разрядов.
    \en The function converts a type of elements by means of most significant bits truncation.

		\~
		\~
    \param pSrcImg
        \ru Указатель на первый элемент ROI для исходного изображения.
        \en Pointer to the first ROI element for the source image.
		\~
    \param nSrcStride \ru Межстроковое смещение для исходного изображения
                          (измеряется в 32-х разрядных словах).
    		          \en Row-to-row shift for the source image \n
    	                  (measured in 32-bit words).
    \param pDstImg
        \ru Указатель на первый элемент ROI для результирующего изображения.
        \en Pointer to the first ROI element for the result image.
		\~
    \param nDstStride \ru Межстроковое смещение для результирующего изображения
                          (измеряется в 32-х разрядных словах).
    		          \en Row-to-row shift for the result image \n
    	                  (measured in 32-bit words).
    \param nShift
        \ru Определяет число бит на которое предварительно сдвигается исходное
                          изображение.
        \en Defines for how many bits the source image is preliminary shifted.
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
            - Ширина ROI должна быть кратна числу пикселей результирующего изображения
              в 64-х разрядном слове;
            - Межстроковые смещения должны быть кратны двум.
            - Значение параметра nShift должно быть кратно 2.
        \en
            - Pointers to the first ROI element should be aligned
                in memory by the 64-bit word boundary;
            - ROI width should be divisible by the number of pixels of the result image
                in a 64-bit word;
            - Row-to-row shifts should be divisible by two;
            - nShift parameter value should be divisible by two.

    \par
    \xmlonly
        <testperf>
          <param> pSrcImg </param> <values> L G </values>
          <param> nSrcStride </param>  <values> 128 </values>
          <param> nShift </param>  <values> 2 </values>
          <param> pDstImg  </param>  <values> L G </values>
          <param> nDstStride </param>  <values> 64 </values>
          <param> nHeight </param>  <values> 128 </values>
          <param> nWidth </param>  <values> 128 </values>
          <size> nWidth*nHeight </size>
        </testperf>
        <testperf>
          <param> pSrcImg </param> <values> L </values>
          <param> nSrcStride </param>  <values> 128 </values>
          <param> nShift </param>  <values> 2 </values>
          <param> pDstImg  </param>  <values> G </values>
          <param> nDstStride </param>  <values> 64 </values>
          <param> nHeight </param>  <values> 128 </values>
          <param> nWidth </param>  <values> 8 32 128 </values>
          <size> nWidth*nHeight </size>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppiRShiftConvert(nm32s* pSrcImg, int nSrcStride, nm16s* pDstImg,  int nDstStride, int nShift, int nWidth, int nHeight);
    //! \}


//    \ru Функция конвертирует элементы RGB между 8-м разрядным представлением
//        и 10-ти разрядным. Элемент исходного изображения располагается
//        в 32-х битовом слове. Компоненты RGB занимают младшие 3 байта,
//        а старший байт не используется.\n
//        Элемент выходного изображения располагается в 32-х битовом слове.
//        Компоненты RGB занимают 3 младших 10-ти битовых поля,
//        а оставшиеся 2 бита не используются.
//    \en Function converts RGB elements from 8-bits presentation in 10-bits.
//        Source elements are locate in 32-bits word. Components RGB occupy
//        low three bytes. Hi byte is not use.\n
//        Output elements are locate in 32-bits word too. Components RGB
//        occupy three low 10-bits fields, but stayed two bits are not used.
// \~

    /**
    \defgroup nmppiConvert nmppiConvert
    \ingroup iInit
    \brief
        \ru Преобразование типов для элементов изображения.
        \en Conversion of types for image elements.

		\~
    \ru Функция конвертирует элементы RGB между 8-м разрядным представлением
        и 10-ти разрядным.
    \en Function converts RGB elements between 8-bits presentation and 10-bits.

		\~
		\~
    \param pSrcImg
        \ru Указатель на первый элемент исходного изображения.
        \en Pointer to the first element of the source image.
		\~
    \param pDstImg
        \ru Указатель на первый элемент результирующего изображения.
        \en Pointer to the first element of the result image.
		\~
    \param nSize
        \ru Количество элементов в изображении.
        \en Quantity of elements.

		\~
    \return \e void

    \restr
        \ru
            - Указатели на изображения должны быть выровнены
              в памяти на границу 64-х разрядного слова;
        \en
            - Pointers to the images should be aligned in memory
              by the 64-bit word boundary;

    \par
    \xmlonly
        <testperf>
          <param> pSrcImg </param> <values> L G </values>
          <param> pDstImg  </param>  <values> L G </values>
          <param> nSize </param>  <values> 128 </values>
          <size> nSize </size>
        </testperf>
        <testperf>
          <param> pSrcImg </param> <values> L </values>
          <param> pDstImg  </param>  <values> G </values>
          <param> nSize </param>  <values> 8 32 128 </values>
          <size> nSize </size>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppiConvertRGB32_8u10u(RGB32_nm8u* pSrcImg, RGB32_nm10u* pDstImg, int nSize);
void nmppiConvertRGB32_10u8u(RGB32_nm10u* pSrcImg, RGB32_nm8u* pDstImg, int nSize);
    //! \}



// Входная упаковка длинного слова: [ 0RGB0RGB ] ( два пикселя )
// 0.299=4c8b,   0.587=9646,   0.114=1d2f
//--------------------------------------------
//            255
//pDstGray[i]=CLIP(0.299*R+0.587*G+0.114*B);
//            0
//            +127
//
//pDstGray[i]=CLIP(0.299*(R-128)+0.587*(G-128)+0.114*B(-128) +128);
//            -128
// где 0.299=4c8b,   0.587=9646,   0.114=1d2f
//--------------------------------------------
//            255
//pDstGray[i]=CLIP(0.299*R+0.587*G+0.114*B);
//            0
// где 0.299=4c8b,   0.587=9646,   0.114=1d2f

	/**
	\defgroup nmppiRGB32ToGray nmppiRGB32ToGray
	\ingroup iInit
	\brief
		\ru Преобразование пикселей из RGB в яркость
		\en

	\~
	\param pRGB
		\ru Вход, по 4 байта на пиксель. Порядок байтов B, G, R, 0.
		\en
	\param pDstGray
		\ru Результат в виде 32 битных целых чисел, в которых
            полезные данные занимают младшие 24 бита. Для получения
            восьмибитовых пикселей неоходимо вырезать биты 16..23,
            например, с помощью
           nmppsClipRShiftConvert_Add_32s(nm32s* pSrcVec, int nClipFactor,int nShift, nm64u* nAddValue,nm8s* pDstVec, int nSize);
           с параметрами nClipFactor=24,  nShift=16.
		\en
	\param nSize
		\ru Количество пикселей на входе и выходе. nSize=[64,128,192,...]
		\en
	\param pTmpBuf
        \ru Временный массив размером nm32s[nSize] .
        \en Temporary array with size of  nm32s[nSize].

		\~
    \par
    \xmlonly
        <testperf>
          <param> pRGB </param> <values> L G </values>
          <param> pDstGray  </param>  <values> L G </values>
          <param> pTmpBuf </param> <values> L G </values>
          <param> nSize </param>  <values> 128 </values>
          <size> nSize </size>
        </testperf>
        <testperf>
          <param> pRGB </param> <values> L </values>
          <param> pDstGray  </param>  <values> G </values>
          <param> pTmpBuf </param> <values> G </values>
          <param> nSize </param>  <values> 8 32 128 </values>
          <size> nSize </size>
        </testperf>
    \endxmlonly

	*/
   //!  \{
void nmppiRGB32ToGray_8u32u(RGB32_nm8u* pRGB, nm32u* pDstGray, int nSize);
void nmppiRGB32ToGray_8u32s(RGB32_nm8u* pRGB, nm32s* pDstGray, int nSize);
void nmppiRGB32ToGray_8u8s(RGB32_nm8u*  pRGB, nm8s* pDstGray, int nSize, void *pTmpBuf);

void nmppiRGB32ToGray_10s32s(RGB32_nm10s* pRGB, nm32s* pDstGray, int nSize);
void nmppiRGB32ToGray_10s32u(RGB32_nm10s* pRGB, nm32u* pDstGray, int nSize);
void nmppiRGB32ToGray_10s8s(RGB32_nm10s* pRGB, nm8s*  pDstGray, int nSize, void *pTmpBuf);
  //! \}






	/**
	\internal
	\defgroup nmppiGrayToRGB242424242424242424 nmppiGrayToRGB242424242424242424
	\ingroup iInit
	\brief
		\ru преобразование из чернобелого формата в RGB24
		\en Gray to RGB24 conversion
		\~
	\~
	\param pSrcImg
		\ru Входное изображение
		\en Input image
		\~
	\param pDstImg
		\ru Выходное изображение
		\en Output image
		\~
	\param nSize
		\ru Размер изображение в пикселях
		\en Size of image in pixels
		\~
	*/
	//! \{
void nmppiGrayToRGB242424242424242424(nm8u* pSrcImg, RGB24_nm8u* pDstImg, int nSize);
void nmppiRGB24ToGray(RGB24_nm8u* pRGB, nm8u* pDstGray, int nSize);
	//! \}
// #ifdef __cplusplus
// 	};
// #endif
#endif
