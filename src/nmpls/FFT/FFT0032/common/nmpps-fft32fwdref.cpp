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

#ifndef PI
#define PI 3.14159265359
#endif

static cmplx<double> Rounder(0.5,0.5);

cmplx<double> W32(int power)
{
	power-=(power>>8)<<8;
	cmplx<double> z(0,-(double(power)*2.0*PI)/32.0);
	return exp(z);
}

cmplx<int > toFix(cmplx<double> X,double Ampl)
{
	cmplx<int > Y;
	X.re*=Ampl;
	X.im*=Ampl;
	X+=Rounder;
	Y.re=X.re;	
	Y.im=X.im;	
	return Y;
}

void nmppsFFT32FwdRawRef2x16( nm32sc* src, nm32sc* dst)
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
}


