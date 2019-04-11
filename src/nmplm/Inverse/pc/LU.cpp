#include "mInverse.h"

#ifdef __cplusplus
		extern "C" {
#endif


void nmppmLUDecomp_64f (
	const double  * A,
	double        * L,
	double        * U,
	int			    n
)
{
	// LU
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			U[i][j] = A[i][j];	
		}
	}
  
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			L[i][j]= i==j?1:0;
		}
	}
    
	for(i=0; i<n-1; i++){
		for(j=i+1; j<n; j++){
			L[j][i] = U[j][i]/U[i][i];
			for(k=i; k<n; k++){
				U[j][k] = U[j][k] - L[j][i]*U[i][k];	
			}
		}
	}
}  


void nmppmLUResolve_64f (
	const double        * L,
	const double        * U,
	const double        * b,
	double              * x,
	double              * y,
	int				    N
)
{
   //SLAY
   // L*y = b;  U*x = y

	for(i=0; i<n; i++){
		x[i] = y[i] = 1;
	}
   
   
	for(i=0; i<n; i++){
		t = 0;
		for(j=0; j<i; j++){
			t+=L[i][j]*y[j]; 
		}
		y[i] = b[i]-t;
	}

	for(i=0; i<n; i++){
		t=0;
		for(j=0; j<i; j++){
			t+= U[n-i-1][n-j-1]*x[n-j-1];
		}
		x[n-i-1] = (y[n-i-1]-t)/U[n-i-1][n-i-1];
	}
}


#ifdef __cplusplus
		};
#endif