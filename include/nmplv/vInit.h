
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   vInit.h
//! \author Сергей Мушкаев
//! \brief  Определение функций инициализации для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef _VINIT_H_INCLUDED_
#define _VINIT_H_INCLUDED_

typedef int NmppRoundMode;

#define              nmppRndUp                  5
#define              nmppRndDown                3
#define              nmppRndNear                1
#define              nmppRndZero                7

#ifdef __cplusplus
		extern "C" {
#endif

    /**
    \defgroup nmppsSet nmppsSet-инициализация
    \ingroup vInit
    \brief
        \ru Функция инициализации элементов массива постоянным значением.
        \en Function of array initialization with a constant value.

		\~

	\f[
        pVec[i]  =  nVal,
    \f]

	\f[
        i = \overline{0 \ldots nSize-1}
    \f]

    \param nSize
        \ru Размер вектора в элементах.
        \en Size of vec in elements.
		\~
    \param nVal
        \ru Константа. Диапазон значений nVal должен соответсвовать типу результирующего вектора.
        \en A constant. Range of nVal must correspond to type of result vec
		\~
    \retval pVec
        \ru Результирующий вектор.
        \en The result vec.
		\~
    \return \e void


    \par
    \xmlonly
        <testperf>
	        <param> pVec </param> <values> L G </values>
	        <param> nVal </param> <values> n </values>
	        <param> nSize  </param> <values> 10240 </values>
        </testperf>
        <testperf>
	        <param> pVec </param> <values> G </values>
	        <param> nVal </param> <values> n </values>
	        <param> nSize  </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{

void nmppsSet_8s(nm8s* pVec,  int8b nVal, int nSize);
void nmppsSet_16s(nm16s* pVec, int16b nVal, int nSize);
void nmppsSet_32s(nm32s* pVec, int32b nVal, int nSize);
void nmppsSet_64sp(nm64s* pVec, int64b* nVal, int nSize);
__INLINE__ void nmppsSet_64s(nm64s* pVec, int64b  nVal, int nSize)  {nmppsSet_64sp((nm64s*) pVec, (int64b*)&nVal, nSize);}

__INLINE__ void nmppsSet_8u(nm8u* pVec,  uint8b nVal, int nSize)	{nmppsSet_8s((nm8s*) pVec,  (int8b)nVal, nSize);}
__INLINE__ void nmppsSet_16u(nm16u* pVec, uint16b nVal, int nSize)	{nmppsSet_16s((nm16s*) pVec, (int16b)nVal, nSize);}
__INLINE__ void nmppsSet_32u(nm32u* pVec, uint32b nVal, int nSize)	{nmppsSet_32s((nm32s*) pVec, (int32b)nVal, nSize);}
__INLINE__ void nmppsSet_64u(nm64u* pVec, uint64b  nVal, int nSize)	{nmppsSet_64s((nm64s*) pVec, (int64b)nVal, nSize);}
__INLINE__ void nmppsSet_64up(nm64u* pVec, uint64b* nVal, int nSize){nmppsSet_64sp((nm64s*) pVec, (int64b*)nVal, nSize);}


    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsRandUniform nmppsRandUniform
    \ingroup vInit
    \brief
        \ru Инициализация массива случайными числами.
        \en Initialization of an array with random numbers.
		\~
    \param nSize
        \ru Размер вектора.
        \en Vector size.
		\~
    \param nRandomize
        \ru Произвольное число для инициализации
                            генератора случайных чисел.
        \en Arbitrary number for initialization
                            of a random-number generator.
		\~
    \retval pDstVec
        \ru Результирующий вектор.
        \en Result vec.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
             <param> pDstVec </param> <values> L G </values>
             <param> nRandomize </param> <values> 1 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
             <param> pDstVec </param> <values> G </values>
             <param> nRandomize </param> <values> 1 </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
/**
	/ru  Инициализация массива 32-разрядными случайными числами.
	/en Random initialization of 32-bit buffer
	/~
*/
//void nmppsRandUniform_32u(nm32u* pDstVec, int nSize, unsigned nRandomize );
void nmppsRandUniform_64s(nm64s* pDstVec, int nSize);
__INLINE__ void nmppsRandUniform_8s (nm8s* pDstVec,  int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>3);}
__INLINE__ void nmppsRandUniform_16s(nm16s* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>2);}
__INLINE__ void nmppsRandUniform_32s(nm32s* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>1);}
__INLINE__ void nmppsRandUniform_8u (nm8u* pDstVec,  int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>3);}
__INLINE__ void nmppsRandUniform_16u(nm16u* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>2);}
__INLINE__ void nmppsRandUniform_32u(nm32u* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize>>1);}
__INLINE__ void nmppsRandUniform_64u(nm64u* pDstVec, int nSize) {nmppsRandUniform_64s((nm64s*)pDstVec,  nSize   );}

void nmppsRandUniform_64f(nm64f* pDstVec, int nSize, double low, double hi);
void nmppsRand_32f(nm32f* pDstVec, int nSize,float low,float hi);

void nmppsRandUniform_32f_integer(nm32f *pDstVec,int nSize,int hi,int low);

//__INLINE__ void nmppsRandUniform_64s(nm64s* pDstVec, int nSize, unsigned nRandomize = 1) {nmppsRandUniform_32u((nm32u*)pDstVec,  nSize<<1, nRandomize);}

/**
	/ru  Инициализация массива 64-разрядными случайными числами.
	/en Random initialization of 64-bit buffer
	/~

*/

    //! \}



//*****************************************************************************

    /**
    \defgroup nmppsRandUniform_ nmppsRandUniform_
    \ingroup vInit
    \brief
        \ru Генерация случайного числа с равномерным раcпределением.
        \en Random number generation with uniform distribution.

		\~
	  \~
    \param nMin
        \ru Минимальное возможное значение случайного числа.
        \en Minimal value for random number.
		\~
    \param nMax
        \ru Максимальное возможное значение случайного числа.
        \en Maximal value for random number.
		\~
    \param nDivisible
        \ru Значение, которому будет кратно случайное число.
        \en Random number will be divisible by this value.
		\~
    \return \e int
		\ru Случайное число в диапазоне либо [nMin, nMax]. Для функции без параметров
			данный диапазон [-2^31; 2^31-1].
        \en Random number in range [nMin, nMax]. For function without parameters
			this range is [-2^31; 2^31-1].

		\~
    \par
    \xmlonly
        <testperf>
          <param> nMin </param> <values> 0 128 		</values>
          <param> nMax  </param> <values> 10240 </values>
          <param> nDivisible </param> <values> 1 </values>
          <size> 1 </size>
        </testperf>
        <testperf>
          <param> nMin </param> <values> 128 		</values>
          <param> nMax  </param> <values> 1024 10240 </values>
          <param> nDivisible </param> <values> 1 </values>
          <size> 1 </size>
        </testperf>
        <testperf>
          <param> nMin </param> <values> 128 		</values>
          <param> nMax  </param> <values> 10240 </values>
          <param> nDivisible </param> <values> 1 2 </values>
          <size> 1 </size>
        </testperf>

    \endxmlonly
    */
    //! \{
int nmppsRandUniform2_32s(int nMin, int nMax, int nDivisible);
int nmppsRandUniform3_32s(int nMin, int nMax);
int nmppsRandUniform();

    //! \}


//*****************************************************************************

    /**
    \defgroup nmppsRamp_ nmppsRamp_
    \ingroup vInit
    \brief
        \ru Инициализация массива элементами арифметической прогрессии.
        \en Initialization of an array by ramped numbers.

		\~

	\f[
        pVec[i] = nOffset + nSlope \cdot i
    \f]

	\f[
        i = \overline{0 \ldots nSize-1}
    \f]

    \~
    \param nOffset
        \ru Первый член арифметической прогрессии.
        \en Init value.
		\~
    \param nSlope
        \ru Разность арифметической прогрессии.
        \en Common difference.
		\~
    \param nSize
        \ru Размер вектора.
        \en Vector size.
		\~
    \retval pVec
        \ru Результирующий массив.
        \en Result array.
		\~
    \return \e void


    \par
    \xmlonly
        <testperf>
             <param> pVec </param> <values> L G </values>
             <param> nOffset </param> <values> 10 </values>
             <param> nSlope </param> <values> 2 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
             <param> pVec </param> <values> G </values>
             <param> nOffset </param> <values> -10 10 </values>
             <param> nSlope </param> <values> 2 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
             <param> pVec </param> <values> G </values>
             <param> nOffset </param> <values> 10 </values>
             <param> nSlope </param> <values> -2 2 </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
             <param> pVec </param> <values> G </values>
             <param> nOffset </param> <values> 10 </values>
             <param> nSlope </param> <values> 2 </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly
    */
    //! \{
void nmppsRamp_8s(nm8s* pVec,  int8b nOffset,  int8b nSlope, int nSize);
void nmppsRamp_16s(nm16s* pVec, int16b nOffset, int16b nSlope, int nSize);
void nmppsRamp_32s(nm32s* pVec, int32b nOffset, int32b nSlope, int nSize);
void nmppsRamp_64s(nm64s* pVec, int64b nOffset, int64b nSlope, int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsConvert nmppsConvert
    \ingroup vInit
    \brief
        \ru Изменение разрядности элементов вектора.
        \en Change of vec elements word-length.

		\~
        \ru Преобразование знаковых данных к меньшей разрядности осуществляется
	        отбрасыванием старших битов.
	        Преобразование знаковых данных к большей разрядности осуществляется
	        c распространением влево старшего (знакового) бита.
            Преобразование беззнаковых данных к большей разрядности осуществляется
	        добавлением слева старших нулевых битов.
        \en Signed data are converted to lesser word-length is made by means of
            the most significant bits truncation.
            Signed data are converted to greater word-length is made with
            left expansion of the most significant (sign) bit.
            Unsigned data are converted to greater word-length is made by means of
            addition of the most significant zero bits on the left.
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
             <param> pSrcVec </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
             <param> pSrcVec </param> <values> L </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly



    */
	//todo Impelenment NM versin of void nmppsConvert_32s(nm32s *pSrcVec, nm4s *pDstVec, int nSize);
    //! \{

/**
 \restr nSize =[32*64,32*64*2,32*64*3,....]
*/
void nmppsConvert_1s2s  (const nm1* pSrcVec, nm2s* pDstVec, int nSize);
/**
 \restr nSize =[32*64,32*64*2,32*64*3,....]
*/
void nmppsConvert_1u2u  (const nm1* pSrcVec, nm2u* pDstVec, int nSize);
void nmppsConvert_1u4u  (const nm1* pSrcVec, nm4u* pDstVec, int nSize);

void nmppsConvert_2s1s	(const nm2s* pSrcVec, nm1*  pDstVec, int nSize);
void nmppsConvert_2s4s  (const nm2s* pSrcVec, nm4s* pDstVec, int nSize);
void nmppsConvert_2u4u  (const nm2u* pSrcVec, nm4u* pDstVec, int nSize);

void nmppsConvert_4s1s	(const nm4s* pSrcVec, nm1*  pDstVec, int nSize);
void nmppsConvert_4s2s	(const nm4s* pSrcVec, nm2s* pDstVec, int nSize);
void nmppsConvert_4s8s  (const nm4s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsConvert_4u8u  (const nm4u* pSrcVec, nm8u* pDstVec, int nSize);

void nmppsConvert_8s4s  (const nm8s* pSrcVec, nm4s*  pDstVec, int nSize);
void nmppsConvert_8s16s (const nm8s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsConvert_8s32s (const nm8s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsConvert_8s64s (const nm8s* pSrcVec, nm64s* pDstVec, int nSize);
void nmppsConvert_8u16u (const nm8u* pSrcVec, nm16u* pDstVec, int nSize);
void nmppsConvert_8u32u (const nm8u* pSrcVec, nm32u* pDstVec, int nSize);
void nmppsConvert_8u64u (const nm8u* pSrcVec, nm64u* pDstVec, int nSize);

void nmppsConvert_16s4s (const nm16s* pSrcVec, nm4s* pDstVec, int nSize);
void nmppsConvert_16s8s (const nm16s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsConvert_16s32s(const nm16s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsConvert_16s64s(const nm16s* pSrcVec, nm64s* pDstVec, int nSize);
void nmppsConvert_16u32u(const nm16u* pSrcVec, nm32u* pDstVec, int nSize);
void nmppsConvert_16u64u(const nm16u* pSrcVec, nm64u* pDstVec, int nSize);

void nmppsConvert_32s8s (const nm32s* pSrcVec, nm8s* pDstVec, int nSize);
void nmppsConvert_32s16s(const nm32s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsConvert_32s64s(const nm32s* pSrcVec, nm64s* pDstVec, int nSize);
void nmppsConvert_32u64u(const nm32u* pSrcVec, nm64u* pDstVec, int nSize);

void nmppsConvert_64s32s(const nm64s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsConvert_64s16s(const nm64s* pSrcVec, nm16s* pDstVec, int nSize);

    //! \}
//void nmppsConvert_32s(nm32s *pSrcVec, nm4s *pDstVec, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора целых беззнаковых чисел в вектор комплексных чисел, где мнимая(равна 0) и действительная части - 32-битные числа с плавающей точкой
 *
    \param pSrcVec указатель на входной вектор целых беззнаковых чисел
    \param pDstVec указатель на выходной вектор комплексных чисел с плавающей точкой
    \param nSize число элементов во входном векторе
    \details После конвертации мнимая часть каждого комплексного числа в выходном векторе будет равна 0
 *  \details Функция выполняется на сопроцессоре (процессор 1879ВМ6Я) с плавающей точкой с использованием переупаковщика данных
 */
void nmppsConvert_32u32fcr(const nm32u* pSrcVec, nm32fcr* pDstVec, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора целых чисел в вектор комплексных чисел, где мнимая(равна 0) и действительная части - 32-битные числа с плавающей точкой
 *
    \param pSrcVec указатель на входной вектор целых чисел
    \param pDstVec указатель на выходной вектор комплексных чисел с плавающей точкой
    \param nSize число элементов во входном векторе
    \details После конвертации мнимая часть каждого комплексного числа в выходном векторе будет равна 0
 *  \details Функция выполняется на сопроцессоре (процессор 1879ВМ6Я) с плавающей точкой с использованием переупаковщика данных
 */
void nmppsConvert_32s32fcr(const nm32s* pSrcVec, nm32fcr* pDstVec, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора комплексных чисел с целыми действительной и мнимой частью (32 бита) в вектор комплексных чисел, где мнимая и действительная части - 32-битные числа с плавающей точкой
 *
	\param pSrcVec указатель на входной вектор целых чисел
	\param pDstVec указатель на выходной вектор комплексных чисел с плавающей точкой
	\param nSize число элементов во входном векторе
 *  \details Функция выполняется на сопроцессоре (процессор 1879ВМ6Я) с плавающей точкой с использованием переупаковщика данных
 */

void nmppsConvert_32f32fcr(const nm32f* pSrcVec, nm32fcr* pDstVec, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора комплексных чисел с целыми действительной и мнимой частью (32 бита) в вектор комплексных чисел, где мнимая и действительная части - 32-битные числа с плавающей точкой
 *
    \param pSrcVec указатель на входной вектор чисел с плавающей точкой (float)
    \param pDstVec указатель на выходной вектор комплексных чисел с плавающей точкой
    \param nSize число элементов во входном векторе
 *  \details Функция выполняется на сопроцессоре (процессор 1879ВМ6Я) с плавающей точкой с использованием переупаковщика данных
 */

void nmppsConvert_32sc32fcr(const nm32sc* pSrcVec, nm32fcr* pDstVec, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора комплексных чисел с целыми действительной и мнимой частью (32 бита) в вектор комплексных чисел, где мнимая и действительная части - 32-битные числа с плавающей точкой
 *
	\param pSrcVec указатель на входной вектор целых чисел
	\param pDstVec указатель на выходной вектор комплексных чисел с плавающей точкой
	\param nSize число элементов во входном векторе (может быть только четным)
 *  \details Функция выполняется на сопроцессоре (процессор 1879ВМ6Я) с плавающей точкой с использованием переупаковщика данных
 *  \details Функуция округляет все дробные числа из pSrcVec до ближайших целых (например, 1.5 будет округлено до 2, 1.7 до 2, а 1.4 до 1)
 */

void nmppsConvert_32f32s_rounding(const nm32f* pSrcVec, nm32s* pDstVec, int scale, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора комплексных чисел с целыми действительной и мнимой частью (32 бита) в вектор комплексных чисел, где мнимая и действительная части - 32-битные числа с плавающей точкой
 *
	\param pSrcVec указатель на входной вектор целых чисел
	\param pDstVec указатель на выходной вектор комплексных чисел с плавающей точкой
	\param nSize число элементов во входном векторе (может быть только четным)
 *  \details Функция выполняется на сопроцессоре (процессор 1879ВМ6Я) с плавающей точкой с использованием переупаковщика данных
 *  \details Функуция округляет все дробные числа из pSrcVec к меньшему по модулю (например, 1.5 будет округлено до 1, 1.7 до 1, а -1.1 до -1)
 */

//int nmppsConvert_32f32s_Sfs(const nm32f* pSrcVec, nm32s* pDstVec, NmppRoundMode rndMode, int scaleFactor, int nSize);
void nmppsConvert_32f32s_ceiling(const nm32f* pSrcVec, nm32s* pDstVec, int scale, int nSize);
void nmppsConvert_32f32s_floor(const nm32f* pSrcVec, nm32s* pDstVec, int scale, int nSize);
void nmppsConvert_32f32s_truncate(const nm32f* pSrcVec, nm32s* pDstVec, int scale, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора комплексных чисел с целыми действительной и мнимой частью (32 бита) в вектор комплексных чисел, где мнимая и действительная части - 32-битные числа с плавающей точкой
 *
	\param pSrcVec указатель на входной вектор целых чисел
	\param pDstVec указатель на выходной вектор комплексных чисел с плавающей точкой
	\param nSize число элементов во входном векторе (может быть только четным)
 *  \details Функция выполняется на сопроцессоре (процессор 1879ВМ6Я) с плавающей точкой с использованием переупаковщика данных
 */

void nmppsConvert_32s32f(const nm32s* pSrcVec, nm32f* pDstVec, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция соединяет 2 массива 32-х чисел с плавающей точкой (float) в один. Результирующий массив { pSrcVec1[0], pSrcVec2[0], pSrcVec1[1], pSrcVec2[1], pSrcVec1[2], pSrcVec2[2] .... }
 *
    \param pSrcVec1 указатель на входной массив чисел float
    \param pSrcVec2 указатель на входной массив чисел float
    \param pDstVec указатель на выходной массив чисел float
    \param nSize количество элементов в массиве pSrcVec (в массиве pDstVec элементов будет в 2 раза больше)
 */
void nmppsJoin_32f(const nm32f* pSrcVec1, const nm32f* pSrcVec2, nm32f* pDstVec, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора беззнаковых байт в вектор беззнаковых целых чисел
 *
	\param pSrcVec указатель на входной вектор беззнаковых байт
	\param pDstVec указатель на выходной вектор беззнаковых целых чисел
	\param nSize число элементов во входном векторе (должно быть кратно 8 и не может быть меньше 8)
 *  \details Функция выполняется на RISC-процессоре
 */
void nmppsConvertRisc_8u32u(const nm8u* pSrcVec, nm32u* pDstVec, int nSize);

/**
 *  \ingroup nmppsConvert nmppsConvert
 *  \brief Функция конвертации вектора беззнаковых байт в вектор беззнаковых целых чисел
 *
    \param pSrcVec указатель на входной вектор беззнаковых целых чисел
    \param pDstVec указатель на выходной вектор беззнаковых байт
    \param nSize число элементов во входном векторе (должно быть кратно 4 и не может быть меньше 4)
 *  \details Функция выполняется на RISC-процессоре
 */
void nmppsConvertRisc_32u8u(const nm32u* pSrcVec, nm8u* pDstVec, int nSize);

//*****************************************************************************

    /**
    \defgroup nmppsCopy_ nmppsCopy_
    \ingroup vInit
    \brief
        \ru Копирование вектора.
        \en Vector copying.

		\~

	\f[
        pDstVec[i]  =  pSrcVec[i],
    \f]

	\f[
        i = \overline{0 \ldots nSize-1}
    \f]

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
             <param> pSrcVec </param> <values> L G </values>
             <param> pDstVec </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
             <param> pSrcVec </param> <values> L </values>
             <param> pDstVec </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly

        */
    //! \{
void nmppsCopy_2s (const nm2s*  pSrcVec, nm2s*  pDstVec, int nSize);
void nmppsCopy_4s (const nm4s*  pSrcVec, nm4s*  pDstVec, int nSize);
void nmppsCopy_8s (const nm8s*  pSrcVec, nm8s*  pDstVec, int nSize);
void nmppsCopy_16s(const nm16s* pSrcVec, nm16s* pDstVec, int nSize);
void nmppsCopy_32s(const nm32s* pSrcVec, nm32s* pDstVec, int nSize);
void nmppsCopy_64s(const nm64s* pSrcVec, nm64s* pDstVec, int nSize);

__INLINE__ void nmppsCopy_4u (const nm4u*  pSrcVec, nm4u*  pDstVec, int nSize) { nmppsCopy_4s (( nm4s*)  pSrcVec, (nm4s*)  pDstVec,  nSize);}
__INLINE__ void nmppsCopy_8u (const nm8u*  pSrcVec, nm8u*  pDstVec, int nSize) { nmppsCopy_8s (( nm8s*)  pSrcVec, (nm8s*)  pDstVec,  nSize);}
__INLINE__ void nmppsCopy_16u(const nm16u* pSrcVec, nm16u* pDstVec, int nSize) { nmppsCopy_16s(( nm16s*) pSrcVec, (nm16s*) pDstVec,  nSize);}
__INLINE__ void nmppsCopy_32u(const nm32u* pSrcVec, nm32u* pDstVec, int nSize) { nmppsCopy_32s(( nm32s*) pSrcVec, (nm32s*) pDstVec,  nSize);}
__INLINE__ void nmppsCopy_64u(const nm64u* pSrcVec, nm64u* pDstVec, int nSize) { nmppsCopy_64s(( nm64s*) pSrcVec, (nm64s*) pDstVec,  nSize);}

    //! \}



//*****************************************************************************

    /**
    \defgroup nmppsCopyua_ nmppsCopyua_
    \ingroup vInit
    \brief
        \ru Копирование вектора с невыровненной байтовой позиции в выровненную.
        \en Copying a vec from an unaligned byte position to aligned one.

		\~

	\f[
        pDstVec[i] = pSrcVec[nSrcOffset+i]
    \f]

	\f[
        i = \overline{0 \ldots nSize-1}
    \f]

	\ru Позиция байта считается выровненной если она совпадает с границей 64р. слов в памяти.
    \en Position is defined as aligned if it points to 64-bit words boundary in memory.

		\~
	\~
	\param pSrcVec
        \ru Входной вектор.
        \en Input vec.
		\~
    \param pDstVec
        \ru Результирующий вектор.
        \en Output vec.
		\~
    \param nSrcOffset
        \ru Смещение в элементах относительно начала вектора. nSrcOffset Может принимать любое значение.
        \en Shift in elements relatively to the origin of the vec. nSrcOffset may be any.
		\~
    \param nSize
        \ru Кол-во копируемых элементов.
        \en Number of elements being copied.
		\~
    \return \e void

    \par
    \xmlonly
        <testperf>
            <param> pSrcVec    </param> <values> L G </values>
            <param> pDstVec    </param> <values> L G </values>
            <param> nSrcOffset </param> <values> 3 </values>
            <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
            <param> pSrcVec    </param> <values> L </values>
            <param> pDstVec    </param> <values> G </values>
            <param> nSrcOffset </param> <values> 0 3 7 </values>
            <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
            <param> pSrcVec    </param> <values> L </values>
            <param> pDstVec    </param> <values> G </values>
            <param> nSrcOffset </param> <values> 3 </values>
            <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly

    */
    //! \{
void nmppsCopyua_8s(const nm8s* pSrcVec, int nSrcOffset, nm8s* pDstVec,  int nSize);
    //! \}

//*****************************************************************************

    /**
    \defgroup nmppsSwap_ nmppsSwap_
    \ingroup vInit
    \brief
        \ru Перестановка двух векторов.
        \en Swap of two vectors.


		\~
    \param pSrcVec1
        \ru Первый входной вектор.
        \en The first input vec.
		\~
    \param pSrcVec2
        \ru Второй входной вектор.
        \en The second input vec.
		\~
    \param nSize
        \ru Размер векторов в элементах.
        \en Vector size in elements.
		\~
    \return \e void


    \par
    \xmlonly
        <testperf>
             <param> pSrcVec1 </param> <values> L G </values>
             <param> pSrcVec2 </param> <values> L G </values>
             <param> nSize </param> <values> 10240 </values>
        </testperf>
        <testperf>
             <param> pSrcVec1 </param> <values> L </values>
             <param> pSrcVec2 </param> <values> G </values>
             <param> nSize </param> <values> 8 128 1024 10240 </values>
        </testperf>
    \endxmlonly

    */
    //! \{
void nmppsSwap_64s(nm64s* pSrcVec1, nm64s* pSrcVec2, int nSize);
    //! \}




#ifdef __cplusplus
		};
#endif

#endif // _INIT_H_INCLUDED_
