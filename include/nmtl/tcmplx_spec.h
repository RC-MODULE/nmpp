/////////////////////////////////////////////////////////////////////////////
//                                                                         // 
//  Header file of template class of complex numbers                        //
//                                                                         // 
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef _TCMPLX_CPEC_H_INCLUDED_
#define _TCMPLX_CPEC_H_INCLUDED_

#include <nmtl.h>



//------- Z>>=y -----------------------------------------------------------
template<>
cmplx<double>& cmplx<double>::operator>>= (const int Shr);
//{
//	double n=pow((double)2,Shr);
//	re/=n;
//	im/=n;
//	return (*this);
//}
/*
//------- Z=X>>y -----------------------------------------------------------
cmplx<double>	cmplx<double>::operator>> (const int y) const
{
	cmplx<T> z(*this);
	z>>=y;
	return z;
}*/
//------- Z<<=y -----------------------------------------------------------
template<>
cmplx<double>& cmplx<double>::operator<<= (const int Shl);
//{
//	double n=pow((double)2,Shl);
//	re*=n;
//	im*=n;
//	return (*this);
//}
/*
//------- Z=X<<y -----------------------------------------------------------
cmplx<double>	cmplx<double>::operator<< (const int y) const
{
	cmplx<T> z(*this);
	z<<=y;
	return z;
}
*/
//------------ Z=Y --------------------------------------------------
/*
template <class T> cmplx<T>::operator cmplx<double> ()
{
	cmplx<Double> DblComplex;
	DblComplex.re=re;
	DblComplex.im=im;
	return (DblComplex);
}	 
*/

#endif
