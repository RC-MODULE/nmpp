//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*  (C-callable functions)                                                 */
//*                                                                         */
//*  $Workfile:: pcFFT512.cpp                                              $*/
//*   Contents:         C++ Equivalent  of the function FFT_Fwd512            */
//*                     Additional FFT512 functions using                   */
//*                         fixed and floating-point arithmetic             */
//*                                                                         */
//*                                                                         */
//*  Author:     S.Mushkaev                                                 */
//*                                                                         */
//*  Version         1.0                                                    */
//*  Start    Date:  15.01.2001                                             */
//*  Release $Date: 2005/02/10 11:48:00 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/
#include "fft.h"
#include "fftext.h"
#include "nmtl/tcmplx_spec.h"
//#include "internal.h"

#ifndef PI
#define PI 3.14159265359
#endif

int FlagsFFT512=FFT7BIT;

static cmplx<double> Rounder(0.5,0.5);
// Setting of the calculation accuracy for FFT_Fwd512 function
void FFT_Fwd512Set( int	Flag)			// See header for more information
{
	FlagsFFT512=Flag;
}
void FFT_Fwd512Set6bit()	// Sets 6-bit accuracy of sin-cosine coefficients
{
	FFT_Fwd512Set(FFT6BIT);
}
extern "C" {
void FFT_Fwd512Set7bit()	// Sets 7-bit accuracy of sin-cosine coefficients
{
	FFT_Fwd512Set(FFT7BIT);
}
}
///////////////////////////////////////////////////////////////////
// Computing FFT-512 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd512 Assembly Code
int FFT_Fwd512(
			vec<cmplx<int > > &X,		// input array
			vec<cmplx<int > > &Y,		// output array
			vec<cmplx<char > >  &W1_512,	// table of coefficients
			vec<cmplx<char > >  &W2_512,	// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			)
{
	ASSERTE(X.size==512);
	ASSERTE(Y.size==512);
	
	vec<cmplx<int > > S(512);
	vec<cmplx<int > > T(512);
	
	int l,p,i,j,n;
	// first 2-point fft
	for (n=0;n<256;n++)
	{
		S[n]		=X[n]+X[n+256];
		S[n+256]	=X[n]-X[n+256];
	}
	// second 16-point fft
	cmplx<int > Summ;
	for (i=0;i<16;i++)
	{
		int idx=0;
		//k=0
		for (p=0;p<16;p++)
		{
			Summ=0;
			for (j=0;j<16;j++,idx++)
				Summ+=W1_512[idx]*S[256*0+16*j+i];
			T[256*0+16*p+i]=Summ;
		}
		//k=1
		for (p=0;p<16;p++)
		{
			Summ=0;
			for (j=0;j<16;j++,idx++)
				Summ+=W1_512[idx]*S[256*1+16*j+i];
			T[256*1+16*p+i]=Summ;
		}
	}

	if (Shr1>0)
	{
		// Not implemented in FFT_Inv512
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(512);
		cmplx<int >OneHalf(1<<(Shr1-1),1<<(Shr1-1));
		VcRound=OneHalf;
		T+=VcRound;
		//-----------------------------------
		T>>=Shr1; 
	}
	
	// third 16-point fft
	int idx=0;
	for (p=0;p<16;p++)
	{
		//k=0
		for (l=0;l<16;l++)
		{  
			Summ=0;
            for (i=0;i<16;i++,idx++)
                Summ+=W2_512[idx]*T[256*0+16*p+i];
            Y[32*l+2*p+0]=Summ;
        }
		//k=1
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
               Summ+=W2_512[idx]*T[256*1+16*p+i];
            Y[32*l+2*p+1]=Summ;
        }
	}
	if (Shr2>0)
	{
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(512);
		cmplx<int >OneHalf(1<<(Shr2-1),1<<(Shr2-1));
		VcRound=OneHalf;
		Y+=VcRound;
		//-----------------------------------
		Y>>=Shr2;
	}
	return 0;
}



__INLINE__ cmplx<double> W512(int power)
{
	power-=(power>>9)<<9;
	cmplx<double> z(0,-(double(power)*2.0*PI)/512.0);
	return exp(z);
}
/////////////////////////////////////////////////////////////////////
//	 Initialization table of double coefficients 
void MakeTable512W1W2(
				vec<cmplx<double > > &W1_512,
				vec<cmplx<double > > &W2_512
					)
{
	ASSERTE(W1_512.size==16*2*16);
	ASSERTE(W2_512.size==16*16*16*2);
	
	int l,p,i,j;
	int idx=0;
	
	
	// second 16-point fft
	for (p=0;p<16;p++)
		for (j=0;j<16;j++,idx++)
			W1_512[idx]=W512(16*(2*p+0)*j);
		//k=1
	for (p=0;p<16;p++)
		for (j=0;j<16;j++,idx++)
			W1_512[idx]=W512(16*(2*p+1)*j);

	
   // third 16-point fft
	idx=0;
	for (p=0;p<16;p++)
	{
		//k=0
		for (l=0;l<16;l++)
	        for (i=0;i<16;i++,idx++)
               W2_512[idx]=W512((32*l+2*p+0)*i);
		//k=1
		for (l=0;l<16;l++)
            for (i=0;i<16;i++,idx++)
               W2_512[idx]=W512((32*l+2*p+1)*i);
            
	}
}
/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void MakeTable512W1W2(
				vec<cmplx<char > > &W1_512,
				vec<cmplx<char > > &W2_512,
				double Ampl)
{
	ASSERTE(W1_512.size==16*2*16);
	ASSERTE(W2_512.size==16*16*16*2);
	
	vec<cmplx<double > >  fW1_512(16*2*16);
	vec<cmplx<double > >  fW2_512(16*16*16*2);
	
	MakeTable512W1W2(fW1_512,fW2_512);
	cmplx<double> Mult(Ampl,0);
	fW1_512*=Mult;
	fW2_512*=Mult;

	int i;
	for(i=0;i<W1_512.size;i++)
	{
		W1_512[i].re=floor(fW1_512[i].re+0.5);
		W1_512[i].im=floor(fW1_512[i].im+0.5);
	}

	for(i=0;i<W2_512.size;i++)
	{
		W2_512[i].re=floor(fW2_512[i].re+0.5);
		W2_512[i].im=floor(fW2_512[i].im+0.5);
	}
}
/////////////////////////////////////////////////////////////////////
//	 This is the C equivalent of the function FFT_Fwd512
extern "C" {
void FFT_Fwd512(
			nm32sc*	GSrcBuffer,	// Source buffer :long[512]
			nm32sc*	GDstBuffer,	// Result FFT    :long[512]
			void*	LBuffer,	// Temp buffer   :long[512*3]
			void*	GBuffer,	// Temp buffer   :long[512*2]
			int			ShiftR		// Shift normalization
			)
{
	vec<cmplx<char > >  W1_512(16*2*16);
	vec<cmplx<char > >  W2_512(16*16*16*2);
	if (FlagsFFT512 & FFT7BIT==FFT7BIT)
	{
		MakeTable512W1W2(W1_512,W2_512,127.0);
		if (ShiftR==-1)
			ShiftR=14;
	}
	else
	{
		MakeTable512W1W2(W1_512,W2_512,64.0);
		if (ShiftR==-1)
			ShiftR=12;
	}
	
	vec<cmplx<int> > X((cmplx<int>*)GSrcBuffer,512);
	vec<cmplx<int> > Y((cmplx<int>*)GDstBuffer,512);
	
	FFT_Fwd512(X,Y,W1_512,W2_512,0,ShiftR);


}
}

///////////////////////////////////////////////////////////////////
// Computing FFT-512 using floating-point arithmetic
int FFT512(
		vec<cmplx<double> > &	X,	// Source buffer :long[512]
		vec<cmplx<double> > &	Y	// Result FFT    :long[512]
		)
{
	ASSERTE(X.size==512);
	ASSERTE(Y.size==512);
	
	vec<cmplx<double> > S(512);
	vec<cmplx<double> > T(512);
	
	vec<cmplx<double > > W1_512(16*2*16);
	vec<cmplx<double > > W2_512(16*16*16*2);
	MakeTable512W1W2(W1_512,W2_512);
	int l,p,i,j,n;
	// first 2-point fft
	for (n=0;n<256;n++)
	{
		S[n]		=X[n]+X[n+256];
		S[n+256]	=X[n]-X[n+256];
	}
	// second 16-point fft
	cmplx<double> Summ;
	for (i=0;i<16;i++)
	{
		int idx=0;
		//k=0
		for (p=0;p<16;p++)
		{
			Summ=0;
			for (j=0;j<16;j++,idx++)
				Summ+=W1_512[idx]*S[256*0+16*j+i];
			T[256*0+16*p+i]=Summ;
		}
		//k=1
		for (p=0;p<16;p++)
		{
			Summ=0;
			for (j=0;j<16;j++,idx++)
				Summ+=W1_512[idx]*S[256*1+16*j+i];
			T[256*1+16*p+i]=Summ;
		}
	}

	
	
	// third 16-point fft
	int idx=0;
	for (p=0;p<16;p++)
	{
		//k=0
		for (l=0;l<16;l++)
		{  
			Summ=0;
            for (i=0;i<16;i++,idx++)
                Summ+=W2_512[idx]*T[256*0+16*p+i];
            Y[32*l+2*p+0]=Summ;
        }
		//k=1
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
               Summ+=W2_512[idx]*T[256*1+16*p+i];
            Y[32*l+2*p+1]=Summ;
        }
	}
	return 0;
}

	