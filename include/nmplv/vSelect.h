//------------------------------------------------------------------------
//
//  $Workfile:: vSelect.h  $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/07/13 14:19:56 $
//
//	author: S. Mushkaev
//------------------------------------------------------------------------

#ifndef VSELECT_H
#define VSELECT_H

#include "malloc32.h"
#ifdef __cplusplus
		extern "C" {
#endif

    /**
    \defgroup nmppsMax_ nmppsMax_
    \ingroup vSelect
    \brief
        \ru Поиск значения максимального элемента вектора.
        \en Search of the maximum vec element value.

		\~

	\f[
         nMaxValue  =  \mathop {max}\limits_{i} \left({pSrcVec[i]} \right)
    \f]

    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nSize
        \ru Размер  вектора в элементах.
        \en Vector size in elements.
		\~
    \retval nMaxValue
        \ru значение максимального элемент вектора.
        \en maximum vec element value.
		\~
    \return \e void
    \restr
        \ru Ограничения на параметры приводятся в описании каждой из функций.
        \en Restrictions on parameters are defined in the descriptions of functions.
		\~
    \par
    \xmlonly
        <testperf>
			<param name="pSrcVec"> im0 im1 </param>
			<param name="nMaxValue"> im1 </param>
			<param name="nSize"> 2048 </param>
			<init>
					nmppsSet($pSrcVec, 0, nSize);
					nmppsPut($pSrcVec, nSize-1, 1);
			</init>
        </testperf>
        <testperf>
			<param name="pSrcVec"> im0 </param>
			<param name="nMaxValue"> im1 </param>
			<param name="nSize"> 8 128 1024 2048 </param>
			<init>
					nmppsSet($pSrcVec, 0, nSize);
					nmppsPut($pSrcVec, nSize-1, 1);
			</init>
        </testperf>
    \endxmlonly

    */
    //! \{
/**
 \restr
	\ru Физический размер вектора должен быть кратен блоку из 32-х 64р. слов
	\en Actual size of vec should be divisible by block of 32 64bit words.

		\~
		\ru Максимальный и минимальный элементы массива должны отличатся не более чем на 127. \n
         Примеры допустимых диапазонов входных чисел:\n
     \en The difference between the maximum and minimum elements of the array should not be more than 127. \n
         Here are some examples of admissible ranges for input numbers: \n
     \~  [00h..7Fh]=[   0..+127]
         [FFh..7Eh]=[  -1..+126]
	        [C0h..3Fh]=[-64..+63]
         [80h..00h]=[-128..0	]
*/
void nmppsMax_8s7b(const nm8s7b* pSrcVec, int nSize, int8b* nMaxValue);
/**
\restr
\ru Максимальный и минимальный элементы массива должны отличатся не более чем на 2^15-1. \n
	Примеры допустимых диапазонов входных чисел:\n
\en The difference between the maximum and minimum elements of the array should not be more than 2^15-1. \n
	Here are some examples of admissible ranges for input numbers: \n
    [0000h..7FFFh]=[     0..+32767	]
    [FFFFh..7FFEh]=[    -1..+32766	]
    [C000h..3FFFh]=[-16384..+16383	]
    [8000h..0000h]=[-32768..0		]
*/
void nmppsMax_16s15b(const nm16s15b* pSrcVec, int nSize, int16b* nMaxValue);
/**
\restr
\ru Максимальный и минимальный элементы массива должны отличатся не более чем на 2^31-1. \n
	Примеры допустимых диапазонов входных чисел:\n
\en The difference between the maximum and minimum elements of the array should not be more than 2^31-1. \n
	Here are some examples of admissible ranges for input numbers: \n
\~
    [00000000h..7FFFFFFFh]=[	  0..+2^31-1]
    [FFFFFFFFh..7FFFFFFEh]=[    -1..+2^31-2	]
    [C0000000h..3FFFFFFFh]=[ -2^30..+2^30-1	]
    [80000000h..00000000h]=[ -2^31..0		]
*/
void nmppsMax_32s31b(const nm32s31b* pSrcVec, int nSize, int* nMaxValue);
void nmppsMax_64s63b(const nm64s63b* pSrcVec, int nSize, int64b *nMaxValue);

int nmppsMax_8sm (const nm8s*  srcVec, int size, int8b*  maxValue, nm16s* tmp);
int nmppsMax_16sm(const nm16s* srcVec, int size, int16b* maxValue, nm32s* tmp);
int nmppsMax_32sm(const nm32s* srcVec, int size, int32b* maxValue, nm64s* tmp);


    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsMin nmppsMin
    \ingroup vSelect
    \brief
        \ru Поиск значения минимального элемента вектора.
        \en Search of the minimum vec element value.

		\~

	\f[
         nMinValue  =  \mathop {min}\limits_{i} \left({pSrcVec[i]} \right)
    \f]

    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nSize
        \ru Размер  вектора в элементах.
        \en Vector size in elements.
		\~
    \retval nMinValue
        \ru значение минимального элемент.
        \en minimum element value.
		\~
    \return \e void
    \restr
        \ru Ограничения на параметры приводятся в описании каждой из функций.
        \en Restrictions on parameters are defined in the descriptions of functions.
		\~
    \par
    \xmlonly
        <testperf>
			<param name="pSrcVec"> im0 im1 </param>
			<param name="nMinValue"> im1	</param>
			<param name="nSize"> 2048 </param>
			<init>
					nmppsSet($pSrcVec, 0, nSize);
					nmppsPut($pSrcVec, nSize-1, -1);
			</init>
        </testperf>
        <testperf>
			<param name="pSrcVec"> im0 </param>
			<param name="nMinValue"> im2	</param>
			<param name="nSize"> 8 128 1024 2048 </param>
			<init>
					nmppsSet($pSrcVec, 0, nSize);
					nmppsPut($pSrcVec, nSize-1, -1);
			</init>
        </testperf>
    \endxmlonly

    */
    //! \{
/**
\restr

		\~
    \ru Максимальный и минимальный элементы массива должны отличатся не более чем на 127. \n
        Примеры допустимых диапазонов входных чисел:\n
    \en The difference between the maximum and minimum elements of the array should not be more than 127. \n
        Here are some examples of admissible ranges for input numbers: \n
    \~
        [00h..7Fh]=[   0..+127]
        [FFh..7Eh]=[  -1..+126]
        [C0h..3Fh]=[-64..+63]
        [80h..00h]=[-128..0	]
*/
void nmppsMin_8s7b(const nm8s7b* pSrcVec, int nSize, int8b* nMinValue);
/**
\restr
    \ru Максимальный и минимальный элементы массива должны отличатся не более чем на 2^15-1. \n
        Примеры допустимых диапазонов входных чисел:\n
    \en The difference between the maximum and minimum elements of the array should not be more than 2^15-1. \n
        Here are some examples of admissible ranges for input numbers: \n
    \~  [0000h..7FFFh]=[     0..+32767	]
        [FFFFh..7FFEh]=[    -1..+32766	]
        [C000h..3FFFh]=[-16384..+16383	]
        [8000h..0000h]=[-32768..0		]
*/
void nmppsMin_16s15b(const nm16s15b* pSrcVec, int nSize, int16b* nMinValue);
/**
\restr
    \ru Максимальный и минимальный элементы массива должны отличатся не более чем на 2^31-1. \n
        Примеры допустимых диапазонов входных чисел:\n
    \en The difference between the maximum and minimum elements of the array should not be more than 2^31-1. \n
        Here are some examples of admissible ranges for input numbers: \n
    \~  [00000000h..7FFFFFFFh]=[	  0..+2^31-1]
        [FFFFFFFFh..7FFFFFFEh]=[    -1..+2^31-2	]
        [C0000000h..3FFFFFFFh]=[ -2^30..+2^30-1	]
        [80000000h..00000000h]=[ -2^31..0		]
*/
void nmppsMin_32s31b(const nm32s31b* pSrcVec, int nSize, int* nMinValue);
void nmppsMin_64s63b(const nm64s63b* pSrcVec, int nSize, int64b* nMinValue);


int nmppsMin_8sm (const nm8s*  srcVec, int size, int8b*  minValue, nm16s* tmp);
int nmppsMin_16sm(const nm16s* srcVec, int size, int16b* minValue, nm32s* tmp);
int nmppsMin_32sm(const nm32s* srcVec, int size, int32b* minValue, nm64s* tmp);


    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsMaxIndx_ nmppsMaxIndx_
    \ingroup vSelect
    \brief
        \ru Поиск значения максимального элемента вектора
               и  его положения (положений) в векторе.
        \en Search of the maximum vec element value and its position(s) in the vec

		\~

	\f[
         nMaxValue  =  \mathop {max} \limits_{i} \left(pSrcVec[i] \right)
    \f]

    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nSize
        \ru Размер вектора в элементах. Занимаемый этим вектором объем памяти должен быть кратен 64 длинным словам (nm64s[64,128,...]).
        \en Size of vec in elements. Size of allocated memory in 64-bit words must be divisible by 64 (nm64s[64,128,...])
		\~
    \param pLTmpBuf
        \ru Временный массив на локальной шине  из nSize элементов.
        \en Temporary array on Local bus  of nSize elements.
		\~
	\param pGTmpBuf
        \ru Временный массив на глобальной шине .
        \en Temporary array on Global bus.
		\~
    \param nSearchDir
        \ru Направление поиска максимума. \n
            При nSearchDir = 1, поиск ведется от начала массива.\n
            При nSearchDir = -1, поиск ведется от конца массива.\n
        \en The maximum search direction. \n
    	    When nSearchDir = 1, the search starts from the beginning of the array.\n
            When nSearchDir = -1, the search starts from the end of the array.\n
    \retval nMaxValue
        \ru Значение максимального элемента.
        \en Value of the maximum element
		\~
    \retval nIndex
        \ru Индекс первого найденного максимума среди равных.
        \en Index of the first found maximum among equals.
		\~
    \return \e void
    \restr
        \ru Ограничения на параметры приводятся в описании каждой из функций.
        \en Restrictions on parameters are defined in the descriptions of functions.
		\~
	\restr
		\ru Диапазоны входных элементов могут быть "плавающими"  \n
			Например для данных nm16s15b максимальный и минимальный элементы массива должны отличатся не более чем на 2^15-1.
            Примеры допустимых диапазонов входных чисел для типа nm16s15b :
       \en The range of input data may be floating \n
			For example: if nm16s15b type is used the difference between the maximum and minimum elements of the array should not be more than 2^15-1.
		\~
			Here are some examples of admissible ranges for input numbers: \n
       \~  [0000h..7FFFh]=[     0..+32767	]
           [FFFFh..7FFEh]=[    -1..+32766	]
           [C000h..3FFFh]=[-16384..+16383	]
           [8000h..0000h]=[-32768..0		]
    \par
	\xmlonly
		<testperf>
			<param name="pSrcVec"> im0 im1 </param>
			<param name="pLTmpBuf"> im2 </param>
			<param name="pGTmpBuf"> im3 </param>
			<param name="nMaxValue"> im0 </param>
			<param name="nIndex"> im3 </param>
			<param name="nSearchDir"> 1 -1 </param>
			<param name="nSize"> 64 1024 2048 </param>
			<init>
					nmppsSet($pSrcVec, 0, nSize);
					nmppsPut($pSrcVec, nSize-1, 1);
			</init>
		</testperf>
    \endxmlonly
	*/
    //! \{
void nmppsMaxIndx_8s(nm8s7b  *pSrcVec, int nSize, int* nIndex, int8b *nMaxValue, void *pLTmpBuf,void *pGTmpBuf, int nSearchDir);
void nmppsMaxIndx_16s(nm16s15b *pSrcVec, int nSize, int* nIndex, int16b *nMaxValue, void *pLTmpBuf,void *pGTmpBuf, int nSearchDir);
void nmppsMaxIndx_32s(nm32s31b *pSrcVec, int nSize, int* nIndex, int32b *nMaxValue, void *pLTmpBuf,void *pGTmpBuf, int nSearchDir);
    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsMinIndx_ nmppsMinIndx_
    \ingroup vSelect
    \brief
        \ru Поиск значения минимального элемента вектора
               и  его положения (положений) в векторе.
        \en Search of the minimum vec element value and its position(s) in the vec

		\~

	\f[
         nMinValue  =  \mathop {min} \limits_{i} \left(pSrcVec[i] \right)
    \f]

    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nSize
        \ru Размер вектора в элементах. Занимаемый этим вектором объем памяти должен быть кратен 64 длинным словам (nm64s[64,128,...]).
        \en Size of vec in elements. Size of allocated memory in 64-bit words must be divisible by 64 (nm64s[64,128,...])
		\~
    \param pLTmpBuf
        \ru Временный массив на локальной шине .
        \en Temporary array on Local bus.
		\~
	\param pGTmpBuf
        \ru Временный массив на глобальной шине  из nSize элементов.
        \en Temporary array on Global bus of  nSize elements.
		\~
    \param nSearchDir
        \ru Направление поиска минимума. \n
            При nSearchDir = 1, поиск ведется от начала массива.\n
            При nSearchDir = -1, поиск ведется от конца массива.\n
        \en The minimum search direction. \n
    	    When nSearchDir = 1, the search starts from the beginning of the array.\n
            When nSearchDir = -1, the search starts from the end of the array.\n
    \retval nMinValue
        \ru Значение минимального элемента.
        \en Value of the minimum element
		\~
    \retval nIndex
        \ru Индекс первого найденного минимума среди равных.
        \en Index of the first found minimum among equals.
		\~
    \return \e void
    \restr
        \ru Ограничения на параметры приводятся в описании каждой из функций.
        \en Restrictions on parameters are defined in the descriptions of functions.
		\~
	\restr
		\ru Диапазоны входных элементов могут быть "плавающими"  \n
			Например для данных nm16s15b максимальный и минимальный элементы массива должны отличатся не более чем на 2^15-1.
            Примеры допустимых диапазонов входных чисел для типа nm16s15b :
       \en The range of input data may be floating \n
			For example: if nm16s15b type is used the difference between the maximum and minimum elements of the array should not be more than 2^15-1.
		\~
			Here are some examples of admissible ranges for input numbers: \n
       \~  [0000h..7FFFh]=[     0..+32767	]
           [FFFFh..7FFEh]=[    -1..+32766	]
           [C000h..3FFFh]=[-16384..+16383	]
           [8000h..0000h]=[-32768..0		]
    \par
	\xmlonly
		<testperf>
			<param name="pSrcVec"> im0 im1 </param>
			<param name="pLTmpBuf"> im1 </param>
			<param name="pGTmpBuf"> im2 </param>
			<param name="nMinValue"> 5 </param>
			<param name="nIndex"> 5 </param>
			<param name="nSearchDir"> 1 -1 </param>
			<param name="nSize"> 64 1024 2048 </param>
			<init>
					nmppsSet($pSrcVec,0,nSize);
					nmppsPut($pSrcVec,nSize-1,-1);
			</init>
		</testperf>
	\endxmlonly
	*/
    //! \{
void nmppsMinIndx_8s(nm8s7b   *pSrcVec, int nSize, int* nIndex, int8b  *nMinValue, void *pLTmpBuf,void *pGTmpBuf, int nSearchDir);
void nmppsMinIndx_16s(nm16s15b *pSrcVec, int nSize, int* nIndex, int16b *nMinValue, void *pLTmpBuf,void *pGTmpBuf, int nSearchDir);
void nmppsMinIndx_32s(nm32s31b *pSrcVec, int nSize, int* nIndex, int32b *nMinValue, void *pLTmpBuf,void *pGTmpBuf, int nSearchDir);
    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsMinIndxVN_ nmppsMinIndxVN_
    \ingroup vSelect
	\brief
        \ru Поиск значения минимального элемента вектора  длины N и его положения в векторе.
        \en Search of the minimum vec element value and its position in the vec  with size of N elements

		\~
	\param pSrcVec
	    \ru Массив из N элементов, где N определяется числом в имени функции.
        \en array of N numbers, where N is suffix in function name
		\~
	\param nStride
	    \ru шаг между элементами в 32р. словах
        \en jump between numbers in nm32s words
		\~
	\retval
		\ru Индекс первого найденного минимума.
		\en Index of the first found minimum.
		\~
	\return
	    \ru Значение минимального элемента.
        \en Value of the minimum element

		\~
	\par
	\xmlonly
		<testperf>
			 <param name="pSrcVec"> im0 im1 </param>
			 <param name="nStride"> 2 </param>
			 <param name="nPos"> im2 </param>
			 <size> 1 </size>
		</testperf>
	\endxmlonly
	\restr
		\ru Вычисления проиводятся на скалярном ядре, поэтому указатель на данные pSrcVec может ссылаться на нечетный адрес.
		\en Calculation is performed on scalar RISC core, therefore pointer pSrcVec may refer to odd address.
		\~
	*/

	//! \{
int nmppsMinIndxV9_32s(int* pSrcVec,int nStride,int* nPos);
int nmppsMinIndxV16_32s(int* pSrcVec,int nStride,int* nPos);
int nmppsMinIndxV25_32s(int* pSrcVec,int nStride,int* nPos);
int nmppsMinIndxV256_32s(int* pSrcVec,int nStride,int* nPos);
int nmppsMinIndxV1024_32s(int* pSrcVec,int nStride,int* nPos);
	//! \}

//*****************************************************************************

    /**
    \defgroup nmppsFirstZeroIndx nmppsFirstZeroIndx
    \ingroup vSelect
	\brief
        \ru Поиск позиции первого нулевого элемента в векторе .
        \en Search of first zero element position in the vec

		\~
	\param pSrcVec
	    \ru Входной массив.
        \en Input array
		\~
	\param nIndex
	    \ru Размер массива.
        \en Array size
		\~
	\return
	    \ru Позиция нулевого элемента или -1 в случае если нулевой элемент не найден
        \en Position of zero element or -1 if zero element was not found.
		\~
	\restr
		\ru Вычисления проиводятся на скалярном ядре, поэтому указатель на данные pSrcVec может ссылаться на нечетный адрес.
			Поиск производится до первого нулевого элемента.
		\en Calculation is performed on scalar RISC core, therefore pointer pSrcVec may refer to odd address.
			Search is performed until first zero element is found.

		\~
	\par
	\xmlonly
		<testperf>
			 <param name="pSrcVec"> im0 im1 </param>
			 <param name="nSize"> 8 64 512 </param>
			 <init>  nmppsSet_32s(pSrcVec, 1, nSize); </init>
		</testperf>
	\endxmlonly
	*/
	//! \{
int nmppsFirstZeroIndx_32s(int* pSrcVec, int nSize);
	//! \}
//*****************************************************************************

    /**
    \defgroup nmppsFirstNonZeroIndx nmppsFirstNonZeroIndx
    \ingroup vSelect
	\brief
        \ru Поиск позиции первого ненулевого элемента в векторе .
        \en Search of first nonzero element position in the vec

		\~
	\param pSrcVec
	    \ru Входной массив.
        \en Input array
		\~
	\param nIndex
	    \ru Размер массива.
        \en Array size
		\~
	\return
	    \ru Позиция ненулевого элемента или -1 в случае если ненулевой элемент не найден
        \en Position of nonzero element or -1 if zero element was not found.
		\~
	\restr
		\ru Вычисления проиводятся на скалярном ядре, поэтому указатель на данные pSrcVec может ссылаться на нечетный адрес.
			Поиск производится до первого ненулевого элемента.
		\en Calculation is performed on scalar RISC core, therefore pointer pSrcVec may refer to odd address.
			Search is performed until first nonzero element is found.

		\~
	\par
	\xmlonly
		<testperf>
			 <param name="pSrcVec"> im0 im1 </param>
			 <param name="nSize"> 8 64 512 </param>
			 <init> nmppsSet_32s(pSrcVec, 0, nSize); </init>
		</testperf>
	\endxmlonly
	*/
	//! \{
int nmppsFirstNonZeroIndx_32s(int* pSrcVec, int nSize);
	//! \}

//*****************************************************************************

    /**
    \defgroup nmppsLastZeroIndx nmppsLastZeroIndx
    \ingroup vSelect
	\brief
        \ru Поиск позиции последнего нулевого элемента в векторе .
        \en Search of last zero element position in the vec

		\~
	\param pSrcVec
	    \ru Входной массив.
        \en Input array
		\~
	\param nIndex
	    \ru Размер массива.
        \en Array size
		\~
	\return
	    \ru Позиция нулевого элемента или -1 в случае если нулевой элемент не найден
        \en Position of zero element or -1 if zero element was not found.

		\~
	\restr
		\ru Вычисления проиводятся на скалярном ядре, поэтому указатель на данные pSrcVec может ссылаться на нечетный адрес.
			Поиск производится с конца до первого нулевого элемента.
		\en Calculation is performed on scalar RISC core, therefore pointer pSrcVec may refer to odd address.
			Search is performed from end to start until first zero element is found.
		\~
	\par
	\xmlonly
		<testperf>
			 <param name="pSrcVec"> im0 im1 </param>
			 <param name="nSize"> 8 64 512 </param>
			 <init> nmppsSet_32s(pSrcVec, 1, nSize); </init>
		</testperf>
	\endxmlonly
	*/
	//! \{
int nmppsLastZeroIndx_32s(int* pSrcVec, int nSize);
	//! \}

//*****************************************************************************

    /**
    \defgroup nmppsLastNonZeroIndx nmppsLastNonZeroIndx
    \ingroup vSelect
	\brief
        \ru Поиск позиции последнего ненулевого элемента в векторе .
        \en Search of last nonzero element position in the vec

		\~
	\param pSrcVec
	    \ru Входной массив.
        \en Input array
		\~
	\param nIndex
	    \ru Размер массива.
        \en Array size
		\~
	\return
	    \ru Позиция нулевого элемента или -1 в случае если нулевой элемент не найден
        \en Position of zero element or -1 if zero element was not found.

		\~
	\restr
		\ru Вычисления проиводятся на скалярном ядре, поэтому указатель на данные pSrcVec может ссылаться на нечетный адрес.
			Поиск производится с конца до первого ненулевого элемента.
		\en Calculation is performed on scalar RISC core, therefore pointer pSrcVec may refer to odd address.
			Search is performed from end to start until first nonzero element is found.
		\~
	\par
	\xmlonly
		<testperf>
			 <param name="pSrcVec"> im0 im1  </param>
			 <param name="nSize"> 8 64 512 </param>
			 <init> nmppsSet_32s(pSrcVec, 0, nSize); </init>

		</testperf>
	\endxmlonly

	*/
	//! \{
int nmppsLastNonZeroIndx_32s(int* pSrcVec, int nSize);
	//! \}


//*****************************************************************************
    /**
    \defgroup nmppsMinEvery_ nmppsMinEvery_
    \ingroup vSelect
    \brief
        \ru Поэлементный минимум из двух векторов.
        \en Generation of the vec of two vectors elementwise minima.

		\~

	\f[ pDstMinVec[i] = \min (pSrcVec1[i], pSrcVec2[i]) \f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

    \param pSrcVec1
        \ru Первый входной вектор.
        \en The first input vec.
		\~
    \param pSrcVec2
        \ru Второй Входной вектор.
        \en The second input vec.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vectors size in elements.
		\~
    \retval pDstMinVec
        \ru Массив поэлементных минимумов для входных массивов.
        \en The array of elementwise minima for source arrays.
		\~
    \return \e void

    \restr
        \ru Сравниваемые пары чисел двух массивов должны отличатся не более чем на \f$ 2^{15}-1 \f$. \n
                  Примеры допустимых диапазонов сравниваемых пар чисел:\n
        \en The difference between the comparable pairs of numbers in two arrays
		\~
               should not be more than \f$ 2^{15}-1 \f$. \n
               Here are some examples of admissible ranges for comparable pairs of numbers: \n
        \~     [0000h..7FFFh]=[     0..+32767	]     \n
               [FFFFh..7FFEh]=[    -1..+32766	]     \n
               [C000h..3FFFh]=[-16384..+16383	]     \n
               [8000h..0000h]=[-32768..0		]

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec1"> im0 im1 </param>
             <param name="pSrcVec2"> im0 im1 </param>
             <param name="pDstMinVec"> im2 im3 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec1"> im0 </param>
             <param name="pSrcVec2"> im1 </param>
             <param name="pDstMinVec"> im2 </param>
             <param name="nSize"> 8 128 1024 2048 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsMinEvery_8s(nm8s7b*   pSrcVec1, nm8s7b*   pSrcVec2, nm8s7b*   pDstMinVec, int nSize);
void nmppsMinEvery_16s(nm16s15b* pSrcVec1, nm16s15b* pSrcVec2, nm16s15b* pDstMinVec, int nSize);
void nmppsMinEvery_32s(nm32s31b* pSrcVec1, nm32s31b* pSrcVec2, nm32s31b* pDstMinVec, int nSize);
void nmppsMinEvery_64s(nm64s63b* pSrcVec1, nm64s63b* pSrcVec2, nm64s63b* pDstMinVec, int nSize);

    //! \}
//*****************************************************************************
// numVecs > 2
void nmppsMinNV_8s(nm8s7b**   pSrcVecs, int numVecs, nm8s7b*   pDstMinVec, int nSize);
void nmppsMinNV_16s(nm16s15b** pSrcVecs, int numVecs, nm16s15b* pDstMinVec, int nSize);
void nmppsMinNV_32s(nm32s31b** pSrcVecs, int numVecs, nm32s31b* pDstMinVec, int nSize);
void nmppsMinNV_64s(nm64s63b** pSrcVecs, int numVecs, nm64s63b* pDstMinVec, int nSize);

//*****************************************************************************

    /**
    \defgroup nmppsMaxEvery_ nmppsMaxEvery_
    \ingroup vSelect
    \brief
        \ru Поэлементный максимум из двух векторов.
        \en Generation of the vec of two vectors elementwise minimum.

		\~

	\f[ pDstMaxVec[i] = \max (pSrcVec1[i], pSrcVec2[i]) \f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

    \param pSrcVec1
        \ru Первый входной вектор.
        \en The first input vec.
		\~
    \param pSrcVec2
        \ru Второй Входной вектор.
        \en The second input vec.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vectors size in elements.
		\~
    \retval pDstMaxVec
        \ru Массив поэлементных минимумов для входных массивов.
        \en The array of elementwise Maxima for source arrays.
		\~
    \return \e void

    \restr
        \ru Сравниваемые пары чисел двух массивов должны отличатся не более чем на \f$ 2^{15}-1 \f$. \n
                  Примеры допустимых диапазонов сравниваемых пар чисел:\n
        \en The difference between the comparable pairs of numbers in two arrays
		\~
               should not be more than \f$ 2^{15}-1 \f$. \n
               Here are some examples of admissible ranges for comparable pairs of numbers: \n
        \~     [0000h..7FFFh]=[     0..+32767	]     \n
               [FFFFh..7FFEh]=[    -1..+32766	]     \n
               [C000h..3FFFh]=[-16384..+16383	]     \n
               [8000h..0000h]=[-32768..0		]

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec1"> im0 im1 </param>
             <param name="pSrcVec2"> im0 im1 </param>
             <param name="pDstMaxVec"> im2 im3 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec1"> im0 </param>
             <param name="pSrcVec2"> im1 </param>
             <param name="pDstMaxVec"> im2 </param>
             <param name="nSize"> 8 128 1024 2048 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsMaxEvery_8s(nm8s7b*   pSrcVec1, nm8s7b* pSrcVec2,   nm8s7b*  pDstMaxVec,  int nSize);
void nmppsMaxEvery_16s(nm16s15b* pSrcVec1, nm16s15b* pSrcVec2, nm16s15b* pDstMaxVec, int nSize);
void nmppsMaxEvery_32s(nm32s31b* pSrcVec1, nm32s31b* pSrcVec2, nm32s31b* pDstMaxVec, int nSize);
void nmppsMaxEvery_64s(nm64s63b* pSrcVec1, nm64s63b* pSrcVec2, nm64s63b* pDstMaxVec, int nSize);

    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsMinCmpLtV_ nmppsMinCmpLtV_
    \ingroup vSelect
    \brief
        \ru Поэлементный минимум из двух векторов.
        \en Generation of the vec of two vectors elementwise minima.

		\~

	\f[ pDstMin[i] = \min (pSrcVec1[i], pSrcVec2[i]) \f]

	\f[
        pDstSignMask[i] = \left\{
            \begin{array}{ll}
                11 \ldots 1b,  & pSrcVec1[i] < pSrcVec2[i] \\
                00 \ldots 0b,  & pSrcVec1[i] <= pSrcVec2[i] \\
            \end{array}
        \right.
    \f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

    \param pSrcVec1
        \ru Первый входной вектор.
        \en The first input vec.
		\~
    \param pSrcVec2
        \ru Второй Входной вектор.
        \en The second input vec.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vectors size in elements.
		\~
    \retval pDstMin
        \ru Массив поэлементных минимумов для входных массивов.
        \en The array of elementwise minima for source arrays.
		\~
    \retval pDstSignMask
        \ru Массив знаков поэлементных разностей
                             первого и второго векторов.
        \en The array of signed elementwise differences of the first and the second vectors.
		\~
    \return \e void

    \restr
        \ru Сравниваемые пары чисел двух массивов должны отличатся не более чем на \f$ 2^{15}-1 \f$. \n
                  Примеры допустимых диапазонов сравниваемых пар чисел:\n
        \en The difference between the comparable pairs of numbers in two arrays
		\~
               should not be more than \f$ 2^{15}-1 \f$. \n
               Here are some examples of admissible ranges for comparable pairs of numbers: \n
        \~     [0000h..7FFFh]=[     0..+32767	]     \n
               [FFFFh..7FFEh]=[    -1..+32766	]     \n
               [C000h..3FFFh]=[-16384..+16383	]     \n
               [8000h..0000h]=[-32768..0		]

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec1"> im0 im1 </param>
             <param name="pSrcVec2"> im0 im1 </param>
             <param name="pDstMin"> im2 im3 </param>
             <param name="pDstSignMask"> im0 im1 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec1"> im0 </param>
             <param name="pSrcVec2"> im1 </param>
             <param name="pDstMin"> im2 </param>
             <param name="pDstSignMask"> im3 </param>
             <param name="nSize"> 8 128 1024 4096 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsMinCmpLtV_16s(nm16s15b* pSrcVec1, nm16s15b* pSrcVec2, nm16s15b* pDstMin, nm16s15b* pDstSignMask, int nSize);
    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsCmpLt0 nmppsCmpLt0
    \ingroup vSelect
    \brief
        \ru Сравнивает элементы массива на меньше нуля.
        \en Compares the array elements less zero.

		\~

	\f[
     pDstVec(i)  =  \{ \begin{array}{lcl}
        11 \ldots 1b,   &  if &  pSrcVec(i) < 0  \\
        00 \ldots 0b,   &  if &  pSrcVec(i) \ge 0  \\
     \end{array}
    \f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

    \ru Если элемент входного вектора меньше 0, во все биты
        соответствующего элемента выходного вектора записывается 1.
    \en If an element of the input vec is less than zero then
        1 is beeing written to all bits of output vec element.

		\~
		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vectors size in elements.

		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en The result vec.

		\~
    \return \e void


    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nSize"> 8 128 1024 2048 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsCmpLt0_8s (const nm8s* pSrcVec,  nm8s* pDstVec,  int nSize);
void nmppsCmpLt0_16s(const nm16s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsCmpLt0_32s(const nm32s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsCmpLt0_64s(const nm64s* pSrcVec, nm64s* pDstVec, int nSize);
    //! \}

	/**
	\defgroup snmppsCmpLteC nmppsCmpLteC
	\ingroup vSelect_f
	\brief Функция сравнения элементов массива с константой (меньше или равно)

	\param [in] pSrcVec входной массив (элемент массива представляет собой структура v2nm32f, состоящая из двух чисел float)
	\param [in] C константа (два числа float)
	\retval [out] evenFlags маска полученная после сравнения первого поля из структуры v2nm32f
	\retval [out] oddFlags маска полученная после сравнения второго поля из структуры v2nm32f
	\param [in] step шаг,  с которым будут браться элементы из pSrcVec
	\param [in] nSize размер массива (в v2nm32f)
	\details В структуре v2nm32f два поля. Первое - v0. Второе - v1.
 *
 */
//! \{
void nmppsCmpLteC_v2nm32f(const v2nm32f* pSrcVec, const v2nm32f* C, nm1* evenFlags, nm1* oddFlags, int step, int nSize);
//! \}

	/**
	\defgroup snmppsCmpLtC nmppsCmpLtC
	\ingroup vSelect_f
	\brief Функция сравнения элементов массива с константой (меньше или равно)

	\param [in] pSrcVec входной массив (элемент массива представляет собой структура v2nm32f, состоящая из двух чисел float)
	\param [in] C константа (два числа float)
	\retval [out] evenFlags маска полученная после сравнения первого поля из структуры v2nm32f
	\retval [out] oddFlags маска полученная после сравнения второго поля из структуры v2nm32f
	\param [in] step шаг,  с которым будут браться элементы из pSrcVec
	\param [in] nSize размер массива (в v2nm32f)
	\details В структуре v2nm32f два поля. Первое - v0. Второе - v1.
 *
 */
//! \{
void nmppsCmpLtC_v2nm32f(const v2nm32f* pSrcVec, const v2nm32f* C, nm1* evenFlags, nm1* oddFlags, int step, int nSize);
//! \}

//*****************************************************************************

    /**
    \defgroup nmppsCmpEq0 nmppsCmpEq0
    \ingroup vSelect
    \brief
        \ru Сравнивает элементы массива на признак равенства нулю.
        \en Compare vec elements to zero equlity.

		\~

	\f[
        pDstVec(i)  =  \{ \begin{array}{lcl}
            1,    &  if &  pSrcVec(i) = 0  \\
            0,    &  if &  pSrcVec(i) \neq 0\\
        \end{array}, if~ nTrueFlag=1
    \f]

	\f[
        pDstVec(i)  =  \{ \begin{array}{lcl}
            0,    &  if &  pSrcVec(i) = 0  \\
            1,    &  if &  pSrcVec(i) \neq 0\\
        \end{array}, if~ nTrueFlag=0
    \f]


	\f[ i = \overline{0 \ldots nSize-1} \f]


		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nSize     \ru Размер векторов в элементах.
                     \ru Vector size in elements.
    \param nTrueFlag \ru Младший бит nTrueFlag определяет значение выходного бита при выполнении условия.
                     \en Lowest  bit of nTrueFlag is set in result bit if condition is true.

		\~
    \retval pDstVec
        \ru Результирующий бинарный вектор.
        \en Destination binary vec.

		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nTrueFlag"> -1 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nTrueFlag"> 0 -1 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nTrueFlag"> -1 </param>
             <param name="nSize"> 8 128 1024 4096 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
/**
	\note nSize =[1,2,3,4...]
*/
void nmppsCmpEq0_8u7b(nm8u7b* pSrcVec, nm1* pDstVec, int nSize, int nTrueFlag);
/**
	\note nSize =[1,2,3,4...]
*/
void nmppsCmpEq0_16u15b(nm16u15b* pSrcVec, nm1* pDstVec, int nSize, int nTrueFlag);
/**
	\note nSize =[1,2,3,4...]
*/
void nmppsCmpEq0_32u31b(nm32u31b* pSrcVec, nm1* pDstVec, int nSize, int nTrueFlag);

//void nmppsCmpNe0_8s (const nm8s*  pSrcVec, nm8s* pDstVec,  int nSize);
//void nmppsCmpNe0_16s(const nm16s* pSrcVec, nm16s* pDstVec, int nSize);
//void nmppsCmpNe0_32s(const nm32s* pSrcVec, nm32s* pDstVec, int nSize);
//void nmppsCmpNe0_64s(const nm64s* pSrcVec, nm64s* pDstVec, int nSize);

    //! \}

    /**
    \defgroup nmppsCmpMinMaxV_ nmppsCmpMinMaxV_
    \ingroup vSelect

    \brief
        \ru Поэлементное сравнение двух векторов.
        \en Elementwise comparision of two vectors.

		\~

	\f[ pDstMin[i] = \min (pSrcVec1[i], pSrcVec2[i]) \f]

	\f[ pDstMax[i] = \max (pSrcVec1[i], pSrcVec2[i]) \f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

    \param pSrcVec1
        \ru Первый входной вектор.
        \en The first input vec.
		\~
    \param pSrcVec2
        \ru Второй Входной вектор.
        \en The second input vec.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vectors size in elements.
		\~
    \retval pDstMin
        \ru Массив поэлементных минимумов для входных массивов.
        \en The array of elementwise minimums for source arrays.
		\~
    \retval pDstMax
        \ru Массив поэлементных максимумов для входных массивов.
        \en The array of elementwise maximums for source arrays.
		\~
    \return \e void

    \restr
        \ru Сравниваемые пары чисел двух массивов должны отличатся не более чем на \f$ 2^{15}-1 \f$. \n
                  Примеры допустимых диапазонов сравниваемых пар чисел:\n
        \en The difference between the comparable pairs of numbers in two arrays
		\~
               should not be more than \f$ 2^{15}-1 \f$. \n
               Here are some examples of admissible ranges for comparable pairs of numbers: \n
        \~     [0000h..7FFFh]=[     0..+32767	]     \n
               [FFFFh..7FFEh]=[    -1..+32766	]     \n
               [C000h..3FFFh]=[-16384..+16383	]     \n
               [8000h..0000h]=[-32768..0		]

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec1"> im0 im1 </param>
             <param name="pSrcVec2"> im0 im1 </param>
             <param name="pDstMin"> im2 im3 </param>
             <param name="pDstMax"> im2 im3 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
    \endxmlonly


		*/
    //! \{
void nmppsCmpMinMaxV_8s(nm8s*  pSrcVec1, nm8s* pSrcVec2,  nm8s*  pDstMin,  nm8s*  pDstMax, int nSize);
void nmppsCmpMinMaxV_16s(nm16s*  pSrcVec1, nm16s* pSrcVec2,  nm16s*  pDstMin,  nm16s*  pDstMax, int nSize);
void nmppsCmpMinMaxV_32s(nm32s*  pSrcVec1, nm32s* pSrcVec2,  nm32s*  pDstMin,  nm32s*  pDstMax, int nSize);
    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsClipPowC_ nmppsClipPowC_
    \ingroup vSelect
    \brief
        \ru Функция насыщения.
        \en Saturation function.

		\~

	\f[
        pDstVec[i]  =  \left \{ \begin{array}{lcl}
            -2^{nClipFactor},  & if & pSrcVec[i] < -2^{nClipFactor}  \\
            pSrcVec[i],        & if & -2^{nClipFactor} \le pSrcVec[i] \le 2^{nClipFactor}-1  \\
            2^{nClipFactor}-1, & if & pSrcVec[i] > 2^{nClipFactor}-1 \\
        \end{array} \right.
    \f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nClipFactor
        \ru Показатель степени, определяющий верхний и нижний пороги насыщения. nClipFactor>0
        \en Index of the degree defining the upper and the lower saturation thresholds.
		\~
    \param nSize
        \ru Размер вектора в элементах.
        \en Vector size in elements.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en The result vec.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nClipFactor"> 2 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nClipFactor"> 2 3 5 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nClipFactor"> 2 </param>
             <param name="nSize"> 8 128 1024 2048 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsClipPowC_8s(nm8s*  pSrcVec, int nClipFactor, nm8s*  pDstVec, int nSize);
void nmppsClipPowC_16s(nm16s* pSrcVec, int nClipFactor, nm16s* pDstVec, int nSize);
void nmppsClipPowC_32s(nm32s* pSrcVec, int nClipFactor, nm32s* pDstVec, int nSize);
void nmppsClipPowC_64s(nm64s* pSrcVec, int nClipFactor, nm64s* pDstVec, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsClipCC_ nmppsClipCC_
    \ingroup vSelect
    \brief
        \ru Функция насыщения с произвольными порогами.
        \en Saturation function with arbitrary thresholds.

		\~

	\f[
        pDstVec[i]  =  \left \{ \begin{array}{lcl}
            nPosThresh,   & if & pSrcVec[i] > nPosThresh \\
            pSrcVec[i],   & if & nNegThresh \le pSrcVec[i] \le nPosThresh  \\
            nNegThresh,   & if & pSrcVec[i] < nNegThresh  \\
        \end{array} \right.
    \f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nNegThresh
        \ru Нижний порог насыщения.
        \en The lower saturation threshold.
		\~
    \param nPosThresh
        \ru Верхний порог насыщения.
        \en The upper saturation threshold.
		\~
    \param nSize
        \ru Размер вектора в элементах.
        \en Vector size in elements.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en The result vec.
		\~
    \return \e void

    \restr
        \ru
            - Диапазон изменения для \f$ nPosThresh \subset [0 \ldots 2^{30}-1] \f$.
            - Диапазон изменения для \f$ nNegThresh \subset [-2^{30} \ldots 0] \f$. \n
        \en
            - Range of changing for \f$ nPosThresh \subset [0 \ldots 2^{30}-1] \f$.
            - Range of changing for \f$ nNegThresh \subset [-2^{30} \ldots 0] \f$. \n

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nNegThresh"> -127 </param>
             <param name="nPosThresh"> 127 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nNegThresh"> -255 -127 </param>
             <param name="nPosThresh"> 127 255 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nNegThresh"> -127 </param>
             <param name="nPosThresh"> 127 </param>
             <param name="nSize"> 8 128 1024 2048 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsClipCC_32s(nm32s30b* pSrcVec, int30b nNegThresh, int30b nPosThresh, nm32s30b* pDstVec, int nSize);
    //! \}
	
	/**
    \defgroup nmppsThreshold_Lt_Gt_f nmppsThreshold_Lt_Gt_f
    \ingroup vSelect
    \brief
        \ru Пороговая функция с нижним и верхним порогами
        \en Threshold function with loaw and high thresholds.

		\~

	\f[
        pDstVec[i]  =  \left \{ \begin{array}{lcl}
            max,   & if & pSrcVec[i] > max \\
            pSrcVec[i],   & if & min \le pSrcVec[i] \le max  \\
            min,   & if & pSrcVec[i] < min  \\
        \end{array} \right.
    \f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
	\retval pDstVec
        \ru Результирующий вектор.
        \en The result vec.
		\~
    \param min
        \ru Нижний порог насыщения.
        \en The lower saturation threshold.
		\~
    \param max
        \ru Верхний порог насыщения.
        \en The upper saturation threshold.
		\~
    \param nSize
        \ru Размер вектора в элементах.
        \en Vector size in elements.
		\~
    \return \e void


    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="min"> -127 </param>
             <param name="max"> 127 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="min"> -255 -127 </param>
             <param name="max"> 127 255 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="min"> -127 </param>
             <param name="max"> 127 </param>
             <param name="nSize"> 8 128 1024 2048 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsThreshold_Lt_Gt_32f(nm32f* pSrcVec, nm32f* pDstVec, float min, float max,  int nSize);
	//! \}

//*****************************************************************************

    /**
    \defgroup nmppsClipRShiftConvert_AddC_ nmppsClipRShiftConvert_AddC_
    \ingroup vSelect
    \brief
        \ru Сокращение разрядности данных c предварительной их обработкой.
        \en Data word-length reduction with their preprocessing.

		\~

	\f[
	    pDstVec[i] = Convert(Clip(pSrcVec[i],nClipFactor) >> nShift) + nAddValue
	\f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

	  \ru Сокращение разрядности данных выполняется после предварительной обработки и осуществляется
	    путем отбрасывания старших битов.
	  \en Data word-length is reduced after preprocessing and is made by means of the most significant bits truncation.

		\~
		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nClipFactor
        \ru Показатель степени, определяющий верхний и нижний пороги насыщения. =[1,2,3...15]
        \en Index of the degree defining the upper and the lower saturation thresholds. =[1,2,3...15]
		\~
    \param nShift
        \ru Параметр определяет на сколько позиций =[2,4,6...14] нужно
                           сдвинуть биты элементов вектора;
        \en This parameter defines for how many positions =[2,4,6...14] vec elements should be shifted
		\~
    \param nAddValue
        \ru Добавляемая константа.
        \en Additive constant.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vector size in elements.

		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en The result vec.

		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nClipFactor"> 4 </param>
             <param name="nShift"> 2 </param>
             <param name="nAddValue"> 127 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nClipFactor"> 1 4 15 </param>
             <param name="nShift"> 2 </param>
             <param name="nAddValue"> 127 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nClipFactor"> 4 </param>
             <param name="nShift"> 2 4 6 </param>
             <param name="nAddValue"> 127 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nClipFactor"> 4 </param>
             <param name="nShift"> 2 </param>
             <param name="nAddValue"> 0 64 127 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nClipFactor"> 4 </param>
             <param name="nShift"> 2 </param>
             <param name="nAddValue"> 127 </param>
             <param name="nSize"> 8 128 1024 4096 </param>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsClipRShiftConvertAddC_16s8s(nm16s* pSrcVec, int nClipFactor,int nShift, int8b nAddValue,nm8s* pDstVec, int nSize);
void nmppsClipRShiftConvertAddC_32s8s(nm32s* pSrcVec, int nClipFactor,int nShift, int8b nAddValue,nm8s* pDstVec, int nSize);
    //! \}

//extern "C" nm64u VEC_TBL_Diagonal_01h_G[8];
//extern "C" nm64u VEC_TBL_Diagonal_01h_L[8];
/**
\defgroup nmppsClipConvert_AddC_ nmppsClipConvert_AddC_
    \ingroup vSelect
    \brief
        \ru Сокращение разрядности данных c предварительной их обработкой.
        \en Data word-length reduction with their preprocessing.

		\~

	\f[
	    pDstVec[i] = Convert(Clip(pSrcVec[i],nClipFactor)) + nAddValue
	\f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

	  \ru Сокращение разрядности данных выполняется после предварительной обработки и осуществляется
	    путем отбрасывания старших битов.
	  \en Data word-length is reduced after preprocessing and is made by means of the most significant bits truncation.

		\~
		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nClipFactor
        \ru Показатель степени, определяющий верхний и нижний пороги насыщения. =[1,2,3...15]
        \en Index of the degree defining the upper and the lower saturation thresholds. =[1,2,3...15]
		\~
    \param nAddValue
        \ru Добавляемая константа.
        \en Additive constant.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vector size in elements.
	\param weights
        \ru указатель на матрицу коэфициентов для векторного умножителя. Для ускорения.
        \en Vector size in elements.

		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en The result vec.

		\~
    \return \e void

    \par
    */
    //! \{
//void nmppsClipConvertAddC_16s8s(nm16s* pSrcVec, int nClipFactor, int8b nAddValue,nm8s* pDstVec, int nSize, nm64u* weights); //=VEC_TBL_Diagonal_01h_G
typedef nm64u NmppsWeightState;
void nmppsClipConvertAddCInitAlloc_16s8s(NmppsWeightState** ppState);
void nmppsClipConvertAddC_16s8s(nm16s* pSrcVec, int nClipFactor, int8b nAddValue,nm8s* pDstVec, int nSize, NmppsWeightState* pState); //=VEC_TBL_Diagonal_01h_G
void nmppsClipConvertAddCFree(NmppsWeightState* pState);
    //! \}


//*****************************************************************************
  /**
  \internal
  \defgroup nmppsClipRShiftConvert_AddC_Ext_ nmppsClipRShiftConvert_AddC_Ext_
  \ingroup vSelect

	\brief
	  \ru Сокращение разрядности данных c предварительной их обработкой.
	  \en Data word-length reduction with their preprocessing.

		\~

	\f[
		pDstVec[i][j] = DstType(Clip(pSrcVec[i][j],pClipFactor[j]) >> pShift[j]) + pAddValue[j]
	\f]

	\f[ i = \overline{0 \ldots nSize-1} \f]

	\f[ j = \overline{0 \ldots 7} \f]

	\ru Сокращение разрядности данных выполняется после предварительной обработки и осуществляется
		путем отбрасывания старших битов.
	\en Data word-length is reduced after preprocessing and is made by means of the most significant
	bits truncation.

		\~
	\~
	\param pSrcVec
		\ru Входной вектор.
		\en Input vec.

		\~
	\param pnClipFactor
		\ru Массив из 8 показателей степени, определяющие верхний и нижний пороги насыщения
							как -2^pnClipFactor[j] and 2^pnClipFactor[j]-1. =[1,2,3...15]
		\en Array of 8 factors, wich defining the lower and  the upper saturation thresholds
							as -2^pnClipFactor[j] and 2^pnClipFactor[j]-1.  =[1,2,3...15]

		\~
	\param pnShift
	  \ru Массив из 8 параметров,  определяющих  на сколько позиций =[2,4,6...14] нужно
							сдвинуть биты элементов вектора;
		\en Array of 8 parameters which defines for how many positions =[2,4,6...14] vec
		elements should be shifted

		\~
	\param pnAdd
	  \ru Массив из 8 костант.
		\en Array of 8 constants.

		\~
	\param nSize
	  \ru Размер векторов в элементах.
		\en Vector size in elements.

		\~
	\retval pDstVec
	  \ru Результирующий вектор.
		\en The result vec.

		\~
	\return \e void

  \par
	\xmlonly
		<testperf>
			 <init>
					im2[]={2,2,2,2,2,2,2,2};
					im3[]={0};
			</init>
			<param name="pSrcVec"> im0 im1  </param>
			<param name="pnShift"> im1 </param>
			<param name="pnClipFactor"> im2 </param>
			<param name="pnAdd"> im3 </param>
			<param name="pDstVec"> L G </param>
			<param name="nSize"> 4096 </param>
		</testperf>
		<testperf>
			<init>
					im2[]={2,2,2,2,2,2,2,2};
					im3[]={0};
			</init>
			 <param name="pSrcVec"> im0  </param>
			 <param name="pnShift"> im1 </param>
			 <param name="pnClipFactor"> im2 </param>
			 <param name="pnAdd"> im3 </param>
			 <param name="pDstVec"> G </param>
			 <param name="nSize"> 128 1024 4096 </param>
		</testperf>
	\endxmlonly
	*/
	//! \{
//void nmppsClipRShiftConvert_AddC_Ext_(v8nm16s* pSrcVec, v8nm32s* pnClipFactor, v8nm32s* pnShift, v8nm8s* pnAdd,  v8nm8s* pDstVec, int nSize);
void nmppsClipRShiftConvert_AddC_Ext_(v8nm16s* pSrcVec, v8nm32s* pnClipFactor, v8nm32s* pnShift, v8nm32s* pnAdd,  v8nm8s* pDstVec, int nSize);

	//! \}
//void nmppsClipRShiftConvert_AddC_Ext_(v16nm16s* pSrcVec, v16nm32s* pnClipFactor, v16nm32s* pnShift,v16nm4s* pnAdd,
//							  v16nm4s* pDstVec, int nSize);


//******************************************************************************************

  /**
	\defgroup nmppsCmpEqC nmppsCmpEqC
    \ingroup vSelect
    \brief
        \ru Сравнивает элементы массива на признак равенства константе.
        \en Compare vec elements to const equality.

		\~

	\f[
        pDstVec(i)  =  \{ \begin{array}{lcl}
            nTrueFlag,		&  if &  pSrcVec(i) = nCmpVal  \\
            0,				&  if &  pSrcVec(i) \neq nCmpVal   \\
        \end{array}
    \f]


	\f[ i = \overline{0 \ldots nSize-1} \f]

		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
	\param nCmpVal
		\ru	Значение константы для сравнения
		\en Comparision constant value
		\~
    \param nSize
		\ru Размер векторов в элементах.
        \en Vector size in elements.
		\~
    \param nTrueFlag
		\ru Значние флага, устанавливаемого при выполнении условия
        \en Flag value, being set if condition is true.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en Destination vec.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nCmpVal"> 0 </param>
			 <param name="nTrueFlag"> 1 </param>
             <param name="nSize"> 4096 </param>
        </testperf>
      \endxmlonly
    */

  //! \{
void nmppsCmpEqC_16u15b(nm16u15b* pSrcVec,  uint15b nCmpVal,   nm16s* pDstVec, int nSize, int16b nTrueFlag);
void nmppsCmpEqC_8u7b  (nm8u7b* pSrcVec,	uint7b nCmpVal,		nm8s* pDstVec, int nSize, int8b nTrueFlag);
void nmppsCmpEqC_4u3b  (nm4u3b* pSrcVec,	uint3b nCmpVal,		nm4s* pDstVec, int nSize, int4b nTrueFlag);
  //! \}


//******************************************************************************************

  /**
	\defgroup nmppsCmpNe0 nmppsCmpNe0
    \ingroup vSelect
    \brief
        \ru Сравнивает элементы массива на признак неравенства нулю.
        \en Compare vec elements to zero nonequality.

		\~

	\f[
        pDstVec(i)  =  \{ \begin{array}{lcl}
            -1,		&  if &  pSrcVec(i) \neq 0  \\
            0,		&  if &  pSrcVec(i) = 0   \\
        \end{array}
    \f]


	\f[ i = \overline{0 \ldots nSize-1} \f]

		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nSize
		\ru Размер векторов в элементах.
        \en Vector size in elements.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en Destination vec.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nSize"> 8 128 512 1024 2048 </param>
        </testperf>
      \endxmlonly
    */
	//! \{

	void nmppsCmpNe0_8s (const nm8s* pSrcVec,   nm8s* pDstVec, int nSize);
	void nmppsCmpNe0_16s(const nm16s* pSrcVec, nm16s* pDstVec, int nSize);
	void nmppsCmpNe0_32s(const nm32s* pSrcVec, nm32s* pDstVec, int nSize);
	void nmppsCmpNe0_64s(const nm64s* pSrcVec, nm64s* pDstVec, int nSize);

	//! \}

  /**
	\defgroup nmppsCmpEq0 nmppsCmpEq0
    \ingroup vSelect
    \brief
        \ru Сравнивает элементы массива на признак равенства нулю.
        \en Compare vec elements to zero equality.

		\~

	\f[
        pDstVec(i)  =  \{ \begin{array}{lcl}
			-1,	&	if	&	pSrcVec(i) = 0	\\
			0,		&	if	&	pSrcVec(i) \neq 0 		\\
        \end{array}
    \f]


	\f[ i = \overline{0 \ldots nSize-1} \f]

		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en Destination vec.
		\~
    \param nSize
		\ru Размер векторов в элементах.
        \en Vector size in elements.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nSize"> 8 128 512 1024 4096 </param>
        </testperf>
      \endxmlonly
    */
	//! \{

	void nmppsCmpEq0_32s(const nm32s* pSrcVec, nm32s* pDstVec, int nSize);

	//! \}


  /**
	\defgroup nmppsCmpNeC nmppsCmpNeC
    \ingroup vSelect
    \brief
        \ru Сравнивает элементы массива на признак неравенства константе.
        \en Compare vec elements to const nonequality.

		\~



	\f[ i = \overline{0 \ldots nSize-1} \f]

		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
	\param nCmpVal
		\ru	Значение константы для сравнения
		\en Comparision constant value
		\~
    \param nSize
		\ru Размер векторов в элементах.
        \en Vector size in elements.
		\~
    \param nTrueFlag
		\ru Значние флага, устанавливаемого при выполнении условия
        \en Flag value, being set if condition is true.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en Destination vec.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nCmpVal"> 0 </param>
             <param name="nSize"> 8 128 512 1024 2048 </param>
        </testperf>
      \endxmlonly
    */
	//! \{
	void nmppsCmpNeC_8s     (const nm8s* pSrcVec,  int8b  nCmpVal, nm8s* pDstVec, int nSize);
	void nmppsCmpNeC_16s    (const nm16s* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int nSize);
	void nmppsCmpNeC_32s    (const nm32s* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int nSize);
	void nmppsCmpNeC_64s    (const nm64s* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int nSize);
	//! \}

	/**
  	\defgroup nmppsCmpNeC_flag nmppsCmpNeC_flag
      \ingroup vSelect
      \brief
          \ru Сравнивает элементы массива на признак неравенства константе.
          \en Compare vec elements to const nonequality.

  		\~
		\f[
		pDstVec(i)  =  \{ \begin{array}{lcl}
		nTrueFlag,		&  if &  pSrcVec(i) \neq nCmpVal  \\
		0,				&  if &  pSrcVec(i) = nCmpVal   \\
		\end{array}
		\f]

  	\f[
          pDstVec(i)  =  \{ \begin{array}{lcl}
              nTrueFlag,		&  if &  pSrcVec(i) \neq nCmpVal  \\
              0,				&  if &  pSrcVec(i) = nCmpVal   \\
          \end{array}
      \f]


  	\f[ i = \overline{0 \ldots nSize-1} \f]

  		\~
      \param pSrcVec
          \ru Входной вектор.
          \en Input vec.
  		\~
  	\param nCmpVal
  		\ru	Значение константы для сравнения
  		\en Comparision constant value
  		\~
      \param nSize
  		\ru Размер векторов в элементах.
          \en Vector size in elements.
  		\~
      \param nTrueFlag
  		\ru Значние флага, устанавливаемого при выполнении условия
          \en Flag value, being set if condition is true.
  		\~
      \retval pDstVec
          \ru Результирующий вектор.
          \en Destination vec.
  		\~
      \return \e void

      \par
      \xmlonly
          <testperf>
               <param name="pSrcVec"> im0 im1 </param>
               <param name="pDstVec"> im0 im1 </param>
               <param name="nCmpVal"> 0 </param>
               <param name="nSize"> 8 128 512 1024 2048 </param>
  			 <param name="nTrueFlag"> 1 </param>
          </testperf>
        \endxmlonly
      */
  	//! \{
	void nmppsCmpNeC_8u7b  (nm8u7b* pSrcVec,	uint7b nCmpVal,		nm8s* pDstVec, int nSize, int8b nTrueFlag);
	void nmppsCmpNeC_16u15b(nm16u15b* pSrcVec,  uint15b nCmpVal,   nm16s* pDstVec, int nSize, int16b nTrueFlag);
	//! \}

	int nmppsCmpNeC_8s8um    (const nm8s* pSrcVec,  int8b  nCmpVal, nm8u* pDstVec, int nSize, struct NmppsTmpSpec *spec);
	int nmppsCmpNeC_16s8um   (const nm16s* pSrcVec, int16b nCmpVal, nm8u* pDstVec, int nSize, struct NmppsTmpSpec *spec);
	int nmppsCmpNeC_32s8um   (const nm32s* pSrcVec, int32b nCmpVal, nm8u* pDstVec, int nSize, struct NmppsTmpSpec *spec);
	int nmppsCmpNeC_64s8um   (const nm64s* pSrcVec, int64b nCmpVal, nm8u* pDstVec, int nSize, struct NmppsTmpSpec *spec);






	//spec.mode=ONE_TIME_ALLOC|ROUTE_ALLOC|OPTIMIZE_ROUTE;

	//int nmppsCmpLtC_8s8um      (const nm8s* pSrcVec,  int8b  nCmpVal, nm8s* pDstVec,  int nSize, struct NmppsTmpSpec *spec);
	//int nmppsCmpLtC_16s8um     (const nm16s* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int nSize, struct NmppsTmpSpec *spec);
	//int nmppsCmpLtC_32s8um     (const nm32s* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int nSize, struct NmppsTmpSpec *spec);
	//int nmppsCmpLtC_64s     (const nm64s* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int nSize, Tmp2BuffSpec *spec);
	//
	int nmppsCmpLtC_8s8um   (const nm8s* pSrcVec,  int8b  nCmpVal, nm8u* pDstVec, int nSize, struct NmppsTmpSpec *spec);
	int nmppsCmpLtC_16s8um  (const nm16s* pSrcVec, int16b nCmpVal, nm8u* pDstVec, int nSize, struct NmppsTmpSpec *spec);
	int nmppsCmpLtC_32s8um  (const nm32s* pSrcVec, int32b nCmpVal, nm8u* pDstVec, int nSize, struct NmppsTmpSpec *spec);
	int nmppsCmpLtC_64s8um  (const nm64s* pSrcVec, int64b nCmpVal, nm8u* pDstVec, int nSize, struct NmppsTmpSpec *spec);

/*
	void nmppsCmpGtC_8s      (nm8s* pSrcVec,  int8b  nCmpVal, nm8s* pDstVec,  int nSize, Tmp2BuffSpec *spec);
	void nmppsCmpGtC_16s     (nm16s* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int nSize, Tmp2BuffSpec *spec);
	void nmppsCmpGtC_32s     (nm32s* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int nSize, Tmp2BuffSpec *spec);
	void nmppsCmpGtC_64s     (nm64s* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int nSize, Tmp2BuffSpec *spec);
*/
/**
  \defgroup nmppsCmpLtC nmppsCmpLtC
  \ingroup vSelect
  \brief
	  \ru Функция сравнения элементов массива с константой (меньше)
	  \en Compare vec elements to const (less).

	  \~
  \param pSrcVec
	  \ru Входной вектор.
	  \en Input vec.
	  \~
  \param nCmpVal
	  \ru	Значение константы для сравнения
	  \en Comparision constant value
	  \~
  \retval pDstVec
	  \ru Результирующий вектор.
	  \en Destination vec.
	  \~
  \param nSize
  \ru Размер векторов в элементах.
  \en Vector size in elements.
  \~
  \return \e void

  \par
  \xmlonly
	  <testperf>
		   <param name="pSrcVec"> im0 im1 </param>
		   <param name="pDstVec"> im0 im1 </param>
		   <param name="nCmpVal"> 0 </param>
		   <param name="nSize"> 2048 </param>
	  </testperf>
	\endxmlonly
  */
  //! \{
	void nmppsCmpLtC_8s7b    (const nm8s7b  * pSrcVec,  int8b  nCmpVal,nm8s*  pDstVec, int nSize);
	void nmppsCmpLtC_16s15b  (const nm16s15b* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int nSize);
	void nmppsCmpLtC_32s31b  (const nm32s31b* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int nSize);
	void nmppsCmpLtC_64s63b  (const nm64s63b* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int nSize);
  //! \}

  /**
    \defgroup nmppsCmpGtC nmppsCmpGtC
    \ingroup vSelect
    \brief
  	  \ru Функция сравнения элементов массива с константой (больше)
  	  \en Compare vec elements to const (greater).

  	  \~
    \param pSrcVec
  	  \ru Входной вектор.
  	  \en Input vec.
  	  \~
    \param nCmpVal
  	  \ru	Значение константы для сравнения
  	  \en Comparision constant value
  	  \~
    \retval pDstVec
  	  \ru Результирующий вектор.
  	  \en Destination vec.
  	  \~
    \param nSize
    \ru Размер векторов в элементах.
    \en Vector size in elements.
    \~
    \return \e void

    \par
    \xmlonly
  	  <testperf>
  		   <param name="pSrcVec"> im0 im1 </param>
  		   <param name="pDstVec"> im0 im1 </param>
  		   <param name="nCmpVal"> 0 </param>
  		   <param name="nSize"> 2048 </param>
  	  </testperf>
  	\endxmlonly
    */
    //! \{
	void nmppsCmpGtC_8s7b    (const nm8s7b  * pSrcVec,  int8b nCmpVal, nm8s * pDstVec, int nSize);
	void nmppsCmpGtC_16s15b  (const nm16s15b* pSrcVec, int16b nCmpVal, nm16s* pDstVec, int nSize);
	void nmppsCmpGtC_32s31b  (const nm32s31b* pSrcVec, int32b nCmpVal, nm32s* pDstVec, int nSize);
	void nmppsCmpGtC_64s63b  (const nm64s63b* pSrcVec, int64b nCmpVal, nm64s* pDstVec, int nSize);
    //! \}

	/**
	\defgroup nmppsCmpGteC nmppsCmpGteC
	\ingroup vSelect_f
	\brief Функция сравнения элементов массива с константой (больше или равно)

	\param [in] pSrcVec входной массив (элемент массива представляет собой структура v2nm32f, состоящая из двух чисел float)
	\param [in] C константа (два числа float)
	\retval [out] evenFlags маска полученная после сравнения первого поля из структуры v2nm32f
	\retval [out] oddFlags маска полученная после сравнения второго поля из структуры v2nm32f
	\param [in] step шаг, с которым будут браться элементы из pSrcVec
	\param [in] nSize размер массива (в v2nm32f)
	\details В структуре v2nm32f два поля. Первое - v0. Второе - v1.
 */
//! \{
void nmppsCmpGteC_v2nm32f(const v2nm32f* pSrcVec, const v2nm32f* C, nm1* evenFlags, nm1* oddFlags, int step, int nSize);
//! \}

	/**
	\defgroup nmppsCmpGtC nmppsCmpGtC
	\ingroup vSelect_f
	\brief Функция сравнения элементов массива с константой (больше или равно)

	\param [in] pSrcVec входной массив (элемент массива представляет собой структура v2nm32f, состоящая из двух чисел float)
	\param [in] C константа (два числа float)
	\retval [out] evenFlags маска полученная после сравнения первого поля из структуры v2nm32f
	\retval [out] oddFlags маска полученная после сравнения второго поля из структуры v2nm32f
	\param [in] step шаг, с которым будут браться элементы из pSrcVec
	\param [in] nSize размер массива (в v2nm32f)
	\details В структуре v2nm32f два поля. Первое - v0. Второе - v1.
 */
//! \{
void nmppsCmpGtC_v2nm32f(const v2nm32f* pSrcVec, const v2nm32f* C, nm1* evenFlags, nm1* oddFlags, int step, int nSize);
//! \}

//******************************************************************************************

	/**
	\defgroup nmppsCmpEqV_ nmppsCmpEqV_
    \ingroup vSelect
    \brief
        \ru Поэлементное сравнение элементов двух вектров на признак равенства.
        \en Elementwise vec comparision for equality .
		\~

	\f[
        pDstVec(i)  =  \{ \begin{array}{lcl}
            nTrueFlag,		&  if &  pSrcVec(i) = nCmpVal  \\
            0,				&  if &  pSrcVec(i) \neq nCmpVal   \\
        \end{array}
    \f]


	\f[ i = \overline{0 \ldots nSize-1} \f]

		\~
    \param pSrcVec1
        \ru Первый входной вектор.
        \en First input vec.
		\~
    \param pSrcVec2
        \ru Второй входной вектор.
        \en Second input vec.
		\~
    \param nSize
		\ru Размер векторов в элементах.
        \en Vector size in elements.
		\~
    \param nTrueFlag
		\ru Значние флага, устанавливаемого при выполнении условия
        \en Flag value, being set if condition is true.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en Destination vec.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec1"> im0 im1 </param>
			 <param name="pSrcVec2"> im0 im1 </param>
             <param name="pDstVec"> im2 im3 </param>
             <param name="nSize"> 8 128 512 1024 2048 </param>
			 <param name="nTrueFlag"> 1 </param>
        </testperf>
      \endxmlonly
    */
	//! \{
void nmppsCmpEqV_16u15b(nm16u15b* pSrcVec1, nm16u15b* pSrcVec2, nm16s* pDstVec, int nSize, int16b nTrueFlag);
void nmppsCmpEqV_8u7b(nm8u7b* pSrcVec1, nm8u7b* pSrcVec2, nm8s* pDstVec, int nSize, int8b nTrueFlag);
	//! \}

	/**
  	\defgroup nmppsCmpNe nmppsCmpNe
      \ingroup vSelect
      \brief
          \ru Сравнивает элементы массива на признак неравенства константе.
          \en Compare vec elements to const nonequality.

  		\~



  	\f[ i = \overline{0 \ldots nSize-1} \f]

  		\~
      \param pSrcVec1
          \ru Входной вектор1
          \en Input vec1
  		\~
  	\param pSrcVec2
  		\ru	Входной вектор2
        \en Input vec2
  		\~
      \param nSize
  		\ru Размер векторов в элементах
          \en Vector size in elements
  		\~
      \retval pDstVec
          \ru Результирующий вектор
          \en Destination vec
  		\~
      \return \e void

      \par
      \xmlonly
          <testperf>
               <param name="pSrcVec1"> im0 </param>
			   <param name="pSrcVec2"> im1 </param>
               <param name="pDstVec"> im2 </param>
               <param name="nSize"> 2048 </param>
          </testperf>
        \endxmlonly
      */
//! \{
void nmppsCmpNe_8s   (const nm8s*  pSrcVec1, const  nm8s* pSrcVec2, nm8s*  pDstVec, int nSize);
void nmppsCmpNe_16s  (const nm16s* pSrcVec1, const nm16s* pSrcVec2, nm16s* pDstVec, int nSize);
void nmppsCmpNe_32s  (const nm32s* pSrcVec1, const nm32s* pSrcVec2, nm32s* pDstVec, int nSize);
void nmppsCmpNe_64s  (const nm64s* pSrcVec1, const nm64s* pSrcVec2, nm64s* pDstVec, int nSize);
//! \}

int nmppsCmpNe_8s8um (const nm8s*  pSrcVec1, const  nm8s* pSrcVec2, nm8u*  pDstVec, int nSize, struct NmppsTmpSpec* spec);
int nmppsCmpNe_16s8um(const nm16s* pSrcVec1, const nm16s* pSrcVec2, nm8u*  pDstVec, int nSize, struct NmppsTmpSpec* spec);
int nmppsCmpNe_32s8um(const nm32s* pSrcVec1, const nm32s* pSrcVec2, nm8u*  pDstVec, int nSize, struct NmppsTmpSpec* spec);
int nmppsCmpNe_64s8um(const nm64s* pSrcVec1, const nm64s* pSrcVec2, nm8u*  pDstVec, int nSize, struct NmppsTmpSpec* spec);


/**
  \defgroup nmppsCmpLt nmppsCmpLt
  \ingroup vSelect
  \brief
	  \ru Функция сравнения элементов массива с константой (меньше)
	  \en Compare vec elements to const (less).

	  \~
  \param pSrcVec1
	  \ru Входной вектор1
	  \en Input vec1
	  \~
  \param pSrcVec2
	  \ru Входной вектор2
	  \en Input vec2
	  \~
  \retval pDstVec
	  \ru Результирующий вектор
	  \en Destination vec
	  \~
  \param nSize
  \ru Размер векторов в элементах
  \en Vector size in elements
  \~
  \return \e void

  \par
  \xmlonly
	  <testperf>
		   <param name="pSrcVec"> im0 im1 </param>
		   <param name="pDstVec"> im0 im1 </param>
		   <param name="nSize"> 2048 </param>
	  </testperf>
	\endxmlonly
  */
//! \{
void nmppsCmpLt_8s7b  (const nm8s*  pSrcVec1,const  nm8s* pSrcVec2, nm8s*  pDstVec, int nSize);
void nmppsCmpLt_16s15b(const nm16s* pSrcVec1,const nm16s* pSrcVec2, nm16s* pDstVec, int nSize);
void nmppsCmpLt_32s31b(const nm32s* pSrcVec1,const nm32s* pSrcVec2, nm32s* pDstVec, int nSize);
void nmppsCmpLt_64s63b(const nm64s* pSrcVec1,const nm64s* pSrcVec2, nm64s* pDstVec, int nSize);
//! \}
int nmppsCmpLt_8s8um (const nm8s*  pSrcVec1, const  nm8s* pSrcVec2, nm8u*  pDstVec, int nSize, struct NmppsTmpSpec* spec);
int nmppsCmpLt_16s8um(const nm16s* pSrcVec1, const nm16s* pSrcVec2, nm8u*  pDstVec, int nSize, struct NmppsTmpSpec* spec);
int nmppsCmpLt_32s8um(const nm32s* pSrcVec1, const nm32s* pSrcVec2, nm8u*  pDstVec, int nSize, struct NmppsTmpSpec* spec);
int nmppsCmpLt_64s8um(const nm64s* pSrcVec1, const nm64s* pSrcVec2, nm8u*  pDstVec, int nSize, struct NmppsTmpSpec* spec);

//******************************************************************************************

	/**
	\defgroup nmppsCmpNeV_ nmppsCmpNeV_
    \ingroup vSelect
    \brief
        \ru Поэлементное сравнение элементов двух вектров на признак неравенства.
        \en Elementwise vec comparision for nonequality .
		\~

	\f[
        pDstVec(i)  =  \{ \begin{array}{lcl}
            nTrueFlag,		&  if &  pSrcVec(i) \neq nCmpVal  \\
            0,				&  if &  pSrcVec(i) = nCmpVal   \\
        \end{array}
    \f]


	\f[ i = \overline{0 \ldots nSize-1} \f]

		\~
    \param pSrcVec1
        \ru Первый входной вектор.
        \en First input vec.
		\~
    \param pSrcVec2
        \ru Второй входной вектор.
        \en Second input vec.
		\~
    \param nSize
		\ru Размер векторов в элементах.
        \en Vector size in elements.
		\~
    \param nTrueFlag
		\ru Значние флага, устанавливаемого при выполнении условия
        \en Flag value, being set if condition is true.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en Destination vec.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec1"> im0 im1 </param>
			 <param name="pSrcVec2"> im0 im1 </param>
             <param name="pDstVec"> im2 im3 </param>
             <param name="nSize"> 2048 </param>
			 <param name="nTrueFlag"> 1 </param>
        </testperf>
      \endxmlonly
    */
	//! \{
void nmppsCmpNeV_16u(nm16u15b* pSrcVec1, nm16u15b* pSrcVec2, nm16s* pDstVec, int nSize, int16b nTrueFlag);
void nmppsCmpNeV_8u(nm8u7b* pSrcVec1, nm8u7b* pSrcVec2, nm8s* pDstVec, int nSize, int8b nTrueFlag);
	//! \}


void nmppsCmpNeV_8s8u(nm8s* src1, nm8s* src2, nm8u* dst, int nSize, int8b nTrueFlag);

//******************************************************************************************


/**
    \defgroup Vec_ClipRShiftConvert_AddC Vec_ClipRShiftConvert_AddC
    \ingroup vInit
    \brief
        \ru Изменение разрядности элементов вектора с клиппированием
        \en Change of vec elements word-length with clipping

		\~
        \ru Преобразование 32р знаковых данных к восьмиразрядным осуществляется
	        вырезанием битов 16..31.. ,затем клиппированием и вырезанием восьми
            младших бит реультата. При клиппировании используется глобальая
            константа типа nm64s с именем _F1CR_16_to_x. По умолчанию, там лежит
            ff00_ff00_ff00_ff00 соответствующая диапазону результата [-255..256].
            К каждому полученному 64р слову результата прибавляется значение
            глобальной переменной _VR_16_to_x, которая по умолчанию равна нулю.
        \en Signed data are converted to lesser word-length is made by means of
            the low significant bits truncation.

		\~
		\~
    \param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vector size in elements.

		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en The result vec.

		\~
    \return \e void


    \par
    \xmlonly
        <testperf>
             <param name="pSrcVec"> im0 im1 </param>
             <param name="pDstVec"> im0 im1 </param>
             <param name="nSize"> 2048 </param>
        </testperf>
        <testperf>
             <param name="pSrcVec"> im0 </param>
             <param name="pDstVec"> im1 </param>
             <param name="nSize"> 8 128 1024 2048 </param>
        </testperf>
    \endxmlonly
    \{
    */
  //! \{
void Vec_ClipRShiftConvert_AddC( nm32s* pSrcVec, nm8u* pDstVec, int nSize);
  //! \}

#ifdef __cplusplus
		};
#endif

#endif
