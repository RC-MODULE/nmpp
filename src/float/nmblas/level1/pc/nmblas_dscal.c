void nmblas_dscal(
   const int                  N,
   const double               ALPHA,
   double                     * X,
   const int                  INCX
)
{
  int i,pointer_x;
  if(N<=0){return;} 
  for(i=0,pointer_x=0;i<N;i++,pointer_x+=INCX){
    X[pointer_x] = ALPHA*X[pointer_x];
  }
  return;
}