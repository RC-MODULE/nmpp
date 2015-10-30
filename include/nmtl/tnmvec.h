//------------------------------------------------------------------------
//
//  $Workfile:: tnmvec. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2004/12/21 16:52:31 $
//
//! \if file_doc
//!
//! \file   tnmvec.h
//! \author Сергей Мушкаев
//! \brief  Определяет шаблон для класса вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef _TNMVEC_H_INCLUDED_
#define _TNMVEC_H_INCLUDED_

#include <string.h>
#include "tnmint.h"
//#include "nmpl.h"


//*****************************************************************************
/**
	 \ingroup nmtl
	 \ru Класс векторов.
	 \en Class nmvec
	
		\~
	   \ru \par Примеры:
		 \en \par Example:
			\~
			\code
      int Test[10]={1,125,3,4,5,6,7,8,9,10};
      int Res [10];
      nmvec<int> A0(3);	 
      nmvec<int> B0(3);
      nmvec<int> C0(3);
			\endcode
*/

//*****************************************************************************

	

template<class T> class nmvec
{
protected:
	T*		m_container;
	int		m_border;
public:
	int		size;
	T*		m_data;

	nmvec(void*	Data, int Size, int Border=0):m_data((T*)Data),size(Size),m_container(0),m_border(Border)
	{
	
	};

	nmvec(int Size, int Border=0):size(Size),m_border(Border)
	{	
		m_container=new T[size+2*m_border];
		m_data=m_container+m_border;
		//tmalloc(m_container,size+2*m_border);
//		nmppsMalloc_(&m_container,size+2*m_border);
//		m_data=nmppsAddr_(m_container,m_border);
	}

	nmvec(const nmvec<T> &vec)
	{
		size=vec.size;
		m_border=vec.m_border;
		m_container=new T[size+2*m_border];
		m_data=m_container+m_border;
		memcpy(m_data,vec.m_data,size*sizeof(T));
//		nmppsMalloc_(&m_container,size+2*m_border);
//		m_data=nmppsAddr_(m_container,m_border);
//		nmppsCopy_(vec.m_data,m_data,size);
	};


	~nmvec()
	{
		if (m_container)
			//delete []m_container;
//			nmppsFree_(m_container);
		m_container=0;
	

	}

	inline nmvec<T>& operator= (const nmvec<T>& vec) // спец. добавил const - nmcpp ругается
	{
		ASSERTE(vec.size==size);
		memcpy(m_data,vec.m_data,size*sizeof(T));
//		nmppsCopy_(vec.m_data,m_data,size);
		return *this;
	}	 

	inline nmint<T>&    operator [] (int idx) 
	{
		ASSERTE(idx>=-m_border);
		ASSERTE(idx<size+m_border);
		nmint<T>* res=(nmint<T>*)(m_data+idx);
		return *res;
	}

	template <class T2> nmvec<T2>& operator*= (const nmint<T2> val) 
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]*=val.m_value;
		return (*this);
	}
	
	//////////// operator * ///////////////////////////
	
	template <class T2> nmvec<T2> operator* (const nmint<T2>& val) const
	{
		nmvec<T2> res(size);
		for(int idx=0;idx<size;idx++)
			res.m_data[idx]=m_data[idx]*val.m_value;
		return res;
	}
	template <class T2> nmint<T2> operator* (const nmvec<T2>& vec) const
	{
		ASSERTE(size==vec.size);
		nmint<T2> res;
		for (int idx=0;idx<size;idx++)
			res.m_value+=m_data[idx]*vec.m_data[idx];
		return res;
	}

	//////////// operator += ///////////////////////////

	nmvec<T>& operator+= (const nmint<T> &val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]+=val.m_value;
		return (*this);
	}
	
	nmvec<T>& operator+= (const nmvec<T> &vec)
	{
		ASSERTE (vec.size==size);
		for(int idx=0;idx<size;idx++)
			m_data[idx]+=vec.m_data[idx];
		return (*this);
	}
	
	//////////// operator + ///////////////////////////
	
	nmvec<T> operator+ (const nmint<T>& val) const
	{
		nmvec<T> res(*this); 
		res+=val;
		return res;
	}
	
	nmvec<T> operator+ (const nmvec<T>& vec) const
	{
		ASSERTE (vec.size==size);
		nmvec<T> res(*this); 
		res+=vec;
		return res;
	}
	//////////// operator -= ///////////////////////////

	nmvec<T>& operator-= (const nmint<T> &val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]-=val.m_value;
		return (*this);
	}

	nmvec<T>& operator-= (const nmvec<T> &vec)
	{
		ASSERTE (vec.size==size);
		for(int idx=0;idx<size;idx++)
			m_data[idx]-=vec.m_data[idx];
		return (*this);
	}
	
	//////////// operator - ///////////////////////////

	nmvec<T> operator- () const
	{
		nmvec<T> res(*this);
		for(int idx=0;idx<size;idx++)
			m_data[idx]=-m_data[idx];
		return res;
	}

	nmvec<T> operator- (const nmint<T>& val) const
	{
		nmvec<T> res(*this); 
		res-=val;
		return res;
	}
	

	nmvec<T> operator- (const nmvec<T>& vec) const
	{
		ASSERTE (vec.size==size);
		nmvec <T> res(*this); 
		res-=vec;
		return res;
	}

	//////////// operator /= ///////////////////////////

	
	nmvec<T>&  operator/=(const nmint<T> val)
	{
		ASSERTE(val.m_value!=0);
		for(int idx=0;idx<size;idx++)
			m_data[idx]/=val.m_value;
		return (*this);
	}
	
	//////////// operator / ///////////////////////////
	nmvec<T> operator/ (const T val) const
	{
		nmvec<T> res(*this);
		res/=val;
		return res;
	}

	//////////// operator >>= ///////////////////////////
	nmvec<T>& operator>>=(const int shr)
	{
		ASSERTE(shr>=0);
		if (shr==0)
			return(*this);
		for(int idx=0;idx<size;idx++)
			m_data[idx]>>=shr;
		return (*this);
	}
	
	nmvec<T> operator>> (const int shr) const
	{
		ASSERTE(shr>=0);
		nmvec<T> res(*this);
		res>>=shr;
		return res;
	}

	nmvec<T>& operator<<=(const int shl)
	{
		ASSERTE(shl>=0);
		if (shl==0) 
			return(*this);
		for(int idx=0;idx<size;idx++)
			m_data[idx]<<=shl;
		return (*this);
	}

	nmvec<T> operator<< (const int shl) const
	{
		ASSERTE(shl>=0);
		nmvec<T> res(*this);
		res<<=shl;
		return res;
	}
	/////////////// operator |=
	nmvec<T>& operator|= (const nmint<T> &val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]|=val;
		return (*this);
	}

	nmvec<T>& operator|= (const nmvec<T> &vec)
	{
		ASSERTE (vec.size==size);
		for(int idx=0;idx<size;idx++)
			m_data[idx]|=vec.m_data[idx];
		return (*this);
	}
	
	/////////////// operator |
	nmvec<T> operator| (const nmint<T>& val) const
	{
		nmvec <T> res(*this); 
		res|=val;
		return res;
	}

	nmvec<T> operator| (const nmvec<T>& vec) const
	{
		ASSERTE (vec.size==size);
		nmvec <T> res(*this); 
		res-=vec;
		return res;
	}

	/////////////// operator &=
	nmvec<T>& operator&= (const nmint<T> &val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]&=val;
		return (*this);
	}

	nmvec<T>& operator&= (const nmvec<T> &vec)
	{
		ASSERTE (vec.size==size);
		for(int idx=0;idx<size;idx++)
			m_data[idx]&=vec.m_data[idx];
		return (*this);
	}
	/////////////// operator &
	nmvec<T> operator& (const nmint<T>& val) const
	{
		nmvec <T> res(*this); 
		res&=val;
		return res;
	}

	nmvec<T> operator& (const nmvec<T>& vec) const
	{
		ASSERTE (vec.size==size);
		nmvec <T> res(*this); 
		res&=vec;
		return res;
	}

	/////////////// operator ^=
	nmvec<T>& operator^= (const nmint<T> &val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]^=val;
		return (*this);
	}

	nmvec<T>& operator^= (const nmvec<T> &vec)
	{
		ASSERTE (vec.size==size);
		for(int idx=0;idx<size;idx++)
			m_data[idx]^=vec.m_data[idx];
		return (*this);
	}
	
	/////////////// operator ^
	nmvec<T> operator^ (const nmint<T>& val) const
	{
		nmvec <T> res(*this); 
		res^=val;
		return res;
	}

	nmvec<T> operator^ (const nmvec<T>& vec) const
	{
		nmvec <T> res(*this); 
		res^=vec;
		return res;
	}


	nmvec<T>& operator~ () const
	{
		nmvec<T> res(*this);
		for(int idx=0;idx<size;idx++)
			res.m_data[idx]=~m_data[idx];
		return res;
	}


	bool	operator==	(const nmvec<T>& vec) const
	{
		ASSERTE (vec.size==size);
		for(int idx=0;idx<size;idx++)
			if (m_data[idx]!=vec.m_data[idx]) 
				return false;
		return true;
	
	}
	
	bool	operator!=	(const nmvec<T>& vec) const
	{
		ASSERTE (vec.size==size);
		for(int idx=0;idx<size;idx++)
			if (m_data[idx]==vec.m_data[idx]) 
				return false;
		return true;
	}
	
//	template<class T2> void setetData(T2* Data)
//	{
//		for(int i=0;i<size;i++)
//			m_data[i]=Data[i];
//	}
//	
//	template<class T2> void GetData(T2* Data)
//	{
//		for(int i=0;i<size;i++)
//			Data[i]=(T2)m_data[i].value;
//	}
	void set(const T& val)
	{
		nmppsSet_(m_data,val,size);
	}

	void reset()
	{
		memset(m_container,0,(size+2*m_border)*sizeof(T));
	}

};

#ifdef __NM__
#else
typedef  nmvec<char>			nmvec8s;
typedef  nmvec<unsigned char>	nmvec8u;

typedef  nmvec<short>			nmvec16s;
typedef  nmvec<unsigned short>	nmvec16u;
#endif

typedef  nmvec<int>				nmvec32s;
typedef  nmvec<long long>			nmvec64s;

typedef  nmvec<unsigned int>	nmvec32u;
typedef  nmvec<unsigned long long> nmvec64u;


#endif
