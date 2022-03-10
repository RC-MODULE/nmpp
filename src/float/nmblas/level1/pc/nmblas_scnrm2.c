#include <math.h>

float nmblas_scnrm2(
   const int                  N,
   const float                * X,
   const int                  INCX
)
{
  int i,pointer_x;
  int inner_inc_x = INCX<<1;
  float sum=0;
  if(N<=0){return(0);}
  for(i=0,pointer_x=0;i<N;i++,pointer_x+=inner_inc_x){
    sum+=X[pointer_x]*X[pointer_x]+X[pointer_x+1]*X[pointer_x+1];
  }
  return(sqrt(sum));
}