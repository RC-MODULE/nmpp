//------------------------------------------------------------------------
//
//  $Workfile:: main.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.3 $      $Date: 2005/06/27 14:33:52 $
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
	// Conversion from double to fixed-point 32 format
	int fixp32  ;
	fixp32=SCL_DoubleToFix32(0.25);
	fixp32=SCL_DoubleToFix32(0.33);
	fixp32=SCL_DoubleToFix32(0.5);
	fixp32=SCL_DoubleToFix32(0.99);
	fixp32=SCL_DoubleToFix32(1.0);
	fixp32=SCL_DoubleToFix32(1.0);
	// Conversion from fixed-point 32 format to double
	x=SCL_Fix32ToDouble(fixp32);
	// Calculation square root
	int z;
	z=SCL_FixSqrt32(fixp32);
	z=SCL_FixSqrt32(fixp32*4);
	// Calculation of exponent 
	z=SCL_FixExp32(fixp32);
	z=SCL_FixExp32(fixp32*4);
	// Calculation of sin& cos
	int sin;
	int cos;
	SCL_FixSinCos32(fixp32,&sin,&cos);
	// Calculation of arctangent
	fixp32/=2;
	z= SCL_FixArcTan32(fixp32);
	// Multipliation of two fixed point numbers
	int i=0x20000;
	int j=0x30000;
	z=SCL_FixMul32(i,j);
	// Division of two integer numbers with retrun in fixed-point format (16.16)
	z=SCL_FixDiv32(j,i);
	z=SCL_FixDiv32(i,j);
	// 
	z=SCL_FixInv32(0x1,0);
	z=SCL_FixInv32(0x1,1);
	z=SCL_FixInv32(0x1,16);
	z=SCL_FixInv32(0x2,16);
	z=SCL_FixInv32(0x1000,16);
	z=SCL_FixInv32(0x2000,16);
	z=SCL_FixInv32(0x3000,16);

	// Table functions
	int nArg=0x8000;
	//nArg=-nArg;
	z=SCL_TblFixArcCos32(nArg);
	z=SCL_TblFixArcSin32(nArg);
	z=SCL_TblFixCos32(nArg*2);
	z=SCL_TblFixSin32(nArg);
	//z=SCL_TblFixTan32(nArg);
	
	int nQ;
	int nR;
	SCL_FixDivMod32(0x50000,0x20000,&nQ,&nR);
	SCL_FixDivMod32(0x50000,0x30000,&nQ,&nR);
	SCL_FixDivMod32(0x50000,0x40000,&nQ,&nR);
	SCL_FixDivMod32(0x50000,0x50000,&nQ,&nR);
	SCL_FixDivMod32(0x50000,0x60000,&nQ,&nR);
	SCL_FixDivMod32(0x50000,0x70000,&nQ,&nR);
	
	SCL_FixDivPosMod32(0x50000,0x20000,&nQ,&nR);
	SCL_FixDivPosMod32(0x50000,0x30000,&nQ,&nR);
	SCL_FixDivPosMod32(0x50000,0x40000,&nQ,&nR);
	SCL_FixDivPosMod32(0x50000,0x50000,&nQ,&nR);
	SCL_FixDivPosMod32(~0x50000,0x60000,&nQ,&nR);
	SCL_FixDivPosMod32(~0x50000,0x70000,&nQ,&nR);
	
	nm64sc nSrcA;
	nm64s nSrcB;
	nm64sc nDst;
	SCL_DivC(&nSrcA, &nSrcB, &nDst);

	t1=clock();

	return t1-t0;
}
