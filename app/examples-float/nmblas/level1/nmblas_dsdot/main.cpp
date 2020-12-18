#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include <nmpp.h>

#define SIZE 16

#ifdef __GNUC__ //  NMC-GCC C++ compilier 
float buffer_a[SIZE] __attribute__ ((section (".data_imu1")));
float buffer_b[SIZE] __attribute__ ((section (".data_imu2")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
float buffer_a[SIZE];
#pragma data_section ".data_imu2"
float buffer_b[SIZE];
#endif 

/*
NAME
     dsdot - Compute the double precision dot product of two sin-
     gle precision vectors x and y.

SYNOPSIS
     DOUBLE PRECISION FUNCTION DSDOT (N, X, INCY, Y, INCY )

     INTEGER INCX, INCY, N

     REAL    X( * ), Y( * )



     #include <sunperf.h>

     double dsdot_(int n, float *sx, int  incx,  float  *sy,  int
               incy) ;

PURPOSE
     DSDOT - Compute the double precision dot product of x and  y
     where x and y are single precision n-vectors.


PARAMETERS
     N         - INTEGER.
               On entry, N specifies the number  of  elements  in
               the  vector.   If N is not positive then the func-
               tion returns the value 0.0.  Unchanged on exit.

     X         - REAL array of DIMENSION at least
               ( 1 + ( n - 1 )*abs( INCX  )  ).   On  entry,  the
               incremented array X must contain the vector x.  On
               exit, the y vector.

     INCX      - INTEGER.
               On entry, INCX specifies  the  increment  for  the
               elements  of  X. INCX must not be zero.  Unchanged
               on exit.

     Y         - REAL array of DIMENSION at least
               ( 1 + ( m - 1 )*abs( INCY  )  ).   On  entry,  the
               incremented  array  Y  must  contain the vector y.
               Unchanged on exit.

     INCY      - INTEGER.
               On entry, INCY specifies  the  increment  for  the
               elements  of  Y. INCY must not be zero.  Unchanged
               on exit.
*/
int main(){

	int i=0;
	int r;
	double result =0;

	for(i=0;i<SIZE;i++){
		buffer_a[i]=i;
		buffer_b[i]=i;
		printf("%f %f\n",buffer_a[i],buffer_b[i]);
	}
	
	result = nmblas_dsdot(i,buffer_a,1,buffer_b,1);
	printf("result=  %f\n",result);
	return 0;
}

