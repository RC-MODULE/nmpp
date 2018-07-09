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
    \defgroup snmppsSin_32f nmppsSin_32f
    \ingroup sElementary
   	\brief Функция, вычисляющая синус над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)
    */
	/**
 *  \ingroup snmppsSin_32f 
	\brief Функция, вычисляющая синус над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)

	\param [in] pSrcVec входной вектор чисел с плавающей точкой
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой
	\param [in] nSize число элементов в векторе
 *  \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 * 
 */
void nmppsSin_32f(const nm32f* pSrcVec, nm32f* pDstVec, int nSize);

    /**
    \defgroup snmppsCos_32f nmppsCos_32f
    \ingroup sElementary
   	\brief Функция, вычисляющая косинус над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)
    */
	/**
 *  \ingroup snmppsCos_32f 
	\brief Функция, вычисляющая синус над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)

	\param [in] pSrcVec входной вектор чисел с плавающей точкой одинарной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой одинарной точности
	\param [in] nSize число элементов в векторе
 *  \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 * 
 */
void nmppsCos_32f(const nm32f* pSrcVec, nm32f* pDstVec, int nSize);

    /**
    \defgroup snmppsDiv_32f nmppsDiv_32f
    \ingroup sElementary
   	\brief Функция, вычисляющая x/y (pSrcVec1 / pSrcVec2), где x и y (делимые числа и делители) это вектора чисел с плавающей точкой одинарной точности
    */
	/**
 *  \ingroup snmppsDiv_32f 
	\brief Функция, вычисляющая x/y (pSrcVec1 / pSrcVec2), где x и y (делимые числа и делители) это вектора чисел с плавающей точкой одинарной точности

	\param [in] pSrcVec1 входной вектор делимых чисел с плавающей точкой одинарной точности
	\param [in] pSrcVec2 входной вектор делителей с плавающей точкой одинарной точности
	\retval [out] pDstVec выходной вектор частных с плавающей точкой одинарной точности
	\param [in] nSize число элементов в векторе
 *  \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 * 
 */
void nmppsDiv_32f(const nm32f *pSrcVec1, const nm32f *pSrcVec2, nm32f *pDstVec, int nSize);

    /**
    \defgroup snmppsExp_32f nmppsExp_32f
    \ingroup sElementary
   	\brief Функция, вычисляющая экспоненту над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)
    */
	/**
 *  \ingroup snmppsExp_32f 
	\brief Функция, вычисляющая экспоненту над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)

	\param [in] pSrcVec входной вектор чисел с плавающей точкой одинарной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой одинарной точности
	\param [in] nSize число элементов в векторе
 *  \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 * 
 */
void nmppsExp_32f(const nm32f *pSrcVec, nm32f *pDstVec, int nSize);

    /**
    \defgroup snmppsExp_64f nmppsExp_64f
    \ingroup sElementary
   	\brief Функция, вычисляющая экспоненту над каждым элементом вектора чисел с плавающей точкой двойной точности (64f)
    */
	/**
 *  \ingroup snmppsExp_64f 
	\brief Функция, вычисляющая экспоненту над каждым элементом вектора чисел с плавающей точкой двойной точности (64f)

	\param [in] pSrcVec входной вектор чисел с плавающей точкой двойной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой двойной точности
	\param [in] nSize число элементов в векторе
 *  \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 * 
 */
void nmppsExp_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize);

    /**
    \defgroup snmppsLog_32f nmppsLog_32f
    \ingroup sElementary
   	\brief Функция, вычисляющая логарифм над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)
    */
	/**
 *  \ingroup snmppsLog_32f 
	\brief Функция, вычисляющая логарифм над каждым элементом вектора чисел с плавающей точкой одинарной точности (32f)

	\param [in] pSrcVec входной вектор чисел с плавающей точкой одинарной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой одинарной точности
	\param [in] nSize число элементов в векторе
 *  \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 * 
 */
void nmppsLog_64f (const nm32f *pSrcVec, nm32f *pDstVec, int nSize);

    /**
    \defgroup snmppsLog_64f nmppsLog_64f
    \ingroup sElementary
   	\brief Функция, вычисляющая логарифм над каждым элементом вектора чисел с плавающей точкой двойной точности (64f)
    */
	/**
 *  \ingroup snmppsLog_64f 
	\brief Функция, вычисляющая логарифм над каждым элементом вектора чисел с плавающей точкой двойной точности (64f)

	\param [in] pSrcVec входной вектор чисел с плавающей точкой двойной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой двойной точности
	\param [in] nSize число элементов в векторе
 *  \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 * 
 */
void nmppsLog_64f(const nm64f *pSrcVec, nm64f *pDstVec, int nSize);

    /**
    \defgroup snmppsPowx_64f nmppsPowx_64f
    \ingroup sElementary
   	\brief Функция возводит в степень (Deg) каждый элемент вектора чисел с плавающей точкой двойной точности (64f)
    */
	/**
 *  \ingroup snmppsPowx_64f
	\brief Функция, вычисляющая логарифм над каждым элементом вектора чисел с плавающей точкой двойной точности (64f)

	\param [in] pSrcVec входной вектор чисел с плавающей точкой двойной точности
	\retval [out] pDstVec выходной вектор чисел с плавающей точкой двойной точности
	\param [in] Deg степень, в которую возводится каждый элемент входного вектора
	\param [in] nSize число элементов в векторе
 *  \details Функция совместима ТОЛЬКО с NMC-GCC-SDK и входит в состав библиотеки libnmpp-nmc4f.a
 * 
 */
void nmppsPowx_64f(const nm64f *pSrcVec, nm64f *pDstVec, nm32u Deg, int nSize);

#ifdef __cplusplus
};
#endif

#endif // _SECARITM_H_INCLUDED_