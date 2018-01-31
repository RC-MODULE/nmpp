void nmblas_sger( 
	const int                  M,//row
   const int                  N,//coullum
   const float                ALPHA,
   const float                * X,
   const int                  INCX,
   const float                * Y,
   const int                  INCY,
   float                      * A,
   const int                  LDA
){
 float             t0;
 int               i, iaij, ix, j, jaj, jy;

   if( ( M == 0 ) || ( N == 0 ) || ( ALPHA == 0 ) ) return;

   for( j = 0, jaj = 0, jy = 0; j < N; j++, jaj++, jy += INCY )
   {
      t0 = ALPHA * Y[jy];
      for( i = 0, iaij = jaj, ix = 0; i < M; i++, iaij += LDA, ix += INCX )
      {  
         A[iaij] += X[ix] * t0;
       }
	}

	return;
}	
