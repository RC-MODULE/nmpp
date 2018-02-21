#include <math.h>

double nmblas_dnrm2(
   const int                  N,
   const double               * X,
   const int                  INCX
)
{
  int i,pointer_x;
  double sum=0;
  for(i=0,pointer_x=0;i<N;i++,pointer_x+=INCX){
    sum+=X[pointer_x]*X[pointer_x];
  }
  return(sqrt(sum));
};
