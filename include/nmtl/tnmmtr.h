/////////////////////////////////////////////////////////////////////////////
//                                                                         // 
//  Header file of template of class nmmtr                                //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#ifndef _TNMMTR_H_INCLUDED_
#define _TNMMTR_H_INCLUDED_

//#ifdef __cplusplus


#include "tnmvec.h"
#include <string.h>
		
///////////////////////////////////////////////////////////
//
// Class of nmmtres
//


	//--------------------------------------------------------------------
    //! \defgroup nmtl контроль переполнения
    //! \ingroup implement
    //! \ru определяет классы, предназначенные для контроля переполнения
    //!     при реализации библиотеки на PC.
    //! 
    //! \ru –реализации библиотеки на PC производит контроль переполнения 
    //!     с выдачей сообщения об ошибке пользователю библиотеки. Для этой цели определены
    //!     шаблонные классы для вектора, матрицы и скалярного числа, позволяющие
    //!     производить базовые операции над их элементами.

	//--------------------------------------------------------------------
	//! \ingroup nmtl
	//! \ru  класс матриц.
	//--------------------------------------------------------------------

template<class T> class nmmtr
{
protected:
	T*		m_container;
//	bool	m_flag_new;
public:
	int		m_height,m_width,m_size,m_stride,m_border;
	T*		m_data;
	
	nmmtr(int Height, int Width,int Border=0):m_height(Height), m_width(Width)//,m_flag_new(true)
	{
		m_border=Border;
		m_container=new T[(m_height+2*m_border)*m_width];
		m_data=m_container+m_width*m_border;
		//nmppsMalloc_64s(&m_container,(m_height+2*m_border)*m_width);
		//m_data=nmppsAddr_(m_container,m_border*m_width);
		m_size=m_width*m_height;
		m_stride=m_width;
		ASSERTE(m_data!=NULL);
	}

//#ifndef NMTL_DISABLE_INDEX_CHECK
//	inline nmint<T>* operator[](int y)
//	{
//		ASSERTE(y>=-m_border);
//		ASSERTE(y<m_height+m_border);
//		
//		return (nmint<T>*) (m_data+y*m_stride);
//	}
//#else	
	inline nmvec<T> operator [](int y) const
	{
		ASSERTE(y>=-m_border);
		ASSERTE(y<m_height+m_border);
		return nmvec<T>(m_data+y*m_stride,m_width);
	}
//#endif
	
	//nmmtr(const nmmtr<T>& mtr)
	nmmtr( nmmtr<T>& mtr)
	{
		m_height=mtr.m_height;
		m_width =mtr.m_width;
		m_border=mtr.m_border;
		m_size  =mtr.m_size;
		m_container=new T[(m_height+2*m_border)*m_width];
		m_data=m_container+m_width*m_border;
		
		//m_flag_new=true;
		m_stride=m_width;
		for(int y=0; y<m_height; y++)
			memcpy(m_data+y*m_stride,mtr.m_data+y*mtr.m_stride,m_width*sizeof(T));

	};
  nmmtr(T* Data,int Height,int Width,int Stride=0):m_height(Height), m_width(Width), m_data(Data),m_stride(Stride),m_border(0) //m_flag_new(FALSE),
	{
	  if (m_stride==0)
		  m_stride=m_width;
		m_size  =m_height*m_width;
		m_container=0;
	};

  nmmtr(const T* Data,int Height,int Width,int Stride=0):m_height(Height), m_width(Width), m_data((T*)Data),m_stride(Stride),m_border(0) //m_flag_new(false),
	{
	  if (m_stride==0)
		  m_stride=m_width;
		m_size  =m_height*m_width;
		m_container=0;
	};

	~nmmtr() 
	{ 	
		if (m_container)
			delete m_container;	
	}

	//nmmtr<T>& operator= (const nmmtr<T>& mtr)
	nmmtr<T>& operator= ( const nmmtr<T>& mtr)
	{
		ASSERTE(mtr.m_height==m_height);
		ASSERTE(mtr.m_width ==m_width);
		for(int y=0; y<m_height; y++)
			(*this)[y]=mtr[y];
		return *this;
	}	

	nmmtr<T>& operator*= (const nmint<T>& val)
	{
		T* pData=m_data;
		for(int y=0; y< m_height; y++,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]*=val.m_value;
		return *this;
	}

	template <class T2> nmmtr<T2> operator* (const nmint<T2>& val)
	{
		nmmtr<T2> mRes(m_height,m_width);
		T* pResData=mRes.m_data;
		T* pData   =m_data;
		for(int y=0; y< m_height; y++,pResData+=m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pResData[x]=pData[x]*val.m_value;
		return mRes;
	}

	template <class T2> nmvec<T2> operator* (const nmvec<T2>& vec)
	{
		ASSERTE(m_width==vec.m_size);
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

	template <class T2> nmmtr<T2> operator* (const nmmtr<T2>& mtr)
	{
		ASSERTE(m_width==mtr.m_height);
		nmmtr<T2> mRes(m_height,mtr.m_width);
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
	
	nmmtr<T>& operator+= (const nmmtr<T> &mtr)
	{
		ASSERTE (mtr.m_size==m_size);

		T* pParData =mtr.m_data;
		T* pData =m_data;
		for(int y=0; y< m_height; y++,pParData+=mtr.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]+=pParData[x];

		return (*this);
	}
	
	nmmtr<T> operator+ (const nmmtr<T>& mtr) const
	{
		ASSERTE (mtr.m_size==m_size);
		nmmtr<T> res(*this); 
		res+=mtr;
		return res;
	}
	
	nmmtr<T>& operator-= (const nmmtr<T> &mtr)
	{
		ASSERTE (mtr.m_size==m_size);
		T* pParData =mtr.m_data;
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pParData+=mtr.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]-=pParData[x];
		return (*this);
	}
	
	nmmtr<T> operator- (const nmmtr<T>& mtr) const
	{
		ASSERTE (mtr.m_size==m_size);
		nmmtr <T> res(*this); 
		res-=mtr;
		return res;
	}
	
	nmmtr<T> operator- () const
	{
		nmmtr<T> mRes(m_height,m_width);
		T* pResData =mRes.m_data;
		T* pData =m_data;
		for(int y=0; y< m_height; y++, pResData+=mRes.m_stride, pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pResData[x]=-pData[x];
		return mRes;
	}
	
	nmmtr<T>&  operator/=(const T val)
	{
		//ASSERTE(val.m_value!=0);
		T* pData =m_data;
		for(int y=0; y<m_height; y++, pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]/=val;

		return (*this);
	}
	
	nmmtr<T> operator/ (const nmint<T> val) const
	{
		nmmtr<T> mRes(*this);
		mRes/=val.m_value;
		return mRes;
	}

	nmmtr<T>& operator>>=(const int shr)
	{
		ASSERTE(shr>=0);
		if (shr==0)
			return(*this);
		T* pData =m_data;
		for(int y=0; y<m_height; y++, pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]>>=shr;
		return (*this);
	}
	
	nmmtr<T> operator>> (const int shr) const
	{
		ASSERTE(shr>=0);
		nmmtr<T> mRes(*this);
		mRes>>=shr;
		return mRes;
	}

	nmmtr<T>& operator<<=(const int shl)
	{
		ASSERTE(shl>=0);
		if (shl==0)
			return(*this);
		T* pData =m_data;
		for(int y=0; y<m_height; y++, pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]<<=shl;
		return (*this);
	}

	nmmtr<T> operator<< (const int shl) const
	{
		ASSERTE(shl>=0);
		nmmtr<T> mRes(*this);
		mRes<<=shl;
		return mRes;
	}

	nmmtr<T>& operator|= (const nmmtr<T> &mtr)
	{
		ASSERTE (mtr.m_size==m_size);
		T* pParData =mtr.m_data;
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pParData+=mtr.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]|=pParData[x];
		return (*this);
	}
	
	nmmtr<T> operator| (const nmmtr<T>& mtr) const
	{
		ASSERTE (mtr.m_size==m_size);
		nmmtr <T> res(*this); 
		res|=mtr;
		return res;
	}

	nmmtr<T>& operator&= (const nmmtr<T> &mtr)
	{
		ASSERTE (mtr.m_size==m_size);
		T* pParData =mtr.m_data;
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pParData+=mtr.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]&=pParData[x];
		return (*this);
	}
	
	nmmtr<T> operator& (const nmmtr<T>& mtr) const
	{
		ASSERTE (mtr.m_size==m_size);
		nmmtr<T> res(*this); 
		res&=mtr;
		return res;
	}

	nmmtr<T>& operator^= (const nmint<T> &val)
	{
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]^=val.m_value;
		return (*this);
	}
	
	nmmtr<T> operator^ (const nmint<T>& val) const
	{
		nmmtr<T> res(*this); 
		res&=val;
		return res;
	}

	nmmtr<T> operator~ () const
	{
		nmmtr<T> res(m_height,m_width); 
		T* pResData =res.m_data;
		T* pData	=m_data;
		for(int y=0; y< m_height; y++,pResData+=res.m_stride,pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pResData[x]=~pData[x];
		return res;
	}


	
	inline T* addr(int y, int x)
	{
		return m_data+y*m_stride+x;
	}


	inline nmvec<T> vec(int y)
	{
		return nmvec<T>(m_data+y*m_stride,m_width,m_border);
	}

void fill(nmint<T> &nVal)
	{
		T* pData =m_data;
		for(int y=0; y< m_height; y++,	pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]=nVal.m_value;;
	}

	nmmtr<T> transpose()
	{
		nmmtr<T> Z(m_width,m_height);
		for(int y=0;y<m_height;y++)
			for(int x=0;x<m_width;x++)
				Z[x][y]=(*this)[y][x];
		return Z;
	}

	template<class T2> void set(nmmtr<T2>& mSrcMtr) const
	{
		T* pSrcData=mSrcMtr.m_data;
		T* pDstData=m_data;
		for(int y=0; y< m_height; y++,	pDstData+=m_stride, pSrcData+=mSrcMtr.m_stride)
			for(int x=0; x<m_width; x++)
				*pDstData[x]=pSrcData[x];
	}

	template<class T2> void set(mtr<T2> &Mtr)
	{
		T* pData =m_data;
		for(int y=0; y< m_height; y++,	pData+=m_stride)
			for(int x=0; x<m_width; x++)
				pData[x]=Mtr[y][x];
	}

	void set(const T val)
	{
		for(int y=0; y< m_height; y++)
			vec(y).set(val);
	}

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

#ifdef __NM__
#else
typedef  nmmtr<signed char>	nmmtr8s;
typedef  nmmtr<signed short>	nmmtr16s;
typedef  nmmtr<unsigned char>		nmmtr8u;
typedef  nmmtr<unsigned short>		nmmtr16u;
#endif

typedef  nmmtr<signed int>		nmmtr32s;
typedef  nmmtr<long long>	nmmtr64s;	
typedef  nmmtr<unsigned int>		nmmtr32u;
typedef  nmmtr<unsigned long long>	nmmtr64u;	

#ifndef __NM__
/*
template <class T> inline ostream& operator<< (ostream& s, nmmtr<T>& mtr)
{
	s <<"{\n";
	for(int y=0;y<mtr.m_height-1;y++)
	{
		s << "\t{ ";
		for(int x=0;x<mtr.m_width-1;x++)
		{
			s<< (mtr[y][x]) << ", ";
	 	}
		s << (mtr[y][mtr.m_width-1]) << " },\n";
	}

	s << "\t{ ";
	for(int x=0;x<mtr.m_width-1;x++)
	{
		s<< (mtr[mtr.m_height-1][x]) << ", ";
	}
	s <<  (mtr[mtr.m_height-1][mtr.m_width-1]) << " }\n";
	s << "};\n";
	return s;
}

		

inline ostream& AsmArray (ostream& s,  nmmtr64s& mtr)
{
	s << " long[" << dec << mtr.m_width <<"*" << mtr.m_height << "]=(\n";
	for(int y=0;y<mtr.m_height-1;y++)
	{
		for(int x=0;x<mtr.m_width;x++)
		{

			int hi,lo;
			hi=int(mtr[y][x].m_value>>32);
			lo=int(mtr[y][x].m_value);
			s << "0" 
				<< hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << hi << "_"
				<< hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << lo << "hl,";
		}
		s << "\n";
	}

	for(int x=0;x<mtr.m_width-1;x++)
	{
		int hi,lo;
		hi=int(mtr[mtr.m_height-1][x].m_value>>32);
		lo=int(mtr[mtr.m_height-1][x].m_value);
		s << "0" 
			<< hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << hi << "_"
			<< hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << lo << "hl,";
	}

	{
		int hi,lo;
		hi=int(mtr[mtr.m_height-1][mtr.m_width-1].m_value>>32);
		lo=int(mtr[mtr.m_height-1][mtr.m_width-1].m_value);
		s << "0" 
			<< hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << hi << "_"
			<< hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << lo << "hl";
	}
		s << "\n);\n";

	return s;
}

inline ostream& AsmArray (ostream& s,  nmmtr8s& mtr)
{
	ASSERTE(mtr.m_width%8==0);
	nmmtr64s mClone((__int64*)mtr.m_data,mtr.m_height,mtr.m_width/8,mtr.m_stride/8);
	AsmArray(s,mClone);
	return s;
}
*/
	template<class T1, class T2> void DotMul(nmmtr<T1>& mSrcMtr1, nmmtr<T2>& mSrcMtr2, nmmtr<T2>& mDstMtr ) 
	{
		for(int y=0; y< mSrcMtr1.m_height; y++)
			for(int x=0; x<mSrcMtr1.m_width; x++)
			{
				nmint<T2> res=mSrcMtr1[y][x]*mSrcMtr2[y][x];
				mDstMtr[y][x]=res;
			}
	}

	template<class T1, class T2> void GetSum(nmmtr<T1>& mSrcMtr1, nmint<T2>& nResSum) 
	{
		nResSum=0;
		for(int y=0; y< mSrcMtr1.m_height; y++)
			for(int x=0; x<mSrcMtr1.m_width; x++)
				nResSum+=nmint<T2> (mSrcMtr1[y][x].m_value);
	}

#endif

#endif


	
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

//	inline nmvec<T> GetVec(int y)
//	{
//		ASSERTE(y>=0);
//		ASSERTE(y<m_height);
//		return nmvec<T>(m_data+y*m_stride,m_width);
//	}
//
//	inline nmvec<T> GetVec(int y,int x,int len)
//	{
//		ASSERTE(y>=0);
//		ASSERTE(y<m_height);
//		return nmvec<T>(m_data+y*m_stride+x,len);
//	}
//
//	inline nmmtr<T>& SetMtr(int y,int x,nmmtr<T>& mSrc)
//	{
//		T* dst=m_data+y*m_width+x;
//		T* src=mSrc.m_data;
//		for(int i=0;i<mSrc.m_height;i++)
//		{
//			memcpy(dst,src,mSrc.m_stride*sizeof(T));
//			dst+=m_stride;
//			src+=mSrc.m_stride;
//		}
//		return *this;
//	}
//
//	inline nmmtr<T>& GetMtr(int y,int x,nmmtr<T>& mRes)
//	{
//		T* src=m_data+y*m_stride+x;
//		T* dst=mRes.m_data;
//		for(int i=0;i<mRes.m_height;i++)
//		{
//			memcpy(dst,src,mRes.m_stride*sizeof(T));
//			dst+=mRes.m_stride;
//			src+=m_stride;
//		}
//		return mRes;
//	}
//
//	inline nmmtr<T> GetMtr(int y,int x,int height,int width)
//	{
//		nmmtr<T> Res(height,width);
//		GetMtr(y,x,Res);
//		return Res;
//	}

	//	template<class T2> nmmtr<T2>& DotMul(const nmmtr<T2>& mMtr,nmmtr<T2>& mRes) const
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
//	template<class T2> nmmtr<T2> DotMul(const nmmtr<T2>& Mtr) const
//	{
//		nmmtr<T2> Res;
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

//	template<class T2> nmmtr<T>& DotMul(nmmtr<T2>& mMtr1, nmmtr<T>& mMtr2) 
//	{
//		T2*  pMtr1 =mMtr1.m_data;
//		T* pMtr2 =mMtr2.m_data;
//		T* pMtrRes=m_data;
//		for(int y=0; y< m_height; y++,	pMtr1+=mMtr1.m_stride, pMtr2+=mMtr2.m_stride,pMtrRes+=m_stride)
//			for(int x=0; x<m_width; x++)
//				pMtrRes[x]=pMtr1[x]*pMtr2[x];
//		return (*this);
//	}

//	template<class T2> nmmtr<T2>& Convert(nmmtr<T2>& mRes) const
//	{
//		T* pData =m_data;
//		T* pResData=mRes.m_data;
//		for(int y=0; y< m_height; y++,	pData+=m_stride, pResData+=mRes.m_stride)
//			for(int x=0; x<m_width; x++)
//				pResData[x]=pData[x];
//		return mRes;
//	}


//#endif