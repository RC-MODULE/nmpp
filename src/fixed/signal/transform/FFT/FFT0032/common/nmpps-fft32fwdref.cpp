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
//*                                                                         */
//***************************************************************************/

#include "fft.h"
#include "nmtl/tcmplx_spec.h"
#include <math.h>
#include "nmpp.h"

#ifndef PI
#define PI 3.14159265359
#endif


cmplx<double> W32(int power)
{
	power-=(power>>8)<<8;
	cmplx<double> z(0,-(double(power)*2.0*PI)/32.0);
	return exp(z);
}

cmplx<int > toFix(cmplx<double> X,double Ampl);


#ifdef __cplusplus
		extern "C" {
#endif
void nmppsFFT32FwdRef2x16( nm32sc* src, nm32sc* dst)
{
	int MAX=128;
	vec<cmplx<int> > x((cmplx<int>*)src,32);
	vec<cmplx<int> > y((cmplx<int>*)dst,32);
	vec<cmplx<int> > sum(16);
	vec<cmplx<int> > dif(16);
	nmppsSet_64s(0, (nm64s*)dst, 32);
	
	//------- stage 1 --------------
	for(int i=0; i<16; i++){
		sum[i]=x[i]+x[i+16];
		dif[i]=x[i]-x[i+16];
	}
	//------- stage 2 -------------
	// stage 2.1
	for(int k=0; k<32; k+=2){
		for(int p=0; p<16; p++){
			y[k]+=toFix(W32(p*k),MAX)*sum[p];
		}
		y[k].re+=MAX/2;
		y[k].im+=MAX/2;
		y[k].re>>=7;
		y[k].im>>=7;
	}
	// stage 2.2
	for(int k=1; k<32; k+=2){
		for(int p=0; p<16; p++){
			y[k]+=toFix(W32(p*k),MAX)*dif[p];
		}
		y[k].re+=MAX/2;
		y[k].im+=MAX/2;
		y[k].re>>=7;
		y[k].im>>=7;
	}
	//---------------------------------
}


void nmppsFFT32FwdRef2x16_f( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(32);
	vec<cmplx<double> > y(32);
	vec<cmplx<double> > sum(16);
	vec<cmplx<double> > dif(16);
	//-------------- copy -------
	for(int i=0; i<32; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
	}
	//---------- stage 1 --------------
	for(int i=0; i<16; i++){
		sum[i]=x[i]+x[i+16];
		dif[i]=x[i]-x[i+16];
	}
	//---------- stage 2 --------------
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
	//--------- round --------------
	for(int i=0; i<32; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}



#ifdef __cplusplus
		};
#endif