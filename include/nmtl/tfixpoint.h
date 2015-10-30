#ifndef _tfixpoint
#define _tfixpoint
//#include <math.h>
//#define STAT_MINMAX
//#define STAT_FIXPOINT
//#ifdef __NM__
//#define _ASSERTE(a)
//#else
//#include <crtdbg.h>
//#endif

#define FIX_TYPE __int64
#define ROUND2FIXED(a) ((a) >= 0 ? (((a)+0.5)) : (((a)-0.5)))

#define FIXPOINT_ONE (T(1)<<point)

#define DOUBLE2FIX64(a,point) (ROUND2FIXED((a)*((__int64(1))<<point)))
#define DOUBLE2FIX32(a,point) (ROUND2FIXED((a)*(int(1)<<point))




//#define FIX_POINT_ONE (1<<FIX_POINT)
#define FLT2FIX(f) (DOUBLE2FIX64((f),(FIX_POINT)))

#define MULI(a,i) ((a).m_value*(i))
#define MULC(a,c) ((a.m_value*c)>>FIX_POINT)
#define MULX(a,n) (((a).m_value*(n).m_value)>>FIX_POINT)

#define ADDC(a,c) (a.m_value+c)
#define ADDN(a,n) (a.m_value+n.m_value)
#define SUBC(a,c) (a.m_value-c)
#define SUBN(a,n) (a.m_value-n.m_value)

//#define SHR(a,shift) (((a)+ ((1)<<((shift)-1)))>>shift)
//#define FIX_RSH(a,shift) ((a)>>shift)
#define SHR(a,shift) ((a)>>shift)


//#ifndef _ASSERTE 
//#define _ASSERTE(a)
//#endif

#define DBL2FIX DOUBLE2FIX64

#ifdef __NM__
	#define INLINE
#else 
	#define INLINE __INLINE__
#endif

template<class T, int point> class tfixpoint{
public:
	T m_value;	// m_value
	//---------- 0 operands constructors --------------------------------------------------
	INLINE tfixpoint(void){}
	//---------- 1 operands constructors --------------------------------------------------

	
	INLINE tfixpoint(const int val)
	{
		m_value=T(val)<<point;
		//_ASSERTE(m_value<(T(1)<<32));
		//_ASSERTE(m_value>(-(T(1)<<32)));
	}
	
	INLINE tfixpoint(const float val)
	{
		m_value=ROUND2FIXED(val*FIXPOINT_ONE);
		//_ASSERTE(m_value<(T(1)<<32));
		//_ASSERTE(m_value>(-(T(1)<<32)));
	}
	INLINE tfixpoint(const double val) 
	{
		m_value=ROUND2FIXED(val*FIXPOINT_ONE);
		//_ASSERTE(m_value<(T(1)<<32));
		//_ASSERTE(m_value>(-(T(1)<<32)));
	}
	
	//tfixpoint(const tfixpoint<T,point> val)
	//{
	//	m_value=val.m_value;
	//}
	
	INLINE tfixpoint<T,point>&		operator=	(const int val)
	{
		m_value=T(val)<<point;
		return (*this);
	}
	
	INLINE tfixpoint<T,point>&		operator=	(const float val)
	{
		m_value=ROUND2FIXED(val*FIXPOINT_ONE);
		return (*this);
	}

	tfixpoint<T,point>&		operator=	(const double val)
	{
		m_value=ROUND2FIXED(val*FIXPOINT_ONE);
		return (*this);
	}

	INLINE tfixpoint<T,point>&		operator=	(const tfixpoint<T,point>& val)
	{
		m_value=val.m_value;
		return (*this);
	}
//#endif

	

//	tfixpoint<T,point>&		operator=	(const tfixpoint<T,point>& val)
//	{
//		m_value=val.m_value;
//		return (*this);
//	}

//	template <class T2> tfixpoint<T,point>&		operator=	(const T2& value)
//	{
//		m_value=value;
//		return (*this);
//	}


	INLINE tfixpoint<T,point>&	operator-=	(const tfixpoint<T,point>& val)	
	{
		#ifdef STAT_FIXPOINT
		stat.subs++;
		#endif
		m_value-=val.m_value;
		return (*this);
	}	

	
	INLINE tfixpoint<T,point>&	operator+=	(const tfixpoint<T,point>& val)	
	{
#ifdef STAT_FIXPOINT
		stat.adds++;
#endif
		m_value+=val.m_value;
		return (*this);
	}

	INLINE tfixpoint<T,point>	operator-	(const tfixpoint<T,point>& val) const	
	{
		tfixpoint<T,point> Res(*this); 
		Res-=val;
		return Res;
	}

	INLINE tfixpoint<T,point>	operator+	(const tfixpoint<T,point>& val) const	
	{
		tfixpoint<T,point> Res(*this); 
		Res+=val;
		return Res;
	}

	INLINE tfixpoint<T,point>&	operator++	(int) 
	{
#ifdef STAT_FIXPOINT
		stat.adds++;
#endif
		m_value+=FIXPOINT_ONE; 
		return (*this);
	}

	INLINE tfixpoint<T,point>& operator--	(int)
	{
#ifdef STAT_FIXPOINT
		stat.subs++;
#endif
		m_value-=FIXPOINT_ONE; 
		return (*this);
	}
	
	
	

	
	template<class T2, int point2> INLINE tfixpoint<T,point>& operator*=	(const tfixpoint<T2,point2> val)
	{
#ifdef STAT_FIXPOINT
		stat.muls++;
#endif
		m_value*=val.m_value;
		m_value+=(T(1)<<(point2-1));
		m_value>>=point2;
		return (*this);
	}	

	INLINE tfixpoint<T,point>& operator*=	(const int val)
	{
#ifdef STAT_FIXPOINT
		stat.muls++;
#endif
		m_value*=val;
		return (*this);
	}	

	INLINE tfixpoint<T,point>& operator*=	(const float val)
	{
#ifdef STAT_FIXPOINT
		stat.muls++;
#endif
		m_value=ROUND2FIXED(m_value*val);
		return (*this);
	}	

	INLINE tfixpoint<T,point>& operator*=	(const double val)
	{
#ifdef STAT_FIXPOINT
		stat.muls++;
#endif
		//m_value*=val;
		m_value=ROUND2FIXED(m_value*val);
		return (*this);
	}	

	template <int point2>  INLINE tfixpoint<T,point>	operator*	(const tfixpoint<T,point2> val) const	
	{
		tfixpoint<T,point> Res(*this);
		Res*=val;
		return Res;
	}
	
	INLINE tfixpoint<T,point>	operator*	(const int val) const	
	{
		tfixpoint<T,point> Res(*this);
		Res*=val;
		return Res;
	}

/*
	INLINE tfixpoint<T,point>	operator*	(const float val) const	
	{
		tfixpoint<T,point> Res(*this);
		Res*=val;
		return Res;
	}

	INLINE tfixpoint<T,point>	operator*	(const double val) const	
	{
		tfixpoint<T,point> Res(*this);
		Res*=val;
		return Res;
	}
*/
	INLINE tfixpoint<T,point>&	operator/=	(const tfixpoint<T,point> val)		
	{
#ifdef STAT_FIXPOINT
		stat.divs++;
#endif
			long long val64=m_value;
			val64<<=point;
			val64/=val.m_value;
			m_value=val64;
			return (*this);
	}	

	INLINE tfixpoint<T,point>		operator/	(const tfixpoint<T,point> val) const	
	{
		tfixpoint<T,point> Res(*this);
		Res/=val;
		return Res;
	}

	INLINE tfixpoint<T,point>&	operator>>=	(const int y)		
	{
		m_value>>=y;
		return (*this);
	}

	INLINE tfixpoint<T,point>	operator>>	(const int y) const	
	{
		tfixpoint<T,point> z(*this);
		z>>=y;
		return z;
	}

	INLINE tfixpoint<T,point>&	operator<<=	(const int y)	
	{
		m_value<<=y;
		return (*this);
	}

	INLINE tfixpoint<T,point>	operator<<	(const int n) const
	{
		tfixpoint<T,point> Res(*this);
		Res<<=n;
		return Res;
	}

	INLINE tfixpoint<T,point>&	operator^=	(tfixpoint<T,point> &val)
	{
		m_value^=val.m_value;
		return (*this);
	}
	INLINE tfixpoint<T,point>	operator^	(tfixpoint<T,point> &val) const
	{
		tfixpoint<T,point> Res(*this);
		Res^=val;
		return Res;
	}


	INLINE tfixpoint<T,point>			operator-	() const				
	{
#ifdef STAT_FIXPOINT
		stat.subs++;
#endif
		tfixpoint<T,point> Res;
		Res.m_value=-m_value;
		return Res;
	}

	bool		operator>	(const tfixpoint<T,point>& y) const	
	{ return m_value>y.m_value;}
	bool		operator>=	(const tfixpoint<T,point>& y) const	
	{ return m_value>=y.m_value;}
	bool		operator<	(const tfixpoint<T,point>& y) const	
	{ return m_value<y.m_value;}
	bool		operator<=	(const tfixpoint<T,point>& y) const	
	{ return m_value<=y.m_value;}
	bool		operator==	(const tfixpoint<T,point>& y) const	
	{ return m_value==y.m_value;}
	bool		operator!=	(const tfixpoint<T,point>& y) const	
	{ return m_value!=y.m_value;}

	float flt(){
		float res=m_value;
		res/=FIXPOINT_ONE;
		return res;
	}
};

//template class tfixpoint<float>;
/*
template <class T, int point> INLINE tfixpoint<T,point> pow (tfixpoint<T,point> a, tfixpoint<T,point> b) { return pow(a.flt(), b.flt());}
template <class T, int point> INLINE tfixpoint<T,point> fabs(tfixpoint<T,point> a)  { return fabs(a.flt());}
template <class T, int point> INLINE tfixpoint<T,point> log (tfixpoint<T,point> a)	{ return log (a.flt());}
template <class T, int point> INLINE tfixpoint<T,point> sqrt(tfixpoint<T,point> a)  { return sqrt(a.flt());}
template <class T, int point> INLINE tfixpoint<T,point> cos (tfixpoint<T,point> a)	{ return cos (a.flt());}
template <class T, int point> INLINE tfixpoint<T,point> sin (tfixpoint<T,point> a)	{ return sin (a.flt());}
*/

//template class<int point> fixpoint32<point>: public ;

#define fixpoint64(point) tfixpoint<__int64,point>
#define fixpoint32(point) tfixpoint<int,point>

//typedef template <int point> fixpoint32<int,point>;

#define FIXPOINT64(val,point) (ROUND2FIXED((val)*((__int64(1))<<point)))

double __INLINE__ cnv2double(double x){
	return x;
}

float __INLINE__ cnv2float(float x){
	return x;
}

template <class T, int point> double __INLINE__ cnv2double(tfixpoint<T,point>& x){
	return x.flt();
}
template <class T, int point> float __INLINE__ cnv2float(tfixpoint<T,point>& x){
	return x.flt();
}

#endif
