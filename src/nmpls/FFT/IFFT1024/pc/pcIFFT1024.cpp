//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcIFFT1024.cpp                                      */
//*   Contents:         C++ Equivalent of the function FFT_Inv1024           */
//*                     Additional IFFT1024 functions using                 */
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
int FlagsIFFT1024=FFT7BIT;

// Setting of the calculation accuracy for FFT_Inv1024 function
void FFT_Inv1024Set( int	Flag)			// See header for more information
{
	FlagsIFFT1024=Flag;
}
void FFT_Inv1024Set6bit()	// Sets 6-bit accuracy of sin-cosine coefficients
{
	FFT_Inv1024Set(FFT6BIT);
}
void FFT_Inv1024Set7bit()	// Sets 7-bit accuracy of sin-cosine coefficients
{
	FFT_Inv1024Set(FFT7BIT);
}

///////////////////////////////////////////////////////////////////
// Computing FFT-1024 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd1024 Assembly Code
int FFT_Inv1024(
			vec<cmplx<int > > &X,		// input array
			vec<cmplx<int > > &Y,		// output array
			vec<cmplx<char > >  &IW1_1024,// table of coefficients
			vec<cmplx<char > >  &IW2_1024,// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			)
{
	ASSERTE(X.size==1024);
	ASSERTE(Y.size==1024);
	vec<cmplx<int > > S(1024);
	vec<cmplx<int > > T(1024);
	
	int l,p,i,j,n;
	for (n=0;n<512;n++)
	{
		S[n]		=X[n]+X[n+512];
		S[n+512]	=X[n]-X[n+512];
	}

	// second 32-point fft
	cmplx<int > Summ;
	for (i=0;i<16;i++)
	{
		int idx=0;
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
			{
				Summ+=IW1_1024[idx]*S[512*0+16*j+i];
			}
			T[512*0+16*p+i]=Summ;
		}
		
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
			{
				Summ+=IW1_1024[idx]*S[512*1+16*j+i];
			}
			T[512*1+16*p+i]=Summ;
		}
	}
	if (Shr1>0)
	{
		// Not implemented in FFT_Inv1024
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(1024);
		cmplx<int >OneHalf(1<<(Shr1-1),1<<(Shr1-1));
		VcRound=OneHalf;
		T+=VcRound;
		//-----------------------------------
		T>>=Shr1; 
	}

	int idx=0;
	for (p=0;p<32;p++)
	{
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
            {
               Summ+=IW2_1024[idx]*T[512*0+16*p+i];
            }
            Y[64*l+2*p+0]=Summ;
        }
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
            {
               Summ+=IW2_1024[idx]*T[512*1+16*p+i];
            }
            Y[64*l+2*p+1]=Summ;
        }
	}
	if (Shr2>0)
	{
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(1024);
		cmplx<int >OneHalf(1<<(Shr2-1),1<<(Shr2-1));
		VcRound=OneHalf;
		Y+=VcRound;
		//-----------------------------------
		Y>>=Shr2;
	}
	return 0;
}

__INLINE__ cmplx<double> IW1024(int power)
{
	power-=(power>>10)<<10;
	cmplx<double>Z (0,double(power)*2.0*PI/1024.0);
	return exp(Z);

}

/////////////////////////////////////////////////////////////////////
//	 Initialization table of double coefficients 
void IMakeTable1024W1W2(
					vec<cmplx<double> > &IW1,
					vec<cmplx<double> > &IW2)
{
	ASSERTE(IW1.size==32*32*2);
	ASSERTE(IW2.size==32*16*16*2);

	
	int p,j,i,l;
	int idx=0;
	for (p=0;p<32;p++)
		for (j=0;j<32;j++,idx++)
			IW1[idx]=IW1024(16*(2*p+0)*j);
		
	for (p=0;p<32;p++)
		for (j=0;j<32;j++,idx++)
			IW1[idx]=IW1024(16*(2*p+1)*j);

	idx=0;
	for (p=0;p<32;p++)
	{
		for (l=0;l<16;l++)
	        for (i=0;i<16;i++,idx++)
               IW2[idx]=IW1024((64*l+2*p+0)*i);
    	for (l=0;l<16;l++)
	        for (i=0;i<16;i++,idx++)
               IW2[idx]=IW1024((64*l+2*p+1)*i);
    }

}


/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void IMakeTable1024W1W2(
				vec<cmplx<char > > &IW1_1024,
				vec<cmplx<char > > &IW2_1024,
				double Ampl)
{
	ASSERTE(IW1_1024.size==32*32*2);
	ASSERTE(IW2_1024.size==32*16*16*2);

	vec<cmplx<double > >  fIW1_1024(32*32*2);
	vec<cmplx<double > >  fIW2_1024(32*16*16*2);
	IMakeTable1024W1W2(fIW1_1024,fIW2_1024);
	cmplx<double> Mult(Ampl,0);
	fIW1_1024*=Mult;
	fIW2_1024*=Mult;
	int i;
	for(i=0;i<IW1_1024.size;i++)
	{
		IW1_1024[i].re=floor(fIW1_1024[i].re+0.5);
		IW1_1024[i].im=floor(fIW1_1024[i].im+0.5);
	}

	for(i=0;i<IW2_1024.size;i++)
	{
		IW2_1024[i].re=floor(fIW2_1024[i].re+0.5);
		IW2_1024[i].im=floor(fIW2_1024[i].im+0.5);
	}
}

/////////////////////////////////////////////////////////////////////
//	 This is the C equivalent of the function FFT_Inv1024
void FFT_Inv1024(
			nm32sc*	SrcBuffer,	// Source buffer :long[1024]
			nm32sc*	DstBuffer,	// Result FFT    :long[1024]
			void*	LBuffer,	// Temp buffer   :long[1024*3]
			void*	GBuffer,	// Temp buffer   :long[1024*3]
			int			ShiftR1,	// First Right shift normalization
			int			ShiftR2		// Final Right shift normalization
			)

{
	vec<cmplx<char > >  IW1_1024(32*32*2);
	vec<cmplx<char > >  IW2_1024(32*16*16*2);
	
	if (FlagsIFFT1024 & FFT7BIT==FFT7BIT)
	{
		IMakeTable1024W1W2(IW1_1024,IW2_1024,127.0);
		if (ShiftR2==-1)
			ShiftR2=14;
	}
	else
	{
		IMakeTable1024W1W2(IW1_1024,IW2_1024,64.0);
		if (ShiftR2==-1)
			ShiftR2=12;
	}
	
	
	
	vec<cmplx<int > > X((cmplx<int>*)SrcBuffer,1024);
	vec<cmplx<int > > Y((cmplx<int>*)DstBuffer,1024);
	
	FFT_Inv1024(X,Y,IW1_1024,IW2_1024,ShiftR1,ShiftR2);

}

///////////////////////////////////////////////////////////////////
// Computing IFFT-1024 using floating-point arithmetic
int IFFT1024(
		vec<cmplx<double> > &	X,	// Source buffer :long[1024]
		vec<cmplx<double> > &	Y	// Result IFFT    :long[1024]
		)
{
	ASSERTE(X.size==1024);
	ASSERTE(Y.size==1024);
	
	vec<cmplx<double> > S(1024);
	vec<cmplx<double> > T(1024);
	
	vec<cmplx<double > > IW1_1024(32*32*2);
	vec<cmplx<double > > IW2_1024(32*16*16*2);
	IMakeTable1024W1W2(IW1_1024,IW2_1024);
	
	int l,p,i,j,n;
	for (n=0;n<512;n++)
	{
		S[n]		=X[n]+X[n+512];
		S[n+512]	=X[n]-X[n+512];
	}

	// second 32-point fft
	cmplx<double> Summ;
	for (i=0;i<16;i++)
	{
		int idx=0;
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
			{
				Summ+=IW1_1024[idx]*S[512*0+16*j+i];
			}
			T[512*0+16*p+i]=Summ;
		}
		
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
			{
				Summ+=IW1_1024[idx]*S[512*1+16*j+i];
			}
			T[512*1+16*p+i]=Summ;
		}
	}
	
	int idx=0;
	for (p=0;p<32;p++)
	{
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
            {
               Summ+=IW2_1024[idx]*T[512*0+16*p+i];
            }
            Y[64*l+2*p+0]=Summ;
        }
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
            {
               Summ+=IW2_1024[idx]*T[512*1+16*p+i];
            }
            Y[64*l+2*p+1]=Summ;
        }
	}
	Y>>=10;
	return 0;
}