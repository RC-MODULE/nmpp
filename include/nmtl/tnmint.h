//------------------------------------------------------------------------
//
//  $Workfile:: tnmint. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/01/21 19:22:37 $
//
//! \if file_doc
//!
//! \file   tnmint.h
//! \author Сергей Мушкаев
//! \brief  Определение шаблона класса для целых чисел с заданным 
//!         значением битов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#ifndef _TNMINT_H_INCLUDED_
#define _TNMINT_H_INCLUDED_

//#include "tnmvecpack.h"





/*
#define CHECK_OVERFLOW_ON()  _putenv("nmppsCheckOverflow_=On")
#define CHECK_OVERFLOW_OFF() _putenv("nmppsCheckOverflow_=")
#define ENABLE_CHECK_OVERFLOW() _putenv("nmppsCheckOverflow_=On")
#define DISABLE_CHECK_OVERFLOW() _putenv("nmppsCheckOverflow_=")
*/
/*
extern int nmppsCheckOverflow_;
#define CHECK_OVERFLOW_ON()  nmppsCheckOverflow_=1
#define CHECK_OVERFLOW_OFF() nmppsCheckOverflow_=0
#define ENABLE_CHECK_OVERFLOW()  nmppsCheckOverflow_=1
#define DISABLE_CHECK_OVERFLOW() nmppsCheckOverflow_=0

#define CHECK_OVERFLOW() (nmppsCheckOverflow_==1)	//Getting check overflow status
*/

//extern int nmppsCheckOverflow_;
#define CHECK_OVERFLOW_ON() 
#define CHECK_OVERFLOW_OFF()
#define ENABLE_CHECK_OVERFLOW() 
#define DISABLE_CHECK_OVERFLOW()

#define CHECK_OVERFLOW() 0


	//--------------------------------------------------------------------
	//! \ingroup nmtl
	//! \ru Класс целых чисел разрядностью N бит.
	//--------------------------------------------------------------------


template <class T>class nmint
{

public:
	T m_value;	// m_value
	T *m_pvalue;
	int m_disp;
	//---------- 0 operands constructors --------------------------------------------------
	nmint(void):m_value(0){}
	//---------- 1 operands constructors --------------------------------------------------

	nmint(const T val)
	{
		m_value=val;
	}
	

	nmint<T>&		operator=	(const T& val)
	{
		m_value=val;
		return (*this);
	}

	nmint<T>&		operator=	(T& val)
	{
		m_value=val;
		return (*this);
	}

/*
	nmint<T>&		operator=	(const nmint<T>& val)
	{
		m_value=val.m_value;
		return (*this);
	}

	template <class T2> nmint<T>&		operator=	(const T2& value)
	{
		m_value=value;
		return (*this);
	}
*/

	nmint<T>&	operator-=	(const nmint<T>& val)	
	{
		/*
		if (CHECK_OVERFLOW())
		{
			__int64 tmp=m_value;
			tmp-= val.m_value;
			(tmp<<=(64-N))>>=(64-N);
			if(tmp+val.m_value!=m_value)
				OverflowMessage("Subtraction Overflow ( Res=A-B )",m_value,val.m_value,tmp,N,N,N);
			m_value = tmp;
			return (*this);
		}
		else
		{*/
			m_value-=val.m_value;
		//	(m_value<<=(64-N))>>=(64-N);
			return (*this);
		//}
	}	

	
	nmint<T>&	operator+=	(const nmint<T>& val)	
	{
//		if (CHECK_OVERFLOW())
//		{
//			__int64 tmp=m_value;
//			tmp += val.m_value;
//			(tmp<<=(64-N))>>=(64-N);
//			if(tmp-val.m_value!=m_value)
//				OverflowMessage("Summation Overflow  ( Res=A+B )",m_value,val.m_value,tmp,N,N,N);
//			m_value = tmp;
//			return (*this);
//		}
//		else
//		{
//			m_value+=val.m_value;
//			(m_value<<=(64-N))>>=(64-N);
//			return (*this);
//		}

		m_value+=val.m_value;
		return (*this);
	}

	nmint<T>	operator-	(const nmint<T>& val) const	
	{
		nmint<T> Res(*this); 
		Res-=val;
		return Res;
	}

	nmint<T>	operator+	(const nmint<T>& val) const	
	{
		nmint<T> Res(*this); 
		Res+=val;
		return Res;
	}

	void		operator++	(int) 
	{
		(*this)+=1; 
	}

	void		operator--	(int)
	{
		(*this)-=1;
	}
	
	
	

	
	nmint<T>& operator*=	(const nmint<T>& val)
	{
		m_value*=val.m_value;
	}	

	template <class T2> nmint<T2>	operator*	(const nmint<T2>& val) const	
	{
		nmint<T2> Res;
		Res.m_value=m_value*val.m_value;
		return Res;
	}


	inline nmint<T>&	operator/=	(const nmint<T>& val)		
	{
			m_value/=val.m_value;
	}	

	inline nmint<T>		operator/	(const nmint<T>& val) const	
	{
		nmint<T> Res(*this);
		Res/=val;
		return Res;
	}

	inline nmint<T>&	operator>>=	(const int y)		
	{
		m_value>>=y;
		return (*this);
	}

	inline nmint<T>	operator>>	(const int y) const	
	{
		nmint<T> z(*this);
		z>>=y;
		return z;
	}

	inline nmint<T>&	operator<<=	(const int y)	
	{
		m_value<<=y;
		return (*this);
	}

	inline nmint<T>	operator<<	(const int n) const
	{
		nmint<T> Res(*this);
		Res<<=n;
		return Res;
	}

	inline nmint<T>&	operator^=	(nmint<T> &val)
	{
		m_value^=val.m_value;
		return (*this);
	}
	inline nmint<T>	operator^	(nmint<T> &val) const
	{
		nmint<T> Res(*this);
		Res^=val;
		return Res;
	}

	nmint<T>			operator-	() const				
	{
		nmint<T> Res;
		Res.m_value=-m_value;
		return Res;
	}

	bool		operator>	(const nmint<T>& y) const	
	{ return m_value>y.m_value;}
	bool		operator>=	(const nmint<T>& y) const	
	{ return m_value>=y.m_value;}
	bool		operator<	(const nmint<T>& y) const	
	{ return m_value<y.m_value;}
	bool		operator<=	(const nmint<T>& y) const	
	{ return m_value<=y.m_value;}
	bool		operator==	(const nmint<T>& y) const	
	{ return m_value==y.m_value;}
	bool		operator!=	(const nmint<T>& y) const	
	{ return m_value!=y.m_value;}
};



/*

template <int N> void Round(double& X,nmint<T> &Y)
{
	Y=X+0.5;
}



///////////////////////////////////////////////////////////////////////////
// Conversion of to different types
template<int N> inline double double_(const nmint<T> &x)
{
	return double(x.m_value);
}

template<int N> inline int int_(const nmint<T> &x)
{
	return int(x.m_value);
}
template<int N> inline short int shortint_(const nmint<T> &x)
{
	return short int(x.m_value);
}
*/

#ifdef __NM__
#else
typedef  nmint<char>		nmint8s;
typedef  nmint<short>		nmint16s;
#endif

typedef  nmint<int>		nmint32s;
typedef  nmint<long long>	nmint64s;

#endif

