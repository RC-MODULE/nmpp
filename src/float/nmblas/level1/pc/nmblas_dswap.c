void nmblas_dswap(
   const int                  N,
   double                      * X,
   const int                  INCX,
   double                      * Y,
   const int                  INCY
){
  
  int i,pointer_x,pointer_y;
  double inner_x,inner_y;
  if(N<=0){return;}
  for(i=0,pointer_x=0,pointer_y=0;i<N;i++,pointer_x+=INCX,pointer_y+=INCY){
    inner_x = X[pointer_x];
    inner_y = Y[pointer_y];
    Y[pointer_y] = inner_x;
    X[pointer_x] = inner_y;
  }
  return;
}
