//------------------------------------------------------------------------
//
//  $Workfile:: sElementary.h             $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//
//! \if file_doc
//!
//! \file   sElementary.h
//! \author Андрей Бродяженко
//! \brief  Определение элементарных математических функций над векторами
//!
//! \endif
//!
//------------------------------------------------------------------------

#ifndef _SARITHM_H_INCLUDED_
#define _SARITHM_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

/**
    \defgroup SinCos Тригонометрические функции
    \ingroup Elementary_f
    \brief Функция, вычисляющая синус/косинус над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)
    \param [in] pSrcVec входной вектор чисел с плавающей точкой
    \retval [out] pDstVec выходной вектор чисел с плавающей точкой
    \param [in] nSize число элементов в векторе
    \details Функции совместимы ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
*/
//! \{
void nmppsSin_32f(const nm32f* pSrcVec, nm32f* pDstVec, int nSize);
void nmppsCos_32f(const nm32f* pSrcVec, nm32f* pDstVec, int nSize);
//! \}

/**
    \defgroup Div Функция деления векторов
    \ingroup Elementary_f
   	\brief Функция, вычисляющая x/y (pSrcVec1 / pSrcVec2), где x и y (делимые числа и делители) это вектора чисел с плавающей точкой одинарной
	\param [in] pSrcVec1 входной вектор делимых чисел с плавающей точкой одинарной точности
	\param [in] pSrcVec2 входной вектор делителей с плавающей точкой одинарной точности
	\retval [out] pDstVec выходной вектор частных с плавающей точкой одинарной точности
	\param [in] nSize число элементов в векторе
    \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
*/
//! \{
void nmppsDiv_32f(const nm32f *pSrcVec1, const nm32f *pSrcVec2, nm32f *pDstVec, int nSize);
//! \}
/**
    \defgroup Exp Экспонента
    \ingroup Elementary_f
   	\brief Функция, вычисляющая экспоненту над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)
	\param [in] pSrcVec входной вектор чисел с плавающей точкой одинарной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой одинарной точности
	\param [in] nSize число элементов в векторе
    \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 */
//! \{
void nmppsExp_32f(const nm32f *pSrcVec, nm32f *pDstVec, int nSize);
void nmppsExp_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize);
//! \}

/**
    \defgroup Log Натуральный логарифм
    \ingroup Elementary_f
   	\brief Функция, вычисляющая натуральный логарифм над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)
	\param [in] pSrcVec входной вектор чисел с плавающей точкой одинарной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой одинарной точности
	\param [in] nSize число элементов в векторе
    \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
*/
//! \{
void nmppsLn_32f(const nm32f *pSrcVec, nm32f *pDstVec, int nSize);
void nmppsLn_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize);
//! \}

/**
    \defgroup Pow Возведение в степень
    \ingroup Elementary_f
   	\brief Функция возводит в степень (Deg) каждый элемент вектора чисел с плавающей точкой двойной точности (64f)
	\param [in] pSrcVec входной вектор чисел с плавающей точкой двойной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой двойной точности
	\param [in] Deg степень, в которую возводится каждый элемент входного вектора
	\param [in] nSize число элементов в векторе
    \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 */
//! \{
void nmppsPowx_64f(const nm64f *pSrcVec, nm64f *pDstVec, nm32u Deg, int nSize);
//! \}

/**
    \defgroup Sqrt Вычисление квадратного корня
    \ingroup Elementary_f
   	\brief Функция вычисляет квадратный корень от каждого элемента входного вектора чисел с плавающей точкой
	\param [in] pSrcVec входной вектор чисел с плавающей точкой
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой
	\param [in] pTmpBuf дополнительный буфер, необходимый для ускорения работы функции (размер равен размеру pDstVec). Ускорение произойдет только при условии, что pDstVec и pTmpBuf лежат в разных банках.
	\param [in] nSize число элементов в векторе
    \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 */
//! \{
void nmppsSqrt_32f(const nm32f* pSrcVec, nm32f* pDstVec, nm32f* pTmpBuf, int nSize);
//! \}

#ifdef __cplusplus
};
#endif

#endif // _SECARITM_H_INCLUDED_
