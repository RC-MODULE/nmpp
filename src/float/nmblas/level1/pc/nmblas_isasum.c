#include <math.h>
int nmblas_isamax(
   const int                  N,
   const float               * X,
   const int                  INCX
)
{
  int i,pointer_x,max_index=0;
  float max = fabsf(X[0]);
  float abs;
  if(N<=0){return(0);}
  if(N==1){return(0);}
  for(i=0,pointer_x=0;i<N;i++,pointer_x+=INCX){
    abs =fabsf(X[pointer_x]);
    if(max<abs){
      max = abs;
      max_index = i;
    }
  }
  return(max_index);
};