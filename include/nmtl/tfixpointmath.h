#ifndef _tfixpoint_MATH
#define _tfixpoint_MATH
#include <math.h>


template <class T, int point> inline tfixpoint<T,point> pow (tfixpoint<T,point> a, tfixpoint<T,point> b) { return pow(a.flt(), b.flt());}
template <class T, int point> inline tfixpoint<T,point> fabs(tfixpoint<T,point> a)  { return fabs(a.flt());}
template <class T, int point> inline tfixpoint<T,point> log (tfixpoint<T,point> a)	{ return log (a.flt());}
template <class T, int point> inline tfixpoint<T,point> sqrt(tfixpoint<T,point> a)  { return sqrt(a.flt());}
template <class T, int point> inline tfixpoint<T,point> cos (tfixpoint<T,point> a)	{ return cos (a.flt());}
template <class T, int point> inline tfixpoint<T,point> sin (tfixpoint<T,point> a)	{ return sin (a.flt());}


#endif
