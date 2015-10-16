//------------------------------------------------------------------------
//
//  $Workfile:: tVector. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.7 $      $Date: 2005/06/29 14:14:06 $
//
//! \if file_doc
//!
//! \file   tvector.h
//! \author Сергей Мушкаев
//! \brief  Определяет шаблон для класса вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------
#ifndef _TVECTOR_H_INCLUDED_
#define _TVECTOR_H_INCLUDED_

#ifdef ENABLE_ASSERTE
#include <crtdbg.h>
#define ASSERTE _ASSERTE
#else
#define ASSERTE(expression)
#endif


#include<string.h>

template <class T> class mtr;


//#include "tMatrix.h"

//*****************************************************************************
/**
	 \ingroup nmtl
	 \ru Класс векторов.
	 \en Class vec
	
		\~
	   \ru \par Примеры:
		 \en \par Example:
			\~
			\code
      int Test[10]={1,125,3,4,5,6,7,8,9,10};
      int Res [10];
      vec<int> A0(3);	 
      vec<int> B0(3);
      vec<int> C0(3);
      scalar<int> a0(2);
      A0[0]=1;
      A0[1]=2;
      A0[2]=3;
      B0.SetData(Test);	
      B0=A0;		
      a0=A0[1];	

      C0=A0+B0;	
      C0=A0*a0;	
      a0=A0*A0;	

			\endcode
*/

//*****************************************************************************

//void* allocate()	

template<class T> class vec
{
protected:
	T* m_container;
public:
	int m_border;
	int size;
	T  *m_data;

	explicit vec()
	{	
		size=0;
		m_border=0;
		m_container=0;
		m_data=0;
	}
	
	void resize(int Size, int Border=0)
	{	
		if (m_container)
			delete []m_container;
		size=Size;
		m_border=Border;
		m_container=new T[size+2*m_border];
		m_data=m_container+m_border;
	}

	explicit vec(T  *	Data, int Size, int Border=0):m_data(Data),size(Size),m_border(Border),m_container(0)
	{
	 
	};

	explicit vec(int Size, int Border=0)
	{	
		size=Size;
		m_border=Border;
		m_container=new T[size+2*m_border];
		m_data=m_container+m_border;
	}
	
	/*explicit*/ vec(const vec<T> &vect) 
	{
		m_border=vect.m_border;
		size  =vect.size;
		m_container=new T[size+2*m_border];
		m_data=m_container+m_border;
		for (int idx=0;idx<size;idx++)
			m_data[idx]=vect.m_data[idx];
	};	
/*
	template<class T2> explicit vec(const vec<T2> &vect) 
	{
		m_border=vect.m_border;
		size  =vect.size;
		m_container=new T[size+2*m_border];
		m_data=m_container+m_border;
		for (int idx=0;idx<size;idx++)
			m_data[idx]=vect.m_data[idx];
	};

*/
	~vec()
	{
		if (m_container)
			delete []m_container;
	}

	void reset()
	{
		ASSERTE(m_container);
		memset(m_container,0,(size+2*m_border)*sizeof(T));
	}

	vec<T>& InitRamp(T StartValue, T Increment)
	{
		m_data[0]=StartValue;
		for(int i=1; i<size; i++){
			m_data[i]=m_data[i-1]+Increment;
		}
		return *this;
	}

	int MaxPos(T& maxval)
	{
		maxval=m_data[0];
		int maxpos=0;
		for(int i=1; i<size; i++)		{
			if (maxval<m_data[i]){
				maxpos=i;
				maxval=m_data[i];
			}
		}
		return maxpos;
	}
	int MinPos(T& minval)
	{
		minval=m_data[0];
		int minpos=0;
		for(int i=1; i<size; i++)		{
			if (minval>m_data[i]){
				minpos=i;
				minval=m_data[i];
			}
		}
		return minpos;
	}
	
	double Mean()
	{
		T Res=m_data[0];
		for(int i=1; i<size; i++)		{
			Res+=m_data[i];
		}
		return double(Res)/size;
	}

	T& CustomMax()
	{
		T max=m_data[0];
		//int maxpos=0;
		for(int i=1; i<size; i++)		{
			max = tCustomMax(max,m_data[i]);
		}
		return max;
	}
	vec<T>& operator= (const T& val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]=val;
		return *this;
	}	 

	vec<T>& operator= (const vec<T>& vect)
	{
		ASSERTE(vect.size==size);
		for(int idx=0;idx<size;idx++)
			m_data[idx]=vect.m_data[idx];
		return *this;
	}	 

	inline T* addr(int idx)
	{
		ASSERTE(idx>=-m_border);
		ASSERTE(idx<size+m_border);
		return m_data+idx;
	}

	inline T&    operator [] (int idx)
	{
		ASSERTE(idx>=-m_border);
		ASSERTE(idx<size+m_border);
		T* res=(T*)(m_data+idx);
		return *res;
	}

	vec<T>& operator*= (const T& val) 
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]*=val;
		return (*this);
	}
	
	vec<T> operator* (const T& val) const
	{
		vec<T> res(size);
		for(int idx=0;idx<size;idx++)
			res.m_data[idx]=m_data[idx]*val;
		return res;
	}

	T operator* (const vec<T>& vect) const
	{
		ASSERTE(size==vect.size);
		T res=0;
		for (int idx=0;idx<size;idx++)
			res+=m_data[idx]*vect.m_data[idx];
		return res;
	}

	vec<T> operator* (const mtr<T> matr) const
	{
		ASSERTE(size==matr.m_height);
		vec<T> res(matr.m_width);
		for(int i=0; i<matr.m_width; i++){
			T sum=matr[0][i]*m_data[0];
			for(int j=1; j<matr.m_height; j++){
				sum+=matr[j][i]*m_data[j];
			}
			res[i]=sum;
		}
		return res;
	}
	vec<T>& operator+= (const T &val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]+=val;
		return (*this);
	}
	
	vec<T>& operator+= (const vec<T> &vect)
	{
		ASSERTE (vect.size==size);
		for(int idx=0;idx<size;idx++)
			m_data[idx]+=vect.m_data[idx];
		return (*this);
	}
	
	vec<T> operator+ (const T& val) const
	{
		vec<T> res(*this); 
		res+=val;
		return res;
	}
	
	vec<T> operator+ (const vec<T>& vect) const
	{
		ASSERTE (vect.size==size);
		vec<T> res(*this); 
		res+=vect;
		return res;
	}

	vec<T>& operator-= (const T &val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]-=val;
		return (*this);
	}

	vec<T>& operator-= (const vec<T> &vect)
	{
		ASSERTE (vect.size==size);
		for(int idx=0;idx<size;idx++)
			m_data[idx]-=vect.m_data[idx];
		return (*this);
	}
	
	vec<T> operator- (const vec<T>& vect) const
	{
		ASSERTE (vect.size==size);
		vec<T> res(*this); 
		res-=vect;
		return res;
	}
	
	vec<T> operator- () const
	{
		vec<T> res(*this);
		for(int idx=0;idx<size;idx++)
			res.m_data[idx]=-m_data[idx];
		return res;
	}
	
	vec<T>&  operator/=(const T val)
	{
		ASSERTE(val!=0);
		for(int idx=0;idx<size;idx++)
			m_data[idx]/=val;
		return (*this);
	}
	
	vec<T> operator/ (const T val) const
	{
		vec<T> res(*this);
		res/=val;
		return res;
	}

	vec<T>& operator>>=(const int shr)
	{
		ASSERTE(shr>=0);
		if (shr==0) return(*this);
		for(int idx=0;idx<size;idx++)
			m_data[idx]>>=shr;
		return (*this);
	}
	
	vec<T> operator>> (const int shr) const
	{
		ASSERTE(shr>=0);
		vec<T> res(*this);
		res>>=shr;
		return res;
	}

	vec<T>& operator<<=(const int shl)
	{
		ASSERTE(shl>=0);
		if (shl==0) return(*this);
		for(int idx=0;idx<size;idx++)
			m_data[idx]<<=shl;
		return (*this);
	}

	vec<T> operator<< (const int shl) const
	{
		ASSERTE(shl>=0);
		vec<T> res(*this);
		res<<=shl;
		return res;
	}
	
	//-----------------------------------------
	vec<T>& operator&=(const T& val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]&=val;
		return (*this);
	}

	vec<T>& operator&=(const vec<T>& vect)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]&=vect.m_data[idx];
		return (*this);
	}

	vec<T> operator& (const T& val) const
	{
		vec<T> res(*this);
		res&=val;
		return res;
	}

	vec<T> operator& (const vec<T>& vect) const
	{
		vec<T> res(*this);
		res&=vect;
		return res;
	}
	//-----------------------------------------
	vec<T>& operator|=(const T& val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]|=val;
		return (*this);
	}

	vec<T>& operator|=(const vec<T>& vect)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]|=vect.m_data[idx];
		return (*this);
	}

	vec<T> operator| (const T& val) const
	{
		vec<T> res(*this);
		res|=val;
		return res;
	}

	vec<T> operator| (const vec<T>& vect) const
	{
		vec<T> res(*this);
		res|=vect;
		return res;
	}
	//-----------------------------------------
	vec<T>& operator^=(const T& val)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]^=val;
		return (*this);
	}

	vec<T>& operator^=(const vec<T>& vect)
	{
		for(int idx=0;idx<size;idx++)
			m_data[idx]^=vect.m_data[idx];
		return (*this);
	}

	vec<T> operator^ (const T& val) const
	{
		vec<T> res(*this);
		res^=val;
		return res;
	}

	vec<T> operator^ (const vec<T>& vect) const
	{
		vec<T> res(*this);
		res^=vect;
		return res;
	}
  	int sum()
	{
		int summ=0;
		for(int i=0;i<size;i++)
			summ+=m_data[i];
		return summ;
	}

	bool operator== (const vec<T> &vect)
	{
		ASSERTE (vect.size==size);
		for(int idx=0;idx<size;idx++)
			if (m_data[idx]!=vect.m_data[idx])
				return false;
		return true;
	}
	
	bool operator!= (const vec<T> &vect)
	{
		ASSERTE (vect.size==size);
		for(int idx=0;idx<size;idx++)
			if (m_data[idx]!=vect.m_data[idx])
				return true;
		return false;
	}
	//-----------------------------------------

	
/*
  template<class T2> void SetData(T2* Data)
	{
		for(int i=0;i<size;i++)
			m_data[i]=Data[i];
	}
	
  template<class T2> void GetData(T2* Data)
	{
		for(int i=0;i<size;i++)
			Data[i]=(T2)m_data[i].value;
	}
*/
//void InitConst(T Value) 
//{
//	for (int idx=0;idx<size;idx++)
//		m_data[idx]=Value;
//}
};
//template <class T>	void InitInc(vec<T>& A,T StartValue=0,T Increment=1) 
//{
//	for (int idx=0;idx<A.size;idx++,StartValue+=Increment)
//		A[idx]=StartValue;
//}

	template<class T1, class T2> void Convert(vec<T1>& vSrc, vec<T2>& vDst){
		ASSERTE(vSrc.size==vDst.size);
		for(int i=0; i<vSrc.size; i++){
			vDst[i]=(T2)vSrc[i];
		}
	}

//bool	operator==	(const vec<T>& vec) const
//bool	operator!=	(const vec<T>& vec) const;


//*****************************************************************************
//*    Math function                                                          *
//*****************************************************************************
//////////////////////////////////////////////////////////////////////////////////
/*
template <class T> T Norm2(vec<T>& X)
{	
	T Buffer(0);
	for(int idx=0;idx<X.size;idx++)
		for(int col=0;col<X.width;col++)
			Buffer+=X[idx]*X[idx];
	return sqrt(Buffer);
}

template <class T> double vectorError(vec<T>& A,double *B)
{	
	double Buffer=0;
	double diff;
	int idx=0;
	for(int idx=0;idx<A.size;idx++,idx++)
		for(int col=0;col<A.width;col++)
		{
			diff=double_(A[idx])-B[idx];
			Buffer+=diff*diff;
		}
	return sqrt(Buffer)/(A.width*A.size);
}
*/
template <class T> vec<T> Sqr(vec<T>& A)
{
	vec<T> Res(A);
	for (int i=0;i<A.size;i++)
		Res[i]=A[i]*A[i];
	return Res;
}
//template <class T> vec<T> Sqrt(vec<T>& A)
//{
//	vec<T> Res(A);
//	for (int i=0;i<A.size;i	++)
//		Res[i]=(T)sqrt((double)A[i]);
//	return Res;
//}

template <class T> T Summ(vec<T>& A)
{
	T Sum(0);
	for (int i=0;i<A.size;i	++)
		Sum+=A[i];
	return Sum;
}

template <class T>	void Clear(vec<T>& A) 
{
	for (int idx=0;idx<A.size;idx++)
		A[idx]=0;
}


#endif
