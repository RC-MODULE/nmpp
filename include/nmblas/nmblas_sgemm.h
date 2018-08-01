
 /**
 *  \ingroup LEVEL3
 *  \brief     part of nmblas library, sgemm function implementation
 *  \details   single precision matrix multiplication implementation
 *  \details   C = alpha*A*B + beta*C
 *  \details   see blas\cblas docs for detailed description
 *  \details   limitations: M, N, K, ld* must be all even, all matrix rows must be even aligned
 *  \details   limitations: row major (C order, not Fortran) only
 *  \details   limitations: TransA is not supported yet
 *  \author    leshabirukov
 *  \version   1.0
 *  \date      2018-07-26
 *  \param [in] TransA transpose first multiplicand (A) flag
 *  \param [in] TransB transpose second multiplicand (B) flag
 *  \param [in] M number of rows of the matrix A and C
 *  \param [in] N number of columns of the matrix B and C
 *  \param [in] K number of rows of the matrix B and of columns of the matrix C
 *  \param [in] alpha specifies the scalar alpha
 *  \param [in] A pointer to the first multiplicand
 *  \param [in] lda A stride, first dimension of A holder
 *  \param [in] B pointer to the second multiplicand
 *  \param [in] ldb B stride, first dimension of B holder
 *  \param [in] beta specifies the scalar beta
 *  \param [in,out] C pointer to accumulator matrix
 *  \param [in] ldc C stride, first dimension of C holder
 *  \bug
 *  \warning
 *  \copyright (c) RC Module Inc.
 *  \file nmblas_sgemm.h
 */

 //! \defgroup LEVEL3 BLASS-LEVEL3
 //! \{

 //! \}

#ifndef NMBLAS_SGEMM_H_
#define NMBLAS_SGEMM_H_

#define ALL_FPU( instr ) 	"fpu 0 " instr "\n\t" \
							"fpu 1 " instr "\n\t" \
							"fpu 2 " instr "\n\t" \
							"fpu 3 " instr "\n\t"


//static inline storeToMemory()
//{
//
//}
//

static inline
void nmblas_sgemm(	const enum nm_trans TransA,
					const enum nm_trans TransB,
					const int M,
					const int N,
					const int K,
					const float alpha,
					const float *A,
					const int lda,
					const float *B,
					const int ldb,
					const float beta,
					float *C,
					const int ldc
					)
{
	if( TransA != nm_n || TransB != nm_n || alpha != 1 || beta != 1 ){/*!!!!!!!!!!!!!!!!!!!!!!!!!*/}

	const int I=M;
	const int J=N;
	int i, j, k;
	int dummy_to_link;

	for(i=0; i<I; i+=32){
		asm (
				"vlen= %1;\n\t"
					: "=m" (dummy_to_link)
					: "g"( I-i-1 >= 31 ? 31 : I-i-1  ) );

		for(j=0; j<J; j+=8){
			//	read C[i][j]
			float* pc  = C + i   *ldc +j;
			asm (
					"ar0= %1;\n\t"
					"gr0= %2;\n\t"
					"fpu 0 rep vlen vreg7= [ar0++gr0];\n\t"
					"ar0= %1+2;\n\t"
					"fpu 1 rep vlen vreg7= [ar0++gr0];\n\t"
					"ar0= %1+4;\n\t"
					"fpu 2 rep vlen vreg7= [ar0++gr0];\n\t"
					"ar0= %1+6;\n\t"
					"fpu 3 rep vlen vreg7= [ar0++gr0];\n\t"
					: "+m"(dummy_to_link), "+a"(pc)
					: "r"(ldc), "m"(*pc)
						: "ar0", "gr0" );

			const float* pa;
			const float* pb;
			const float* pb1;
			for(k=0; k<K; k+=2){
				//C[i][j] += A[i][k]*B[k][j];
				pa  = A + i*lda +k;
				pb  = B + k*ldb +j;
				pb1 = B +(k+1)*ldb +j;

				asm (
						"ar0= %1;\n\t"
						"gr0= %2;\n\t"
						"fpu 0 rep vlen vreg3 = [ar0++gr0];\n\t"
						"fpu 1 vreg3 = fpu 0 vreg3;\n\t"
						"fpu 2 vreg3 = fpu 1 vreg3;\n\t"
						"fpu 3 vreg3 = fpu 2 vreg3;\n\t"
							: "+m" (dummy_to_link), "+a" (pa)
							: "r"(lda), "m"(*pa)
							: "ar0", "gr0" );

				asm (
						"fpu 0 rep 1 vreg4 = [%1++];\n\t"
						"fpu 0 rep 1 vreg5 = [%2++];\n\t"
						"fpu 1 rep 1 vreg4 = [%1++];\n\t"
						"fpu 1 rep 1 vreg5 = [%2++];\n\t"
						"fpu 2 rep 1 vreg4 = [%1++];\n\t"
						"fpu 2 rep 1 vreg5 = [%2++];\n\t"
						"fpu 3 rep 1 vreg4 = [%1++];\n\t"
						"fpu 3 rep 1 vreg5 = [%2++];\n\t"
				      	ALL_FPU (".matrix vreg7= vreg3 * .retrieve (vreg4,vreg5) + vreg7;")
							: "+m" (dummy_to_link), "+a" (pb), "+a" (pb1)
							: "m"(*pb) );
				k+=2;
				if ( !( k<K ) )
					break;
				pa  = A + i*lda +k;
				pb  = B + k*ldb +j;
				pb1 = B +(k+1)*ldb +j;
				asm (
						"ar0= %1;\n\t"
						"gr0= %2;\n\t"
						"fpu 0 rep vlen vreg0 = [ar0++gr0];\n\t"
						"fpu 1 vreg0 = fpu 0 vreg0;\n\t"
						"fpu 2 vreg0 = fpu 1 vreg0;\n\t"
						"fpu 3 vreg0 = fpu 2 vreg0;\n\t"
							: "+m" (dummy_to_link), "+a" (pa)
							: "r"(lda), "m"(*pa)
							: "ar0", "gr0" );

				asm (
						"fpu 0 rep 1 vreg4 = [%1++];\n\t"
						"fpu 0 rep 1 vreg5 = [%2++];\n\t"
						"fpu 1 rep 1 vreg4 = [%1++];\n\t"
						"fpu 1 rep 1 vreg5 = [%2++];\n\t"
						"fpu 2 rep 1 vreg4 = [%1++];\n\t"
						"fpu 2 rep 1 vreg5 = [%2++];\n\t"
						"fpu 3 rep 1 vreg4 = [%1++];\n\t"
						"fpu 3 rep 1 vreg5 = [%2++];\n\t"
				      	ALL_FPU (".matrix vreg7= vreg0 * .retrieve (vreg4,vreg5) + vreg7;")
							: "+m" (dummy_to_link), "+a" (pb), "+a" (pb1)
							: "m"(*pb) );
			}
			//	write C[i][j]
			pc  = C + i   *ldc +j+0;
			asm (
					"ar0= %1;\n\t"
					"gr0= %2;\n\t"
					"fpu 0 rep vlen [ar0++gr0] = vreg7;\n\t"
					: "=m"(*pc), "+a"(pc)
					: "r"(ldc), "m"(dummy_to_link)
						: "ar0", "gr0" );
			if ( J-j<=2 )
				break;
			pc  = C + i   *ldc +j+2;
			asm (
					"ar0= %1;\n\t"
					"gr0= %2;\n\t"
					"fpu 1 rep vlen [ar0++gr0] = vreg7;\n\t"
					: "=m"(*pc), "+a"(pc)
					: "r"(ldc), "m"(dummy_to_link)
						: "ar0", "gr0" );
			if ( J-j<=4 )
				break;
			pc  = C + i   *ldc +j+4;
			asm (
					"ar0= %1;\n\t"
					"gr0= %2;\n\t"
					"fpu 2 rep vlen [ar0++gr0] = vreg7;\n\t"
					: "=m"(*pc), "+a"(pc)
					: "r"(ldc), "m"(dummy_to_link)
						: "ar0", "gr0" );
			if ( J-j<=6 )
				break;
			pc  = C + i   *ldc +j+6;
			asm (
					"ar0= %1;\n\t"
					"gr0= %2;\n\t"
					"fpu 3 rep vlen [ar0++gr0] = vreg7;\n\t"
					: "=m"(*pc), "+a"(pc)
					: "r"(ldc), "m"(dummy_to_link)
						: "ar0", "gr0" );
		}
	}
}



#endif /* NMBLAS_SGEMM_H_ */
