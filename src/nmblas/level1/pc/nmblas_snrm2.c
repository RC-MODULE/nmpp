#include <math.h>

float nmblas_snrm2(
   const int                  N,
   const float                * X,
   const int                  INCX
)
{
  int i,pointer_x;
  float sum=0;
  if(N<=0){return(0);}
  for(i=0,pointer_x=0;i<N;i++,pointer_x+=INCX){
    sum+=X[pointer_x]*X[pointer_x];
  }
  return(sqrt(sum));
};
