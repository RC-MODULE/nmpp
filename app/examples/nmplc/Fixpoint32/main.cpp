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
	fixp32=nmppcDoubleToFix32(0.25);
	fixp32=nmppcDoubleToFix32(0.33);
	fixp32=nmppcDoubleToFix32(0.5);
	fixp32=nmppcDoubleToFix32(0.99);
	fixp32=nmppcDoubleToFix32(1.0);
	fixp32=nmppcDoubleToFix32(1.0);
	// Conversion from fixed-point 32 format to double
	x=nmppcFix32ToDouble(fixp32);
	// Calculation square root
	int z;
	z=nmppcFixSqrt32(fixp32);
	z=nmppcFixSqrt32(fixp32*4);
	// Calculation of exponent 
	z=nmppcFixExp32(fixp32);
	z=nmppcFixExp32(fixp32*4);
	// Calculation of sin& cos
	int sin;
	int cos;
	nmppcFixSinCos32(fixp32,&sin,&cos);
	// Calculation of arctangent
	fixp32/=2;
	z= nmppcFixArcTan32(fixp32);
	// Multipliation of two fixed point numbers
	int i=0x20000;
	int j=0x30000;
	z=nmppcFixMul32(i,j);
	// Division of two integer numbers with retrun in fixed-point format (16.16)
	z=nmppcFixDiv32(j,i);
	z=nmppcFixDiv32(i,j);
	// 
	z=nmppcFixInv32(0x1,0);
	z=nmppcFixInv32(0x1,1);
	z=nmppcFixInv32(0x1,16);
	z=nmppcFixInv32(0x2,16);
	z=nmppcFixInv32(0x1000,16);
	z=nmppcFixInv32(0x2000,16);
	z=nmppcFixInv32(0x3000,16);

	// Table functions
	int nArg=0x8000;
	//nArg=-nArg;
	z=nmppcTblFixArcCos32(nArg);
	z=nmppcTblFixArcSin32(nArg);
	z=nmppcTblFixCos32(nArg*2);
	z=nmppcTblFixSin32(nArg);
	//z=nmppcTblFixTan32(nArg);
	
	int nQ;
	int nR;
	nmppcFixDivMod32(0x50000,0x20000,&nQ,&nR);
	nmppcFixDivMod32(0x50000,0x30000,&nQ,&nR);
	nmppcFixDivMod32(0x50000,0x40000,&nQ,&nR);
	nmppcFixDivMod32(0x50000,0x50000,&nQ,&nR);
	nmppcFixDivMod32(0x50000,0x60000,&nQ,&nR);
	nmppcFixDivMod32(0x50000,0x70000,&nQ,&nR);
	
	nmppcFixDivPosMod32(0x50000,0x20000,&nQ,&nR);
	nmppcFixDivPosMod32(0x50000,0x30000,&nQ,&nR);
	nmppcFixDivPosMod32(0x50000,0x40000,&nQ,&nR);
	nmppcFixDivPosMod32(0x50000,0x50000,&nQ,&nR);
	nmppcFixDivPosMod32(~0x50000,0x60000,&nQ,&nR);
	nmppcFixDivPosMod32(~0x50000,0x70000,&nQ,&nR);
	
	nm64sc nSrcA;
	nm64s nSrcB;
	nm64sc nDst;
	nmppcDivC(&nSrcA, &nSrcB, &nDst);

	t1=clock();

	return t1-t0;
}
