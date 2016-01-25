//------------------------------------------------------------------------
//
//  $Workfile:: tnmcvec. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/05/03 13:22:40 $
//
//! \if file_doc
//!
//! \file   tnmcvec.h
//! \author Сергей Мушкаев
//! \brief  Определяет шаблон для класса вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef _Tnmcvec_H_INCLUDED_
#define _Tnmcvec_H_INCLUDED_

#ifdef __cplusplus

#ifdef ENABLE_ASSERTE
#include <crtdbg.h>
#define ASSERTE _ASSERTE
#else
#define ASSERTE(expression)
#endif

#include "tnmint.h"

//*****************************************************************************
/**
	 \ingroup nmtl
	 \ru Класс векторов.
	 \en Class nmcvec
	
		\~
	   \ru \par Примеры:
		 \en \par Example:
			\~
			\code
      int Test[10]={1,125,3,4,5,6,7,8,9,10};
      int Res [10];
      nmcvec<int> A0(3);	 
      nmcvec<int> B0(3);
      nmcvec<int> C0(3);
			\endcode
*/

//*****************************************************************************

	

template<class T> class nmcvec
{
protected:
	cmplx<nmint<T> > *		m_container;
	bool	m_flag_new;
public:
	int		m_size;
	cmplx<nmint<T> > *		m_data;

	nmcvec(cmplx<nmint<T> >*	Data, int Size):m_data(Data),m_size(Size),m_flag_new(false){};

	nmcvec(int Size,int Reserve=0):m_size(Size),m_flag_new(true)
	{	
		m_container=new cmplx<nmint<T> >[m_size+2*Reserve];
		m_data=m_container+Reserve;
	}
	
	//nmcvec(T  *	Data, int Size):m_data(Data),m_size(Size),m_flag_new(false){};


	nmcvec(const nmcvec<T> &vec)
	{
		m_flag_new=true;
		m_size=vec.m_size;
		m_data=m_container=new T[m_size];
		memcpy(m_data,vec.m_data,m_size*sizeof(T));
	};


	~nmcvec()
	{
		if (m_flag_new)
			delete []m_container;

	}

	nmcvec<T>& operator= (nmcvec<T>& vec)
	{
		ASSERTE(vec.m_size==m_size);
		memcpy(m_data,vec.m_data,m_size*sizeof(T));
		return *this;
	}	 

#ifndef NMTL_DISABLE_INDEX_CHECK
	inline cmplx<nmint<T> >&    operator [] (int idx)
	{
		ASSERTE(idx>=0);
		ASSERTE(idx<m_size);
		cmplx<nmint<T> >* res=(cmplx<nmint<T> >*)(m_data+idx);
		return *res;
	}
#else
	inline cmplx<nmint<T> >&    operator [] (int idx)
	{
		return (cmplx<nmint<T> >*)(m_data+idx);
	}
#endif

	template <class T2> nmcvec<T2>& operator*= (const cmplx<nmint<T2> > val) 
	{
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]*=val.m_value;
		return (*this);
	}
	
	template <class T2> nmcvec<T2> operator* (const cmplx<nmint<T2> >& val) const
	{
		nmcvec<T2> res(m_size);
		for(int idx=0;idx<m_size;idx++)
			res.m_data[idx]=m_data[idx]*val.m_value;
		return res;
	}
	template <class T2> nmint<T2> operator* (const nmcvec<T2>& vec) const
	{
		ASSERTE(m_size==vec.m_size);
		nmint<T2> res;
		for (int idx=0;idx<m_size;idx++)
			res.m_value+=m_data[idx]*vec.m_data[idx];
		return res;
	}

	nmcvec<T>& operator+= (const cmplx<nmint<T> > &val)
	{
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]+=val.m_value;
		return (*this);
	}
	
	nmcvec<T>& operator+= (const nmcvec<T> &vec)
	{
		ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]+=vec.m_data[idx];
		return (*this);
	}
	
	nmcvec<T> operator+ (const cmplx<nmint<T> >& val) const
	{
		nmcvec<T> res(*this); 
		res+=val;
		return res;
	}
	
	nmcvec<T> operator+ (const nmcvec<T>& vec) const
	{
		ASSERTE (vec.m_size==m_size);
		nmcvec<T> res(*this); 
		res+=vec;
		return res;
	}
	
	nmcvec<T>& operator-= (const nmcvec<T> &vec)
	{
		ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]-=vec.m_data[idx];
		return (*this);
	}
	
	nmcvec<T> operator- (const nmcvec<T>& vec) const
	{
		ASSERTE (vec.m_size==m_size);
		nmcvec <T> res(*this); 
		res-=vec;
		return res;
	}
	
	nmcvec<T> operator- () const
	{
		nmcvec<T> res(*this);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]=-m_data[idx];
		return res;
	}
	
	nmcvec<T>&  operator/=(const cmplx<nmint<T> > val)
	{
		ASSERTE(val.m_value!=0);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]/=val.m_value;
		return (*this);
	}
	
	nmcvec<T> operator/ (const T val) const
	{
		nmcvec<T> res(*this);
		res/=val;
		return res;
	}

	nmcvec<T>& operator>>=(const int shr)
	{
		ASSERTE(shr>=0);
		if (shr==0) return(*this);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]>>=shr;
		return (*this);
	}
	
	nmcvec<T> operator>> (const int shr) const
	{
		ASSERTE(shr>=0);
		nmcvec<T> res(*this);
		res>>=shr;
		return res;
	}

	nmcvec<T>& operator<<=(const int shl)
	{
		ASSERTE(shl>=0);
		if (shl==0) return(*this);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]<<=shl;
		return (*this);
	}

	nmcvec<T> operator<< (const int shl) const
	{
		ASSERTE(shl>=0);
		nmcvec<T> res(*this);
		res<<=shl;
		return res;
	}

  template<class T2> void SetData(T2* Data)
	{
		for(int i=0;i<m_size;i++)
			m_data[i]=Data[i];
	}
	
  template<class T2> void GetData(T2* Data)
	{
		for(int i=0;i<m_size;i++)
			Data[i]=(T2)m_data[i].value;
	}

		void SetConst(const cmplx<nmint<T > > val)
		{
			for (int idx=0;idx<m_size;idx++)
				m_data[idx]=val;

		}
};
/*
template <class T>	void InitInc2(nmcvec<T>& A,cmplx<nmint<T> > StartValue=0,cmplx<nmint<T> > Increment=1) 
{
	for (int idx=0;idx<A.m_size;idx++,StartValue+=Increment)
		A[idx]=StartValue;
}
*/
//bool	operator==	(const nmcvec<T>& vec) const
//bool	operator!=	(const nmcvec<T>& vec) const;

#ifdef __NM__
#else
typedef  nmcvec<char >	nmvec8sc;
typedef  nmcvec<short >	nmvec16sc;
#endif
typedef  nmcvec<int >		nmvec32sc;
typedef  nmcvec<long long> nmvec64sc;

#endif

#endif