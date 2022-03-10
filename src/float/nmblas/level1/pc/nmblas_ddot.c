double nmblas_ddot(
   const int                  N,
   const double               * X,
   const int                  INCX,
   const double               * Y,
   const int                  INCY
)
{
  int i,pointer_x,pointer_y;
  double ddot_product =0;
  for(i=0,pointer_x=0,pointer_y=0;i<N;i++,pointer_x+=INCX,pointer_y+=INCY){
    ddot_product+=X[pointer_x]*Y[pointer_y]; 
  }

  return(ddot_product);
}