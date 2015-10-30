//------------------------------------------------------------------------
//
//  $Workfile:: VecLogic.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2013/01/24 13:50:15 $
//
//! \if file_doc
//!
//! \file   VecOrNV.cpp
//! \author Сергей Мушкаев
//! \brief  Логические и бинарные функции для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmplv.h"
//void nmppsOrNV_64u(nm64u** pSrcVecs, int numVecs, nm64u* pDstVec, int nSize);
///////////////////////////////////////////////////////////
// pDstVec[i] = !pSrcVec[i]; 
void nmppsOr4V_64u(nm64u* pVec0, 
				nm64u* pVec1, 
				nm64u* pVec2, 
				nm64u* pVec3, 
				nm64u* pDstVec, 
				int 	nSize)
{


	for(int i=0; i<nSize; i++){
			pDstVec[i] = pVec0[i] | pVec1[i] | pVec2[i] | pVec3[i];
	}
		
	
}
///////////////////////////////////////////////////////////////////////////////
