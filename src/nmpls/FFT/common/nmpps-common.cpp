

 
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
//#include "fft.h"
//#include "fftext.h"
#include "nmtl.h"
#include <math.h>

#ifndef PI
#define PI 3.14159265359
#endif


template<int power> void expFFT(int arg, float* re, float* im)
{
	float x=-2.0*PI/power*arg;
	*re=cosf(x);
	*im=sinf(x);
}

template<int power> cmplx<double> expFFT(int arg)
{
	cmplx<double> z;
	float im=-2.0*PI/power*arg;
	z.re=cosf(im);
	z.im=sinf(im);
	return z;
}

template<int power> void expFFT_8s(int arg, int amplitude, nm32sc* z)
{
	float re;
	float im;
	expFFT<power>(arg,&re,&im);
	z->re=floor(re+0.5);	
	z->im=floor(im+0.5);
	z->re= z->re > 127 ? 127:z->re;
	z->im= z->im > 127 ? 127:z->im;	
}

template<int power> nm32sc expFFT_8s(int arg, int amplitude)
{
	float re;
	float im;
	nm32sc z;
	expFFT<power>(arg,&re,&im);
	z.re=floor(re+0.5);	
	z.im=floor(im+0.5);
	z.re= z.re > 127 ? 127:z.re;
	z.im= z.im > 127 ? 127:z.im;	
	return z;
}


template<int power> void expFFT_16s(int arg, int amplitude, nm32sc* z)
{
	float re;
	float im;
	expFFT<power>(arg,&re,&im);
	z->re=floor(re+0.5);	
	z->im=floor(im+0.5);
}



/*
	cmplx<int > toFix(cmplx<double> X,double Ampl)
	{
		cmplx<int > Y;
		X.re*=Ampl;
		X.im*=Ampl;
		Y.re=floor(X.re+0.5);	
		Y.im=floor(X.im+0.5);
		if (Ampl>127){
			Y.re= Y.re > 127 ? 127:Y.re;
			Y.im= Y.im > 127 ? 127:Y.im;	
		}
		return Y;
	}
		
}
*/

cmplx<int > cos2048(cmplx<double> X,double Ampl)
{
	cmplx<int > Y;
	X.re*=Ampl;
	X.im*=Ampl;
	Y.re=floor(X.re+0.5);	
	Y.im=floor(X.im+0.5);
	if (Ampl>127){
		Y.re= Y.re > 127 ? 127:Y.re;
		Y.im= Y.im > 127 ? 127:Y.im;	
	}
	return Y;
}

cmplx<int > toFix(cmplx<double> X,double Ampl)
{
	cmplx<int > Y;
	X.re*=Ampl;
	X.im*=Ampl;
	Y.re=floor(X.re+0.5);	
	Y.im=floor(X.im+0.5);
	return Y;
}
cmplx<int > toFix127(cmplx<double> X,double Ampl)
{
	cmplx<int > Y;
	X.re*=Ampl;
	X.im*=Ampl;
	Y.re=floor(X.re+0.5);	
	Y.im=floor(X.im+0.5);
	if (Ampl>127){
		Y.re= Y.re > 127 ? 127:Y.re;
		Y.im= Y.im > 127 ? 127:Y.im;	
	}
	return Y;
}


static nm32sc wfifo[32];
static int wfifoSize;


void load_wfifo(nm64s* wfifoData, int wfifoStep, int size){
	wfifoSize=size;
	for(int i=0; i<wfifoSize; i++){
		nm32sc* w=(nm32sc*)wfifoData;
		wfifo[i].re=w->re;
		wfifo[i].im=w->im;
		wfifoData+=wfifoStep;
	}
}

void load_wfifo(cmplx<int>* wcoef, int wstep, int size){
	load_wfifo((nm64s*)wcoef, wstep, size);
}

void load_wfifo(nm32sc* wcoef, int wstep, int size){
	load_wfifo((nm64s*)wcoef, wstep, size);
}

void vsum_data(nm8s* data,  nm32sc* afifo, int vr){

	afifo->re=vr;
	afifo->im=vr;
	for(int i=0; i<8; i++){
		afifo->re+=data[i]*wfifo[i].re;
		afifo->im+=data[i]*wfifo[i].im;
	}
}

void vsum_data(nm16s* data,  nm32sc* afifo, int vr){

	afifo->re=vr;
	afifo->im=vr;
	for(int i=0; i<4; i++){
		afifo->re+=data[i]*wfifo[i].re;
		afifo->im+=data[i]*wfifo[i].im;
	}
}
void vsum_data(nm16s* data,  cmplx<int>* afifo, int vr){

	vsum_data(data,  (nm32sc*)afifo, vr);
}


void vsum_data(nm8s* data,  cmplx<int>* afifo, int vr){
	vsum_data(data,  (nm32sc*)afifo, vr);
}

