#include "math.h"
float nmblas_sasum(
   const int                  N,
   const float               * X,
   const int                  INCX
)
{
  float sum = 0;
  int i,j;
  if(N<=0){return(0);}
  for(i=0,j=0;i<N;i++,j+=INCX){
    sum += fabsf(X[j]);  
  }
  return(sum);
};
