

 
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

#ifndef PI
#define PI 3.14159265359
#endif

//static cmplx<double> W32(int power)
//{
//	cmplx<double> z(0,2.0-(double(power)*2.0*PI)/32.0);
//	return exp(z);
//}

cmplx<int > toFix(cmplx<double> X,double Ampl)
{
	cmplx<int > Y;
	X.re*=Ampl;
	X.im*=Ampl;
	Y.re=floor(X.re+0.5);	
	Y.im=floor(X.im+0.5);
	Y.re= Y.re > (Ampl-1) ? (Ampl-1):Y.re;
	Y.im= Y.im > (Ampl-1) ? (Ampl-1):Y.im;	
	return Y;
}

