#include <stdio.h>
#include <stdlib.h>
#include <nmblas.h>
#include "nmpp.h"

#define SIZE 16
#ifdef __GNUC__ //  NMC-GCC C++ compilier 
double buffer_a[SIZE] __attribute__ ((section (".data_imu1")));
#else 		// NMSDK C++ compiler
#pragma data_section ".data_imu1"
double buffer_a[SIZE];

#endif 
/*
NAME
       DSCAL - BLAS level one, scales a double precision vector

SYNOPSIS
       SUBROUTINE DSCAL    ( n, alpha, x, incx )

           INTEGER           n, incx

           DOUBLE PRECISION  alpha, x


DESCRIPTION
       DSCAL  scales a double precision vector with a double precision scalar.
       DSCAL scales the vector x of length n and increment incx  by  the  con-
       stant a.

       This routine performs the following vector operation:

                 x <-- alpha x

       where alpha is a double precisoin scalar, and x is a double precision
       vector.

ARGUMENTS
       n       INTEGER. (input)
               Number of elements in the vector.
               If n <= 0, this routine returns without computation.

       alpha   DOUBLE PRECISION scalar alpha. (input)

       x       DOUBLE PRECISION, (input and output)
               Array of dimension (n-1) * |incx| + 1. Vector to be scaled.

       incx    INTEGER. (input)
               Increment between elements of x.
               If incx = 0, the results will be unpredictable.

NOTES
       This  routine  is  Level  1  Basic  Linear Algebra Subprograms (Level 1
       BLAS).

       When working backward (incx < 0 or incy < 0), each  routine  starts  at
       the end of the vector and moves backward, as follows:

            x(1-incx * (n-1)), x(1-incx * (n-2)), ..., x(1)
*/			
int main(){
	printf("Input:\n");
	for(int i=0;i<SIZE;i++){
		buffer_a[i] = i;	
		printf("%f\n",buffer_a[i]);
	}
	// DSCAL scales a vector by a constant.
	
	// ------ case 1: x2.0-----------
	nmblas_dscal(SIZE,2.0,buffer_a,1);
	
	printf("Result case 1:\n");
	for(int i=0;i<SIZE;i++){
		printf("%f\n",buffer_a[i]);
	}
	printf("Result case 2:x2.0\n");
	for(int i=0;i<SIZE;i++){
		printf("%f\n",buffer_a[i]);
	}
	// ------ case 2 -----------
	printf("Result case 2 :x10.0\n");
	
	nmblas_dscal(SIZE/2,10,buffer_a,2);
	for(int i=0;i<SIZE;i++){
		printf("%f\n",buffer_a[i]);
	}
	// ------ case 3 -----------
	printf("Result case 3: x0.1 \n");
	
	nmblas_dscal(SIZE/2,0.1,buffer_a+SIZE,-2);
	for(int i=0;i<SIZE;i++){
		printf("%f\n",buffer_a[i]);
	}
	// ------ case 4 -----------
	printf("Result case 3: x0.5 \n");
	
	nmblas_dscal(SIZE,0.5,buffer_a+SIZE,-1);
	for(int i=0;i<SIZE;i++){
		printf("%f\n",buffer_a[i]);
	}
	
	return 0;
}

