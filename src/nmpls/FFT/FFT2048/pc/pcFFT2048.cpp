//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcFFT2048.cpp                                       */
//*   Contents:         C++ Equivalent  of the function FFT_Fwd2048.          */
//*                     Additional FFT2048 functions using                  */
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

#include "fft.h"
#include "fftext.h"

#ifndef PI
#define PI 3.14159265359
#endif

static cmplx<double> Rounder(0.5,0.5);
int FlagsFFT2048=FFT7BIT;
// Setting of the calculation accuracy for FFT_Fwd1024 function
void FFT_Fwd2048Set( int	Flag)			// See header for more information
{
	FlagsFFT2048=Flag;
}
void FFT_Fwd2048Set6bit()	// Sets 6-bit accuracy of sin-cosine coefficients
{
	FFT_Fwd2048Set(FFT6BIT);
}
void FFT_Fwd2048Set7bit()	// Sets 7-bit accuracy of sin-cosine coefficients
{
	FFT_Fwd2048Set(FFT7BIT);
}
///////////////////////////////////////////////////////////////////
// Computing FFT-2048 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd2048 Assembly Code
int FFT_Fwd2048(
			vec<cmplx<int > > &X,		// input array
			vec<cmplx<int > > &Y,		// output array
			vec<cmplx<char > >  &W1_2048,// table of coefficients
			vec<cmplx<char > >  &W2_2048,// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			)
{
	ASSERTE(X.size==2048);
	ASSERTE(Y.size==2048);
	vec<cmplx<int > > S(2048);
	vec<cmplx<int > > T(2048);
	
	size_t l,p,i,j,n,idx;
	// first 2-point fft
	for (n=0;n<1024;n++)
	{
		S[n]	=X[n]+X[n+1024];
		S[n+1024]=X[n]-X[n+1024];
	}
	// second 32-point fft
	cmplx<int > Summ;
	for (i=0;i<32;i++)
	{
		idx=0;
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
				Summ+=W1_2048[idx]*S[1024*0+32*j+i];
			T[1024*0+32*p+i]=Summ;
		}
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
				Summ+=W1_2048[idx]*S[1024*1+32*j+i];
			T[1024*1+32*p+i]=Summ;
		}
	}
	if (Shr1>0)
	{
		
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(2048);
		cmplx<int >OneHalf(1<<(Shr1-1),1<<(Shr1-1));
		VcRound=OneHalf;
		T+=VcRound;
		//-----------------------------------
		T>>=Shr1;
	}
	// third 32-point fft
	idx=0;
	for (p=0;p<32;p++)
	{
		for (l=0;l<32;l++)
		{  
            Summ=0;
            for (i=0;i<32;i++,idx++)
               Summ+=W2_2048[idx]*T[1024*0+32*p+i];
            Y[64*l+2*p+0]=Summ;
        }
		for (l=0;l<32;l++)
		{  
            Summ=0;
            for (i=0;i<32;i++,idx++)
               Summ+=W2_2048[idx]*T[1024*1+32*p+i];
            Y[64*l+2*p+1]=Summ;
        }
	}
	if (Shr2>0)
	{
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(2048);
		cmplx<int >OneHalf(1<<(Shr2-1),1<<(Shr2-1));
		VcRound=OneHalf;
		Y+=VcRound;
		//-----------------------------------
		Y>>=Shr2;

	}
	return 0;
	
}

__INLINE__ cmplx<double> W2048(size_t power)
{
	power-=(power>>11)<<11;
	cmplx<double>Z (0,-double(power)*2.0*PI/2048.0);
	return exp(Z);

}

/////////////////////////////////////////////////////////////////////
//	 Initialization table of double coefficients 
void MakeTable2048W1W2(
					vec<cmplx<double> > &W1,
					vec<cmplx<double> > &W2)
{
	ASSERTE(W1.size==2048);
	ASSERTE(W2.size==2048*32);

	size_t l,p,i,j;
	size_t idx=0;

	for (p=0;p<32;p++)
		for (j=0;j<32;j++,idx++)
			W1[idx]=W2048(32*(2*p+0)*j);

	for (p=0;p<32;p++)
		for (j=0;j<32;j++,idx++)
			W1[idx]=W2048(32*(2*p+1)*j);
	
	idx=0;
	for (p=0;p<32;p++)
	{
		for (l=0;l<32;l++)
	        for (i=0;i<32;i++,idx++)
               W2[idx]=W2048((64*l+2*p+0)*i);
		for (l=0;l<32;l++)
            for (i=0;i<32;i++,idx++)
               W2[idx]=W2048((64*l+2*p+1)*i);
	}
}


/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void MakeTable2048W1W2(
				vec<cmplx<char > > &W1_2048,
				vec<cmplx<char > > &W2_2048,
				double Ampl)
{
	ASSERTE(W1_2048.size==2048);
	ASSERTE(W2_2048.size==2048*32);

	vec<cmplx<double > >  fW1_2048(2048);
	vec<cmplx<double > >  fW2_2048(2048*32);
	MakeTable2048W1W2(fW1_2048,fW2_2048);
//	scalar<cmplx<double> > Mult(Ampl,0);
	cmplx<double> Mult(Ampl,0);
	fW1_2048*=Mult;
	fW2_2048*=Mult;

	int i;
	for(i=0;i<W1_2048.size;i++)
	{
		W1_2048[i].re=floor(fW1_2048[i].re+0.5);
		W1_2048[i].im=floor(fW1_2048[i].im+0.5);
	}

	for(i=0;i<W2_2048.size;i++)
	{
		W2_2048[i].re=floor(fW2_2048[i].re+0.5);
		W2_2048[i].im=floor(fW2_2048[i].im+0.5);
	}
}

/////////////////////////////////////////////////////////////////////
//	 This is the C equivalent of the FFT_Fwd2048 Assembly Code 
void FFT_Fwd2048(
			nm32sc*	GSrcBuffer,	// Source buffer :long[2048]
			nm32sc*	LDstBuffer,	// Result FFT    :long[2048]
			void*		LBuffer,	// Temp buffer   :long[2048*3]
			int			ShiftR		// Shift normalization
			)
{
	vec<cmplx<char > >  W1_2048(2048);
	vec<cmplx<char > >  W2_2048(2048*32);
	
	if (FlagsFFT2048 & FFT7BIT==FFT7BIT)
	{
		MakeTable2048W1W2(W1_2048,W2_2048,127.0);
		if (ShiftR==-1)
			ShiftR=14;
	}
	else
	{
		MakeTable2048W1W2(W1_2048,W2_2048,64.0);
		if (ShiftR==-1)
			ShiftR=12;
	}
	
	vec<cmplx<int > > X((cmplx<int>*)GSrcBuffer,2048);
	vec<cmplx<int > > Y((cmplx<int>*)LDstBuffer,2048);
	
	FFT_Fwd2048(X,Y,W1_2048,W2_2048,0,ShiftR);
	

}

///////////////////////////////////////////////////////////////////
// Computing FFT-2048 using floating-point arithmetic
int FFT2048(
		vec<cmplx<double> > &	X,	// Source buffer :long[1024]
		vec<cmplx<double> > &	Y	// Result FFT    :long[1024]
		)
{
	ASSERTE(X.size==2048);
	ASSERTE(Y.size==2048);
	
	vec<cmplx<double> > S(2048);
	vec<cmplx<double> > T(2048);
	
	vec<cmplx<double > > W1_2048(2048);
	vec<cmplx<double > > W2_2048(2048*32);
	MakeTable2048W1W2(W1_2048,W2_2048);
	
	
	size_t l,p,i,j,n,idx;
	for (n=0;n<1024;n++)
	{
		S[n]	=X[n]+X[n+1024];
		S[n+1024]=X[n]-X[n+1024];
	}
	// second 32-point fft
	cmplx<double> Summ;
	for (i=0;i<32;i++)
	{
		idx=0;
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
				Summ+=W1_2048[idx]*S[1024*0+32*j+i];
			T[1024*0+32*p+i]=Summ;
		}
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
				Summ+=W1_2048[idx]*S[1024*1+32*j+i];
			T[1024*1+32*p+i]=Summ;
		}
	}
	// third 32-point fft
	idx=0;
	for (p=0;p<32;p++)
	{
		for (l=0;l<32;l++)
		{  
            Summ=0;
            for (i=0;i<32;i++,idx++)
               Summ+=W2_2048[idx]*T[1024*0+32*p+i];
            Y[64*l+2*p+0]=Summ;
        }
		for (l=0;l<32;l++)
		{  
            Summ=0;
            for (i=0;i<32;i++,idx++)
               Summ+=W2_2048[idx]*T[1024*1+32*p+i];
            Y[64*l+2*p+1]=Summ;
        }
	}
	return 0;
	
}
