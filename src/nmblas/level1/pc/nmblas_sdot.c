float nmblas_sdot(
   const int                  N,
   const float               * X,
   const int                  INCX,
   const float               * Y,
   const int                  INCY
)
{
  int i,pointer_x,pointer_y;
  float ddot_product =0;
  if(N<=0){return(0);}
  for(i=0,pointer_x=0,pointer_y=0;i<N;i++,pointer_x+=INCX,pointer_y+=INCY){
    ddot_product+=X[pointer_x]*Y[pointer_y]; 
  }

  return(ddot_product);
}