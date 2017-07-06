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

	double x=0.5;

	t0=clock();
	// Conversion from double to fixed-point 64 format
	long fixp64  ;
	fixp64=nmppcDoubleToFix64(0.25,32);
	fixp64=nmppcDoubleToFix64(0.33,32);
	fixp64=nmppcDoubleToFix64(0.5,32);
	fixp64=nmppcDoubleToFix64(0.99,32);
	fixp64=nmppcDoubleToFix64(1.0,32);
	fixp64=nmppcDoubleToFix64(1.0,34);
	// Conversion from fixed-point 64 format to double
	x=nmppcFix64ToDouble(fixp64,34);
	// Division of two numbers
	long nDividend=64;
	long nDivisor=128;
	long nQuotient;
	nmppcFixDiv64(&nDividend,	&nDivisor, 32, &nQuotient);
	// Calculation sin & cos in fixedpoint format 32.32
	long nSin;
	long nCos;
	long nArg=0x80000000; // (0.5) 
	nmppcFixSinCos64(nArg,&nSin,&nCos);
	// Calculation of arctan in fixedpoint format 32.32
	long nArctan= nmppcFixArcTan64(nArg);
	
	nArg=0x1l<<60;
	long e=nmppcFix64Exp01(nArg);
	
	double d=1.333;
	e=nmppcFrExp(d);
	t1=clock();
	
	
	return t1-t0;
}
