enum nm_trans{nm_n=0,nm_t=1};  

void nmblas_sgemv(
   const enum nm_trans           TRANS,
   const int                  M,//rows in case notrans
   const int                  N,
   const float               ALPHA,
   const float               * A,
   const int                  LDA,
   const float               * X,
   const int                  INCX,
   const float               BETA,
   float                     * Y,
   const int                  INCY
   )
{
  int i,row_index,y_index;
  int j,x_index,matrix_pointer;
  float semi_result;
  if((M<=0)|(N<=0)){
    return;
  }

  if(TRANS==nm_n){
    //not tramsponented matrix
    for(i=0,row_index=0,y_index=0; i<M; i++,row_index+=LDA,y_index+=INCY){
      float inner_y = BETA*Y[y_index];
      semi_result =0;
      for(j=0,x_index=0,matrix_pointer=row_index;j<N;j++,x_index+=INCX,matrix_pointer++){
        semi_result+=A[matrix_pointer]*X[x_index];
      }
      Y[y_index] = inner_y + ALPHA*semi_result;
    }
  }
  else{
   for(i=0,row_index=0,y_index=0; i<N;i++,row_index++,y_index+=INCY){
      float inner_y = BETA*Y[y_index];
      semi_result =0;
      for(j=0,x_index=0,matrix_pointer=row_index;j<M;j++,x_index+=INCX,matrix_pointer+=LDA){
        semi_result+=A[matrix_pointer]*X[x_index];
      }
      Y[y_index] = inner_y + ALPHA*semi_result;
    }
  }
  return;
};
