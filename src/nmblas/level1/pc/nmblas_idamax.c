#include <math.h>
int nmblas_idamax(
   const int                  N,
   const double               * X,
   const int                  INCX
)
{
  int i,pointer_x,max_index=0;
  double max = fabs(X[0]);
  double abs;
  if(N<=0){return(0);}
  if(N==1){return(0);}
  for(i=0,pointer_x=0;i<N;i++,pointer_x+=INCX){
    abs = fabs(X[pointer_x]);
    if(max<abs){
      max = abs;
      max_index = i;
    }
  }
  return(max_index);
};