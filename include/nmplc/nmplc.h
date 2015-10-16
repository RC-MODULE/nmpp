
#ifndef INCLUDED_nmplc
#define INCLUDED_nmplc

#include "nmtype.h"
#include "nmdef.h"



/*! \ru 
	\page intro Введение 
	\en 
	\page intro Introduction
	\~
    \ingroup SCL_Group

	\ru 
Назначением данной библиотеки является предоставление базовых операций по работе со скалярными данными для процессора NM6403, NM6404, NM6405. 

В состав библиотеки входят арифметические, тригонометрические функции, функции для работы с данными в формате с фиксированной точкой. 

Библиотека предназначена для быстрой разработки эффективных пользовательских программ на языке высокого уровня(С++). 
	\en
The purpose of the library is to support the base operations with image processing on NM6403, NM6404, NM6405 processors. Library contains two-dimensional filters, arithmetical operations with images, color conversions. The library is meant for fast development of effective user programs in a high level language using the advantages of this processor architecture. 

The library functions have a C++ interface. Most of the library functions are implemented in assembly language with using vector core instructions and optimized for the processor architecture. 

For convenience of application programs development the library has implementations of functions for processors of x86 series in C++. These implementations allow to execute application programs written by means of this library on a personal computer. 
	\~
*/


	/**
    *
    * \ru
    *     \defgroup cInit Инициализация
    * \en
    *     \defgroup cInit Initialization
	* \~
    * \ingroup SCL_Group
	*/

#include "cInit.h"


	/**
    *
    * \ru
    *     \defgroup cInteger Integer operations
    * \en
    *     \defgroup cInteger Integer operations
	* \~
    * \ingroup SCL_Group
	*/
#include "cInteger.h"

	/**
    *
    * \ru
    *     \defgroup cFixpoint64 Fix-point 64
    * \en
    *     \defgroup cFixpoint64 Fix-point 64
	* \~
    * \ingroup SCL_Group
	*/
#include "cfixpnt64.h"
	/**
    *
    * \ru
    *     \defgroup cFixpoint32 Fix-point 32
    * \en
    *     \defgroup cFixpoint32 Fix-point 32
	* \~
    * \ingroup SCL_Group
	*/
#include "cfixpnt32.h"

#include "cfixpnt64.h"
	/**
    *
    * \ru
    *     \defgroup cArithmetic Арифметические операции
    * \en
    *     \defgroup cArithmetic Arithmetic operation
	* \~
    * \ingroup SCL_Group
	*/
#include "cArithmetic.h"




#endif
