
#ifndef INCLUDED_nmpli
#define INCLUDED_nmpli

#include "nmtype.h"
#include "nmdef.h"
#include "nmpp.h"
#include "iDef.h"

#include "warpimg.h"
/*! \ru 
	\page intro Введение 
	\en 
	\page intro Introduction
	\~
    \ingroup IMG_Group
	
	\ru 
Назначением данной библиотеки является предоставление базовых операций обработки изображений для процессора NM6403, NM6404, NM6405. В состав библиотеки входят функции двумерной фильтрации, арифметические действия и цветовые преобразования. Библиотека предназначена для быстрой разработки эффективных пользовательских программ на языке высокого уровня с использованием преимуществ архитектуры данного процессора. 

Функции библиотеки имеют C++ интерфейс. Большинство функций библиотеки реализованы на языке ассемблера с использованием векторных инструкций и оптимизированы под архитектуру процессора NM6403. 

Для удобства разработки прикладных программ библиотека содержит аналогичные реализации функций для процессоров серии x86, выполненных на языке С++. Данные реализации позволяют выполнять написанные с использованием данной библиотеки прикладные программы на персональном компьютере. 
	\en
The purpose of the library is to support the base operations with image processing for NM6403, NM6404, NM6405 processor. Library contains two-dimensional filters, arithmetical operations with images, color conversions. The library is meant for fast development of effective user programs in a high level language using the advantages of this processor architecture. 

The library functions have a C++ interface. Most of the library functions are implemented in assembly language with using vector core instructions and optimized for the processor architecture. 

For convenience of application programs development the library has implementations of functions for processors of x86 series in C++. These implementations allow to execute application programs written by means of this library on a personal computer. 
	\~
*/


//*****************************************************************************

    /**
    * \ru
    *     \defgroup iArithmetics Арифметические действия
    * \en
    *     \defgroup iArithmetics Arithmetics
    * \~
    * \ingroup IMG_Group
    */
#include "iArithmetics.h"

//*****************************************************************************

	/** 
    * \ru
    *     \defgroup iFiltration Масочная фильтрация
    * \en
    *     \defgroup iFiltration Mask filtration
     * \~
    * \ingroup IMG_Group
    */
#include "iFiltration.h"
//*****************************************************************************

    /**
    * \ru
    *     \defgroup iInit Инициализация и копирование 
    * \en
    *     \defgroup iInit Initialization and copy
    * \~
    * \ingroup IMG_Group
    */

#include "iInit.h"
//*****************************************************************************

    /*
	\internal
    * \ru
    *     \defgroup iResample Изменение размеров
    * \en
    *     \defgroup iResample Resampling
    * \~
    * \ingroup IMG_Group
    */

#include "iResample.h"
//*****************************************************************************

    /*
	\internal
    * \ru
    *     \defgroup iSelect Операции выборки
    * \en
    *     \defgroup iSelect Select operations
    * \~
    * \ingroup IMG_Group
    */

#include "iSelect.h"

//*****************************************************************************

	/**
	* \ru 
	* 	\defgroup iSupport Функции поддержки 
	* \en
	*     \defgroup iSupport Support functions 
    * \~
    * \ingroup IMG_Group
	*/
#include "iSupport.h"

#include "iFloodFill.h"

#include "iCellTexture.h"

#include "iDeinterlace.h"

#include "iReodering.h"

//*****************************************************************************

	/**
	* \ru 
	* 	\defgroup IMG_Print Функции графического вывода текста 
	* \en
	*	\defgroup IMG_Print Graphic print functions
    * \~
    * \ingroup IMG_Group
	*/
#include "iPrint.h"

#include "filter.h"

#endif
