void nmblas_scopy(
   const int                  N,
   const float              * X,
   const int                  INCX,
   float                    * Y,
   const int                  INCY
)
{
  int i,pointer_x,pointer_y;
  for(i=0,pointer_x=0,pointer_y=0;i<N;i++,pointer_x+=INCX,pointer_y+=INCY){
    Y[pointer_y] = X[pointer_x];
  }
  return;

  
};