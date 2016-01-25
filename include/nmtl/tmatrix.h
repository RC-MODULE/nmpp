   /////////////////////////////////////////////////////////////////////////////
//                                                                         // 
//  Header file of template of class mtr                                //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#ifndef _TMATRIX_H_INCLUDED_
#define _TMATRIX_H_INCLUDED_

//#ifdef __cplusplus

#include "crtdbg2.h"

#include <stdio.h>
#include "tvector.h"
#include <string.h>
		
///////////////////////////////////////////////////////////
//
// Class of matrixes
//

//*****************************************************************************
/**
	 \ingroup nmtl
	 \ru Êëàññ ìàòðèö.
	 \en Class mtr
	
		\~
	   \ru \par Ïðèìåðû:
		 \en \par Example:
			\~
			\code
      int Test[10]={1,125,3,4,5,6,7,8,9,10};
      int Res [10];

      mtr<int> AA0(3,3);	
      vec<int> A0(3);		
      scalar<int> a0(2);		

      mtr<int> BB0(3,3);
      mtr<int> CC0(3,3);
      vec<int> C0(3);

      BB0.SetData(Test);	

      BB0=AA0;			
      A0 =AA0[2];		
      a0 =AA0[2][2];

      CC0=AA0+BB0;	
      CC0=AA0*a0;		
      C0 =AA0*A0;		
      CC0=AA0*BB0;	
			\endcode
*/

//*****************************************************************************

#ifndef GetVec
#define GetVec getvec
#endif 

#ifndef GetCol
#define GetCol getcol
#endif 

#ifndef Min
#define Min min
#endif


#ifndef	Max
#define Max max
#endif


#ifndef MinPos
#define MinPos minpos
#endif

#ifndef MaxPos
#define MaxPos maxpos
#endif



template<class T> class mtr
{
protected:
	T*  m_container;
public:
	int m_border;
	int m_stride;
	int m_height,m_width,m_size;
	int m_x0;
	int m_y0;
	T  *m_data;
	
	explicit mtr()
	{
		m_height=0;
		m_width=0;
		m_size=0;
		m_container=0;
		m_data=0;
		m_stride=0;
	}
	
	// Setting (0,0) index for element [y][x]
	void origin(int y,int x){
		m_x0=x;
		m_y0=y;
	}

	// Setting value
	inline void setval(int y, int x, const T& val)
	{
		ASSERTE(y>=-m_border);
		ASSERTE(y<m_height+m_border);
		m_data[y*m_stride+x]=val;
	}

	// extended setting value 
	inline void setvalx(int y, int x, const T& val)
	{
		ASSERTE(y+m_y0>=-m_border);
		ASSERTE(y+m_y0<m_height+m_border);
		m_data[(y+m_y0)*m_stride+x+m_x0]=val;
	}
	// getting value
	inline T getval(int y,int x) const
	{
		ASSERTE(y>=-m_border);
		ASSERTE(y<m_height+m_border);
		T val=m_data[y*m_stride+x];
		return val;
	}
	// extended getting value
	inline T getvalx(int y,int x) const
	{
		ASSERTE(y+m_y0>=-m_border);
		ASSERTE(y+m_y0<m_height+m_border);
		T val=m_data[(y+m_y0)*m_stride+x+m_x0];
		return val;
	}

	// constructor
	explicit mtr(int nHeight, int nWidth, int nBorder=0)
	{
		m_border=nBorder;
		m_height=nHeight;
		m_width=nWidth;
		m_stride=m_width;
		m_size=m_width*m_height;
		m_container=new T[m_size+2*m_stride*m_border];
		m_data=m_container+m_border*m_stride;
		ASSERTE(m_container!=NULL);
	}

	// resizing of matrix dimensions
	void resize(int nHeight, int nWidth, int nBorder=0)
	{
		if (m_container)
			delete m_container;
		m_border=nBorder;
		m_height=nHeight;
		m_width =nWidth;
		m_size  =m_width*m_height;
		m_stride=m_width;
		m_container=new T[m_size+2*m_stride*m_border];
		m_data=m_container+m_border*m_stride;
	}

	// constructor for matrix duplication
	/*explicit*/ mtr(const mtr<T>& matr)
	{
		m_height=matr.m_height;
		m_width =matr.m_width;
		m_size  =matr.m_size;
		m_stride=m_width;
		m_border=matr.m_border;
		m_container  =new T[m_size+2*m_stride*m_border];
		m_data=m_container+m_border*m_stride;

		for(int y=0;y<m_height;y++){
			for(int x=0;x<m_width;x++){
				T val=matr.getval(y,x);
				setval(y,x,val);
			}
		}
	};
	
/*
	..\include\tmatrix.h(162) : error C2535: '__thiscall mtr<T2>::mtr<T2>(const class mtr<T2> &)' : member function already defined or declared
        ..\include\tmatrix.h(143) : see declaration of 'mtr<T>::mtr<T>'
        ..\include\tmatrix.h(692) : see reference to class template instantiation 'mtr<T>' being compiled
	template <class T2> mtr(const mtr<T2>& matr)
	{
		m_height=matr.m_height;
		m_width =matr.m_width;
		m_size  =matr.m_size;
		m_stride=m_width;
		m_border=matr.m_border;
		m_container  =new T[m_size+2*m_border*m_stride];
		m_data=m_container+m_border*m_stride;

		for(int y=0;y<m_height;y++){
			for(int x=0;x<m_width;x++){
				T val=matr.getval(y,x);
				setval(y,x,val);
			}
		}
	};
*/
	// constructoê of matrix over existing data
	void assign(T* Data,int nHeight,int nWidth,int nStride=0){
		m_height=nHeight;
		m_width=nWidth;
		if (nStride==0)
			m_stride=m_width;	
		else	
			m_stride=nStride;
		m_size  =m_height*m_width;
		m_data=Data;
		m_container=0;
		m_border=0;
	}
	explicit mtr(T* Data,int nHeight,int nWidth,int nStride=0)
	{
		assign(Data,nHeight,nWidth,nStride);
	};

	// destructor
	~mtr() 
	{ 	
		if (m_container)
			delete m_container;	
	}

	// assignment

	mtr<T>& operator= (mtr<T>& matr)
	{
		ASSERTE(matr.m_height==m_height);
		ASSERTE(matr.m_width ==m_width);
		T* pSrcData=matr.m_data;
		T* pDstData=m_data;
		for(int y=0;y<m_height;y++,pSrcData+=matr.m_stride, pDstData+=m_stride)
			for(int x=0; x<m_width; x++)
				pDstData[x]=pSrcData[x];
		return *this;
	}	
	
	// filling of matrix with constant value
	mtr<T>& operator= (T& val)
	{
		for(int y=0;y<m_height;y++)
			getvec(y)=val;
		return *this;
	}	

//#ifdef _DEBUG
//	inline vec<T> operator[](int row)
//	{
//		ASSERTE(row<m_height+m_border);
//		ASSERTE(row>=-m_border);
//		return vec<T>(m_data+row*m_stride,m_width,m_border);
//	}
	// return pointer to first element in row 
	inline T* operator[](int row) const
	{
		ASSERTE(row<m_height+m_border);
		ASSERTE(row>=-m_border);
		return m_data+row*m_stride;
	}

	// getting value by linear index
	inline T& index(int idx)
	{
		ASSERTE(idx>=0);
		ASSERTE(idx<m_size);
		ASSERTE(m_width==m_stride);
		return(m_data[idx]);
	}

//#else
//	inline T* operator[](int row)
//	{
//		return (m_data+row*m_stride);
//	}
//#endif

	// inplace multiplication by constant value 
	mtr<T>& operator*= (const T val)
	{
		for(int y=0;y<m_height;y++)
			getvec(y)*=val;
		return *this;
	}

	// multiplication by constant value 
	mtr<T> operator* (const T& val) const
	{
		mtr<T> res(*this);
		return res*=val;
	}

	// multiplication by vector
	vec<T> operator* (const vec<T>& vect)
	{
		ASSERTE(m_width==vect.m_size);
		vec<T> res(m_height);
		for(int y=0;y<m_height;y++)
			res[y]=getvec(y)*vect;
		return vec<T>(res);
	}

//	mtr<T> operator* (const mtr<T>& matr)
//	{
//		ASSERTE(m_width==matr.m_height);
//		mtr<T> res(m_height,matr.m_width);
//		for(int row=0;row<res.m_height;row++)
//			for(int col=0;col<res.m_width;col++)
//			{
//				T sum(0);
//				for(int i=0;i<m_width;i++)
//					sum+=m_data[m_width*row+i]*matr.m_data[matr.m_width*i+col];
//				res.m_data[row*res.m_width+col]=sum;
//			}
//		return res;
//	}
	
	// multiplication by matrix
	mtr<T> operator* (const mtr<T>& matr)
	{
		ASSERTE(m_width==matr.m_height);
		mtr<T> res(m_height, matr.m_width);
		res.reset();
		for(int y=0;y<m_height;y++)
		{
			vec<T>& thisvec=getvec(y);
			vec<T>& resvec=res.getvec(y);
			for(int x=0;x<m_width;x++)
				resvec+=matr.getvec(x)*thisvec[x];
		}
		return res;
	}	

	// inplace adding of value to all elements of matrix
	mtr<T>& operator+= (const T &val)
	{
		for(int y=0;y<m_height;y++)
			getvec(y)+=val;
		return (*this);
	}
	
	// inplace summation of matrixes
	mtr<T>& operator+= (const mtr<T> &matr)
	{
		ASSERTE (matr.m_size==m_size);
		for(int y=0;y<m_height;y++)
			getvec(y)+=matr.getvec(y);
		return (*this);
	}
	
	// summation of matrices
	mtr<T> operator+ (const mtr<T>& matr) const
	{
		ASSERTE (matr.m_size==m_size);
		mtr<T> res(*this); 
		res+=matr;
		return res;
	}

	//inplace substraction of matrix
	mtr<T>& operator-= (const mtr<T> &matr)
	{
		ASSERTE (matr.m_size==m_size);
		for(int y=0;y<m_height;y++)
			getvec(y)-=matr.getvec(y);
		return (*this);
	}

	// inplace subtraction of value from all elements of matix
	mtr<T>& operator-= (const T &val)
	{
		for(int y=0;y<m_height;y++)
			getvec(y)-=val;
		return (*this);
	}

	// subtraction of matrixes
	mtr<T> operator- (const mtr<T>& matr) const
	{
		ASSERTE (matr.m_size==m_size);
		mtr <T> res(*this); 
		res-=matr;
		return res;
	}
	
	// sign inversion
	mtr<T> operator- () const
	{
		mtr<T> res(m_height,m_width);
		for(int y=0;y<m_height;y++)
			res.getvec(y)=-getvec(y);
		return res;
	}
	
	// inplace division
	mtr<T>&  operator/=(const T val)
	{
		ASSERTE(val!=0);
		for(int y=0;y<m_height;y++)
			getvec(y)/=val;
		return (*this);
	}

	// division
	mtr<T> operator/ (const T val) const
	{
		mtr<T> res(*this);
		res/=val;
		return res;
	}

	// inplace shift
	mtr<T>& operator>>=(const int shr)
	{
		ASSERTE(shr>=0);
		for(int y=0;y<m_height;y++)
			getvec(y)>>=shr;
		return (*this);
	}
	
	// shift
	mtr<T> operator>> (const int shr) const
	{
		ASSERTE(shr>=0);
		mtr<T> res(*this);
		res>>=shr;
		return res;
	}

	// inplace left shift 
	mtr<T>& operator<<=(const int shl)
	{
		ASSERTE(shl>=0);
		for(int y=0; y<m_height; y++)
			getvec(y)<<=shl;
		return (*this);
	}

	// left shift
	mtr<T> operator<< (const int shl) const
	{
		ASSERTE(shl>=0);
		mtr<T> res(*this);
		res<<=shl;
		return res;
	}

	// inplace AND with value
	mtr<T>& operator&= (const T &val)
	{
		for(int y=0;y<m_height;y++)
			getvec(y)&=val;
		return (*this);
	}
	

	// inplace AND with matrix
	mtr<T>& operator&= (const mtr<T> &matr)
	{
		ASSERTE (matr.m_size==m_size);
		for(int y=0;y<m_height;y++)
			getvec(y)&=matr.getvec(y);
		return (*this);
	}
	
	//  AND 
	mtr<T> operator& (const mtr<T>& matr) const
	{
		ASSERTE (matr.m_size==m_size);
		mtr <T> res(*this); 
		res&=matr;
		return res;
	}
	
	// inplace OR
	mtr<T>& operator|= (const mtr<T> &matr)
	{
		ASSERTE (matr.m_size==m_size);
		for(int y=0;y<m_height;y++)
			getvec(y)|=matr.getvec(y);
		return (*this);
	}
	
	// OR
	mtr<T> operator| (const mtr<T>& matr) const
	{
		ASSERTE (matr.m_size==m_size);
		mtr <T> res(*this); 
		res|=matr;
		return res;
	}

	// inplace XOR
	mtr<T>& operator^= (const mtr<T> &matr)
	{
		ASSERTE (matr.m_size==m_size);
		for(int y=0;y<m_height;y++)
			getvec(y)^=matr.getvec(y);
		return (*this);
	}

	// inplace XOR with constant value
	mtr<T>& operator^= (const T &val)
	{
		for(int y=0;y<m_height;y++)
			getvec(y)^=val;
		return (*this);
	}

	// XOR
	mtr<T> operator^ (const mtr<T>& matr) const
	{
		ASSERTE (matr.m_size==m_size);
		mtr <T> res(*this); 
		res^=matr;
		return res;
	}

	// XOR
	mtr<T> operator^ (const T& val) const
	{
		mtr <T> res(*this); 
		res^=val;
		return res;
	}

	// NOT
	mtr<T> operator ~ ()
	{
		mtr <T> res(*this); 
		T* r=res.m_data;
		T* s=m_data;
		for(int y=0;y<m_height;y++, r+=res.m_stride, s+=m_stride)
			for(int x=0; x<m_width;x++)
				r[x]=~s[x];
				
		return res;
	}



	void set (const T val)
	{
		T* p=m_container;
		for(int y=0; y<m_height; y++,p+=m_stride){
			for(int x=0; x<m_width; x++){
				p[x]=val;
			}
		}
	}


	/*
	void SetBorder(const T val, int nBorderWidth)
	{
		T* p=m_container;
		for(int y=0; y<m_border+nBorderWidth; y++,p+=m_stride){
			for(int x=0; x<m_width; x++){
				p[x]=val;
			}
		}
		
		p=addr(nHeight-1-nBorderWidth,0);
		for(int y=0; y<m_border+nBorderWidth; y++,p+=m_stride){
			for(int x=0; x<m_width; x++){
				p[x]=val;
			}
		}
	}*/
//	void set(const T val, const T border)
//	{
//		T* p0;
//		T* p1;
//		for(p0=m_container,p1=m_data+m_size;p0<m_data;p0++,p1++)
//		{
//			*p0=border;
//			*p1=border;
//		}
//		for(int i=0;i<m_size;i++)
//			m_data[i]=val;
//	}
	/*

	template<class T> void SetData(T* Data)
	{
		for(int i=0;i<m_size;i++)
			m_data[i]=Data[i];
	}
	
	template<class T> void GetData(T* Data)
	{
		for(int i=0;i<m_size;i++)
			Data[i]=(T)m_data[i].value;
	}

	mtr<T>& operator*= (const mtr<T>& matr)
	{
		ASSERTE(m_width==m_height);
		ASSERTE(m_width==matr.m_width);
		ASSERTE(m_height==matr.m_height);
		vec<T> res(m_height);
		for(int row=0;row<m_height;row++)
			res[row]=(*this)[row]*vec;
		return res;
	}

	
	void InitConst(T &Value)
	{
		int m_size=m_height*m_width;
		for(int i=0;i<m_size;i++)
			m_data[i]=Value;
	}
*/
//	void InitConst(T &Value)
//	{
//		int m_size=m_height*m_width;
//		for(int i=0;i<m_size;i++)
//			m_data[i]=Value;
//	}

//THIS FUNCTIONS WAS INSERTED FROM OLD VERSION OF THIS FILE!!!!!!!!!!!!!!!!!!!!!!!!!!
	mtr<T> transpose()
	{
		mtr<T> Z(m_width,m_height);
		for(int row=0;row<m_height;row++)
			for(int col=0;col<m_width;col++)
				Z[col][row]=(*this)[row][col];
		return Z;
	}

	mtr<T>& diag(T val)
	{
		reset();
		int size=(m_height<m_width)?(m_height):(m_width);
		for(int i=0; i<size; i++)
			(*this)[i][i]=val;
		return (*this);
	}

	
		


//	template<class T> void SetMatrix(mtr<T> &matr)
//	{
//		int m_size=m_height*m_width;
//		for(int i=0;i<m_size;i++)
//			m_data[i]=matr.m_data[i];
//	}

	inline T* addr(int y,int x)
	{
		ASSERTE(y<m_height+m_border);
		ASSERTE(y>=-m_border);
		ASSERTE(x<m_width+m_border);
		ASSERTE(x>=-m_border);
		T* address=m_data+m_stride*y+x;
		return address;
	}

	void reset()
	{
//		ASSERTE(m_container);
		if (m_container){
			memset(m_container,0,(m_size+2*m_border*m_width)*sizeof(T));
		}else{
			memset(m_data,0,m_size*sizeof(T));
		}
	}

	int sum()
	{
		int summ=0;
		for(int y=0;y<m_height;y++)
		{
			
			summ+=getvec(y).sum();
		}
		return summ;
	}


	vec<T> getvec(int y) const
	{
		ASSERTE(y>=0 && y<m_height);
		return vec<T>(m_data+y*m_stride,m_width,m_border);
	}

	vec<T> getcol(int x) const
	{
		ASSERTE(x>=0 && x<m_width);
		vec<T> vect(m_height);
		for(int i=0; i<m_height; i++)
			vect[i]=(*this)[i][x];
		return vect;


	}
/*
	T min() 
	{
		T m=m_data[0];
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride)
			for(int x=0; x<m_width; x++)
				if (row[x]<m)
					m=row[x];
		return m;
	}

	T max() 
	{
		T m=m_data[0];
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride)
			for(int x=0; x<m_width; x++)
				if (row[x]>m)
					m=row[x];
		return m;
	}
*/
	T minpos(int &ypos, int &xpos){
		ypos=0;
		xpos=0;
		T m=m_data[0];
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride)
			for(int x=0; x<m_width; x++)
				if (row[x]<m){
					m=row[x];
					ypos=y;
					xpos=x;
				}
		return m;
	}

	T maxpos(int &ypos, int &xpos){
		ypos=0;
		xpos=0;
		T m=m_data[0];
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride)
			for(int x=0; x<m_width; x++)
				if (row[x]>m){
					m=row[x];
					ypos=y;
					xpos=x;
				}
		return m;
	}

	void CopyTo(T* pData){
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride, pData+=m_width){
			memcpy(pData, row, sizeof(T)*m_width);
		}
	}

	void CopyFrom(T* pData){
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride, pData+=m_width){
			memcpy(row, pData, sizeof(T)*m_width);
		}
	}

	template <class T2> void ConvertTo(T2* pData){
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride, pData+=m_width){
			for(int x=0; x<m_width; x++){
				pData[x]=row[x];
			}
		}
	}

	template <class T2> void ConvertFrom(T2* pData){
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride, pData+=m_width){
			for(int x=0; x<m_width; x++){
				row[x]=pData[x];
			}
		}
	}


	/*
	inline T max() 
	{
		T Max=m_data[0];
		T* row=m_data;
		for(int y=0; y<m_height; y++, row+=m_stride)
			for(int x=0; x<m_width; x++)
				if (row[x]<min)
					Max=row[x];
		return Max;
	}
*/
//THIS FUNCTIONS WAS INSERTED FROM OLD VERSION OF THIS FILE!!!!!!!!!!!!!!!!!!!!!!!!!!

};

	
/*
template <class T1, class  T2> convert(mtr<T1>& pSrcMtr1,mtr<T2>& pSrcMtr2)	
{
	for(int i=0;i<pSrcMtr1.m_size;i++)
		pSrcMtr2.m_data[i]=pSrcMtr1.m_data[i];
}
*/	

template<class T> mtr<T> DirectProduct(vec<T>& vSrc1,vec<T>& vSrc2)
{
	mtr<T> res(vSrc1.m_size, vSrc2.m_size);
	for(int y=0; y<res.m_height; y++){
		res.getvec(y)=vSrc2*vSrc1[y];
	}
	return res;

}


#ifndef __NM__

	template<class T1, class T2> void DotMul(mtr<T1>& mSrcMtr1, mtr<T2>& mSrcMtr2, mtr<T2>& mDstMtr ) 
	{
		for(int y=0; y< mSrcMtr1.m_height; y++)
			for(int x=0; x<mSrcMtr1.m_width; x++)
			{
				T2 res=mSrcMtr1[y][x]*mSrcMtr2[y][x];
				mDstMtr[y][x]=res;
			}
	}

	template<class T1, class T2> void GetSum(mtr<T1>& mSrcMtr1, T2& nResSum) 
	{
		nResSum=0;
		for(int y=0; y< mSrcMtr1.m_height; y++)
			for(int x=0; x<mSrcMtr1.m_width; x++)
				nResSum+=T2 (mSrcMtr1[y][x]);
	}
	template<class T1, class T2> void Convert(mtr<T1>& mSrcMtr, mtr<T2>& mDstMtr){
		ASSERTE(mSrcMtr.m_height==mDstMtr.m_height);
		ASSERTE(mSrcMtr.m_width ==mDstMtr.m_width);
		for(int y=0; y<mSrcMtr.m_height; y++){
			for(int x=0; x<mSrcMtr.m_width; x++){
				mDstMtr[y][x]=(T2)mSrcMtr[y][x];
			}
		}
	}
#endif
#endif
