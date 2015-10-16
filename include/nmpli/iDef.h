//------------------------------------------------------------------------
//
//  $Workfile:: C_Frame.h             $
//
//  FRC Library component
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:38 $
//
//! \if file_doc
//!
//! \file   C_Frame.h
//! \author S. Mushkaev
//! \brief  C_Frame class definition
//!
//! \endif
//!
//------------------------------------------------------------------------

#ifndef _IDEF_H_
#define _IDEF_H_

struct RGB24_nm8u
{
	nm8u nB;
	nm8u nG;
	nm8u nR;
};


struct RGB32_nm8u
{
	unsigned int nB:8;
	unsigned int nG:8;
	unsigned int nR:8;
	unsigned int nA:8;
};

struct RGB32_nm8s
{
	int nB:8;
	int nG:8;
	int nR:8;
	int nA:8;
};

struct RGB32_nm10u
{
	unsigned int nB:10;
	unsigned int nG:10;
	unsigned int nR:10;
	unsigned int nA:2;
};

struct RGB32_nm10s
{
	int nB:10;
	int nG:10;
	int nR:10;
	int nA:2;
};

struct RGB64_nm16u
{
	unsigned int nB:16;
	unsigned int nG:16;
	unsigned int nR:16;
	unsigned int nA:16;
};

#endif
