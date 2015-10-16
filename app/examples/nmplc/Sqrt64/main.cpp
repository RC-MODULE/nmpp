//------------------------------------------------------------------------
//
//  $Workfile:: main.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/24 15:48:59 $
//
//! \if file_doc
//!
//! \file   main.cpp
//! \author S. Mushkaev
//! \brief  Example of scalar library using
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmplc.h"
#include "time.h"
int main()
{
	clock_t t0,t1;

	t0=clock();
	// Conversion from double to fixed-point 64 format
	unsigned long x=64*64;
	unsigned long y;
	y=SCL_Sqrt64(x);
	
	t1=clock();

	
	return t1-t0;
}
