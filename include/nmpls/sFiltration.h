//------------------------------------------------------------------------
//
//  $Workfile:: sFiltrat $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file   vFilter.h
//! \author Сергей Мушкаев
//! \brief  Определение функций фильтраций для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#ifndef _SFILTRATION_H_INCLUDED_
#define _SFILTRATION_H_INCLUDED_

#include "nmtype.h"
  



    /**
    \internal
    \defgroup SIG_Median_V9 SIG_Median_V9
		\ingroup sFiltration
    */
    //! \{
int SIG_Median_V9(nm8s* pVec);
int SIG_Median_V9(nm16s* pVec);
int SIG_Median_V9(nm32s* pVec);
int64b SIG_Median_V9(nm64s* pVec);
    //! \}
    
//*****************************************************************************

	/**
	\defgroup nmppcMedian3_32u nmppcMedian3_32u
	\ingroup sFiltration
	\brief
		\ru Вычисление медианы трех чисел
		\en Calculation of median value of 3 numbers
		\~
	\~
	\param a
		\ru Первое число
		\en First number
		\~
	\param b
		\ru Второе число 
		\en Second number
		\~
	\param c
		\ru Третье число
		\en Third number
		\~
	\return 
		\ru Медианное значение
		\en Median value
		\~
    \par
    \xmlonly
        <testperf> 
             <param name="a"> 1 10 100 </param>
             <param name="b"> 8 128 1024 </param>
             <param name="c"> 16 512 10240 </param>
             <size> 1 </size>
        </testperf>
    \endxmlonly
	*/
    //! \{
int nmppcMedian3_32u(int a,int b, int c);
uint32b nmppcMedian3_32u(uint32b a, uint32b b, uint32b c);
    //! \}

#endif // _SFILTRATION_H_INCLUDED_

