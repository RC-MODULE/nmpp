//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcFFT256.cpp                                        */
//*   Contents:         C++ Equivalent function of the FFT_Fwd256.            */
//*                     Additional FFT256 functions using                   */
//*                         fixed and floating-point arithmetic             */ 
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

int	FlagsFFT256=FFT7BIT;	// if 0 (FFT7BIT)- 127.99999 multiplier is used
							// if 1 (FFT6BIT)- 64.000000 multiplier is used 
extern "C" {  
// Setting of the calculation accuracy for FFT_Fwd256 function
void FFT_Fwd256Set( int	Flag)			// See header for more information
{
	FlagsFFT256=Flag;
}
void FFT_Fwd256Set6bit()	// Sets 6-bit accuracy of sin-cosine coefficients
{
	FFT_Fwd256Set(FFT6BIT);
}
void FFT_Fwd256Set7bit()	// Sets 7-bit accuracy of sin-cosine coefficients
{
	FFT_Fwd256Set(FFT7BIT);
}

};

static cmplx<double> Rounder(0.5,0.5);
///////////////////////////////////////////////////////////////////
// Computing FFT-256 using fixed-point arithmetic
// This is the C equivalent of the FFT_Fwd256 Assembly Code
int FFT_Fwd256(
			vec<cmplx<int > > &X,
			vec<cmplx<int > > &Y,
			vec<cmplx<char > >  &W1_256, //(16*16*16);
			vec<cmplx<char > >  &W2_256,	//(16*16*16);
			int Shr1,
			int Shr2
			)
{
	ASSERTE(W1_256.size==16*16*16);
	ASSERTE(W2_256.size==16*16*16);
	vec<cmplx<int > >  S(256);
	// first 16-point fft
	cmplx<int > Summ;
	int idx=0;
	for (int k=0;k<16;k++)
		for (int n=0;n<16;n++)
		{
			Summ=0;
			for (int i=0;i<16;i++)
				Summ+=W1_256[idx++]*X[16*i+n];
			S[16*k+n]=Summ;
		}

	if (Shr1>0)
	{
		// Not implemented in FFT_Inv1024
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(256);
		cmplx<int >OneHalf(1<<(Shr1-1),1<<(Shr1-1));
		cmplx<int >Zero(0);
		VcRound=OneHalf;
		S+=VcRound;
		//-----------------------------------
		S>>=Shr1; 
	}
	// second 16-point fft
	idx=0;
	for (int p=0;p<16;p++)
		for (int k=0;k<16;k++)
		{
			Summ=0;
			for (int n=0;n<16;n++)
				Summ+=W2_256[idx++]*S[16*k+n];
			Y[16*p+k]=Summ;
		}
	
	if (Shr2>0)
	{
		//------- Roundation -----------------
		vec<cmplx<int > > VcRound(256);
		cmplx<int >OneHalf(1<<(Shr2-1),1<<(Shr2-1));
		cmplx<int >Zero(0);
		VcRound=OneHalf;
		Y+=VcRound;
		//-----------------------------------
		Y>>=Shr2;
	}
	return 0;
}


cmplx<double> W256(int power)
{
	power-=(power>>8)<<8;
	cmplx<double> z(0,-(double(power)*2.0*PI)/256.0);
	return exp(z);
}
/////////////////////////////////////////////////////////////////////
//	 Initialization table of double coefficients 
void MakeTable256W1W2(
				vec<cmplx<double > > &W1_256,
				vec<cmplx<double > > &W2_256)
{
	ASSERTE(W1_256.size==16*16*16);
	ASSERTE(W2_256.size==16*16*16);
	int idx=0;
	for (int k=0;k<16;k++)
		for (int n=0;n<16;n++)
			for (int i=0;i<16;i++)
				W1_256[idx++]=W256(16*k*i);
	idx=0;
	for (int p=0;p<16;p++)
		for (int k=0;k<16;k++)
			for (int n=0;n<16;n++)
				W2_256[idx++]=W256((16*p+k)*n);
	
}

/////////////////////////////////////////////////////////////////////
//	 Initialization table of char coefficients 
void MakeTable256W1W2(
				vec<cmplx<char> > &W1_256,
				vec<cmplx<char> > &W2_256,
				double Ampl)
{
	ASSERTE(W1_256.size==16*16*16);
	ASSERTE(W2_256.size==16*16*16);

	vec<cmplx<double> >  fW1_256(16*16*16);
	vec<cmplx<double> >  fW2_256(16*16*16);
	MakeTable256W1W2(fW1_256,fW2_256);
	cmplx<double> Mult(Ampl,0);
	fW1_256*=(Mult);
	fW2_256*=Mult;

	for(int i=0;i<W1_256.size;i++)
	{
		W1_256[i].re=floor(fW1_256[i].re+0.5);
		W1_256[i].im=floor(fW1_256[i].im+0.5);
		W2_256[i].re=floor(fW2_256[i].re+0.5);
		W2_256[i].im=floor(fW2_256[i].im+0.5);
	}


}

extern "C"{

/////////////////////////////////////////////////////////////////////
//	 This is the C equivalent of the function FFT_Fwd256 
void FFT_Fwd256(
			nm32sc*	GSrcBuffer,	// Source buffer :long[256]
			nm32sc*	LDstBuffer,	// Result FFT    :long[256]
			void*		LBuffer,	// Temp buffer   :long[256*3]
			void*		GBuffer,	// Temp buffer   :long[256*2]
			int			ShiftR		// Shift normalization
			)
{
	vec<cmplx<int> > X((cmplx<int>*)GSrcBuffer,256);
	vec<cmplx<int> > Y((cmplx<int>*)LDstBuffer,256);
	
	vec<cmplx<char> >  W1_256(16*16*16);
	vec<cmplx<char> >  W2_256(16*16*16);

	if (FlagsFFT256 & FFT7BIT==FFT7BIT)
	{
		MakeTable256W1W2(W1_256,W2_256,127.0);
		if (ShiftR==-1)
			ShiftR=14;
	}
	else
	{
		MakeTable256W1W2(W1_256,W2_256,64.0);
		if (ShiftR==-1)
			ShiftR=12;
	}
	
	FFT_Fwd256(X,Y,W1_256,W2_256,0,ShiftR);

}

};
///////////////////////////////////////////////////////////////////
// Computing FFT-256 using floating-point arithmetic by radix-16-16 method
int FFT256(
		vec<cmplx<double> > &	X,	// Source buffer 
		vec<cmplx<double> > &	Y	// Result FFT    
		)
{
	ASSERTE(X.size==256);
	ASSERTE(Y.size==256);

	vec<cmplx<double> >  W1_256(16*16*16);
	vec<cmplx<double> >  W2_256(16*16*16);
	MakeTable256W1W2(W1_256,W2_256);
	vec<cmplx<double> >  S(256);
	
	cmplx<double> Summ;
	// first 16-point fft
	for (int k=0;k<16;k++)
		for (int n=0;n<16;n++)
		{
			Summ=0;
			for (int i=0;i<16;i++)
				Summ+=W256(16*k*i)*X[16*i+n];
			S[16*k+n]=Summ;
		}

	// second 16-point fft
	for (int p=0;p<16;p++)
		for (int k=0;k<16;k++)
		{
			Summ=0;
			for (int n=0;n<16;n++)
				Summ+=W256((16*p+k)*n)*S[16*k+n];
			Y[16*p+k]=Summ;
		}
	return 0;
}
/*
///////////////////////////////////////////////////////////////////
// Computing DFT-256 using floating-point arithmetic 
int DFT256_radix2(
		vec<cmplx<double> > &	X,	// Source buffer :long[256]
		vec<cmplx<double> > &	Y	// Result FFT    :long[256]
		)
{
	ASSERTE(X.size==256);
	ASSERTE(Y.size==256);



	cmplx<double> S0,S1,S2,S3,S4,S5,S6,S7;

	for (int k=0,S0=0;k<256;k++)
	{
		for (int n0=0,S1=0;n0<2;n0++)
		{
			for (int n1=0,S2=0;n1<2;n1++)
			{
				for (int n2=0,S3=0;n2<2;n2++)
				{
					for (int n3=0,S4=0;n3<2;n3++)
					{
						for (int n4=0,S5=0;n4<2;n4++)
						{
							for (int n5=0,S6=0;n5<2;n5++)
							{
								for (int n6=0,S7=0;n6<2;n6++)
								{
									for (int n7=0;n7<2;n7++)
										S7+=W256(k*n7<<7)*X[(n7<<7)+(n6<<6)+(n5<<5)+(n4<<4)+(n3<<3)+(n2<<2)+(n1<<1)+n0];
									S6+=W256(k*n6<<6)*S7;
								}
								S5+=W256(k*n5<<5)*S6;
							}
							S4+=W256(k*n4<<4)*S5;
						}
						S3+=W256(k*n3<<3)*S4;
					}
					S2+=W256(k*n2<<2)*S3;
				}
				S1+=W256(k*n1<<1)*S2;
			}
			S0+=W256(k*n0)*S1;
		}
		Y[k]=S0;
	}
	return 0;
}
*/
/////////////////////////////////////////////////////////////////////////////////////
// Computing FFT-256 using floating-point arithmetic by radix-2 method
int FFT256_radix2(
		vec<cmplx<double> > &	X,	// Source buffer 
		vec<cmplx<double> > &	Y	// Result FFT    
		)
{
	ASSERTE(X.size==256);
	ASSERTE(Y.size==256);

	cmplx<double> S;
	
	vec<cmplx<double> > A(256),B(256);
	
	//Stage-1
//	Clear(A);
	A.reset();
	for (int k0=0;k0<2;k0++)
		for (int n0=0;n0<2;n0++)
			for (int n1=0;n1<2;n1++)
				for (int n2=0;n2<2;n2++)
					for (int n3=0;n3<2;n3++)
						for (int n4=0;n4<2;n4++)
							for (int n5=0;n5<2;n5++)
								for (int n6=0;n6<2;n6++)
								{
									S=0;
									int p=(n6<<6)+(n5<<5)+(n4<<4)+(n3<<3)+(n2<<2)+(n1<<1)+n0;
									for (int n7=0;n7<2;n7++)
										S+=W256(k0*n7<<7)*X[(n7<<7)+p];
									A[(k0<<7)+p]=S;
								}
	//Stage-2
//	Clear(B);
	B.reset();
	for (int k1=0;k1<2;k1++)
		for (int k0=0;k0<2;k0++)
			for (int n0=0;n0<2;n0++)
				for (int n1=0;n1<2;n1++)
					for (int n2=0;n2<2;n2++)
						for (int n3=0;n3<2;n3++)
							for (int n4=0;n4<2;n4++)
								for (int n5=0;n5<2;n5++)
								{
									S=0;
									int p=(n5<<5)+(n4<<4)+(n3<<3)+(n2<<2)+(n1<<1)+n0;
									for (int n6=0;n6<2;n6++)
										S+=W256((k1*2+k0)*n6<<6)*A[(k0<<7)+(n6<<6)+p];
									B[((k1*2+k0)<<6)+p]=S;

								}
	//Stage-3
//	Clear(A);
	A.reset();
	for (int k2=0;k2<2;k2++)
		for (int k1=0;k1<2;k1++)
			for (int k0=0;k0<2;k0++)
				for (int n0=0;n0<2;n0++)
					for (int n1=0;n1<2;n1++)
						for (int n2=0;n2<2;n2++)
							for (int n3=0;n3<2;n3++)
								for (int n4=0;n4<2;n4++)
								{
									S=0;
									int p=(n4<<4)+(n3<<3)+(n2<<2)+(n1<<1)+n0;
									for (int n5=0;n5<2;n5++)
										S+=W256((k2*4+k1*2+k0)*n5<<5)*B[((k1*2+k0)<<6)+(n5<<5)+p];
									A[((k2*4+k1*2+k0)<<5)+p]=S;
								}
	//Stage-4		
//	Clear(B);
	B.reset();
	for (int k3=0;k3<2;k3++)
		for (int k2=0;k2<2;k2++)
			for (int k1=0;k1<2;k1++)
				for (int k0=0;k0<2;k0++)
					for (int n0=0;n0<2;n0++)
						for (int n1=0;n1<2;n1++)
							for (int n2=0;n2<2;n2++)
								for (int n3=0;n3<2;n3++)
								{
									S=0;
									int p=(n3<<3)+(n2<<2)+(n1<<1)+n0;
									for (int n4=0;n4<2;n4++)
										S+=W256((k3*8+k2*4+k1*2+k0)*n4<<4)*A[((k2*4+k1*2+k0)<<5)+(n4<<4)+p];
									B[((k3*8+k2*4+k1*2+k0)<<4)+p]=S;
								}
	//Stage-5					
//	Clear(A);
	A.reset();
	for (int k4=0;k4<2;k4++)
		for (int k3=0;k3<2;k3++)
			for (int k2=0;k2<2;k2++)
				for (int k1=0;k1<2;k1++)
					for (int k0=0;k0<2;k0++)
						for (int n0=0;n0<2;n0++)
							for (int n1=0;n1<2;n1++)
								for (int n2=0;n2<2;n2++)
								{
									S=0;
									int p=(n2<<2)+(n1<<1)+n0;
									for (int n3=0;n3<2;n3++)
										S+=W256((k4*16+k3*8+k2*4+k1*2+k0)*n3<<3)*B[((k3*8+k2*4+k1*2+k0)<<4)+(n3<<3)+p];
									A[((k4*16+k3*8+k2*4+k1*2+k0)<<3)+p]=S;
								}
	//Stage-6
//	Clear(B);
	B.reset();
	for (int k5=0;k5<2;k5++)
		for (int k4=0;k4<2;k4++)
			for (int k3=0;k3<2;k3++)
				for (int k2=0;k2<2;k2++)
					for (int k1=0;k1<2;k1++)
						for (int k0=0;k0<2;k0++)
							for (int n0=0;n0<2;n0++)
								for (int n1=0;n1<2;n1++)
								{
									S=0;
									int p=(n1<<1)+n0;
									for (int n2=0;n2<2;n2++)
										S+=W256((k5*32+k4*16+k3*8+k2*4+k1*2+k0)*n2<<2)*A[((k4*16+k3*8+k2*4+k1*2+k0)<<3)+(n2<<2)+p];
									B[((k5*32+k4*16+k3*8+k2*4+k1*2+k0)<<2)+p]=S;
								}

	//Stage-7					
//	Clear(A);
	A.reset();
	for (int k6=0;k6<2;k6++)
		for (int k5=0;k5<2;k5++)
			for (int k4=0;k4<2;k4++)
				for (int k3=0;k3<2;k3++)
					for (int k2=0;k2<2;k2++)
						for (int k1=0;k1<2;k1++)
							for (int k0=0;k0<2;k0++)
								for (int n0=0;n0<2;n0++)
								{
									S=0;
									int p=n0;
									for (int n1=0;n1<2;n1++)
										S+=W256((k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0)*n1<<1)*B[((k5*32+k4*16+k3*8+k2*4+k1*2+k0)<<2)+(n1<<1)+p];
									A[((k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0)<<1)+p]=S;
								}

	//Stage-8
	for (int k7=0;k7<2;k7++)
		for (int k6=0;k6<2;k6++)
			for (int k5=0;k5<2;k5++)
				for (int k4=0;k4<2;k4++)
					for (int k3=0;k3<2;k3++)
						for (int k2=0;k2<2;k2++)
							for (int k1=0;k1<2;k1++)
								for (int k0=0;k0<2;k0++)
								{
									S=0;
									for (int n0=0;n0<2;n0++)
										S+=W256((k7*128+k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0)*n0)*A[((k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0)<<1)+n0];
									Y[k7*128+k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0]=S;
								}


	return 0;
}

cmplx<int > ToFix(cmplx<double> X,double Ampl)
{
	cmplx<int > Y;
	X.re*=Ampl;
	X.im*=Ampl;
	X+=Rounder;
	Y.re=X.re;	
	Y.im=X.im;	

	return Y;
}

/////////////////////////////////////////////////////////////////////////////////////
// Computing FFT-256 using fixed-point arithmetic by radix-2 method
int FFT256_int_radix2(
		vec<cmplx<int > > &X,
		vec<cmplx<int > > &Y)
		
{
	ASSERTE(X.size==256);
	ASSERTE(Y.size==256);

	cmplx<int > S;
	int ShrA;
	int ShrB;
	double Ampl;
	
	if (FlagsFFT256==FFT7BIT)
	{
		Ampl=127.0;
		ShrA=0;
		ShrB=14;
	}
	else
	{
		Ampl=64.0;
		ShrA=0;
		ShrB=12;
		
	}

	vec<cmplx<int > > VcRoundA(256);
	vec<cmplx<int > > VcRoundB(256);
	if (ShrA>0)
	{
		cmplx<int >OneHalf(1<<(ShrA-1),1<<(ShrA-1));
		cmplx<int >Zero(0);
		VcRoundA=OneHalf;
	}			
	if (ShrB>0)
	{
		cmplx<int >OneHalf(1<<(ShrB-1),1<<(ShrB-1));
		cmplx<int >Zero(0);
		VcRoundB=OneHalf;
	}			

	vec<cmplx<int > > A(256),B(256);
	
	//Stage-1
	for (int k0=0;k0<2;k0++)
		for (int n0=0;n0<2;n0++)
			for (int n1=0;n1<2;n1++)
				for (int n2=0;n2<2;n2++)
					for (int n3=0;n3<2;n3++)
						for (int n4=0;n4<2;n4++)
							for (int n5=0;n5<2;n5++)
								for (int n6=0;n6<2;n6++)
								{
									S=0;
									int p=(n6<<6)+(n5<<5)+(n4<<4)+(n3<<3)+(n2<<2)+(n1<<1)+n0;
									for (int n7=0;n7<2;n7++)
										S+=ToFix(W256(k0*n7<<7),Ampl)*X[(n7<<7)+p];
									A[(k0<<7)+p]=S;
								}
	//------- Roundation -----------------
	if (ShrA>0)
	{
		A+=VcRoundA;
		A>>=ShrA;
	}
	//Stage-2
	for (int k1=0;k1<2;k1++)
		for (int k0=0;k0<2;k0++)
			for (int n0=0;n0<2;n0++)
				for (int n1=0;n1<2;n1++)
					for (int n2=0;n2<2;n2++)
						for (int n3=0;n3<2;n3++)
							for (int n4=0;n4<2;n4++)
								for (int n5=0;n5<2;n5++)
								{
									S=0;
									int p=(n5<<5)+(n4<<4)+(n3<<3)+(n2<<2)+(n1<<1)+n0;
									for (int n6=0;n6<2;n6++)
										S+=ToFix(W256((k1*2+k0)*n6<<6),Ampl)*A[(k0<<7)+(n6<<6)+p];
									B[((k1*2+k0)<<6)+p]=S;

								}
	
	//------- Roundation -----------------
	if (ShrB>0)
	{
		B+=VcRoundB;
		B>>=ShrB;
	}

	//Stage-3
	for (int k2=0;k2<2;k2++)
		for (int k1=0;k1<2;k1++)
			for (int k0=0;k0<2;k0++)
				for (int n0=0;n0<2;n0++)
					for (int n1=0;n1<2;n1++)
						for (int n2=0;n2<2;n2++)
							for (int n3=0;n3<2;n3++)
								for (int n4=0;n4<2;n4++)
								{
									S=0;
									int p=(n4<<4)+(n3<<3)+(n2<<2)+(n1<<1)+n0;
									for (int n5=0;n5<2;n5++)
										S+=ToFix(W256((k2*4+k1*2+k0)*n5<<5),Ampl)*B[((k1*2+k0)<<6)+(n5<<5)+p];
									A[((k2*4+k1*2+k0)<<5)+p]=S;
								}
	//------- Roundation -----------------
	if (ShrA>0)
	{
		A+=VcRoundA;
		A>>=ShrA;
	}
	
	//Stage-4		
	for (int k3=0;k3<2;k3++)
		for (int k2=0;k2<2;k2++)
			for (int k1=0;k1<2;k1++)
				for (int k0=0;k0<2;k0++)
					for (int n0=0;n0<2;n0++)
						for (int n1=0;n1<2;n1++)
							for (int n2=0;n2<2;n2++)
								for (int n3=0;n3<2;n3++)
								{
									S=0;
									int p=(n3<<3)+(n2<<2)+(n1<<1)+n0;
									for (int n4=0;n4<2;n4++)
										S+=ToFix(W256((k3*8+k2*4+k1*2+k0)*n4<<4),Ampl)*A[((k2*4+k1*2+k0)<<5)+(n4<<4)+p];
									B[((k3*8+k2*4+k1*2+k0)<<4)+p]=S;
								}
	
	//------- Roundation -----------------
	if (ShrB>0)
	{
		B+=VcRoundB;
		B>>=ShrB;
	}

	//Stage-5					
	for (int k4=0;k4<2;k4++)
		for (int k3=0;k3<2;k3++)
			for (int k2=0;k2<2;k2++)
				for (int k1=0;k1<2;k1++)
					for (int k0=0;k0<2;k0++)
						for (int n0=0;n0<2;n0++)
							for (int n1=0;n1<2;n1++)
								for (int n2=0;n2<2;n2++)
								{
									S=0;
									int p=(n2<<2)+(n1<<1)+n0;
									for (int n3=0;n3<2;n3++)
										S+=ToFix(W256((k4*16+k3*8+k2*4+k1*2+k0)*n3<<3),Ampl)*B[((k3*8+k2*4+k1*2+k0)<<4)+(n3<<3)+p];
									A[((k4*16+k3*8+k2*4+k1*2+k0)<<3)+p]=S;
								}
	//------- Roundation -----------------
	if (ShrA>0)
	{
		A+=VcRoundA;
		A>>=ShrA;
	}
	
	//Stage-6
	for (int k5=0;k5<2;k5++)
		for (int k4=0;k4<2;k4++)
			for (int k3=0;k3<2;k3++)
				for (int k2=0;k2<2;k2++)
					for (int k1=0;k1<2;k1++)
						for (int k0=0;k0<2;k0++)
							for (int n0=0;n0<2;n0++)
								for (int n1=0;n1<2;n1++)
								{
									S=0;
									int p=(n1<<1)+n0;
									for (int n2=0;n2<2;n2++)
										S+=ToFix(W256((k5*32+k4*16+k3*8+k2*4+k1*2+k0)*n2<<2),Ampl)*A[((k4*16+k3*8+k2*4+k1*2+k0)<<3)+(n2<<2)+p];
									B[((k5*32+k4*16+k3*8+k2*4+k1*2+k0)<<2)+p]=S;
								}
	//------- Roundation -----------------
	if (ShrB>0)
	{
		B+=VcRoundB;
		B>>=ShrB;
	}

	//Stage-7					
	for (int k6=0;k6<2;k6++)
		for (int k5=0;k5<2;k5++)
			for (int k4=0;k4<2;k4++)
				for (int k3=0;k3<2;k3++)
					for (int k2=0;k2<2;k2++)
						for (int k1=0;k1<2;k1++)
							for (int k0=0;k0<2;k0++)
								for (int n0=0;n0<2;n0++)
								{
									S=0;
									int p=n0;
									for (int n1=0;n1<2;n1++)
										S+=ToFix(W256((k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0)*n1<<1),Ampl)*B[((k5*32+k4*16+k3*8+k2*4+k1*2+k0)<<2)+(n1<<1)+p];
									A[((k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0)<<1)+p]=S;
								}
	//------- Roundation -----------------
	if (ShrA>0)
	{
		A+=VcRoundA;
		A>>=ShrA;
	}
	
	//Stage-8
	for (int k7=0;k7<2;k7++)
		for (int k6=0;k6<2;k6++)
			for (int k5=0;k5<2;k5++)
				for (int k4=0;k4<2;k4++)
					for (int k3=0;k3<2;k3++)
						for (int k2=0;k2<2;k2++)
							for (int k1=0;k1<2;k1++)
								for (int k0=0;k0<2;k0++)
								{
									S=0;
									for (int n0=0;n0<2;n0++)
										S+=ToFix(W256((k7*128+k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0)*n0),Ampl)*A[((k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0)<<1)+n0];
									Y[k7*128+k6*64+k5*32+k4*16+k3*8+k2*4+k1*2+k0]=S;
								}

	//------- Roundation -----------------
	if (ShrB>0)
	{
		Y+=VcRoundB;
		Y>>=ShrB;
	}
	return 0;
}