//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcFFT1024.cpp                                       */
//*   Contents:         C++ Equivalent  of the function FFT_Fwd1024           */
//*                     Additional FFT1024 functions using                  */
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

int FlagsFFT1024=FFT7BIT;
static cmplx<double> Rounder(0.5,0.5);
// Setting of the calculation accuracy for FFT_Fwd1024 function

extern "C"{
void FFT_Fwd1024Set( int	Flag)			// See header for more information
{
	FlagsFFT1024=Flag;
}
void FFT_Fwd1024Set6bit()	// Sets 6-bit accuracy of sin-cosine coefficients
{
	FFT_Fwd1024Set(FFT6BIT);
}
void FFT_Fwd1024Set7bit()	// Sets 7-bit accuracy of sin-cosine coefficients
{
	FFT_Fwd1024Set(FFT7BIT);
}
};
///////////////////////////////////////////////////////////////////
// Computing FFT-1024 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd1024 Assembly Code
int FFT_Fwd1024(
							/*
			vec<cmplx<int> > &X,		// input array
			vec<cmplx<int> > &Y,		// output array
			vec<cmplx<char> >   &W1_1024,// table of coefficients
			vec<cmplx<char> >   &W2_1024,// table of coefficients
			vec<cmplx<char> >   &W2_1024,// table of coefficients
			*/
			vec<cmplx<int> > &X,		// input array
			vec<cmplx<int> > &Y,		// output array
			vec<cmplx<char> >  &W1_1024,// table of coefficients
			vec<cmplx<char> >  &W2_1024,// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			)
{
//	ASSERTE(X.size==1024);
//	ASSERTE(Y.size==1024);
//	vec<cmplx<int> > S(1024);
//	vec<cmplx<int> > T(1024);
		vec<cmplx<int> > S(1024);
		vec<cmplx<int> > T(1024);

	int l,p,i,j,n;
	for (n=0;n<512;n++)
	{
		S[n]		=X[n]+X[n+512];
		S[n+512]	=X[n]-X[n+512];
	}

	// second 32-point fft
	cmplx<int> Summ;
	for (i=0;i<16;i++)
	{
		int idx=0;
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
			{
				Summ+=W1_1024[idx]*S[512*0+16*j+i];
			}
			T[512*0+16*p+i]=Summ;
		}
		
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
			{
				Summ+=W1_1024[idx]*S[512*1+16*j+i];
			}
			T[512*1+16*p+i]=Summ;
		}
	}

	if (Shr1>0)
	{
		//------- Roundation -----------------
		/*
		vec<cmplx<int> > VcRound(1024);
		cmplx<int> OneHalf(1<<(Shr1-1),1<<(Shr1-1));
		cmplx<int> Zero(0);
		*/
		vec<cmplx<int> > VcRound(1024);
		cmplx<int> OneHalf(1<<(Shr1-1),1<<(Shr1-1));
		cmplx<int> Zero(0);

		//for(int i=0;i<1024;i)
		//InitInc2(VcRound,OneHalf,Zero);
		//VcRound.SetConst(OneHalf);
		
		//T+=VcRound;
		T+=OneHalf;
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
               Summ+=W2_1024[idx]*T[512*0+16*p+i];
            }
            Y[64*l+2*p+0]=Summ;
        }
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
            {
               Summ+=W2_1024[idx]*T[512*1+16*p+i];
            }
            Y[64*l+2*p+1]=Summ;
        }
	}
	if (Shr2>0)
	{
		//------- Roundation -----------------
		vec<cmplx<int> > VcRound(1024);
		cmplx<int> OneHalf(1<<(Shr2-1),1<<(Shr2-1));
		cmplx<int> Zero(0);
		//InitInc(VcRound,OneHalf,Zero);
		//VcRound.SetConst(OneHalf);
		//Y+=VcRound;
		Y+=OneHalf;
		//-----------------------------------
		
		Y>>=Shr2;
	}
	return 0;
}

__INLINE__ cmplx<double> W1024(int power)
{
	power-=(power>>10)<<10;
	cmplx<double>Z (0,-double(power)*2.0*PI/1024.0);
	return exp(Z);

}

/////////////////////////////////////////////////////////////////////
//	 Initialization table of double coefficients 
void MakeTable1024W1W2(
					vec<cmplx<double> > &W1,
					vec<cmplx<double> > &W2)
{
	ASSERTE(W1.size==32*32*2);
	ASSERTE(W2.size==32*16*16*2);

	
	int p,j,i,l;
	int idx=0;
	for (p=0;p<32;p++)
		for (j=0;j<32;j++,idx++)
			W1[idx]=W1024(16*(2*p+0)*j);
		
	for (p=0;p<32;p++)
		for (j=0;j<32;j++,idx++)
			W1[idx]=W1024(16*(2*p+1)*j);

	idx=0;
	for (p=0;p<32;p++)
	{
		for (l=0;l<16;l++)
	        for (i=0;i<16;i++,idx++)
               W2[idx]=W1024((64*l+2*p+0)*i);
    	for (l=0;l<16;l++)
	        for (i=0;i<16;i++,idx++)
               W2[idx]=W1024((64*l+2*p+1)*i);
    }

}


/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void MakeTable1024W1W2(
				vec<cmplx<char> >  &W1_1024,
				vec<cmplx<char> >  &W2_1024,
				double Ampl)
{
//	ASSERTE(W1_1024.size==32*32*2);
//	ASSERTE(W2_1024.size==32*16*16*2);

	vec<cmplx<double > >  fW1_1024(32*32*2);
	vec<cmplx<double > >  fW2_1024(32*16*16*2);
	MakeTable1024W1W2(fW1_1024,fW2_1024);
	cmplx<double> Mult(Ampl,0);
	fW1_1024*=Mult;
	fW2_1024*=Mult;
	int i;
	for(i=0;i<W1_1024.size;i++)
	{
		W1_1024[i].re=floor(fW1_1024[i].re+0.5);
		W1_1024[i].im=floor(fW1_1024[i].im+0.5);
	}

	for(i=0;i<W2_1024.size;i++)
	{
		W2_1024[i].re=floor(fW2_1024[i].re+0.5);
		W2_1024[i].im=floor(fW2_1024[i].im+0.5);
	}
}

/////////////////////////////////////////////////////////////////////
//	 This is the C equivalent of the function FFT_Fwd1024
void FFT_Fwd1024(
			nm32sc*	GSrcBuffer,	// Source buffer :long[1024]
			nm32sc*	LDstBuffer,	// Result FFT    :long[1024]
			void*	LBuffer,	// Temp buffer   :long[1024*3]
			void*	GBuffer,	// Temp buffer   :long[1024*2]
			int			ShiftR		// Shift normalization
			)
{
	vec<cmplx<char> >   W1_1024(32*32*2);
	vec<cmplx<char> >   W2_1024(32*16*16*2);
	
	if (FlagsFFT1024 & FFT7BIT==FFT7BIT)
	{
		MakeTable1024W1W2(W1_1024,W2_1024,127.0);
		if (ShiftR==-1)
			ShiftR=14;
	}
	else
	{
		MakeTable1024W1W2(W1_1024,W2_1024,64.0);
		if (ShiftR==-1)
			ShiftR=12;
	}
	
	
	vec<cmplx<int> > X(1024);
	vec<cmplx<int> > Y(1024);
	int i;
	for(i=0;i<X.size;i++)
	{
		X[i].re=GSrcBuffer[i].re;
		X[i].im=GSrcBuffer[i].im;
	}
	
	FFT_Fwd1024(X,Y,W1_1024,W2_1024,0,ShiftR);

	cmplx<int> tmp;
	for(i=0;i<Y.size;i++)
	{
		tmp=Y[i];
		LDstBuffer[i].re=tmp.re;
		LDstBuffer[i].im=tmp.im;
	}

}

///////////////////////////////////////////////////////////////////
// Computing FFT-1024 using floating-point arithmetic
int FFT1024(
		vec<cmplx<double> > &	X,	// Source buffer :long[1024]
		vec<cmplx<double> > &	Y	// Result FFT    :long[1024]
		)
{
	ASSERTE(X.size==1024);
	ASSERTE(Y.size==1024);
	
	vec<cmplx<double> > S(1024);
	vec<cmplx<double> > T(1024);
	
	vec<cmplx<double > > W1_1024(32*32*2);
	vec<cmplx<double > > W2_1024(32*16*16*2);
	MakeTable1024W1W2(W1_1024,W2_1024);
	
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
				Summ+=W1_1024[idx]*S[512*0+16*j+i];
			}
			T[512*0+16*p+i]=Summ;
		}
		
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
			{
				Summ+=W1_1024[idx]*S[512*1+16*j+i];
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
               Summ+=W2_1024[idx]*T[512*0+16*p+i];
            }
            Y[64*l+2*p+0]=Summ;
        }
		for (l=0;l<16;l++)
		{  
            Summ=0;
            for (i=0;i<16;i++,idx++)
            {
               Summ+=W2_1024[idx]*T[512*1+16*p+i];
            }
            Y[64*l+2*p+1]=Summ;
        }
	}
	return 0;
}