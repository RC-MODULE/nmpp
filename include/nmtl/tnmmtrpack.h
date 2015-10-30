/////////////////////////////////////////////////////////////////////////////
//                                                                         // 
//  Header file of template of class nmmtrpack                                //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#ifndef _Tnmmtrpack_H_INCLUDED_
#define _Tnmmtrpack_H_INCLUDED_




#include "tnmvec.h"
#include <string.h>
		
///////////////////////////////////////////////////////////
//
// Class of nmmtrpackes
//

	//--------------------------------------------------------------------
    //! \defgroup nmtl Контроль переполнения
    //! \ingroup implement
    //! \ru Определяет классы, предназначенные для контроля переполнения
    //!     при реализации библиотеки на PC.
    //! 
    //! \ru Реализации библиотеки на PC производит контроль переполнения 
    //!     с выдачей сообщения об ошибке пользователю библиотеки. Для этой цели определены
    //!     шаблонные классы для вектора, матрицы и скалярного числа, позволяющие
    //!     производить базовые операции над их элементами.
    //--------------------------------------------------------------------

	//--------------------------------------------------------------------
	//! \ingroup nmtl
	//! \ru Класс матриц.
	//--------------------------------------------------------------------

template<class T> class nmmtrpack
{
protected:
	T*		m_container;
	bool	m_flag_new;
public:
	int		m_height,m_width,m_size,m_stride,m_border;
	T*		m_data;
	
	nmmtrpack(int Height, int Width,int Border=0):m_height(Height), m_width(Width),m_flag_new(true)
	{
		m_border=Border;
		//m_container=new T[(m_height+2*m_border)*m_width];
		//m_data=m_container+m_width*m_border;
		nmppsMalloc_(&m_container,(m_height+2*m_border)*m_width);
		m_data=nmppsAddr_(m_container,m_border*m_width);
		m_size=m_width*m_height;
		m_stride=m_width;
		_ASSERTE(m_data!=NULL);
	}

//#ifndef NMTL_DISABLE_INDEX_CHECK
//	__INLINE__ nmint<T>* operator[](int y)
//	{
//		_ASSERTE(y>=-m_border);
//		_ASSERTE(y<m_height+m_border);
//		
//		return (nmint<T>*) (m_data+y*m_stride);
//	}
//#else	
	__INLINE__ nmvecpack<T> operator [](int y) const
	{
		_ASSERTE(y>=-m_border);
		_ASSERTE(y<m_height+m_border);
		return nmvecpack<T>(nmppsAddr_(m_data,y*m_stride),m_width);
	}
//#endif
	
	nmmtrpack(const nmmtrpack<T>& mtr)
	{
		m_height=mtr.m_height;
		m_width =mtr.m_width;
		m_border=mtr.m_border;
		m_size  =mtr.m_size;
		//m_container=new T[(m_height+2*m_border)*m_width];
		//m_data=m_container+m_width*m_border;
		nmppsMalloc_(&m_container,(m_height+2*m_border)*m_width);
		m_data=nmppsAddr_(m_container,m_border*m_width);
		
		m_flag_new=true;
		m_stride=m_width;
		for(int y=0; y<m_height; y++)
			//memcpy(m_data+y*m_stride,mtr.m_data+y*mtr.m_stride,m_width*sizeof(T));
			//nmppsCopy_(nmppsAddr_(mtr.m_data),y*mtr.m_stride)
			(*this)[y]=mtr[y];

	};
  nmmtrpack(T* Data,int Height,int Width,int Stride=0):m_height(Height), m_width(Width), m_data(Data),m_flag_new(false),m_stride(Stride),m_border(0) 
	{
	  if (m_stride==0)
		  m_stride=m_width;
		m_size  =m_height*m_width;
		m_container=0;
	};

  nmmtrpack(const T* Data,int Height,int Width,int Stride=0):m_height(Height), m_width(Width), m_data((T*)Data),m_flag_new(false),m_stride(Stride),m_border(0) 
	{
	  if (m_stride==0)
		  m_stride=m_width;
		m_size  =m_height*m_width;
		m_container=0;
	};

	~nmmtrpack() 
	{ 	
		if (m_flag_new)
			//delete m_container;	
			nmppsFree_(m_container);
	}

	nmmtrpack<T>& operator= (const nmmtrpack<T>& mtr)
	{
		_ASSERTE(mtr.m_height==m_height);
		_ASSERTE(mtr.m_width ==m_width);
		for(int y=0; y<m_height; y++)
			(*this)[y]=mtr[y];
		return *this;
	}	

	nmmtrpack<T>& operator*= (const nmint<T>& val)
	{
		T* pData=m_data;
		for(int y=0; y< m_height; y++,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]*=val.m_value;
		return *this;
	}

	template <class T2> nmmtrpack<T2> operator* (const nmint<T2>& val)
	{
		nmmtrpack<T2> mRes(m_height,m_width);
		T* pResData=mRes.m_data;
		T* pData   =m_data;
		for(int y=0; y< m_height; y++,pResData+=m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pResData[x]=pData[x]*val.m_value;
		return mRes;
	}

	template <class T2> nmvec<T2> operator* (const nmvec<T2>& vec)
	{
		_ASSERTE(m_width==vec.m_size);
		nmvec<T2> vRes(m_height);
		T* pData   =m_data;
		for(int y=0;y<m_height;y++,pData+=m_stride)
		{
			T2 nSum(0);
			for(int x=0; x<m_width; x++)
				nSum+=pData[x]*vec.m_data[x];
			vRes[y]=nSum;
		}
		return vRes;
	}

	template <class T2> nmmtrpack<T2> operator* (const nmmtrpack<T2>& mtr)
	{
		_ASSERTE(m_width==mtr.m_height);
		nmmtrpack<T2> mRes(m_height,mtr.m_width);
		for(int y=0; y<mRes.m_height; y++)
			for(int x=0; x<mRes.m_width; x++)
			{
				T2 sum(0);
				for(int i=0;i<m_width;i++)
					sum+=m_data[m_stride*y+i]*mtr.m_data[mtr.m_stride*i+x];
				mRes.m_data[y*mRes.m_stride+x]=sum;
			}
		return mRes;
	}
	
	nmvec<T>& operator+= (const nmint<T> &val)
	{
		T* pData   =m_data;
		for(int y=0; y< m_height; y++,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]+=val.m_value;
		return (*this);
	}
	
	nmmtrpack<T>& operator+= (const nmmtrpack<T> &mtr)
	{
		_ASSERTE (mtr.m_size==m_size);

		T* pParData =mtr.m_data;
		T* pData =m_data;
		for(int y=0; y< m_height; y++,pParData+=mtr.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]+=pParData[x];

		return (*this);
	}
	
	nmmtrpack<T> operator+ (const nmmtrpack<T>& mtr) const
	{
		_ASSERTE (mtr.m_size==m_size);
		nmmtrpack<T> res(*this); 
		res+=mtr;
		return res;
	}
	
	nmmtrpack<T>& operator-= (const nmmtrpack<T> &mtr)
	{
		_ASSERTE (mtr.m_size==m_size);
		T* pParData =mtr.m_data;
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pParData+=mtr.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]-=pParData[x];
		return (*this);
	}
	
	nmmtrpack<T> operator- (const nmmtrpack<T>& mtr) const
	{
		_ASSERTE (mtr.m_size==m_size);
		nmmtrpack <T> res(*this); 
		res-=mtr;
		return res;
	}
	
	nmmtrpack<T> operator- () const
	{
		nmmtrpack<T> mRes(m_height,m_width);
		T* pResData =mRes.m_data;
		T* pData =m_data;
		for(int y=0; y< m_height; y++, pResData+=mRes.m_stride, pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pResData[x]=-pData[x];
		return mRes;
	}
	
	nmmtrpack<T>&  operator/=(const T val)
	{
		//_ASSERTE(val.m_value!=0);
		T* pData =m_data;
		for(int y=0; y<m_height; y++, pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]/=val;

		return (*this);
	}
	
	nmmtrpack<T> operator/ (const nmint<T> val) const
	{
		nmmtrpack<T> mRes(*this);
		mRes/=val.m_value;
		return mRes;
	}

	nmmtrpack<T>& operator>>=(const int shr)
	{
		_ASSERTE(shr>=0);
		if (shr==0)
			return(*this);
		T* pData =m_data;
		for(int y=0; y<m_height; y++, pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]>>=shr;
		return (*this);
	}
	
	nmmtrpack<T> operator>> (const int shr) const
	{
		_ASSERTE(shr>=0);
		nmmtrpack<T> mRes(*this);
		mRes>>=shr;
		return mRes;
	}

	nmmtrpack<T>& operator<<=(const int shl)
	{
		_ASSERTE(shl>=0);
		if (shl==0)
			return(*this);
		T* pData =m_data;
		for(int y=0; y<m_height; y++, pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]<<=shl;
		return (*this);
	}

	nmmtrpack<T> operator<< (const int shl) const
	{
		_ASSERTE(shl>=0);
		nmmtrpack<T> mRes(*this);
		mRes<<=shl;
		return mRes;
	}

	nmmtrpack<T>& operator|= (const nmmtrpack<T> &mtr)
	{
		_ASSERTE (mtr.m_size==m_size);
		T* pParData =mtr.m_data;
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pParData+=mtr.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]|=pParData[x];
		return (*this);
	}
	
	nmmtrpack<T> operator| (const nmmtrpack<T>& mtr) const
	{
		_ASSERTE (mtr.m_size==m_size);
		nmmtrpack <T> res(*this); 
		res|=mtr;
		return res;
	}

	nmmtrpack<T>& operator&= (const nmmtrpack<T> &mtr)
	{
		_ASSERTE (mtr.m_size==m_size);
		T* pParData =mtr.m_data;
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pParData+=mtr.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]&=pParData[x];
		return (*this);
	}
	
	nmmtrpack<T> operator& (const nmmtrpack<T>& mtr) const
	{
		_ASSERTE (mtr.m_size==m_size);
		nmmtrpack<T> res(*this); 
		res&=mtr;
		return res;
	}

	nmmtrpack<T>& operator^= (const nmint<T> &val)
	{
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]^=val.m_value;
		return (*this);
	}
	
	nmmtrpack<T> operator^ (const nmint<T>& val) const
	{
		nmmtrpack<T> res(*this); 
		res&=val;
		return res;
	}

	nmmtrpack<T> operator~ () const
	{
		nmmtrpack<T> res(m_height,m_width); 
		T* pResData =res.m_data;
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pResData+=res.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pResData[x]=~pData[x];
		return res;
	}


//	template<class T2> void SetData(T2* Data)
//	{
//		for(int i=0;i<m_size;i++)
//			m_data[i]=Data[i];
//	}
//	
//	template<class T2> void GetData(T2* Data)
//	{
//		for(int i=0;i<m_size;i++)
//			Data[i]=(T2)m_data[i].value;
//	}

	__INLINE__ nmvec<T> GetVec(int y)
	{
		_ASSERTE(y>=0);
		_ASSERTE(y<m_height);
		return nmvec<T>(m_data+y*m_stride,m_width);
	}

	__INLINE__ nmvec<T> GetVec(int y,int x,int len)
	{
		_ASSERTE(y>=0);
		_ASSERTE(y<m_height);
		return nmvec<T>(m_data+y*m_stride+x,len);
	}

	__INLINE__ nmmtrpack<T>& SetMtr(int y,int x,nmmtrpack<T>& mSrc)
	{
		T* dst=m_data+y*m_width+x;
		T* src=mSrc.m_data;
		for(int i=0;i<mSrc.m_height;i++)
		{
			memcpy(dst,src,mSrc.m_stride*sizeof(T));
			dst+=m_stride;
			src+=mSrc.m_stride;
		}
		return *this;
	}

	__INLINE__ nmmtrpack<T>& GetMtr(int y,int x,nmmtrpack<T>& mRes)
	{
		T* src=m_data+y*m_stride+x;
		T* dst=mRes.m_data;
		for(int i=0;i<mRes.m_height;i++)
		{
			memcpy(dst,src,mRes.m_stride*sizeof(T));
			dst+=mRes.m_stride;
			src+=m_stride;
		}
		return mRes;
	}

	__INLINE__ nmmtrpack<T> GetMtr(int y,int x,int height,int width)
	{
		nmmtrpack<T> Res(height,width);
		GetMtr(y,x,Res);
		return Res;
	}
	
	__INLINE__ T* Addr(int y, int x)
	{
		return m_data+y*m_stride+x;
	}

//	template<class T2> nmmtrpack<T2>& DotMul(const nmmtrpack<T2>& mMtr,nmmtrpack<T2>& mRes) const
//	{
//		T2* pMtrData =mMtr.m_data;
//		T2* pResData =mRes.m_data;
//		T* pData =m_data;
//		for(int y=0; y< m_height; y++,	pResData+=mRes.m_stride, pMtrData+=mMtr.m_stride,pData	+=m_stride)
//			for(int x=0; x<m_width; x++)
//				pResData[x]=pData[x]*pMtrData[x];
//		return mRes;
//	}
//
//	template<class T2> nmmtrpack<T2> DotMul(const nmmtrpack<T2>& Mtr) const
//	{
//		nmmtrpack<T2> Res;
//		DotMul(Mtr,Res);
//		return Res;
//	}
//
//	template<class T2> void GetSum(nmint<T2>& nRes) const
//	{
//		nRes=0;
//		T* pData =m_data;
//		for(int y=0; y< m_height; y++,	pData+=m_stride)
//			for(int x=0; x<m_width; x++)
//				nRes+=pData[x];
//		
//		return nRes;
//	}

//	template<class T2> nmmtrpack<T>& DotMul(nmmtrpack<T2>& mMtr1, nmmtrpack<T>& mMtr2) 
//	{
//		T2*  pMtr1 =mMtr1.m_data;
//		T* pMtr2 =mMtr2.m_data;
//		T* pMtrRes=m_data;
//		for(int y=0; y< m_height; y++,	pMtr1+=mMtr1.m_stride, pMtr2+=mMtr2.m_stride,pMtrRes+=m_stride)
//			for(int x=0; x<m_width; x++)
//				pMtrRes[x]=pMtr1[x]*pMtr2[x];
//		return (*this);
//	}

//	template<class T2> nmmtrpack<T2>& Convert(nmmtrpack<T2>& mRes) const
//	{
//		T* pData =m_data;
//		T* pResData=mRes.m_data;
//		for(int y=0; y< m_height; y++,	pData+=m_stride, pResData+=mRes.m_stride)
//			for(int x=0; x<m_width; x++)
//				pResData[x]=pData[x];
//		return mRes;
//	}

	template<class T2> void Set(nmmtrpack<T2>& mSrcMtr) const
	{
		T* pSrcData=mSrcMtr.m_data;
		T* pDstData=m_data;
		for(int y=0; y< m_height; y++,	pDstData+=m_stride, pSrcData+=mSrcMtr.m_stride)
			for(int x=0; x<m_width; x++)
				*pDstData[x]=pSrcData[x];
	}

	
	void InitConst(nmint<T> &nVal)
	{
		T* pData =m_data;
		for(int y=0; y< m_height; y++,	pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]=nVal.m_value;;
	}

	nmmtrpack<T> transpose()
	{
		nmmtrpack<T> Z(m_width,m_height);
		for(int y=0;y<m_height;y++)
			for(int x=0;x<m_width;x++)
				Z[x][y]=(*this)[y][x];
		return Z;
	}


//	template<class T2> void SetMatrix(mtr<T2> &Mtr)
//	{
//		T* pData =m_data;
//		for(int y=0; y< m_height; y++,	pData+=m_stride)
//			for(int x=0; x<m_width; x++)
//				pData[x]=Mtr[y][x];
//	}
	
	void reset()
	{
		if (m_width==m_stride)
		{
			if (m_container)
				memset(m_container,0,m_stride*(m_height+m_border*2)*sizeof(T));
			else
				memset(m_data,0,m_stride*m_height*sizeof(T));
		}
		else
		{
			T* p=m_data;
			for(int y=0;y<m_width;y++,p+=m_stride)
				memset(p,0,m_width*sizeof(T));
		}
	}

};

typedef  nmmtrpack<nm1>		nmmtr1;
typedef  nmmtrpack<nm2s>	nmmtr2s;
typedef  nmmtrpack<nm2u>	nmmtr2u;
typedef  nmmtrpack<nm4s>	nmmtr4s;
typedef  nmmtrpack<nm4u>	nmmtr4u;

#ifndef WIN32	
typedef  nmmtrpack<nm8s>	nmmtr8s;
typedef  nmmtrpack<nm8u>	nmmtr8u;
typedef  nmmtrpack<nm16s>	nmmtr16s;
typedef  nmmtrpack<nm16u>	nmmtr16u;
#endif





	
# endif

