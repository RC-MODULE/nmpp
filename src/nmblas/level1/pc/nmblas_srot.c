void nmblas_srot(
   const int                  N,
   float                     * X,
   const int                  INCX,
   float                     * Y,
   const int                  INCY,
   const float               C,
   const float               S
){
  int i,pointer_x,pointer_y;

  /*x
  Each element is replaced by c*x + s*y.

  y
  Each element is replaced by c*y - s*x.
*/
  float inner_x,inner_y;
  if(N<=0|((C == 1)&(S == 0))){
    return;
  }
  
  for(i=0,pointer_x=0,pointer_y=0;i<N;i++,pointer_x+=INCX,pointer_y+=INCY){
    inner_x = C*X[pointer_x] + S*Y[pointer_y];
    inner_y = C*Y[pointer_y] - S*X[pointer_x];
    X[pointer_x] = inner_x;
    Y[pointer_y] = inner_y;
  }
  return;
}