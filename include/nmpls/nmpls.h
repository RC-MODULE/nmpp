
#ifndef INCLUDED_nmpls
#define INCLUDED_nmpls

//#include "nmtype.h"
//#include "nmdef.h"
//#include "nmpp.h"
#include "sfir.h"

/*! \ru 
	\page intro Введение 
	\en 
	\page intro Introduction
	\~
	\ingroup SIG_Group
	\ru 
Назначением данной библиотеки является предоставление базовых функций по обработке сигналов  для процессоров NM6403,NM6404,NM6405. В состав библиотеки входят функции одномерной КИХ фильтрации, нелинейной фильтрации, передискретизации. Библиотека предназначена для быстрой разработки эффективных пользовательских программ как на языке высокого уровня(С++). 

Функции библиотеки имеют C++ интерфейс. Большинство функций библиотеки реализованы на языке ассемблера с использованием векторных инструкций и оптимизированы под архитектуру процессоров NM6403. 

Для удобства разработки прикладных программ библиотека содержит аналогичные реализации функций для процессоров серии x86, выполненных на языке С++. Данные реализации позволяют выполнять написанные с использованием данной библиотеки прикладные программы на персональном компьютере. 
	\en
The purpose of the library is to support the base functions for signal processing on  NM6403,NM6404,NM6405 processors. The library сontains FIR-filters, non-linear filters and resampling functions. The library is meant for fast development of effective user programs in a high level language(С++). 

The library functions have a C++ interface. Most of the library functions are implemented in assembly language with using vector core instructions and optimized for the processor architecture. 

For convenience of application programs development the library has implementations of functions for processors of x86 series in C++. These implementations allow to execute application programs written by means of this library on a personal computer. 
	\~
*/


//*****************************************************************************


	/**
    *
    * \ru
    *     	\defgroup sConvolution Свертка
    * \en
    *     	\defgroup sConvolution Convolution
    * \~
	* \ingroup SIG_Group
	*/

#include "sCorrelation.h"
//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup sFiltration Масочная фильтрация
    * \en
    *     \defgroup sFiltration Mask filtration
    * \~
	* \ingroup SIG_Group
	*/

//#include "sFiltration.h"


//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup sResample Изменение размеров
    * \en
    *     \defgroup sResample Resample
    * \~
	* \ingroup SIG_Group
	*/

#include "sResample.h"

//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup sFFT_32fcr Быстрое преобразование Фурье
    * \en
    *     \defgroup sFFT_32fcr Fast Fourier Trasform
    * \~
	* \ingroup SIG_Group
	*/

#include "fft.h"

//*****************************************************************************

    /**
    *
    * \ru
    *     \defgroup sElementary Элементарные математические функции
    * \en
    *     \defgroup sElementary Elementary mathematical functions
    * \~
    * \ingroup nmppsGroup_
    */
#include "sElementary.h"

#endif


