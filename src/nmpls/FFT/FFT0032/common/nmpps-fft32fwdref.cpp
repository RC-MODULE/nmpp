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
//#include "fftext.h"
#include "nmtl/tcmplx_spec.h"
#include <math.h>
#include "nmpp.h"

#ifndef PI
#define PI 3.14159265359
#endif

//static cmplx<double> Rounder(0.5,0.5);

cmplx<double> W32(int power)
{
	power-=(power>>8)<<8;
	cmplx<double> z(0,-(double(power)*2.0*PI)/32.0);
	return exp(z);
}

cmplx<int > toFix(cmplx<double> X,double Ampl);

void nmppsFFT32FwdRef2x16( nm32sc* src, nm32sc* dst)
{
	int MAX=127;
	vec<cmplx<int> > x((cmplx<int>*)src,32);
	vec<cmplx<int> > y((cmplx<int>*)dst,32);
	vec<cmplx<int> > sum(16);
	vec<cmplx<int> > dif(16);
	
	for(int i=0; i<16; i++){
		sum[i]=x[i]+x[i+16];
		dif[i]=x[i]-x[i+16];
	}
	nmppsSet_64s((nm64s*)dst,0,32);
	
	for(int k=0; k<32; k+=2){
		for(int p=0; p<16; p++){
			y[k]+=toFix(W32(p*k),MAX)*sum[p];
		}
		y[k].re+=MAX/2;
		y[k].im+=MAX/2;
		y[k].re>>=7;
		y[k].im>>=7;
	}

	for(int k=1; k<32; k+=2){
		for(int p=0; p<16; p++){
			y[k]+=toFix(W32(p*k),MAX)*dif[p];
		}
		y[k].re+=MAX/2;
		y[k].im+=MAX/2;
		y[k].re>>=7;
		y[k].im>>=7;
	}
}
/*
void nmppsFFT32FwdRef2x16( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<int> > x((cmplx<int>*)src,32);
	vec<cmplx<int> > y((cmplx<int>*)dst,32);
	vec<cmplx<int> > sum(16);
	vec<cmplx<int> > dif(16);
	
	for(int i=0; i<16; i++){
		sum[i]=x[i]+x[i+16];
		dif[i]=x[i]-x[i+16];
	}
	
	for(int k=0; k<32; k+=2){
		y[k]=toFix(W32(0),127)*sum[0];
		for(int p=1; p<16; p++){
			y[k]+=toFix(W32(p*k),127)*sum[p];
		}
	}

	for(int k=1; k<32; k+=2){
		y[k]=toFix(W32(0),127)*dif[0];
		for(int p=1; p<16; p++){
			y[k]+=toFix(W32(p*k),127)*dif[p];
		}
	}
}*/


void nmppsFFT32FwdRef2x16_f( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(32);
	vec<cmplx<double> > y(32);
	vec<cmplx<double> > sum(16);
	vec<cmplx<double> > dif(16);
	
	for(int i=0; i<32; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
	}
	
	
	for(int i=0; i<16; i++){
		sum[i]=x[i]+x[i+16];
		dif[i]=x[i]-x[i+16];
	}
	
	for(int k=0; k<32; k+=2){
		y[k]=W32(0)*sum[0];
		for(int p=1; p<16; p++){
			y[k]+=W32(p*k)*sum[p];
		}
	}

	for(int k=1; k<32; k+=2){
		y[k]=W32(0)*dif[0];
		for(int p=1; p<16; p++){
			y[k]+=W32(p*k)*dif[p];
		}
	}
	
	for(int i=0; i<32; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}

