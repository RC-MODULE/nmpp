//------------------------------------------------------------------------
//
//  $Workfile:: tnmvec. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:17 $
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
#ifndef _TNMVECPACK_H_INCLUDED_
#define _TNMVECPACK_H_INCLUDED_

#include <string.h>
#include "tnmint.h"
#include "nmpl.h"


template <class T> class nmintpack
{
public:
	T *m_container;
	int m_disp;
	nmintpack(T* base,int idx)
	{
		m_container=base;//(T*)((int*)(base)+intdisp(idx));
		m_disp=idx;//bitdisp(idx);
	}

	nmintpack<T>&	operator=	(const nmintpack<T>& val)
	{
		int n=val;
		VEC_SetVal((T*)m_container,m_disp,n);
		return (*this);
	}

	nmintpack<T>&	operator=	(const int& val)
	{
		VEC_SetVal((T*)m_container,m_disp,val);
		return (*this);
	}

	operator int (void) const
	{

		int n;
		n=VEC_GetVal((T*)m_container,m_disp);
		return n;//get();
	}
	
	
	inline int intdisp(int indx);
	inline int bitdisp(int indx);
};

inline int nmintpack<nm1>::intdisp(int indx)
{
	return indx>>5;
}

inline int nmintpack<nm2s>::intdisp(int indx)
{
	return indx>>4;
}

inline int nmintpack<nm4s>::intdisp(int indx)
{
	return indx>>3;
}

inline int nmintpack<nm8s>::intdisp(int indx)
{
	return indx>>2;
}

inline int nmintpack<nm16s>::intdisp(int indx)
{
	return indx>>1;
}

inline int nmintpack<nm1>::bitdisp(int indx)
{
	return indx&0x1F;
}
inline int nmintpack<nm2s>::bitdisp(int indx)
{
	return indx&0xF;
}
inline int nmintpack<nm4s>::bitdisp(int indx)
{
	return indx&0x7;
}

inline int nmintpack<nm8s>::bitdisp(int indx)
{
	return indx&3;
}

inline int nmintpack<nm16s>::bitdisp(int indx)
{
	return indx&2;
}


//*****************************************************************************
/**
	 \ingroup nmtl
	 \ru Класс векторов.
	 \en Class nmvecpack
	
		\~
	   \ru \par Примеры:
		 \en \par Example:
			\~
			\code
      int Test[10]={1,125,3,4,5,6,7,8,9,10};
      int Res [10];
      nmvecpack<int> A0(3);	 
      nmvecpack<int> B0(3);
      nmvecpack<int> C0(3);
			\endcode
*/

//*****************************************************************************

	

template<class T> class nmvecpack
{
protected:
	T*	m_container;
	int		m_border;
public:
	int		m_size;
	T*	m_data;



	nmvecpack(void*	Data, int Size, int Border=0):m_data((T*)Data),m_size(Size),m_container(0),m_border(Border){};

	nmvecpack(int Size, int Border=0):m_size(Size),m_border(Border)
	{	
		//m_container=new T[m_size+2*m_border];
		//m_data=m_container+m_border;
		//tmalloc(m_container,m_size+2*m_border);
		VEC_Malloc((T**)&m_container,m_size+2*m_border);
		nmintpack<T> first(m_container,m_border);
		m_data=first.m_container;// ERROR here VEC_Addr((T*)m_container,m_border);
		reset();

	}

	nmvecpack(const nmvecpack<T> &vec)
	{
		m_size=vec.m_size;
		m_border=vec.m_border;
		//m_container=new T[m_size+2*m_border];
		//m_data=m_container+m_border;
		//memcpy(m_data,vec.m_data,m_size*sizeof(T));
		VEC_Malloc(&m_container,m_size+2*m_border);
		m_data=VEC_Addr(m_container,m_border);
		VEC_Copy(vec.m_data,m_data,m_size);
	};


	~nmvecpack()
	{
		if (m_container)
			//delete []m_container;
			VEC_Free(m_container);
		m_container=0;
	}

	nmvecpack<T>& operator= (const nmvecpack<T>& vec) // спец. добавил const - nmcpp ругается
	{
		_ASSERTE(vec.m_size==m_size);
		//memcpy(m_data,vec.m_data,m_size*sizeof(T));
		VEC_Copy(vec.m_data,m_data,m_size);
		return *this;
	}	 

	inline nmintpack<T> operator [] (int idx) 
	{
		//_ASSERTE(idx>=-m_border);
		//_ASSERTE(idx<m_size+m_border);
		nmintpack<T> nm(m_data,idx);
		return nm;
	}

	template <class T2> nmvecpack<T2>& operator*= (const nmint<T2> val) 
	{
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]*=val.m_value;
		return (*this);
	}
	
	//////////// operator * ///////////////////////////
	
	template <class T2> nmvecpack<T2> operator* (const nmint<T2>& val) const
	{
		nmvecpack<T2> res(m_size);
		for(int idx=0;idx<m_size;idx++)
			res.m_data[idx]=m_data[idx]*val.m_value;
		return res;
	}
	template <class T2> nmint<T2> operator* (const nmvecpack<T2>& vec) const
	{
		_ASSERTE(m_size==vec.m_size);
		nmint<T2> res;
		for (int idx=0;idx<m_size;idx++)
			res.m_value+=m_data[idx]*vec.m_data[idx];
		return res;
	}

	//////////// operator += ///////////////////////////

	nmvecpack<T>& operator+= (const nmint<T> &val)
	{
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]+=val.m_value;
		return (*this);
	}
	
	nmvecpack<T>& operator+= (const nmvecpack<T> &vec)
	{
		_ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]+=vec.m_data[idx];
		return (*this);
	}
	
	//////////// operator + ///////////////////////////
	
	nmvecpack<T> operator+ (const nmint<T>& val) const
	{
		nmvecpack<T> res(*this); 
		res+=val;
		return res;
	}
	
	nmvecpack<T> operator+ (const nmvecpack<T>& vec) const
	{
		_ASSERTE (vec.m_size==m_size);
		nmvecpack<T> res(*this); 
		res+=vec;
		return res;
	}
	//////////// operator -= ///////////////////////////

	nmvecpack<T>& operator-= (const nmint<T> &val)
	{
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]-=val.m_value;
		return (*this);
	}

	nmvecpack<T>& operator-= (const nmvecpack<T> &vec)
	{
		_ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]-=vec.m_data[idx];
		return (*this);
	}
	
	//////////// operator - ///////////////////////////

	nmvecpack<T> operator- () const
	{
		nmvecpack<T> res(*this);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]=-m_data[idx];
		return res;
	}

	nmvecpack<T> operator- (const nmint<T>& val) const
	{
		nmvecpack<T> res(*this); 
		res-=val;
		return res;
	}
	

	nmvecpack<T> operator- (const nmvecpack<T>& vec) const
	{
		_ASSERTE (vec.m_size==m_size);
		nmvecpack <T> res(*this); 
		res-=vec;
		return res;
	}

	//////////// operator /= ///////////////////////////

	
	nmvecpack<T>&  operator/=(const nmint<T> val)
	{
		_ASSERTE(val.m_value!=0);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]/=val.m_value;
		return (*this);
	}
	
	//////////// operator / ///////////////////////////
	nmvecpack<T> operator/ (const T val) const
	{
		nmvecpack<T> res(*this);
		res/=val;
		return res;
	}

	//////////// operator >>= ///////////////////////////
	nmvecpack<T>& operator>>=(const int shr)
	{
		_ASSERTE(shr>=0);
		if (shr==0)
			return(*this);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]>>=shr;
		return (*this);
	}
	
	nmvecpack<T> operator>> (const int shr) const
	{
		_ASSERTE(shr>=0);
		nmvecpack<T> res(*this);
		res>>=shr;
		return res;
	}

	nmvecpack<T>& operator<<=(const int shl)
	{
		_ASSERTE(shl>=0);
		if (shl==0) 
			return(*this);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]<<=shl;
		return (*this);
	}

	nmvecpack<T> operator<< (const int shl) const
	{
		_ASSERTE(shl>=0);
		nmvecpack<T> res(*this);
		res<<=shl;
		return res;
	}
	/////////////// operator |=
	nmvecpack<T>& operator|= (const nmint<T> &val)
	{
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]|=val;
		return (*this);
	}

	nmvecpack<T>& operator|= (const nmvecpack<T> &vec)
	{
		_ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]|=vec.m_data[idx];
		return (*this);
	}
	
	/////////////// operator |
	nmvecpack<T> operator| (const nmint<T>& val) const
	{
		nmvecpack <T> res(*this); 
		res|=val;
		return res;
	}

	nmvecpack<T> operator| (const nmvecpack<T>& vec) const
	{
		_ASSERTE (vec.m_size==m_size);
		nmvecpack <T> res(*this); 
		res-=vec;
		return res;
	}

	/////////////// operator &=
	nmvecpack<T>& operator&= (const nmint<T> &val)
	{
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]&=val;
		return (*this);
	}

	nmvecpack<T>& operator&= (const nmvecpack<T> &vec)
	{
		_ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]&=vec.m_data[idx];
		return (*this);
	}
	/////////////// operator &
	nmvecpack<T> operator& (const nmint<T>& val) const
	{
		nmvecpack <T> res(*this); 
		res&=val;
		return res;
	}

	nmvecpack<T> operator& (const nmvecpack<T>& vec) const
	{
		_ASSERTE (vec.m_size==m_size);
		nmvecpack <T> res(*this); 
		res&=vec;
		return res;
	}

	/////////////// operator ^=
	nmvecpack<T>& operator^= (const nmint<T> &val)
	{
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]^=val;
		return (*this);
	}

	nmvecpack<T>& operator^= (const nmvecpack<T> &vec)
	{
		_ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			m_data[idx]^=vec.m_data[idx];
		return (*this);
	}
	
	/////////////// operator ^
	nmvecpack<T> operator^ (const nmint<T>& val) const
	{
		nmvecpack <T> res(*this); 
		res^=val;
		return res;
	}

	nmvecpack<T> operator^ (const nmvecpack<T>& vec) const
	{
		nmvecpack <T> res(*this); 
		res^=vec;
		return res;
	}


	nmvecpack<T>& operator~ () const
	{
		nmvecpack<T> res(*this);
		for(int idx=0;idx<m_size;idx++)
			res.m_data[idx]=~m_data[idx];
		return res;
	}


	bool	operator==	(const nmvecpack<T>& vec) const
	{
		_ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			if (m_data[idx]!=vec.m_data[idx]) 
				return false;
		return true;
	
	}
	
	bool	operator!=	(const nmvecpack<T>& vec) const
	{
		_ASSERTE (vec.m_size==m_size);
		for(int idx=0;idx<m_size;idx++)
			if (m_data[idx]==vec.m_data[idx]) 
				return false;
		return true;
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

	void reset()
	{
		memset(m_container,0,(m_size+2*m_border)*sizeof(T));
	}



};


	

typedef  nmvecpack<nm1>		nmvec1;
typedef  nmvecpack<nm2s>	nmvec2s;
typedef  nmvecpack<nm2u>	nmvec2u;
typedef  nmvecpack<nm4s>	nmvec4s;
typedef  nmvecpack<nm4u>	nmvec4u;

#ifndef WIN32
typedef  nmvecpack<nm8s>	nmvec8s;
typedef  nmvecpack<nm8u>	nmvec8u;
typedef  nmvecpack<nm16s>	nmvec16s;
typedef  nmvecpack<nm16u>	nmvec16u;
#endif


#endif
