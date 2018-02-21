double nmblas_dsdot(
   const int                  N,
   const float                * X,
   const int                  INCX,
   const float                * Y,
   const int                  INCY
)
{
 int i,pointer_x,pointer_y;
 double dot_producte = 0;
 if(N<=0){return(0);}
 for(i=0,pointer_x=0,pointer_y=0;i<N;i++,pointer_x+=INCX,pointer_y+=INCY){
  dot_producte += (double)X[pointer_x]*(double)Y[pointer_y];
 }
 return(dot_producte);
};