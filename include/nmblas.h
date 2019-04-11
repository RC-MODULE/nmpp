 /** \ingroup NMBLAS
 *  \brief     nmblas (NeuroMatrix Basic Linear Algebra Subroutines)
 *  \author    Alexandr Bolotnikov
 *  \copyright (c) RC Module Inc.
 */

#ifndef _NMBLAS_H_INCLUDED_
#define _NMBLAS_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

/** \defgroup Level_1 Level-1
    \ingroup NMBLAS
*/

/** \defgroup CORE_nmblas Базовые регистровые функции
    \ingroup Level_1
*/

/**
 *  \ingroup Level_1
 *  \brief Brief description
 *
 *  \param [in] n Description for n
 *  \param [in,out] x Description for x
 *  \param [in] inc_x Description for inc_x
 *  \return Return description
 *
 *  \details More details
*/
double nmblas_dasum(
	const int n,
	const double *x,
	const int inc_x
);

enum nm_trans{nm_n=0,nm_t=1};


void nmblas_daxpy(
	const int n,
	const double alpha,
	const double *arr_x,
	const int inc_x,
	double *arr_y,
	const int inc_y
);
void nmblas_dcopy(
	const int N,
	const double* X,
	const int INCX,
	double* Y,
	const int INCY
);
double nmblas_ddot(
	const int N,
	const double* X,
	const int INCX,
	const double* Y,
	const int INCY
);
double nmblas_dnrm2(
	const int n,
	const double *x,
	const int inc_x
);
void nmblas_drot(
	const int N,
	double *X,
	const int INCX,
	double *Y,
	const int INCY,
	const double C,
	const double S
);
void nmblas_drotg(
	double *a,
	double *b,
	double *c,
	double *s
);
void nmblas_drotm(
	const int N,
	double *X,
	const int INCX,
	double *Y,
	const int INCY,
	double *param
);
void nmblas_dscal(
	const int N,
	const double ALPHA,
	double*X,
	const int INCX
);
double nmblas_dsdot(
	const int N,
	const float* X,
	const int INCX,
	const float* Y,
	const int INCY
);
void nmblas_dswap(
	const int N,
	double *X,
	const int INCX,
	double *Y,
	const int INCY
);
double nmblas_dznrm2(
	const int n,
	const double *x,
	const int inc_x
);
int nmblas_idamax(
	const int N,
	const double* X,
	const int INCX
);
//////////////////////////////////////////////////////level 1 single precition
int nmblas_isamax(
	const int N,
	const float* X,
	const int INCX
);
float nmblas_sasum(
	const int n,
	const float *x,
	const int inc
);
void nmblas_saxpy(int n,
	const float alpha,
	const float *arr_x,
	const int inc_x,
	float *arr_y,
	const int inc_y
);
float nmblas_scnrm2(
	const int N,
	const float* X,
	const int INCX
);
void nmblas_scopy(
	const int N,
	const float* X,
	const int  INCX,
	float* Y,
	const int INCY
);
float nmblas_sdot(
	const int n,
	const float *x,
	const int inc_x,
	const float *y,
	const int inc_y
);
float nmblas_sdsdot(
	const int N,
	const float B,
	const float* X,
	const int INCX,
	const float* Y,
	const int INCY
);
float nmblas_snrm2(
	const int N,
	const float* X,
	const int INCX
);
void nmblas_srot(
	const int N,
	float *X,
	const int INCX,
	float *Y,
	const int INCY,
	const float C,
	const float S
);
void nmblas_srotm(
	const int N,
	float *X,
	const int INCX,
	float *Y,
	const int INCY,
	float *param
);
void nmblas_sscal(
	const int n,
	const float alpha,
	const float *x,
	const int inc_x
);
void nmblas_sswap(
	const int N,
	const float *X,
	const int INCX,
	const float *Y,
	const int INCY
);

/////////////////LEVEL 2

void nmblas_sgemv(
   const enum nm_trans        TRANS,
   const int                  M,
   const int                  N,
   const float               ALPHA,
   const float               * A,
   const int                  LDA,
   const float               * X,
   const int                  INCX,
   const float               BETA,
   float                     * Y,
   const int                  INCY
);

void nmblas_dgemv(
   const enum nm_trans        TRANS,
   const int                  M,
   const int                  N,
   const double               ALPHA,
   const double               * A,
   const int                  LDA,
   const double               * X,
   const int                  INCX,
   const double               BETA,
   double                     * Y,
   const int                  INCY
);


//! \defgroup LEVEL3 BLASS-LEVEL3
//! \{

//! \}

#include<nmblas/nmblas_sgemm.h>

void MullMatrix_f( 
	void* 	A, 
	int 	pI, 
	int 	ldA, 
	void* 	B,
    int 	pK,
    int 	ldB,
    void* 	C,
    int 	pJ,
    int 	ldC,
    bool 	plusC
);


#ifdef __cplusplus
		};
#endif
#endif // _INIT_H_INCLUDED_
