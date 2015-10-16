#ifndef _CARITHMETIC_H_INCLUDED_
#define _CARITHMETIC_H_INCLUDED_

#include "nmtype.h"



	/**
	\defgroup SCL_DivC SCL_DivC
	\ingroup <cArithmetic>
	\brief
		\ru частное двух комплексных чисел
		\en

	\~
	\param *pnSrcA
		\ru указатель на делимое.
		\en
	\param *pnSrcB
		\ru указатель на делитель.
		\en
	\param *Dst
		\ru указатель на частное.
		\en
	*/
	//! \{	
void SCL_DivC(nm64sc *pnSrcA, nm64s *pnSrcB, nm64sc *Dst);
    //! \}

	/**
	\defgroup SCL_ProdC SCL_ProdC
	\ingroup cArithmetic
	\brief
		\ru произведение двух комплексных чисел.
		\en

	\~
	\param *pnSrcA
		\ru указатель на первый множитель.
		\en
	\param *pnSrcB
		\ru указатель на второй множитель.
		\en
	\param *Dst
		\ru указатель на произведение.
		\en
	*/
//! \{	
void SCL_ProdC(nm64sc *pnSrcA, nm64sc *pnSrcB, nm64sc *Dst);//ASM
//! \}

#endif
