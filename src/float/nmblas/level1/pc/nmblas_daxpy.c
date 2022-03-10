void nmblas_daxpy(
   const int                  N,
   const double                ALPHA,
   const double                * X,
   const int                  INCX,
   double                      * Y,
   const int                  INCY
){
  int i,j,c;
  double result;
  if(N<=0){return;}
  for(i=0,j=0,c=0;i<N;i++,j+=INCY,c+=INCX){
    result = Y[j] + ALPHA*X[c];
    Y[j] = result;
  }
  return;
}
