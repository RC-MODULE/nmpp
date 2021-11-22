
#ifndef INCLUDED_nmplv
#define INCLUDED_nmplv









//-----------------------------------------------------------

/*! \ru
	\page intro Введение
	\en
	\page intro Introduction
	\~
	\ingroup nmppsGroup_
	\ru
Назначением данной библиотеки является предоставление базовых операций по обработке одномерных массивов (векторов) для процессоров NM6405,NM6406, систем на кристале с ядром NMC.

В состав библиотеки входят логические и арифметические функции, операции сравнения, инициализации, копирования, преобразования разрядностей и т.п. Библиотека предназначена для быстрой разработки эффективных пользовательских программ как на языке высокого уровня(С++), так и на языке ассемблера с помощью прилагаемой библиотеки ядра низкоурвневых функций.  Функции библиотеки имеют C++ интерфейс.

Большинство функций библиотеки реализованы на языке ассемблера с использованием векторных инструкций и оптимизированы под архитектуру процессоров NMC.  Для удобства разработки прикладных программ библиотека содержит аналогичные реализации функций для процессоров серии x86, выполненных на языке С++. Данные реализации позволяют выполнять написанные с использованием данной библиотеки прикладные программы на персональном компьютере.
	\en
The purpose of the library is to support the base operations for vector processing on NM6403,NM6404,NM6405 processor. The library сontains logical and arithmetical functions, operations of comparision, initialization, copying, datа conversion and so on. The library is meant for fast development of effective user programs as in a high level language(С++) as in assembly language using supported core low-level routines.

The library functions have a C++ interface. Most of the library functions are implemented in assembly language with using vector core instructions and optimized for the processor architecture.

For convenience of application programs development the library has implementations of functions for processors of x86 series in C++. These implementations allow to execute application programs written by means of this library on a personal computer.
	\~
*/
//-------------------------------------------------------------


#include "nmtype.h"
#include "nmdef.h"


//-------------------------------------------------------------

/*! \ru
	\defgroup nmvectype Типы векторных данных
	\en
	\defgroup nmvectype Vector data types
	\~
	\ingroup TYPE_Group
	\ru
В данном разделе описываются  типы  векторных данных с которыми  могут работать функции библиотеки, задействующие векторный узел.
Также  рассматриваюся соглашения о передаче параметров.\n

Поскольку векторный узел работает с  данными произвольной разрядности, упакованными в 64-разрядные слова,
то это накладывает следующие ограничения на работу с  массивами данных и их типами: \n
1. Указатель на векторные данные всегда являтся четным адресом. Т.е. выровнен в памяти по границе 64р. слов. \n
2. Размер массива, передаваемый на вход функций, как правило, исчисляется в отдельных элементах, составляющих этот массив.  \n
   Кратность этого размера по умолчанию  определяется кол-вом чисел, упакованных в 64р. слово. \n
   Например: \n
   для nm8s  кратность-8 \n
   для nm16s кратность-4 \n
   для nm32s кратность-2 \n
   для nm64s кратность-1 \n
   Если в описании указаны другие условия крaтности, как например [32,64,96,128...], то это означает, что допустимые размеры могут только из этого диапазона с кратностью 32.\n
3. Типы nm8s , nm16s, nm32s... хоть и созданы для обозначания разрядности упакованных данных, но с точки зрения С++ таковыми не являются ,
   так как определяются через typedef как производные от стандартных типов char, short и  int, которые все три в свою очередь  являются 32-разрядными типами в архитектуре NeuroMatrix.
   Поэтому эти векторные типы можно использовать только с оператором *  (nm8s*,nm16s*,... ). Операции  же sizeof() к массивам этих типов будут выполянться некорректно.

\n
Расшифровка мнемоники в названии типа:   \n
1. Префикс nm - означет что данные являются векторными ,упакованными в 64р слова (nm8s,nm8u,nm16s.... ).\n
2. Разрядность данных указывается после префикса nm (nm8s,nm8u - байтовые массивы, nm16s,nm16u - 16р. массивы ).\n
3. суфикс s или u оначает знаковый или беззнаковый тип данных. \n
4. Для работы некоторых функций во избежании переполнения требуется суженный диапазон возможных значений, чем позволяет разрядность.
   Такие даные имеют суффикс в виде кол-ва значащих бит в слове и символом b. (nm8s7b) \n
	\en
	\~
*/




//-------------------------------------------------------------

/*! \ru
	\defgroup nmtype Типы скалярных данных
	\en
	\defgroup nmtype Scalar data types
	\~
	\ingroup TYPE_Group
	\ru
Назначением данной библиотеки является предоставление базовых операций по обработке одномерных массивов (векторов) для процессоров семейства NeroMatrix.

В состав библиотеки входят логические и арифметические функции, операции сравнения, инициализации, копирования, преобразования разрядностей и т.п. Библиотека предназначена для быстрой разработки эффективных пользовательских программ как на языке высокого уровня(С++), так и на языке ассемблера с помощью прилагаемой библиотеки ядра низкоурвневых функций.  Функции библиотеки имеют C++ интерфейс.

Большинство функций библиотеки реализованы на языке ассемблера с использованием векторных инструкций и оптимизированы под архитектуру процессоров семейства NeuroMatrix.  Для удобства разработки прикладных программ библиотека содержит аналогичные реализации функций для процессоров серии x86, выполненных на языке С++. Данные реализации позволяют выполнять написанные с использованием данной библиотеки прикладные программы на персональном компьютере.
	\en
The purpose of the library is to support the base operations for vector processing on NM6403,NM6404,NM6405 processor. The library сontains logical and arithmetical functions, operations of comparision, initialization, copying, datа conversion and so on. The library is meant for fast development of effective user programs as in a high level language(С++) as in assembly language using supported core low-level routines.

The library functions have a C++ interface. Most of the library functions are implemented in assembly language with using vector core instructions and optimized for the processor architecture.

For convenience of application programs development the library has implementations of functions for processors of x86 series in C++. These implementations allow to execute application programs written by means of this library on a personal computer.
	\~
*/



//*****************************************************************************

	/**
    *
    *
    * \ru
	*	\defgroup vSupport  Функции поддержки
    * \en
    *   \defgroup vSupport Support functions
	* \~
    * \ingroup nmppsGroup_
	*/

#include "vSupport.h"

//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup vInit Инициализация и копирование
    * \en
    *     \defgroup vInit Initialization and copy
    * \~
    * \ingroup nmppsGroup_
	*/

	/**
	*
	* \ru
	*     \defgroup vInit_f Инициализация и копирование
	* \en
	*     \defgroup vInit_f Initialization and copy
	* \~
	* \ingroup nmppsGroup_f
	*/


#include "vInit.h"


//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup vArithmetics Арифметические операции
    * \en
    *     \defgroup vArithmetics Arithmetic functions
    * \~
    * \ingroup nmppsGroup_
	*/

	/**
    *
    * \ru
    *     \defgroup vArithmetics_f Арифметические операции
    * \en
    *     \defgroup vArithmetics_f Arithmetic functions
    * \~
    * \ingroup nmppsGroup_f
	*/

#include "vArithmetics.h"
#include "vArithmeticsDev.h"


//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup vBitwise Логические и бинарные операции
    * \en
    *     \defgroup vBitwise Logical and binary operations
    * \~
    * \ingroup nmppsGroup_
	*/


#include "vBitwise.h"

//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup vSelect Операции сравнения
    * \en
    *     \defgroup vSelect Comparision operations
    * \~
    * \ingroup nmppsGroup_
	*/

	/**
	*
	* \ru
	*     \defgroup vSelect_f Операции сравнения
	* \en
	*     \defgroup vSelect_f Comparision operations
	* \~
	* \ingroup nmppsGroup_f
	*/

#include "vSelect.h"

//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup vStat Статистические функции
    * \en
    *     \defgroup vStat Statistical functions
    * \~
	* \ingroup nmppsGroup_
	*/

#include "vStat.h"

//*****************************************************************************

	/**
    *
    * \ru
    *     \defgroup vTransform Переупорядочивание и сортировка
    * \en
    *     \defgroup vTransform Sort and transformation
    * \~
    *  \ingroup nmppsGroup_
	*/

#include "vTransform.h"

//*****************************************************************************

    /**
    *
    * \ru
    *     \defgroup Elementary_f Элементарные математические функции
    * \en
    *     \defgroup Elementary_f Elementary mathematical functions
    * \~
    * \ingroup nmppsGroup_f
    */
#include "sElementary.h"

#endif
