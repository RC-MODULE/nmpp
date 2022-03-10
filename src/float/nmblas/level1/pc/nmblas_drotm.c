void nmblas_drotm(
   const int                  N,
   double                      * X,
   const int                  INCX,
   double                      * Y,
   const int                  INCY,
   const double                * PARAM
)
{
 double h11 = *(PARAM+1),h21 = *(PARAM+2),h12 = *(PARAM+3),h22 = *(PARAM+4);
 double flag = *PARAM;
 double inner_x;
 double inner_y;
 int i,pntr2x,pntr2y;
 if(N<=0){return;}
 if(flag == 0){
  h11 = 1.0;
  h22 = 1.0;
 }
 if(flag == 1.0){
  h12 = 1.0;
  h21 = -1.0;
 }
 if(flag == -2.0){
  return;
 }
 for(i=0,pntr2x=0,pntr2y=0;i<N;i++,pntr2x+=INCX,pntr2y+=INCY){
  inner_x = h11*X[pntr2x] + h12*Y[pntr2y];
  inner_y = h21*X[pntr2x] + h22*Y[pntr2y];
  X[pntr2x] = inner_x;
  Y[pntr2y] = inner_y;
 }
return;
/*x
Each element x[i] is replaced by h11*x[i] + h12*y[i].

y
Each element y[i] is replaced by h21*x[i] + h22*y[i].
*/  
}