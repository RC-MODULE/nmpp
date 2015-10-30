//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcIFFT2048.cpp                                      */
//*   Contents:         C++ Equivalent of the function FFT_Inv2048           */
//*                     Additional IFFT2048 functions using                 */
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

int FlagsIFFT2048=FFT7BIT;
static cmplx<double> Rounder(0.5,0.5);
// Setting of the calculation accuracy for FFT_Inv2048 function
void FFT_Inv2048Set( int	Flag)			// See header for more information
{
	FlagsIFFT2048=Flag;
}
void FFT_Inv2048Set6bit()	// Sets 6-bit accuracy of sin-cosine coefficients
{
	FFT_Inv2048Set(FFT6BIT);
}
void FFT_Inv2048Set7bit()	// Sets 7-bit accuracy of sin-cosine coefficients
{
	FFT_Inv2048Set(FFT7BIT);
}
///////////////////////////////////////////////////////////////////
// Computing IFFT-2048 using fixed-point arithmetic
// This is the C equivalent of the FFT_Inv2048 Assembly Code
int FFT_Inv2048(
			vec<cmplx<int> > &X,		// input array
			vec<cmplx<int> > &Y,		// output array
			vec<cmplx<char> >  &IW1_2048,// table of coefficients
			vec<cmplx<char> >  &IW2_2048,// table of coefficients
			int Shr1,							// 1-st shiftr normalization
			int Shr2							// 2-nd shiftr normalization
			)
{
	ASSERTE(X.size==2048);
	ASSERTE(Y.size==2048);
	vec<cmplx<int> > S(2048);
	vec<cmplx<int> > T(2048);
	
	size_t l,p,i,j,n,idx;
	// first 2-point fft
	for (n=0;n<1024;n++)
	{
		S[n]	=X[n]+X[n+1024];
		S[n+1024]=X[n]-X[n+1024];
	}
	// second 32-point fft
	cmplx<int> Summ;
	for (i=0;i<32;i++)
	{
		idx=0;
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
				Summ+=IW1_2048[idx]*S[1024*0+32*j+i];
			T[1024*0+32*p+i]=Summ;
		}
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
				Summ+=IW1_2048[idx]*S[1024*1+32*j+i];
			T[1024*1+32*p+i]=Summ;
		}
	}

	if (Shr1>0)
	{
		
		//------- Roundation -----------------
		vec<cmplx<int> > VcRound(2048);
		cmplx<int> OneHalf(1<<(Shr1-1),1<<(Shr1-1));
		//VcRound=OneHalf;
		//T+=VcRound;
		T+=OneHalf;
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
               Summ+=IW2_2048[idx]*T[1024*0+32*p+i];
            Y[64*l+2*p+0]=Summ;
        }
		for (l=0;l<32;l++)
		{  
            Summ=0;
            for (i=0;i<32;i++,idx++)
               Summ+=IW2_2048[idx]*T[1024*1+32*p+i];
            Y[64*l+2*p+1]=Summ;
        }
	}
	if (Shr2>0)
	{
		//------- Roundation -----------------
		vec<cmplx<int> > VcRound(2048);
		cmplx<int >OneHalf(1<<(Shr2-1),1<<(Shr2-1));
		//VcRound=OneHalf;
		//Y+=VcRound;
		Y+=OneHalf;
		//-----------------------------------
		Y>>=Shr2;

	}
	return 0;
	
}

__INLINE__ cmplx<double> IW2048(size_t power)
{
	power-=(power>>11)<<11;
	cmplx<double>Z (0,double(power)*2.0*PI/2048.0);
	return exp(Z);

}

/////////////////////////////////////////////////////////////////////
//	 Initialization table of double coefficients 
void IMakeTable2048W1W2(
					vec<cmplx<double> > &IW1,
					vec<cmplx<double> > &IW2)
{
	ASSERTE(IW1.size==2048);
	ASSERTE(IW2.size==2048*32);

	size_t l,p,i,j;
	size_t idx=0;

	for (p=0;p<32;p++)
		for (j=0;j<32;j++,idx++)
			IW1[idx]=IW2048(32*(2*p+0)*j);

	for (p=0;p<32;p++)
		for (j=0;j<32;j++,idx++)
			IW1[idx]=IW2048(32*(2*p+1)*j);
	
	idx=0;
	for (p=0;p<32;p++)
	{
		for (l=0;l<32;l++)
	        for (i=0;i<32;i++,idx++)
               IW2[idx]=IW2048((64*l+2*p+0)*i);
		for (l=0;l<32;l++)
            for (i=0;i<32;i++,idx++)
               IW2[idx]=IW2048((64*l+2*p+1)*i);
	}
}


/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void IMakeTable2048W1W2(
				vec<cmplx<char> > &IW1_2048,
				vec<cmplx<char> > &IW2_2048,
				double Ampl)
{
	ASSERTE(IW1_2048.size==2048);
	ASSERTE(IW2_2048.size==2048*32);

	vec<cmplx<double > >  fIW1_2048(2048);
	vec<cmplx<double > >  fIW2_2048(2048*32);
	IMakeTable2048W1W2(fIW1_2048,fIW2_2048);
	cmplx<double> Mult(Ampl,0);
	fIW1_2048*=Mult;
	fIW2_2048*=Mult;
	int i;
	for(i=0;i<IW1_2048.size;i++)
	{
		IW1_2048[i].re=char(floor(fIW1_2048[i].re+0.5));
		IW1_2048[i].im=char(floor(fIW1_2048[i].im+0.5));
	}

	for(i=0;i<IW2_2048.size;i++)
	{
		IW2_2048[i].re=char(floor(fIW2_2048[i].re+0.5));
		IW2_2048[i].im=char(floor(fIW2_2048[i].im+0.5));
	}
}

/////////////////////////////////////////////////////////////////////
//	 This is the C equivalent of the FFT_Inv2048 Assembly Code 
void FFT_Inv2048(
			nm32sc*	SrcBuffer,	// Source buffer :long[2048]
			nm32sc*	DstBuffer,	// Result FFT    :long[2048]
			void*		LBuffer,	// DUMMY ARGUMENT Temp buffer   :long[2048*4]  
			void*		GBuffer,	// DUMMY ARGUMENT Temp buffer   :long[2048*4]
			int			ShiftR1,	// First Right shift normalization
			int			ShiftR2		// Final Right shift normalization
			)
{
	vec<cmplx<char> >  IW1_2048(2048);
	vec<cmplx<char> >  IW2_2048(2048*32);
	
	if (FlagsIFFT2048 & FFT7BIT==FFT7BIT)
	{
		IMakeTable2048W1W2(IW1_2048,IW2_2048,127.0);
		if (ShiftR2==-1)
			ShiftR2=14;
	}
	else
	{
		IMakeTable2048W1W2(IW1_2048,IW2_2048,64.0);
		if (ShiftR2==-1)
			ShiftR2=12;
	}
	
	vec<cmplx<int> > X((cmplx<int>*)SrcBuffer,2048);
	vec<cmplx<int> > Y((cmplx<int>*)DstBuffer,2048);
	
	FFT_Inv2048(X,Y,IW1_2048,IW2_2048,ShiftR1,ShiftR2);
}

///////////////////////////////////////////////////////////////////
// Computing IFFT-2048 using floating-point arithmetic
int IFFT2048(
		vec<cmplx<double> > &	X,	// Source buffer :long[1024]
		vec<cmplx<double> > &	Y	// Result IFFT    :long[1024]
		)
{
	ASSERTE(X.size==2048);
	ASSERTE(Y.size==2048);
	
	vec<cmplx<double> > S(2048);
	vec<cmplx<double> > T(2048);
	
	vec<cmplx<double > > IW1_2048(2048);
	vec<cmplx<double > > IW2_2048(2048*32);
	IMakeTable2048W1W2(IW1_2048,IW2_2048);
	
	
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
				Summ+=IW1_2048[idx]*S[1024*0+32*j+i];
			T[1024*0+32*p+i]=Summ;
		}
		for (p=0;p<32;p++)
		{
			Summ=0;
			for (j=0;j<32;j++,idx++)
				Summ+=IW1_2048[idx]*S[1024*1+32*j+i];
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
               Summ+=IW2_2048[idx]*T[1024*0+32*p+i];
            Y[64*l+2*p+0]=Summ;
        }
		for (l=0;l<32;l++)
		{  
            Summ=0;
            for (i=0;i<32;i++,idx++)
               Summ+=IW2_2048[idx]*T[1024*1+32*p+i];
            Y[64*l+2*p+1]=Summ;
        }
	}
	Y>>=11;
	return 0;
	
}
