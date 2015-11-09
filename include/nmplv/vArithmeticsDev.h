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

#ifdef __cplusplus
		extern "C" {
#endif


	/**
	\internal
	\addtogroup nmppsAdd
	*/
	//! \{
void nmppsAdd_64sc(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize);
	//! \}

	/**
	\internal
	\addtogroup nmppsSub
	*/
	//! \{
void nmppsSub_64sc(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize);
	//! \}


	/**
	\internal
	\addtogroup nmppsMulC
	*/
	//! \{
void nmppsMulC_64sc(nm64sc *pSrcVec, nm64s *pnVal, nm64sc *pDstVec, int nSize);
	//! \}

#ifdef __cplusplus
		};
#endif


#endif
