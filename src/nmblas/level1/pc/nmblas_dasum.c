#include "math.h"
double nmblas_dasum(
   const int                  N,
   const double               * X,
   const int                  INCX
)
{
  double sum = 0;
  int i,j;
  if(N<=0){return(0);}
  for(i=0,j=0;i<N;i++,j+=INCX){
    sum += fabs(X[j]);  
  }
  return(sum);
};
