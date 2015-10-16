//------------------------------------------------------------------------
//
//  $Workfile:: vArithmeticsDev.h             $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.5 $      $Date: 2005/07/13 14:19:56 $
//
//------------------------------------------------------------------------

#ifndef _VARITHMETICSDEV_H_INCLUDED_
#define _VARITHMETICSDEV_H_INCLUDED_

	/**
	\internal
	\addtogroup VEC_AddV
	*/
	//! \{
void VEC_AddV(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize);
	//! \}

	/**
	\internal
	\addtogroup VEC_SubV
	*/
	//! \{
void VEC_SubV(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize);
	//! \}


	/**
	\internal
	\addtogroup VEC_MulC
	*/
	//! \{
void VEC_MulC(nm64sc *pSrcVec, nm64s *pnVal, nm64sc *pDstVec, int nSize);
	//! \}



#endif
