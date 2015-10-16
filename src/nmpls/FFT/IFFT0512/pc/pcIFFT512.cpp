//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcIFFT512.cpp                                       */
//*   Contents:         C++ Equivalent of the function FFT_Inv512            */
//*                     Additional IFFT512 functions using                  */
//*                         fixed and floating-point arithmetic             */ 
//*                                                                         */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Start date:       15.01.2001                                          */
//*   Last update :     -                                                   */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

//#include "internal.h"
#include "fft.h"
#include "fftext.h"
#include "nmtl/tcmplx_spec.h"

#ifndef PI
#define PI 3.14159265359
#endif
static cmplx<double> Rounder(0.5,0.5);
int FlagsIFFT512;
// Setting of the calculation accuracy for FFT_Inv512 functions
void FFT_Inv512Set( int	Flag)			// See header for more information
{
	FlagsIFFT512=Flag;
}
void FFT_Inv512Set6bit()	// Sets 6-bit accuracy of sin-cosine coefficients
{
	FFT_Inv512Set(FFT6BIT);
}
void FFT_Inv512Set7bit()	// Sets 7-bit accuracy of sin-cosine coefficients
{
	FFT_Inv512Set(FFT7BIT);
}
///////////////////////////////////////////////////////////////////
// Computing IFFT-512 using fixed-point arithmetic
// This is the C equivalent of the FFT_Inv512 Assembly Code
int FFT_Inv512(
			vec<cmplx<int > > &X,		// input array
			vec<cmplx<int > > &Y,		// output array
			vec<cmplx<char > >  &IW1_512,// table of coefficients
			vec<cmplx<char > >  &IW2_512,// table of coefficients
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
				Summ+=IW1_512[idx]*S[256*0+16*j+i];
			T[256*0+16*p+i]=Summ;
		}
		//k=1
		for (p=0;p<16;p++)
		{
			Summ=0;
			for (j=0;j<16;j++,idx++)
				Summ+=IW1_512[idx]*S[256*1+16*j+i];
			T[256*1+16*p+i]=Summ;
		}
	}

	if (Shr1>0)
	{
		// Not implemented in FFT_Inv512
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(512);
		cmplx<int >OneHalf(1<<(Shr1-1),1<<(Shr1-1));
		T+=OneHalf;
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
                Summ+=IW2_512[idx]*T[256*0+16*p+i];
            Y[32*l+2*p+0]=Summ;
        }
		//k=1
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
               Summ+=IW2_512[idx]*T[256*1+16*p+i];
            Y[32*l+2*p+1]=Summ;
        }
	}
	if (Shr2>0)
	{
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(512);
		cmplx<int >OneHalf(1<<(Shr2-1),1<<(Shr2-1));
		Y+=OneHalf;
		//-----------------------------------
		Y>>=Shr2;
	}
	return 0;
}



inline cmplx<double> IW512(int power)
{
	power-=(power>>9)<<9;
	cmplx<double> z(0,+(double(power)*2.0*PI)/512.0);
	return exp(z);
}
/////////////////////////////////////////////////////////////////////
//	 Initialization table of double coefficients 
void IMakeTable512W1W2(
				vec<cmplx<double > > &IW1_512,
				vec<cmplx<double > > &IW2_512
					)
{
	ASSERTE(IW1_512.size==16*2*16);
	ASSERTE(IW2_512.size==16*16*16*2);
	
	int l,p,i,j;
	int idx=0;
	
	
	// second 16-point fft
	for (p=0;p<16;p++)
		for (j=0;j<16;j++,idx++)
			IW1_512[idx]=IW512(16*(2*p+0)*j);
		//k=1
	for (p=0;p<16;p++)
		for (j=0;j<16;j++,idx++)
			IW1_512[idx]=IW512(16*(2*p+1)*j);

	
   // third 16-point fft
	idx=0;
	for (p=0;p<16;p++)
	{
		//k=0
		for (l=0;l<16;l++)
	        for (i=0;i<16;i++,idx++)
               IW2_512[idx]=IW512((32*l+2*p+0)*i);
		//k=1
		for (l=0;l<16;l++)
            for (i=0;i<16;i++,idx++)
               IW2_512[idx]=IW512((32*l+2*p+1)*i);
            
	}
}
/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void IMakeTable512W1W2(
				vec<cmplx<char > > &IW1_512,
				vec<cmplx<char > > &IW2_512,
				double Ampl)
{
	ASSERTE(IW1_512.size==16*2*16);
	ASSERTE(IW2_512.size==16*16*16*2);
	
	vec<cmplx<double > >  fIW1_512(16*2*16);
	vec<cmplx<double > >  fIW2_512(16*16*16*2);
	IMakeTable512W1W2(fIW1_512,fIW2_512);
	
	cmplx<double> Mult(Ampl,0);
	fIW1_512*=Mult;
	fIW2_512*=Mult;

	int i;
	for(i=0;i<IW1_512.size;i++)
	{
		IW1_512[i].re=floor(fIW1_512[i].re+0.5);
		IW1_512[i].im=floor(fIW1_512[i].im+0.5);
	}

	for(i=0;i<IW2_512.size;i++)
	{
		IW2_512[i].re=floor(fIW2_512[i].re+0.5);
		IW2_512[i].im=floor(fIW2_512[i].im+0.5);
	}
}
/////////////////////////////////////////////////////////////////////
//	 This is the C equivalent of the function FFT_Fwd512
void FFT_Inv512(
			nm32sc* SrcBuffer,	// Source buffer :long[512]
			nm32sc* DstBuffer,	// Result FFT    :long[512]
			void*	LBuffer,	// Temp buffer   :long[512*3]
			void*	GBuffer,	// Temp buffer	 :long[512*3]	
			int			ShiftR1,	// First shift normalization
			int			ShiftR2		// Final shift normalization
			)

{
	vec<cmplx<char > >  IW1_512(16*2*16);
	vec<cmplx<char > >  IW2_512(16*16*16*2);
	
	if (FlagsIFFT512 & FFT7BIT==FFT7BIT)
	{
		IMakeTable512W1W2(IW1_512,IW2_512,127.0);
		if (ShiftR2==-1)
			ShiftR2=14;
	}
	else
	{
		IMakeTable512W1W2(IW1_512,IW2_512,64.0);
		if (ShiftR2==-1)
			ShiftR2=12;
	}
	
	
	vec<cmplx<int > > X((cmplx<int>*)SrcBuffer,512);
	vec<cmplx<int > > Y((cmplx<int>*)DstBuffer,512);
	
	FFT_Inv512(X,Y,IW1_512,IW2_512,ShiftR1,ShiftR2);
}

///////////////////////////////////////////////////////////////////
// Computing FFT-512 using floating-point arithmetic
int IFFT512(
		vec<cmplx<double> > &	X,	// Source buffer :long[512]
		vec<cmplx<double> > &	Y	// Result IFFT    :long[512]
		)
{
	ASSERTE(X.size==512);
	ASSERTE(Y.size==512);
	
	vec<cmplx<double> > S(512);
	vec<cmplx<double> > T(512);
	
	vec<cmplx<double > > IW1_512(16*2*16);
	vec<cmplx<double > > IW2_512(16*16*16*2);
	IMakeTable512W1W2(IW1_512,IW2_512);
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
				Summ+=IW1_512[idx]*S[256*0+16*j+i];
			T[256*0+16*p+i]=Summ;
		}
		//k=1
		for (p=0;p<16;p++)
		{
			Summ=0;
			for (j=0;j<16;j++,idx++)
				Summ+=IW1_512[idx]*S[256*1+16*j+i];
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
                Summ+=IW2_512[idx]*T[256*0+16*p+i];
            Y[32*l+2*p+0]=Summ;
        }
		//k=1
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
               Summ+=IW2_512[idx]*T[256*1+16*p+i];
            Y[32*l+2*p+1]=Summ;
        }
	}
	Y>>=9;
	return 0;
}

	