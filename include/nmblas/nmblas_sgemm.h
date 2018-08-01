
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

//	aux macros
#define ALL_FPU( instr ) 	"fpu 0 " instr "\n\t" \
							"fpu 1 " instr "\n\t" \
							"fpu 2 " instr "\n\t" \
							"fpu 3 " instr "\n\t"

//	aux functions

//	load old C for specific fpu
static inline void
loadCFromMemory( float* pc, int ldc, const int fpu, int& dummy_to_link )
{
	asm (
			"ar0= %1 + %5;\n\t"
			"gr0= %2;\n\t"
			"fpu %4 rep vlen vreg7= [ar0++gr0];\n\t"
			: "+m"(dummy_to_link)
			: "a"(pc), "g"(ldc), "m"(*pc), "i"(fpu), "i"(fpu*2)
				: "ar0", "gr0" );
}

//	load A for all fpu-s
static inline void
loadAFromMemory( const float* pa, int lda, const int vrNum, int& dummy_to_link )
{
	asm (
			"ar0= %1;\n\t"
			"gr0= %2;\n\t"
			"fpu 0 rep vlen vreg%3 = [ar0++gr0];\n\t"
//	All fpu-s got the same vector
			"fpu 1 vreg%3 = fpu 0 vreg%3;\n\t"
			"fpu 2 vreg%3 = fpu 1 vreg%3;\n\t"
			"fpu 3 vreg%3 = fpu 2 vreg%3;\n\t"
				: "+m" (dummy_to_link), "+a" (pa)
				: "r"(lda), "i"(vrNum), "m"(*pa)
				: "ar0", "gr0" );
}

static inline void
loadBAndMAdd( const float* pb, const float* pb1, int ldb, const int vrNum, int& dummy_to_link )
{
	asm (
			"fpu 0 rep 1 vreg4 = [%1++];\n\t"
			"fpu 0 rep 1 vreg5 = [%2++];\n\t"
			"fpu 1 rep 1 vreg4 = [%1++];\n\t"
			"fpu 1 rep 1 vreg5 = [%2++];\n\t"
			"fpu 2 rep 1 vreg4 = [%1++];\n\t"
			"fpu 2 rep 1 vreg5 = [%2++];\n\t"
			"fpu 3 rep 1 vreg4 = [%1++];\n\t"
			"fpu 3 rep 1 vreg5 = [%2++];\n\t"
	      	ALL_FPU (".matrix vreg7= vreg%3 * .retrieve (vreg4,vreg5) + vreg7;")
				: "+m" (dummy_to_link), "+a" (pb), "+a" (pb1)
				: "i"(vrNum), "m"(*pb) );
}

//	Same as loadBAndMAdd, but without "+C"
static inline void
loadBAndMultiply( const float* pb, const float* pb1, int ldb, const int vrNum, int& dummy_to_link )
{
	asm (
			"fpu 0 rep 1 vreg4 = [%1++];\n\t"
			"fpu 0 rep 1 vreg5 = [%2++];\n\t"
			"fpu 1 rep 1 vreg4 = [%1++];\n\t"
			"fpu 1 rep 1 vreg5 = [%2++];\n\t"
			"fpu 2 rep 1 vreg4 = [%1++];\n\t"
			"fpu 2 rep 1 vreg5 = [%2++];\n\t"
			"fpu 3 rep 1 vreg4 = [%1++];\n\t"
			"fpu 3 rep 1 vreg5 = [%2++];\n\t"
	      	ALL_FPU (".matrix vreg7= vreg%3 * .retrieve (vreg4,vreg5);")
				: "+m" (dummy_to_link), "+a" (pb), "+a" (pb1)
				: "i"(vrNum), "m"(*pb) );
}



static inline void
storeCToMemory( float* pc, int ldc, const int fpu, int& dummy_to_link )
{
	asm (
			"ar0= %1;\n\t"
			"gr0= %2;\n\t"
			"fpu %4 rep vlen [ar0++gr0] = vreg7;\n\t"
			: "=m"(*pc)
			: "g"(pc), "g"(ldc), "m"(dummy_to_link), "i"(fpu)
				: "ar0", "gr0" );
}



static inline void
nmblas_sgemm(	const enum nm_trans TransA,
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
	int dummy_to_link;	//	workaround to reflect dependence by vector registers

	for(i=0; i<I; i+=32){
		asm (
				"vlen= %1;\n\t"
					: "=m" (dummy_to_link)
					: "g"( I-i-1 >= 31 ? 31 : I-i-1  ) );

		for(j=0; j<J; j+=8){

			k=0;
			const float* pa;
			const float* pb;
			const float* pb1;

			if ( beta!=0 ){
				//	read C[i][j]
				loadCFromMemory( C + i   *ldc +j, ldc, 0, dummy_to_link );
				loadCFromMemory( C + i   *ldc +j, ldc, 1, dummy_to_link );
				loadCFromMemory( C + i   *ldc +j, ldc, 2, dummy_to_link );
				loadCFromMemory( C + i   *ldc +j, ldc, 3, dummy_to_link );
			}
			else{
				pa  = A + i*lda +k;
				pb  = B + k*ldb +j;
				pb1 = B +(k+1)*ldb +j;

				loadAFromMemory( pa, lda, 0, dummy_to_link );

				loadBAndMultiply( pb, pb1, ldb, 0, dummy_to_link );
				k+=2;
			}



			for(  ; k<K; k+=2){
				//C[i][j] += A[i][k]*B[k][j];
				pa  = A + i*lda +k;
				pb  = B + k*ldb +j;
				pb1 = B +(k+1)*ldb +j;

				loadAFromMemory( pa, lda, 3, dummy_to_link );

				loadBAndMAdd( pb, pb1, ldb, 3, dummy_to_link );

				k+=2;
				if ( !( k<K ) )
					break;
				pa  = A + i*lda +k;
				pb  = B + k*ldb +j;
				pb1 = B +(k+1)*ldb +j;

				loadAFromMemory( pa, lda, 0, dummy_to_link );

				loadBAndMAdd( pb, pb1, ldb, 0, dummy_to_link );
			}


			//	write C[i][j]
			storeCToMemory( C + i   *ldc +j+0, ldc, 0, dummy_to_link );
			if ( J-j<=2 )
				break;
			storeCToMemory( C + i   *ldc +j+2, ldc, 1, dummy_to_link );
			if ( J-j<=4 )
				break;
			storeCToMemory( C + i   *ldc +j+4, ldc, 2, dummy_to_link );
			if ( J-j<=6 )
				break;
			storeCToMemory( C + i   *ldc +j+6, ldc, 3, dummy_to_link );
		}
	}
}



#endif /* NMBLAS_SGEMM_H_ */
