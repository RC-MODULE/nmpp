   /////////////////////////////////////////////////////////////////////////////
//                                                                         // 
//  Header file of template of class mtr                                //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
#ifndef _TNMTLIO_H_INCLUDED_
#define _TNMTLIO_H_INCLUDED_

#include "nmtl.h"
#include <iomanip>
#ifndef NM6403
#include <iostream>
#endif
#include <stdio.h>
#include <crtdbg.h>

		
///////////////////////////////////////////////////////////
//
// Class of matrixes
//

//*****************************************************************************
/**
	 \ingroup nmtl
	 \ru Класс матриц.
	 \en Class mtr
	
		\~
	   \ru \par Примеры:
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




#ifndef NM6403
__INLINE__ ostream& operator<< (ostream& s, mtr<unsigned char>& mtr)
{
//		char str[255];
		s <<"{\n";
		for(int y=0;y<mtr.m_height-1;y++)
		{
			s << "\t{ ";
			for(int x=0;x<mtr.m_width-1;x++)
			{
				s<< int(mtr[y][x]) << ", ";
		 	}
			s<< int(mtr[y][mtr.m_width-1]) << " },\n";
		}
		//Last string
		s << "\t{ ";
		for(int x=0;x<mtr.m_width-1;x++)
		{
			s<< int(mtr[mtr.m_height-1][x]) << ", ";
		}
		s<<int( mtr[mtr.m_height-1][mtr.m_width-1]) << " }\n};\n";
		
        return s;
}

__INLINE__ ostream& operator<< (ostream& s, mtr<int>& mtr)
{
//		char str[255];
		s <<"{\n";
		for(int y=0;y<mtr.m_height-1;y++)
		{
			s << "\t{ ";
			for(int x=0;x<mtr.m_width-1;x++)
			{
				//sprintf(str,"%d",mtr[y][x]);
				//s<<  dbl << ", ";
				s<< mtr[y][x] << ", ";
		 	}
			//sprintf(dbl,"%20.20f",mtr[y][mtr.m_width-1]);
			//s<<  dbl << " },\n";
			s<< mtr[y][mtr.m_width-1] << " },\n";
		}
		//Last string
		s << "\t{ ";
		for(int x=0;x<mtr.m_width-1;x++)
		{
			s<< mtr[mtr.m_height-1][x] << ", ";
		}
		s<< mtr[mtr.m_height-1][mtr.m_width-1] << " }\n};\n";
		
        return s;
}

__INLINE__  ostream& operator<< (ostream& s, const __int64& y)
{
	
		int hi,lo;
		hi=int(y>>32);
		lo=int(y);
				s<< "0x" << setw(8) << setiosflags(ios::hex|ios::uppercase|ios::internal) << setfill('0') << hi 
				<< setw(8) << setiosflags(ios::hex|ios::uppercase|ios::internal) << setfill('0') << lo ;
        return s;
}


__INLINE__ ostream& operator<< (ostream& s, mtr<__int64>& mtr)
{
//		char str[255];
		s <<"{\n";
		for(int y=0;y<mtr.m_height-1;y++)
		{
			s << "\t{ ";
			for(int x=0;x<mtr.m_width-1;x++)
			{
				//sprintf(str,"%d",mtr[y][x]);
				//s<<  dbl << ", ";
				s<< mtr[y][x] << ", ";
		 	}
			//sprintf(dbl,"%20.20f",mtr[y][mtr.m_width-1]);
			//s<<  dbl << " },\n";
			s<< mtr[y][mtr.m_width-1] << " },\n";
		}
		//Last string
		s << "\t{ ";
		for(int x=0;x<mtr.m_width-1;x++)
		{
			s<< mtr[mtr.m_height-1][x] << ", ";
		}
		s<< mtr[mtr.m_height-1][mtr.m_width-1] << " }\n};\n";
		
        return s;
}



__INLINE__ ostream& operator<< (ostream& s, mtr<double>& mtr)
{
		char dbl[255];
		s <<"{\n";
		for(int y=0;y<mtr.m_height-1;y++)
		{
			s << "\t{ ";
			for(int x=0;x<mtr.m_width-1;x++)
			{
				sprintf(dbl,"%20.20f",mtr[y][x]);
				s<<  dbl << ", ";
		 	}
			sprintf(dbl,"%20.20f",mtr[y][mtr.m_width-1]);
			s<<  dbl << " },\n";
		}
		//Last string
		s << "\t{ ";
		for(int x=0;x<mtr.m_width-1;x++)
		{
			sprintf(dbl,"%20.20f",mtr[mtr.m_height-1][x]);
			s<< dbl << ", ";
		}
		sprintf(dbl,"%20.20f",mtr[mtr.m_height-1][mtr.m_width-1]);
		s<< dbl << " }\n};\n";
		
        return s;
}

/*
///////////////////// NOT CORRECT !!! ONLY FOR ZERO IMAG //////////
template <class T> cmplx<T> sqrt(const cmplx<T>& x)
{

	cmplx<T> Result;
	Result.re=sqrt(double_(x.re));
	return Result;
}

template <class T> ostream&	operator<<	(ostream& s, const cmplx<T>& y)
{
	return s<< '[' << y.re << ','<< y.im <<']';
}
*/

#ifdef WIN32
__INLINE__  ostream& operator<< (ostream& s, const nmint<__int64>& y)
{
	
		int hi,lo;
		hi=int(y.m_value>>32);
		lo=int(y.m_value);
        s<< "0x" << setw(8) << setiosflags(ios::hex|ios::uppercase|ios::internal) << setfill('0') << hi 
				<< setw(8) << setiosflags(ios::hex|ios::uppercase|ios::internal) << setfill('0') << lo ;
        return s;
}

__INLINE__  ostream& operator<< (ostream& s, const nmint<int>& y)
{
	unsigned int x=(__int32)y.m_value;	
	s<< "0x" << setw(8) << setiosflags(ios::hex|ios::uppercase|ios::internal) << setfill('0') << setiosflags(ios::uppercase) << x;
	return s;
}

__INLINE__  ostream& operator<< (ostream& s, const nmint<short>& y)
{
	unsigned __int16 x=(__int16)y.m_value;	
	s<< "0x" << setw(4) << setiosflags(ios::hex|ios::uppercase|ios::internal) << setfill('0') << x ; 
	return s;
}

__INLINE__  ostream& operator<< (ostream& s, const nmint<char>& y)
{
	unsigned __int8 x=y.m_value;	
	s<< "0x" << setw(2)  << setiosflags(ios::hex|ios::uppercase|ios::internal) << setfill('0') << x ; 
	return s;
}
#endif



#endif

#ifdef WIN32
template <class T> __INLINE__ ostream& operator<< (ostream& s, nmmtr<T>& mtr)
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

		

__INLINE__ ostream& AsmArray (ostream& s,  nmmtr64s& mtr)
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

__INLINE__ ostream& AsmArray (ostream& s,  nmmtr8s& mtr)
{
	_ASSERTE(mtr.m_width%8==0);
	nmmtr64s mClone((__int64*)mtr.m_data,mtr.m_height,mtr.m_width/8,mtr.m_stride/8);
	AsmArray(s,mClone);
	return s;
}

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
