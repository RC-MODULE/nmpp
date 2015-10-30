//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*  (C-callable functions)                                                 */
//*                                                                         */
//*  $Workfile:: FFText.h                                                  $*/
//*  Contents:         Header file of FFT extended routines                 */
//*                                                                         */
//*                                                                         */
//*  Author:     S.Mushkaev                                                 */
//*                                                                         */
//*  Version         1.0                                                    */
//*  Start    Date:  03.07.2001                                             */
//*  Release $Date: 2005/02/10 11:47:59 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/

// LIBRARY  pcfft.lib


//#########################################################################################
// The functions declared below are used for modeling and researching FFT calculations on PC
// using fixed and floating-point arithmetic on PC. 
#ifndef _FFTEXT_H_INCLUDED_
#define _FFTEXT_H_INCLUDED_

#define FFT7BIT 1
#define FFT6BIT 2

#ifndef __NM__

#include "nmtl.h"
#include "nmtype.h"
#include "crtdbg2.h"



class Cplx_float
{
public:
	double Re;
	double Im;
} ;

class Wi_4096_fixed
{
public:
	char Re;
	char Im;
} ;



//********************************************************************
///////////////////////////////////////////////////////////////////
// Computing FFT-256 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd256 Assembly Code
int FFT_Fwd256(
			vec<cmplx<int> >	&X,
			vec<cmplx<int> >	&Y,
			vec<cmplx<char> >	&W1_256, 
			vec<cmplx<char> >	&W2_256,
			int							Shr1,
			int							Shr2
			);
///////////////////////////////////////////////////////////////////
// Computing FFT-256 using floating-point arithmetic
int FFT256(
			vec<cmplx<double> >		&X,		// Source buffer :long[256]
			vec<cmplx<double> >		&Y		// Result FFT    :long[256]
			);
/////////////////////////////////////////////////////////////////////
//	 Initialization FFT table of char coefficients 
void MakeTable256W1W2(
			vec<cmplx<char> >	&W1_256,
			vec<cmplx<char> >	&W2_256,
			double	Ampl
			);

//********************************************************************
///////////////////////////////////////////////////////////////////
// Computing FFT-1024 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd512 Assembly Code
int FFT_Fwd512(
			vec<cmplx<int> >	&X,		// input array
			vec<cmplx<int> >	&Y,		// output array
			vec<cmplx<char> >	&W1_512,	// table of coefficients
			vec<cmplx<char> >	&W2_512,	// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			);
///////////////////////////////////////////////////////////////////
// Computing FFT-512 using floating-point arithmetic
int FFT512(
			vec<cmplx<double> >		&X,		// Source buffer :long[512]
			vec<cmplx<double> >		&Y		// Result FFT    :long[512]
			);
/////////////////////////////////////////////////////////////////////
//	 Initialization FFT table of char coefficients 
void MakeTable512W1W2(
			vec<cmplx<char> >	&W1_512,
			vec<cmplx<char> >	&W2_512,
			double Ampl
			);
//********************************************************************
///////////////////////////////////////////////////////////////////
// Computing FFT-1024 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd1024 Assembly Code
int FFT_Fwd1024(
			vec<cmplx<int> >	&X,		// input array
			vec<cmplx<int> >	&Y,		// output array
			vec<cmplx<char> >	&W1_1024,// table of coefficients
			vec<cmplx<char> >	&W2_1024,// table of coefficients
			int Shr1,						// 1-st shiftr normalization
			int Shr2						// 2-nd shiftr normalization
			);
///////////////////////////////////////////////////////////////////
// Computing FFT-1024 using floating-point arithmetic
int FFT1024(
			vec<cmplx<double> >		&X,		// Source buffer :long[1024]
			vec<cmplx<double> >		&Y		// Result FFT    :long[1024]
			);
/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void MakeTable1024W1W2(
			vec<cmplx<char> >	&W1_1024,
			vec<cmplx<char> >	&W2_1024,
			double Ampl
			);
//********************************************************************
///////////////////////////////////////////////////////////////////
// Computing FFT-2048 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd2048 Assembly Code
int FFT_Fwd2048(
			vec<cmplx<int> >	&X,		// input array
			vec<cmplx<int> >	&Y,		// output array
			vec<cmplx<char> >	&W1_2048,// table of coefficients
			vec<cmplx<char> >	&W2_2048,// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			);
///////////////////////////////////////////////////////////////////
// Computing FFT-2048 using floating-point arithmetic
int FFT2048(
			vec<cmplx<double> >		&X,		// Source buffer :long[1024]
			vec<cmplx<double> >		&Y		// Result FFT    :long[1024]
		);
/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void MakeTable2048W1W2(
			vec<cmplx<char> >	&W1_2048,
			vec<cmplx<char> >	&W2_2048,
			double Ampl
			);
//********************************************************************
///////////////////////////////////////////////////////////////////
// Computing FFT-4096 using floating-point arithmetic
void FFT_Fwd4096_float1(
			Cplx_float *X,	// Source buffer :long[4096]
			Cplx_float *Y	// Result FFT    :long[4096]
			);
//********************************************************************
/////////////////////////////////////////////////////////////////////
// Computing IFFT-256 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd256 Assembly Code
int FFT_Inv256(
			vec<cmplx<int> > &X,
			vec<cmplx<int> > &Y,
			vec<cmplx<char> >  &IW1_256,
			vec<cmplx<char> >  &IW2_256,	
			int Shr1,
			int Shr2
			);
///////////////////////////////////////////////////////////////////
// Computing IFFT-256 using floating-point arithmetic
int IFFT256(
			vec<cmplx<double> >		&X,	// Source buffer :long[256]
			vec<cmplx<double> >		&Y	// Result FFT    :long[256]
			);
/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void IMakeTable256W1W2(
			vec<cmplx<char> >	&IW1_256,
			vec<cmplx<char> >	&IW2_256,
			double	Ampl
			);
//********************************************************************
///////////////////////////////////////////////////////////////////
// Computing IFFT-512 using fixed-point arithmetic
// This is the C equivalent of the FFT_Inv512 Assembly Code
int FFT_Inv512(
			vec<cmplx<int> >	&X,		// input array
			vec<cmplx<int> >	&Y,		// output array
			vec<cmplx<char> >	&IW1_512,	// table of coefficients
			vec<cmplx<char> >	&IW2_512,	// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			);
///////////////////////////////////////////////////////////////////
// Computing FFT-512 using floating-point arithmetic
int IFFT512(
			vec<cmplx<double> >		&X,	// Source buffer :long[512]
			vec<cmplx<double> >		&Y	// Result IFFT    :long[512]
			);
/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void IMakeTable512W1W2(
			vec<cmplx<char> >	&IW1_512,
			vec<cmplx<char> >	&IW2_512,
			double Ampl
			);
//********************************************************************
///////////////////////////////////////////////////////////////////
// Computing FFT-1024 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd1024 Assembly Code
int FFT_Inv1024(
			vec<cmplx<int> >	&X,		// input array
			vec<cmplx<int> >	&Y,		// output array
			vec<cmplx<char> >	&IW1_1024,// table of coefficients
			vec<cmplx<char> >	&IW2_1024,	// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			);
///////////////////////////////////////////////////////////////////
// Computing IFFT-1024 using floating-point arithmetic
int IFFT1024(
			vec<cmplx<double> >		&X,	// Source buffer :long[1024]
			vec<cmplx<double> >		&Y	// Result IFFT    :long[1024]
			);
/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void IMakeTable1024W1W2(
			vec<cmplx<char> >	&IW1_1024,
			vec<cmplx<char> >	&IW2_1024,
			double Ampl);
//********************************************************************

///////////////////////////////////////////////////////////////////
// Computing IFFT-2048 using fixed-point arithmetic
// This is the C equivalent of the FFT_Inv2048 Assembly Code
int FFT_Inv2048(
			vec<cmplx<int> >	&X,			// input array
			vec<cmplx<int> >	&Y,			// output array
			vec<cmplx<char> >	&IW1_2048,	// table of coefficients
			vec<cmplx<char> >	&IW2_2048,	// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			);
///////////////////////////////////////////////////////////////////
// Computing IFFT-2048 using floating-point arithmetic
int IFFT2048(
			vec<cmplx<double> >		&X,	// Source buffer :long[1024]
			vec<cmplx<double> >		&Y	// Result IFFT    :long[1024]
			);
/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void IMakeTable2048W1W2(
			vec<cmplx<char> >	&IW1_2048,
			vec<cmplx<char> >	&IW2_2048,
			double Ampl
			);
//********************************************************************
///////////////////////////////////////////////////////////////////
// Computing IFFT-4096 using floating-point arithmetic
void FFT_Inv4096_float1(
			Cplx_float *X,	// Source buffer :long[4096]
			Cplx_float *Y	// Result IFFT   :long[4096]
			);
//********************************************************************
//  Radix-2 FFT-256 Functions

// Computing IFFT-256 using floating-point arithmetic by radix-2 method
int IFFT256_radix2(
			vec<cmplx<double> >		&X,	// Source buffer 
			vec<cmplx<double> >		&Y	// Result IFFT   
			);
// Computing FFT-256 using floating-point arithmetic by radix-2 method
int FFT256_radix2(
			vec<cmplx<double> >		&X,	// Source buffer :long[256]
			vec<cmplx<double> >		&Y	// Result FFT    :long[256]
			);
// Computing FFT-256 using fixed-point arithmetic by radix-2 method
int FFT256_int_radix2(
			vec<cmplx<int> >	&X,
			vec<cmplx<int> >	&Y);
// Computing FFT-256 using fixed-point arithmetic by radix-2 method
int IFFT256_int_radix2(
			vec<cmplx<int> >	&X,
			vec<cmplx<int> >	&Y
			);


__INLINE__ void CmplxPack8to64(
							vec<cmplx<char> > &W,
							vec<nmint64s > &WRePacked,
							vec<nmint64s > &WImPacked)
{
	ASSERTE(W.size==WRePacked.size*8);
	ASSERTE(W.size==WImPacked.size*8);

	__int64 PackageIm=0,PackageRe=0;
	__int64 ByteMask=0xFF;
	for(int i=0,k=0;i<WRePacked.size;i++,k+=8)
	{
		for(int j=7;j>=0;j--)
		{
			PackageRe<<=8;
			PackageRe=PackageRe|(W[k+j].re& ByteMask);

			PackageIm<<=8;
			PackageIm=PackageIm|(W[k+j].im& ByteMask);
		}
		WRePacked[i]=PackageRe;
		WImPacked[i]=PackageIm;
	}
}

//__INLINE__ void OutTable(vec<nmint64s > &Table,nm8s*TableName,nm8s* Section)
__INLINE__ void OutTable(vec<nmint64s > &Table,char*TableName,char* Section)
//__INLINE__ void OutTable(nmvec64s &Table,char*TableName,char* Section)
{
/*
	cout << "data" << '"'<< Section << '"' <<endl; 
	
	cout << "global " << TableName << ":long["<< dec << Table.size<<"]=(" << endl;
	cout << Table << ')'<<';'<<endl;

	cout << "end  "<< '"'<< Section <<'"' <<';' <<endl; 
*/
}



#endif // NM6403
#endif //_NMFFTEXT_H_INCLUDED_