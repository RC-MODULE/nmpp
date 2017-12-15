/////////////////////////////////////////////////////////////////////////////
//                                                                         // 
//  Header file of template class of complex numbers                        //
//                                                                         // 
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef _TCMPLX_H_INCLUDED_
#define _TCMPLX_H_INCLUDED_

#ifdef __cplusplus

#include <assert.h>
#include <math.h>



//*****************************************************************************
/**
	 \ingroup nmtl
	 \ru Класс комплексных чисел.
	 \en Class of complex numbers
	
		\~
	   \ru \par Примеры:
		 \en \par Example:
			\~
			\code
      cmplx<double> a0(1,-1);
      cmplx<double> b0(1,-1);
      cmplx<double> c0;
      c0=a0+b0;
      c0=a0*b0;
      c0*=a0;

      cmplx<int> a1(1,-1);
      cmplx<int> b1(1,-1);
      cmplx<int> c1;
      c1=a1+b1;
      c1=a1*b1;
      c1*=a1;
      c1=c1.conjg();
      int re1=c1.real();
      int im1=c1.imag();

			\endcode
*/

//*****************************************************************************


template <class T> class cmplx 
{
public:
	T re;
	T im;
	
	cmplx()
		:re(0),im(0){}
	cmplx(T _re)
		:re(_re),im(0){}
	cmplx(T _re,T _im)
		:re(_re),im(_im){}
	cmplx(const cmplx<T>& c)
		:re(c.re),im(c.im){}
	explicit cmplx(cmplx<long long>& c)
		:re(c.re),im(c.im){}
	//------------ Z=Y --------------------------------------------------
/*
	cmplx<T>& operator= ( cmplx<T>& y)
	{
		re=y.re;
		im=y.im;
		return (*this);
	}	 

	cmplx<T>& operator= (const cmplx<T>& y)
	{
		re=y.re;
		im=y.im;
		return (*this);
	}	 

	//------------ Z=Y --------------------------------------------------
	cmplx<T>& operator= (const double y)
	{
		re=y;
		im=0;
		return (*this);
	}	 
	*/
	//------------ Z=Y --------------------------------------------------
	cmplx<T>& operator= (const int y)
	{
		re=y;
		im=0;
		return (*this);
	}	 

	cmplx<T>&	operator+=	(const cmplx<T>& y);
	cmplx<T>	operator+	(const cmplx<T>& y) const;
	cmplx<T>&	operator-=	(const cmplx<T>& y);
	cmplx<T>	operator-	(const cmplx<T>& y) const;
	//------------ Z*=Y --------------------------------------------------
	cmplx<T>&	operator*= (const cmplx<T>& y)
	{
		cmplx<T> x(*this);
		re=x.re*y.re-x.im*y.im;
		im=x.re*y.im+x.im*y.re;
		return (*this);
	}
	//------------ Z=X*Y --------------------------------------------------
	template <class P> cmplx<P> operator* (const cmplx<P>& y) const
	{
		cmplx<P> z;
		z.re=re*y.re-im*y.im;
		z.im=re*y.im+im*y.re;
		return z;
	}
	cmplx<T>&	operator/=	(const cmplx<T>& y);
	cmplx<T>	operator/	(const cmplx<T>& y) const;
	cmplx<T>	operator-	(void) const;
	//------- Z>>=y -----------------------------------------------------------
	cmplx<T>& operator>>= (const int y) 
	{
		re>>=y;
		im>>=y;
		return (*this);
	}

	//------- Z=X>>y -----------------------------------------------------------
	cmplx<T> operator>> (const int y) const
	{
		cmplx<T> z(*this);
		z>>=y;
		return z;
	}
	//------- Z<<=y -----------------------------------------------------------
	cmplx<T>& operator<<= (const int y) 
	{
		re<<=y;
		im<<=y;
		return (*this);
	}
	//------- Z=X<<y -----------------------------------------------------------
	cmplx<T> operator<< (const int y) const
	{
		cmplx<T> z(*this);
		z<<=y;
		return z;
	}

	bool		operator==	(const cmplx<T>& y) const
	{
		return ((re==y.re)&&(im==y.im));
	}

	bool		operator!=	(const cmplx<T>& y) const
	{
		return ((re!=y.re)||(im!=y.im));
	}

	cmplx<T>	conjg		() const;
	T			real		() const;
	void		real		(const T& Re);
	T			imag		() const;
	void		imag		(const T& Im);
		
};

//
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
//------------ Z+=Y --------------------------------------------------
template <class T> cmplx<T>& cmplx<T>::operator+= (const cmplx<T>& y)
{
	re+=y.re;
	im+=y.im;
	return (*this);
}
//------------ Z=X+Y --------------------------------------------------
template <class T> cmplx<T> cmplx<T>::operator+ (const cmplx<T>& y) const
{
	cmplx<T> z(*this); 
	z+=y;
	return z;
}
//------------ Z-=Y --------------------------------------------------
template <class T> cmplx<T>& cmplx<T>::operator-= (const cmplx<T>& y) 
{
	re-=y.re;
	im-=y.im;
	return (*this);
}
//------------ Z=X-Y --------------------------------------------------
template <class T> cmplx<T> cmplx<T>::operator- (const cmplx<T>& y) const
{
	cmplx<T> z(*this); 
	z-=y;
	return z;
}
//------------ Z=-Y --------------------------------------------------
template <class T> cmplx<T> cmplx<T>::operator- (void) const
{
	cmplx<T> z(*this);
	z.re=-z.re;
	z.im=-z.im;
	return z;
}
//------- Z/=Y -------------------------------------------------------------
template <class T> cmplx<T>& cmplx<T>::operator/=(const cmplx<T>& y)
{
	//_ASSERTE((y.re!=(T)0)||(y.im!=(T)0));
	//cmplx<T> Conjg;
	//Conjg=y.conjg();
	if (y.im==(T)0)
	{
		re/=y.re;
		im/=y.re;
	}
	else
	{
		(*this)*=y.conjg();
		T denum=y.re*y.re+y.im*y.im;
		re/=denum;
		im/=denum;
	}
	return (*this);
}
//------- Z=X/y -------------------------------------------------------------
template <class T> cmplx<T> cmplx<T>::operator/ (const cmplx<T>& y) const
{
	cmplx<T> z(*this);
	z/=y;
	return z;
}
//*****************************************************************************
//*     Comparision operators                                                 *
//*****************************************************************************

//------------------------------------------------------------------------------

//------------ Z=conjg(X) --------------------------------------------------
template <class T> cmplx<T> cmplx<T>::conjg() const
{
	cmplx<T> z(*this);
	z.im=-z.im;
	return z;
}

template <class T> T cmplx<T>::real() const 
{ return re;}
template <class T> void cmplx<T>::real(const T& Re)
{ re=Re; }
template <class T> T cmplx<T>::imag() const
{ return im;}
template <class T> void cmplx<T>::imag(const T& Im)
{ im=Im; }
/*
template <class T> void	Out(const cmplx<T>& x)
{
	printf("[");
	Out(x.re);
	Out(x.im);
	printf("]");
}
*/

//*****************************************************************************
//*     Type conversion                                                      * 
//*****************************************************************************
/*
template <class T> __INLINE__ void double_(cmplx<T> &X, double* &pDstVec)
{
	double_(X.re,pDstVec);
	double_(X.im,pDstVec);
}
*/



template <class T> double abs2(const cmplx<T>& x)
{
	return (double)(x.re*x.re+x.im*x.im);
}

template <class T, class T2> void abs2(const cmplx<T>& x, T2 &res)
{
	res =(T2)(x.re*x.re+x.im*x.im);
}

template <class T> double abs(const cmplx<T>& x)
{
	return (double)(sqrt(x.re*x.re+x.im*x.im));
}

template <class T> cmplx<T> exp(const cmplx<T> &arg)
{
	cmplx<T> Res(arg);
	T ExpRe;
	ExpRe=exp(arg.re);
	Res.re=ExpRe*cos(arg.im);
	Res.im=ExpRe*sin(arg.im);
	return Res;
}
#endif

#endif
