void nmblas_saxpy(
   const int                  N,
   const float               ALPHA,
   const float               * X,
   const int                  INCX,
   float                     * Y,
   const int                  INCY
){
  int i,j,c;
  float result;
  if(N<=0){return;}
  for(i=0,j=0,c=0;i<N;i++,j+=INCY,c+=INCX){
    result = Y[j] + ALPHA*X[c];
    Y[j] = result;
  }
  return;
}
