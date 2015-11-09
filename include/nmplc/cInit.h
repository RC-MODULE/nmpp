//------------------------------------------------------------------------
//
//  $Workfile:: cInit. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:01:21 $
//
//! \if file_doc
//!
//! \file   cInit.h
//! \author Сергей Мушкаев
//! \brief  Определение функций инициализации для скаляров.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef _CINIT_H_INCLUDED_
#define _CINIT_H_INCLUDED_

//*****************************************************************************

//*****************************************************************************

    /**
    \defgroup nmppsRand nmppsRand
    \ingroup cInit
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
int nmppcRand(int nMin, int nMax, int nDivisible);
int nmppcRand(int nMin, int nMax);
int nmppcRand();
    //! \}


#endif // _CINIT_H_INCLUDED_