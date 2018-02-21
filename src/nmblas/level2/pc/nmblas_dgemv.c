enum nm_trans{nm_n=0,nm_t=1};  

void nmblas_dgemv(
   const enum nm_trans           TRANS,
   const int                  M,//rows in case notrans
   const int                  N,
   const double               ALPHA,
   const double               * A,
   const int                  LDA,
   const double               * X,
   const int                  INCX,
   const double               BETA,
   double                     * Y,
   const int                  INCY
   )
{
  int i,row_index,y_index;
  int j,x_index,matrix_pinter;
  double semi_result;
  if((M<=0)|(N<=0)){
    return;
  }

  if(TRANS==nm_n){
    //not tramsponented matrix
    for(i=0,row_index=0,y_index=0; i<M; i++,row_index+=LDA,y_index+=INCY){
      double inner_y = BETA*Y[y_index];
      semi_result =0;
      for(j=0,x_index=0,matrix_pinter=row_index;j<N;j++,x_index+=INCX,matrix_pinter++){
        semi_result+=A[matrix_pinter]*X[x_index];
      }
      Y[y_index] = inner_y + ALPHA*semi_result;
    }
  }
  else{
   for(i=0,row_index=0,y_index=0; i<N;i++,row_index++,y_index+=INCY){
      double inner_y = BETA*Y[y_index];
      semi_result =0;
      for(j=0,x_index=0,matrix_pinter=row_index;j<M;j++,x_index+=INCX,matrix_pinter+=LDA){
        semi_result+=A[matrix_pinter]*X[x_index];
      }
      Y[y_index] = inner_y + ALPHA*semi_result;
    }
  }
  return;
};
