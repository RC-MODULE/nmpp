//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*  (C-callable functions)                                                 */
//*                                                                         */
//*  $Workfile:: sFFT.h                                                    $*/
//*  Contents:         Header file of FFT routines                          */
//*                                                                         */
//*                                                                         */
//*  Author:     S.Mushkaev                                                 */
//*                                                                         */
//*  Version         1.0                                                    */
//*  Start    Date:  03.07.2001                                             */
//*  Release $Date: 2005/07/13 14:19:56 $									*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/

// LIBRARY  nmfft.lib



#ifndef _SFFT_H_INCLUDED_
#define _SFFT_H_INCLUDED_


#include "nmtype.h"


/* \mainpage Введение
 *
 * \htmlinclude intro.html
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...

 */



//*****************************************************************************



	/**
	*
    * \if Russian
    *     \defgroup sFFT Быстрое Преобразование Фурье
	*	  \ingroup sFFT
    * \endif
    * \if English
    *     \defgroup sFFT Fast Fourier Transform
	*     \ingroup sFFT
    * \endif
    *
	*/



//*****************************************************************************


/*
#ifndef _NMCMPLX_H_INCLUDED_
	struct nm32sc
	{
		int re;//Real;
		int im;//Imag;
		nm32sc():
			re(0),im(0){}; //Real(0),Imag(0){}
		nm32sc(int _Real,int _Imag):
			re(_Real),im(_Imag){};//Real(_Real),Imag(_Imag){}
	};
#endif //_NMCMPLX_H_INCLUDED_
*/
//#include "nmpp.h"

///////////////////////////////////////////////////////////////////////////////////
// The functions listed below are forward and inversed FFT routines for
// 256,512,1024 or 2048-point compex data, represented as arrays of nm32sc type.
// Each complex number is stored in 64-bit word.
// The lower  32-bits is real part of complex number.
// The higher 32-bits is imaginary part of complex number;
// The admissible input range of data depends on dimension of array,
// mode of calculation accuracy and on/off mode of intermediate and final scaling down (shift normalization) of results.
// This range guarantee against overflow during calculation process.
// The table of ranges you may find in "FFT Library Programmer's manual"
//
// The mode of calculation accuracy tells how sine-cosine coeffecients are represented if fixed-point format.
// When the 7-bit accuracy mode is used, output shape accuracy approaches of the maximum,
// but output is reduced by around 2%.
// If the 6-bit accuracy mode is used, then output range corresponds to result of Fourie transform
// based on floating-point arithmetic, but output is less precise.
// The mode of calulation accuracy may be set or switched by appropriate ***Set6bit() or ***Set7bit() function
// NOTE: At least on time the accuracy setting function must be called before FFT routine executing.
#include "malloc32.h"

#ifdef __cplusplus
		extern "C" {
#endif
//=============================  Forward FFT 256 =====================================




    /**
	\defgroup FFT256 FFT-256
    \ingroup sFFT
	*/

    /**
    \ingroup FFT256
    \brief
      \ru Устанавливает 6-битную точность вычислений
      \en Sets 6-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Fwd256Set6bit();	// Sets 6-bit accuracy of sin-cosine coefficients
    /**
    \ingroup FFT256
    \brief
      \ru Устанавливает 7-битную точность вычислений
      \en Sets 7-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Fwd256Set7bit();	// Sets 7-bit accuracy of sin-cosine coefficients



//					The performance of the FFT_Fwd256 routine depends on memory allocation for
//						input,output and temporary buffers.
//						For the maximum speed performance it is recommended
//						to use the following configuration:
//							GSrcBuffer: Global SRAM
//							LDstBuffer: Local  SRAM
//							LBuffer   : Local  SRAM
//							GBuffer   : Global SRAM
//
//						For this configuration the following results were achieved:
//							3994 clocks - full operation (0.1 ms at 40MHz CPU)
//							3662 clocks - without final normalization (0.092ms at 40MHz CPU)
//
//						If you are not going to use this routine as a C callable function,
//						you can reduce the number of instructions removing all stack operations. In this case
//						the total execution time can be reduced by around 50 clocks.




    /**
    \ingroup FFT256
    	\brief
		\ru Прямое быстрое преобразование Фурье-256
		\en Forward Fast Fourier Transform - 256
		\~

  		\ru	Функция выполняет дискретное комплексное 256-точечное преобразовние Фурье  на базе алгоритма БПФ по основанию 16-16
		\en	The function computes 256-point complex Fourier transform by radix-16-16 FFT method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером  256 64-р. слов
			\en Source buffer with size of 256 64-bit words.
		\~\param [out] LDstBuffer
			\ru Результирующий массив размером 256*3 64-р. слов
			\en FFT result buffer with size of 256 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 256*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 256*3 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 256*2 64-р. слов
			\en Temporary buffer on the Local Bus with size of 256*2 64-bit words.
		\~\param [in] ShiftR
			\ru Коэффициент нормализации, выполняет арифметический сдвиг результирующего массива
				на ShiftR бит вправо для получения нормализованного массива LDstBuffer.
				При передаче значения по умолчанию (-1)
				ShiftR автоматически принимается равным 14 если ранее установленна точность 7-бит функцией FFT_Fwd256Set7bit()
				и 12 - если ранее установлена точность 6-бит функцией FFT_Fwd256Set6bit().
			\en Parameter for normalization of the result buffer.
				When performing normalization each 32-bit element is shifted right by the number of bits specified
					by the ShiftR parameter.
				The default value is -1.
					It means that ShiftR will be reset to 14 if 7-bit precision is set by preceding call of the FFT_Fwd256Set6bit()
					or to 12 if 6-bit precision is set by preceding call of the FFT_Fwd256Set6bit()
	    \~ \return  void
			\note
			\ru Использование inplace параметров не допускается ( все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
				\~
    \perf
	\verbatim

    GSrcBuffer| LDstBuffer| LBuffer   | GBuffer   |   ShiftR  |   clocks
    --------------------------------------------------------------------------
        L     |     L     |     L     |     L     |     -1    |     21.54
        L     |     L     |     L     |     G     |     -1    |     16.60
        L     |     L     |     G     |     L     |     -1    |     22.17
        L     |     L     |     G     |     G     |     -1    |     20.98
        L     |     G     |     L     |     L     |     -1    |     20.53
        L     |     G     |     L     |     G     |     -1    |     17.56
        L     |     G     |     G     |     L     |     -1    |     21.17
        L     |     G     |     G     |     G     |     -1    |     21.94
        G     |     L     |     L     |     L     |     -1    |     20.57
        G     |     L     |     L     |     G     |     -1    |     15.64
        G     |     L     |     G     |     L     |     -1    |     21.21
        G     |     L     |     G     |     G     |     -1    |     20.02
        G     |     G     |     L     |     L     |     -1    |     19.57
        G     |     G     |     L     |     G     |     -1    |     16.59
        G     |     G     |     G     |     L     |     -1    |     20.20
        G     |     G     |     G     |     G     |     -1    |     20.97
        L     |     L     |     L     |     L     |     0     |     21.51
        L     |     L     |     L     |     G     |     0     |     16.58
        L     |     L     |     G     |     L     |     0     |     22.15
        L     |     L     |     G     |     G     |     0     |     20.96
        L     |     G     |     L     |     L     |     0     |     20.51
        L     |     G     |     L     |     G     |     0     |     17.53
        L     |     G     |     G     |     L     |     0     |     21.14
        L     |     G     |     G     |     G     |     0     |     21.91
        G     |     L     |     L     |     L     |     0     |     20.55
        G     |     L     |     L     |     G     |     0     |     15.62
        G     |     L     |     G     |     L     |     0     |     21.19
        G     |     L     |     G     |     G     |     0     |     20.00
        G     |     G     |     L     |     L     |     0     |     19.54
        G     |     G     |     L     |     G     |     0     |     16.57
        G     |     G     |     G     |     L     |     0     |     20.18
        G     |     G     |     G     |     G     |     0     |     20.95
 \endverbatim


    \xmlonly
        <testperf>
						 <init> FFT_Fwd256Set6bit(); </init>
             <param name="GSrcBuffer"> L G </param>
             <param name="LDstBuffer"> L G </param>
             <param name="LBuffer"> L G </param>
             <param name="GBuffer"> L G </param>
             <param name="ShiftR"> -1 0</param>
						 <size> 256 </size>
        </testperf>
    \endxmlonly


		*/
void  FFT_Fwd256(
			nm32sc*	GSrcBuffer,		// Source buffer :long[256]
			nm32sc*	LDstBuffer,		// Result FFT    :long[256]
			void*		LBuffer,	// Temp buffer   :long[256*3]
			void*		GBuffer,	// Temp buffer   :long[256*2]
			int			ShiftR=-1	// Shift normalization	by default it means ShiftR=14 at 7 bit precision and   ShiftR=12 at 6 bit precision
			);
#include "time.h"
#include "malloc32.h"






//	int  nmppsFFT256FwdInitAlloc(Malloc32Func* allocate,  Free32Func* free, NmppsFFTSpec* spec);
//	void nmppsFFT256FwdOptimize(void* src, void* dst, uint64* allocOrder);
//	void nmppsFFT256Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec);
//
//	void nmppsFFTFree(NmppsFFTSpec* spec );



   /*
struct s_fft_fwd256_settings {
	int8x8*	dataSinCos0;
	int 	sizeSinCos0; // in int64
	int 	bitsSinCos0;
	int		shift0;
	int8x8*	dataSinCos1;
	int 	sizeSinCos1; // in int64
	int 	bitsSinCos1;
	int 	shift1;
};*/

 /*

s_fft_fwd256_settings s_fft256_default={0,1,1,1,0,1,1,1};

void FFT_Fwd256_ (
	int32x2* pSrc,
	int32x2* pDst,
	int64* tmp0,
	int64* tmp1,
	s_fft_fwd256_settings* s=&s_fft256_default
);
*/

///////////////////////////////////// Inversed FFT 256 ///////////////////////////////////////
   /**
	\defgroup IFFT256 IFFT-256
    \ingroup sFFT
	*/

	/**
    \ingroup IFFT256
      \brief
      \ru Устанавливает 6-битную точность вычислений
      \en Sets 6-bit accuracy of sin-cosine coefficients
      \~
     */
void FFT_Inv256Set6bit();	// Sets 6-bit accuracy of sin-cosine coefficients

	/**
    \ingroup IFFT256
	  \brief
      \ru Устанавливает 7-битную точность вычислений
      \en Sets 7-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Inv256Set7bit();	// Sets 7-bit accuracy of sin-cosine coefficients

    /**
    \ingroup IFFT256
    \brief
      \ru Обратное быстрое преобразование Фурье. ОБПФ-256
      \en Inversed Fast Fourier Transform. FFT-256
      \~

		\ru Функция выполняет обратное дискретное комплексное 256-точечное быстрое преобразование Фурье на базе алгоритма ОБПФ по онованию 16-16.
		\en The function computes 256-point complex iFFT by radix-16-16 method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером  256 64-р. слов
			\en Source buffer with size of 256 64-bit words.
		\~\param [out] GDstBuffer
			\ru Результирующий массив размером 256 64-р. слов
			\en FFT result buffer with size of 256 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 256*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 256*3 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 256*2 64-р. слов
			\en Temporary buffer on the Local Bus with size of 256*2 64-bit words.
		\~\param [in] ShiftR1
			\ru Промежуточный сдвиг результатов на ShiftR1 бит вправо (первая нормализация). Неоходимо для предовтращения переполнения. По умолчанию равен 8
			\en Intermediate shift of results by ShiftR1 bits to the right (the first normalization). It is equal to 8 by default
		\~\param [in] ShiftR2
			\ru	Заключительный сдвиг результатов на ShiftR2 бит вправо (вторая нормализация)
				в конце вычисления обратного БПФ. По умолчанию ShiftR2 принимается равным 14 при установленной точности 7-бит с помощью функции FFT_Inv256Set7bit()
				и 12 - при точности 6-бит, установленной с помощью функции FFT_Inv256Set6bit().
			\en Final normalization of the result buffer.
				The default value of ShiftR2 is -1.
				It means that ShiftR2 will be reset to 14 if 7-bit precision was set by preceding call of the FFT_Inv256Set7bit()
				or to 12 if 6-bit precision was set by preceding call of the FFT_Inv256Set6bit()

		\~ \return void
		\note
			\ru Использование inplace параметров не допускается ( все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
			\~
    \perf
	\verbatim
    GSrcBuffer| GDstBuffer| LBuffer   |  GBuffer  |  ShiftR1  |  ShiftR2  |     clocks
    ----------------------------------------------------------------------------------
        L     |     L     |     L     |     L     |     8     |     -1    |     26.76
        L     |     L     |     L     |     L     |     0     |     -1    |     26.76
        L     |     L     |     L     |     G     |     8     |     -1    |     19.07
        L     |     L     |     L     |     G     |     0     |     -1    |     19.07
        L     |     L     |     G     |     L     |     8     |     -1    |     22.87
        L     |     L     |     G     |     L     |     0     |     -1    |     22.87
        L     |     L     |     G     |     G     |     8     |     -1    |     20.77
        L     |     L     |     G     |     G     |     0     |     -1    |     20.77
        L     |     G     |     L     |     L     |     8     |     -1    |     25.75
        L     |     G     |     L     |     L     |     0     |     -1    |     25.75
        L     |     G     |     L     |     G     |     8     |     -1    |     18.06
        L     |     G     |     L     |     G     |     0     |     -1    |     18.06
        L     |     G     |     G     |     L     |     8     |     -1    |     23.82
        L     |     G     |     G     |     L     |     0     |     -1    |     23.82
        L     |     G     |     G     |     G     |     8     |     -1    |     21.72
        L     |     G     |     G     |     G     |     0     |     -1    |     21.72
        G     |     L     |     L     |     L     |     8     |     -1    |     25.80
        G     |     L     |     L     |     L     |     0     |     -1    |     25.80
        G     |     L     |     L     |     G     |     8     |     -1    |     18.10
        G     |     L     |     L     |     G     |     0     |     -1    |     18.10
        G     |     L     |     G     |     L     |     8     |     -1    |     21.91
        G     |     L     |     G     |     L     |     0     |     -1    |     21.91
        G     |     L     |     G     |     G     |     8     |     -1    |     19.80
        G     |     L     |     G     |     G     |     0     |     -1    |     19.80
        G     |     G     |     L     |     L     |     8     |     -1    |     24.79
        G     |     G     |     L     |     L     |     0     |     -1    |     24.79
        G     |     G     |     L     |     G     |     8     |     -1    |     17.09
        G     |     G     |     L     |     G     |     0     |     -1    |     17.09
        G     |     G     |     G     |     L     |     8     |     -1    |     22.86
        G     |     G     |     G     |     L     |     0     |     -1    |     22.86
        G     |     G     |     G     |     G     |     8     |     -1    |     20.76
        G     |     G     |     G     |     G     |     0     |     -1    |     20.76
        L     |     L     |     L     |     L     |     8     |     0     |     26.74
        L     |     L     |     L     |     L     |     0     |     0     |     26.74
        L     |     L     |     L     |     G     |     8     |     0     |     19.04
        L     |     L     |     L     |     G     |     0     |     0     |     19.04
        L     |     L     |     G     |     L     |     8     |     0     |     22.85
        L     |     L     |     G     |     L     |     0     |     0     |     22.85
        L     |     L     |     G     |     G     |     8     |     0     |     20.75
        L     |     L     |     G     |     G     |     0     |     0     |     20.75
        L     |     G     |     L     |     L     |     8     |     0     |     25.73
        L     |     G     |     L     |     L     |     0     |     0     |     25.73
        L     |     G     |     L     |     G     |     8     |     0     |     18.03
        L     |     G     |     L     |     G     |     0     |     0     |     18.03
        L     |     G     |     G     |     L     |     8     |     0     |     23.80
        L     |     G     |     G     |     L     |     0     |     0     |     23.80
        L     |     G     |     G     |     G     |     8     |     0     |     21.70
        L     |     G     |     G     |     G     |     0     |     0     |     21.70
        G     |     L     |     L     |     L     |     8     |     0     |     25.77
        G     |     L     |     L     |     L     |     0     |     0     |     25.77
        G     |     L     |     L     |     G     |     8     |     0     |     18.08
        G     |     L     |     L     |     G     |     0     |     0     |     18.08
        G     |     L     |     G     |     L     |     8     |     0     |     21.88
        G     |     L     |     G     |     L     |     0     |     0     |     21.88
        G     |     L     |     G     |     G     |     8     |     0     |     19.78
        G     |     L     |     G     |     G     |     0     |     0     |     19.78
        G     |     G     |     L     |     L     |     8     |     0     |     24.76
        G     |     G     |     L     |     L     |     0     |     0     |     24.76
        G     |     G     |     L     |     G     |     8     |     0     |     17.07
        G     |     G     |     L     |     G     |     0     |     0     |     17.07
        G     |     G     |     G     |     L     |     8     |     0     |     22.83
        G     |     G     |     G     |     L     |     0     |     0     |     22.83
        G     |     G     |     G     |     G     |     8     |     0     |     20.73
        G     |     G     |     G     |     G     |     0     |     0     |     20.73
 \endverbatim

    \xmlonly
        <testperf>
			 <init> FFT_Inv256Set6bit(); </init>
             <param name="GSrcBuffer"> L G </param>
             <param name="GDstBuffer"> L G </param>
             <param name="LBuffer"> L G </param>
             <param name="GBuffer"> L G </param>
             <param name="ShiftR1"> 8 0 </param>
             <param name="ShiftR2"> -1 0</param>
						 <size> 256 </size>
        </testperf>
    \endxmlonly
		*/

void  FFT_Inv256(
			nm32sc*	GSrcBuffer,	// Source buffer :long[256]
			nm32sc*	GDstBuffer,	// Result FFT    :long[256]
			void*		LBuffer,	// Temp buffer   :long[256*3]
			void*		GBuffer,	// Temp buffer   :long[256*3]
			int			ShiftR1=8,	// Intermediate shift normalization
			int			ShiftR2=-1	// Final shift normalization
									// by default it means ShiftR2=14 at 7 bit precision
									//				 and   ShiftR2=12 at 6 bit precision
			);


//================================= FFT 512 =================================================
	/**
	\defgroup FFT512 FFT-512
    \ingroup sFFT
	*/


    /**
    \ingroup FFT512
	\brief
      \ru Устанавливает 6-битную точность вычислений
      \en Sets 6-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Fwd512Set6bit();// Sets 6-bit accuracy of sin-cosine coefficients
    /**
    \ingroup FFT512
	\brief
      \ru Устанавливает 7-битную точность вычислений
      \en Sets 7-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Fwd512Set7bit();// Sets 7-bit accuracy of sin-cosine coefficients


    /**
    \ingroup FFT512
    \brief
      \ru Прямое быстрое преобразование Фурье-512
      \en Forward Fast Fourier Transform - 512
      \~

		\ru	Функция выполняет дискретное комплексное 512-точечное преобразовние Фурье  на базе алгоритма БПФ по основанию 2-16-16
		\en	The function computes 512-point complex Fourier transform by radix 2-16-16 FFT method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером  512 64-р. слов
			\en Source buffer with size of 512 64-bit words.
		\~\param [out] GDstBuffer
			\ru Результирующий массив размером 512 64-р. слов
			\en FFT result buffer with size of 512 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 512*2 64-р. слов
			\en Temporary buffer on the Local Bus with size of 512*2 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 512*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 512*3 64-bit words.
		\~\param [in] ShiftR
			\ru Коэффициент нормализации, выполняет арифметический сдвиг результирующего массива
				на ShiftR бит вправо для получения нормализованного массива LDstBuffer.
				При передаче значения по умолчанию (-1)
				ShiftR автоматически принимается равным 14 если ранее установленна точность 7-бит функцией FFT_Fwd512Set7bit()
				и 12 - если ранее установлена точность 6-бит функцией FFT_Fwd512Set6bit().
			\en Parameter for normalization of the result buffer.
				When performing normalization
				each 32-bit element is shifted right by the number of bits specified
					by the ShiftR parameter.
				The default value is -1.
					It means that ShiftR will be reset to 14 if 7-bit precision is set by preceding call of the FFT_Fwd512Set6bit()
					or to 12 if 6-bit precision is set by preceding call of the FFT_Fwd512Set6bit()


	    \~ \return  void
			\note
			\ru Использование inplace параметров не допускается ( все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
		\~

    \perf
	\verbatim
    GSrcBuffer| GDstBuffer| LBuffer   |  GBuffer  |  ShiftR   |     clocks
    ------------------------------------------------------------------------
        L     |     L     |     L     |     L     |     -1    |     24.12
        L     |     L     |     L     |     G     |     -1    |     19.29
        L     |     L     |     G     |     L     |     -1    |     22.81
        L     |     L     |     G     |     G     |     -1    |     21.62
        L     |     G     |     L     |     L     |     -1    |     23.10
        L     |     G     |     L     |     G     |     -1    |     18.27
        L     |     G     |     G     |     L     |     -1    |     23.77
        L     |     G     |     G     |     G     |     -1    |     22.58
        G     |     L     |     L     |     L     |     -1    |     23.06
        G     |     L     |     L     |     G     |     -1    |     18.23
        G     |     L     |     G     |     L     |     -1    |     23.79
        G     |     L     |     G     |     G     |     -1    |     22.60
        G     |     G     |     L     |     L     |     -1    |     22.04
        G     |     G     |     L     |     G     |     -1    |     17.21
        G     |     G     |     G     |     L     |     -1    |     24.75
        G     |     G     |     G     |     G     |     -1    |     23.56
        L     |     L     |     L     |     L     |     0     |     24.11
        L     |     L     |     L     |     G     |     0     |     19.28
        L     |     L     |     G     |     L     |     0     |     22.80
        L     |     L     |     G     |     G     |     0     |     21.61
        L     |     G     |     L     |     L     |     0     |     23.09
        L     |     G     |     L     |     G     |     0     |     18.26
        L     |     G     |     G     |     L     |     0     |     23.76
        L     |     G     |     G     |     G     |     0     |     22.57
        G     |     L     |     L     |     L     |     0     |     23.05
        G     |     L     |     L     |     G     |     0     |     18.22
        G     |     L     |     G     |     L     |     0     |     23.78
        G     |     L     |     G     |     G     |     0     |     22.59
        G     |     G     |     L     |     L     |     0     |     22.03
        G     |     G     |     L     |     G     |     0     |     17.20
        G     |     G     |     G     |     L     |     0     |     24.74
        G     |     G     |     G     |     G     |     0     |     23.55
 \endverbatim

    \xmlonly
        <testperf>
						 <init> FFT_Fwd512Set6bit(); </init>
             <param name="GSrcBuffer"> L G </param>
             <param name="GDstBuffer"> L G </param>
             <param name="LBuffer"> L G </param>
             <param name="GBuffer"> L G </param>
             <param name="ShiftR"> -1 0</param>
						 <size> 512 </size>
        </testperf>
    \endxmlonly
		*/

void  FFT_Fwd512(
			nm32sc*	GSrcBuffer,	// Source buffer :long[512]
			nm32sc*	GDstBuffer,	// Result FFT    :long[512]
			void*		LBuffer,	// Temp buffer   :long[512*3]
			void*		GBuffer,	// Temp buffer	 :long[512*3]
			int			ShiftR=-1	// Right shift normalization
			);
//					\en	The performance of the FFT_Fwd512 routine depends on memory allocation for
//						input,output and temporary buffers.
//						For the maximum speed performance it is recommended
//						to use the following configuration:
//							GSrcBuffer: Global SRAM
//							GDstBuffer: Local  SRAM
//							LBuffer   : Local  SRAM
//							GBuffer   : Global SRAM
//
//						For this configuration the following results were achieved:
//							8766 clocks - full operation		(0.22 ms at 40MHz CPU)
//							8180 clocks - without normalization (0.2 ms at 40MHz CPU)
//
//						If you are not going to use this routine as a C callable function,
//						you can reduce the number of instructions removing all stack operations. In this case
//						the total execution time can be reduced by around 50 clocks.

//======================================= Inversed FFT 512 ============================================
  /**
	\defgroup IFFT512 IFFT-512
    \ingroup sFFT
	*/

/**
    \ingroup IFFT512
 	\brief
      \ru Устанавливает 6-битную точность вычислений
      \en Sets 6-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Inv512Set6bit();// Sets 6-bit accuracy of sin-cosine coefficients
/**
    \ingroup IFFT512
 	\brief
      \ru Устанавливает 7-битную точность вычислений
      \en Sets 7-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Inv512Set7bit();// Sets 7-bit accuracy of sin-cosine coefficients

    /**
    \ingroup IFFT512
    \brief
      \ru Обратное быстрое преобразование Фурье. ОБПФ-512
      \en Inversed Fast Fourier Transform. IFFT-512
      \~

		\ru Функция выполняет обратное дискретное комплексное 512-точечное быстрое преобразование Фурье на базе алгоритма ОБПФ по онованию 2-16-16.
		\en The function computes 512-point complex iFFT by radix 2-16-16 method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером  512 64-р. слов
			\en Source buffer with size of 512 64-bit words.
		\~\param [out] LDstBuffer
			\ru Результирующий массив размером 512 64-р. слов
			\en FFT result buffer with size of 512 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 512*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 512*3 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 512*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 512*3 64-bit words.
		\~\param [in] ShiftR1
			\ru Промежуточный сдвиг результатов на ShiftR1 бит вправо (первая нормализация). Неоходимо для предовтращения переполнения. По умолчанию равен 9
			\en Intermediate shift of results by ShiftR1 bits to the right (the first normalization). It is equal to 9 by default
		\~\param [in] ShiftR2
			\ru	Заключительный сдвиг результатов на ShiftR2 бит вправо (вторая нормализация)
				в конце вычисления обратного БПФ. По умолчанию ShiftR2 принимается равным 14 при установленной точности 7-бит с помощью функции FFT_Inv512Set7bit()
				и 12 - при точности 6-бит, установленной с помощью функции FFT_Inv512Set6bit().
			\en Final normalization of the result buffer.
				The default value of ShiftR2 is -1.
				It means that ShiftR2 will be reset to 14 if 7-bit precision was set by preceding call of the FFT_Inv512Set7bit()
				or to 12 if 6-bit precision was set by preceding call of the FFT_Inv512Set6bit()
		\~\return void
		\note
			\ru Использование inplace параметров не допускается ( все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
		\~
    \perf
	\verbatim
    GSrcBuffer| LDstBuffer|  LBuffer  |  GBuffer  |  ShiftR1  |  ShiftR2   |     clocks
    -----------------------------------------------------------------------------------
        L     |     L     |     L     |     L     |     9     |     -1     |     23.41
        L     |     L     |     L     |     L     |     0     |     -1     |     23.40
        L     |     L     |     L     |     G     |     9     |     -1     |     19.39
        L     |     L     |     L     |     G     |     0     |     -1     |     19.38
        L     |     L     |     G     |     L     |     9     |     -1     |     24.86
        L     |     L     |     G     |     L     |     0     |     -1     |     24.86
        L     |     L     |     G     |     G     |     9     |     -1     |     26.47
        L     |     L     |     G     |     G     |     0     |     -1     |     26.46
        L     |     G     |     L     |     L     |     9     |     -1     |     22.39
        L     |     G     |     L     |     L     |     0     |     -1     |     22.38
        L     |     G     |     L     |     G     |     9     |     -1     |     20.35
        L     |     G     |     L     |     G     |     0     |     -1     |     20.34
        L     |     G     |     G     |     L     |     9     |     -1     |     23.84
        L     |     G     |     G     |     L     |     0     |     -1     |     23.84
        L     |     G     |     G     |     G     |     9     |     -1     |     27.43
        L     |     G     |     G     |     G     |     0     |     -1     |     27.42
        G     |     L     |     L     |     L     |     9     |     -1     |     22.35
        G     |     L     |     L     |     L     |     0     |     -1     |     22.34
        G     |     L     |     L     |     G     |     9     |     -1     |     18.34
        G     |     L     |     L     |     G     |     0     |     -1     |     18.33
        G     |     L     |     G     |     L     |     9     |     -1     |     25.84
        G     |     L     |     G     |     L     |     0     |     -1     |     25.84
        G     |     L     |     G     |     G     |     9     |     -1     |     27.45
        G     |     L     |     G     |     G     |     0     |     -1     |     27.44
        G     |     G     |     L     |     L     |     9     |     -1     |     21.33
        G     |     G     |     L     |     L     |     0     |     -1     |     21.33
        G     |     G     |     L     |     G     |     9     |     -1     |     19.30
        G     |     G     |     L     |     G     |     0     |     -1     |     19.29
        G     |     G     |     G     |     L     |     9     |     -1     |     24.83
        G     |     G     |     G     |     L     |     0     |     -1     |     24.82
        G     |     G     |     G     |     G     |     9     |     -1     |     28.41
        G     |     G     |     G     |     G     |     0     |     -1     |     28.41
        L     |     L     |     L     |     L     |     9     |     0     |     23.40
        L     |     L     |     L     |     L     |     0     |     0     |     23.39
        L     |     L     |     L     |     G     |     9     |     0     |     19.38
        L     |     L     |     L     |     G     |     0     |     0     |     19.37
        L     |     L     |     G     |     L     |     9     |     0     |     24.85
        L     |     L     |     G     |     L     |     0     |     0     |     24.85
        L     |     L     |     G     |     G     |     9     |     0     |     26.45
        L     |     L     |     G     |     G     |     0     |     0     |     26.45
        L     |     G     |     L     |     L     |     9     |     0     |     22.38
        L     |     G     |     L     |     L     |     0     |     0     |     22.37
        L     |     G     |     L     |     G     |     9     |     0     |     20.34
        L     |     G     |     L     |     G     |     0     |     0     |     20.33
        L     |     G     |     G     |     L     |     9     |     0     |     23.83
        L     |     G     |     G     |     L     |     0     |     0     |     23.83
        L     |     G     |     G     |     G     |     9     |     0     |     27.41
        L     |     G     |     G     |     G     |     0     |     0     |     27.41
        G     |     L     |     L     |     L     |     9     |     0     |     22.34
        G     |     L     |     L     |     L     |     0     |     0     |     22.33
        G     |     L     |     L     |     G     |     9     |     0     |     18.33
        G     |     L     |     L     |     G     |     0     |     0     |     18.32
        G     |     L     |     G     |     L     |     9     |     0     |     25.83
        G     |     L     |     G     |     L     |     0     |     0     |     25.83
        G     |     L     |     G     |     G     |     9     |     0     |     27.43
        G     |     L     |     G     |     G     |     0     |     0     |     27.43
        G     |     G     |     L     |     L     |     9     |     0     |     21.32
        G     |     G     |     L     |     L     |     0     |     0     |     21.31
        G     |     G     |     L     |     G     |     9     |     0     |     19.29
        G     |     G     |     L     |     G     |     0     |     0     |     19.28
        G     |     G     |     G     |     L     |     9     |     0     |     24.81
        G     |     G     |     G     |     L     |     0     |     0     |     24.81
        G     |     G     |     G     |     G     |     9     |     0     |     28.40
        G     |     G     |     G     |     G     |     0     |     0     |     28.39
 \endverbatim

    \xmlonly
        <testperf>
						 <init> FFT_Inv512Set6bit(); </init>
             <param name="GSrcBuffer"> L G </param>
             <param name="LDstBuffer"> L G </param>
             <param name="LBuffer"> L G </param>
             <param name="GBuffer"> L G </param>
             <param name="ShiftR1"> 9 0</param>
             <param name="ShiftR2"> -1 0</param>
						 <size> 512 </size>
        </testperf>
    \endxmlonly
		*/
void  FFT_Inv512(
			nm32sc*	GSrcBuffer,	// Source buffer :long[512]
			nm32sc*	LDstBuffer,	// Result FFT    :long[512]
			void*		LBuffer,	// Temp buffer   :long[512*3]
			void*		GBuffer,	// Temp buffer	 :long[512*3]
			int			ShiftR1=9,	// First shift normalization
			int			ShiftR2=-1	// Final shift normalization
			);
//			\en	The performance of the FFT_Fwd256 routine depends on memory allocation for
//					input,output and temporary buffers.
//					For the maximum speed performance it is recommended
//					to use the following configuration:
//						GSrcBuffer: Global SRAM
//						LDstBuffer: Local  SRAM
//						LBuffer   : Local  SRAM
//						GBuffer   : Global SRAM
//
//					For this configuration the following results were achieved:
//						9407 clocks - full operation (0.24ms at 40MHz CPU)
//						8199 clocks - without normalization (0.2ms at 40Mhz CPU)
//
//					If you are not going to use this routine as a C callable function,
//					you can reduce the number of instructions removing all stack operations. In this case
//					the total execution time can be reduced by around 50 clocks.


//========================================= FFT1024 ==================================================
  /**
	\defgroup FFT1024 FFT-1024
    \ingroup sFFT
	*/

    /**
    \ingroup FFT1024
  	\brief
      \ru Устанавливает 6-битную точность вычислений
      \en Sets 6-bit accuracy of sin-cosine coefficients
      \~
	*/
	void FFT_Fwd1024Set6bit();// Sets 6-bit accuracy of sin-cosine coefficients
    /**
    \ingroup FFT1024
  	\brief
      \ru Устанавливает 7-битную точность вычислений
      \en Sets 7-bit accuracy of sin-cosine coefficients
      \~
	*/

	void FFT_Fwd1024Set7bit();// Sets 7-bit accuracy of sin-cosine coefficients

    /**
    \ingroup FFT1024
        \brief
		\ru Прямое быстрое преобразование Фурье-1024
		\en Forward Fast Fourier Transform - 1024
		\~

		\ru	Функция выполняет дискретное комплексное 1024-точечное преобразовние Фурье  на базе алгоритма БПФ по основанию 2-32-16
		\en	The function computes 1024-point complex Fourier transform by radix 2-32-16 FFT method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером  1024 64-р. слов
			\en Source buffer with size of 1024 64-bit words.
		\~\param [out] LDstBuffer
			\ru Результирующий массив размером 1024 64-р. слов
			\en FFT result buffer with size of 1024 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 1024*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 1024*3 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 1024*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 1024*3 64-bit words.
		\~\param [in] ShiftR
			\ru Коэффициент нормализации, выполняет арифметический сдвиг результирующего массива
				на ShiftR бит вправо для получения нормализованного массива LDstBuffer.
				При передаче значения по умолчанию (-1)
				ShiftR автоматически принимается равным 14 если ранее установленна точность 7-бит функцией FFT_Fwd1024Set7bit()
				и 12 - если ранее установлена точность 6-бит функцией FFT_Fwd1024Set6bit().
			\en Parameter for normalization of the result buffer.
				When performing normalization
				each 32-bit element is shifted right by the number of bits specified
					by the ShiftR parameter.
				The default value is -1.
					It means that ShiftR will be reset to 14 if 7-bit precision is set by preceding call of the FFT_Fwd1024Set6bit()
					or to 12 if 6-bit precision is set by preceding call of the FFT_Fwd1024Set6bit()
	    \~ \return  void
			\note
			\ru Использование inplace параметров не допускается ( все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
		\~
    \perf
	\verbatim
    GSrcBuffer| LDstBuffer|  LBuffer  |  GBuffer  |  ShiftR   |     clocks
    ------------------------------------------------------------------------
        L     |     L     |     L     |     L     |     -1    |     22.55
        L     |     L     |     L     |     G     |     -1    |     20.52
        L     |     L     |     G     |     L     |     -1    |     26.08
        L     |     L     |     G     |     G     |     -1    |     25.93
        L     |     G     |     L     |     L     |     -1    |     21.53
        L     |     G     |     L     |     G     |     -1    |     21.48
        L     |     G     |     G     |     L     |     -1    |     25.06
        L     |     G     |     G     |     G     |     -1    |     26.89
        G     |     L     |     L     |     L     |     -1    |     21.55
        G     |     L     |     L     |     G     |     -1    |     19.51
        G     |     L     |     G     |     L     |     -1    |     27.03
        G     |     L     |     G     |     G     |     -1    |     26.87
        G     |     G     |     L     |     L     |     -1    |     20.52
        G     |     G     |     L     |     G     |     -1    |     20.48
        G     |     G     |     G     |     L     |     -1    |     26.00
        G     |     G     |     G     |     G     |     -1    |     27.84
        L     |     L     |     L     |     L     |     0     |     22.55
        L     |     L     |     L     |     G     |     0     |     20.51
        L     |     L     |     G     |     L     |     0     |     26.08
        L     |     L     |     G     |     G     |     0     |     25.92
        L     |     G     |     L     |     L     |     0     |     21.52
        L     |     G     |     L     |     G     |     0     |     21.48
        L     |     G     |     G     |     L     |     0     |     25.05
        L     |     G     |     G     |     G     |     0     |     26.89
        G     |     L     |     L     |     L     |     0     |     21.54
        G     |     L     |     L     |     G     |     0     |     19.51
        G     |     L     |     G     |     L     |     0     |     27.02
        G     |     L     |     G     |     G     |     0     |     26.87
        G     |     G     |     L     |     L     |     0     |     20.52
        G     |     G     |     L     |     G     |     0     |     20.47
        G     |     G     |     G     |     L     |     0     |     26.00
        G     |     G     |     G     |     G     |     0     |     27.83
 \endverbatim

    \xmlonly
        <testperf>
						 <init> FFT_Fwd1024Set6bit(); </init>
             <param name="GSrcBuffer"> L G </param>
             <param name="LDstBuffer"> L G </param>
             <param name="LBuffer"> L G </param>
             <param name="GBuffer"> L G </param>
             <param name="ShiftR"> -1 0</param>
						 <size> 1024 </size>
        </testperf>
    \endxmlonly

		*/
void  FFT_Fwd1024(
			nm32sc*	GSrcBuffer,	// Source buffer :long[1024]
			nm32sc*	LDstBuffer,	// Result FFT    :long[1024]
			void*		LBuffer,	// Temp buffer   :long[1024*3]
			void*		GBuffer,	// Temp buffer   :long[1024]
			int			ShiftR=-1	// Right shift normalization
			);
//			\en The performance of the FFT_Fwd1024 routine depends on memory allocation for
//					input,output and temporary buffers.
//					For the maximum speed performance it is recommended
//					to use the following configuration:
//						GSrcBuffer: Global SRAM
//						LDstBuffer: Local  SRAM
//						LBuffer   : Local  SRAM
//						GBuffer   : Global SRAM
//
//					For this configuration the following results were achieved:
//						20041 clocks - full operation		(0.5ms at 40MHz CPU)
//						18900 clocks - without normalization (0.47ms at 40MHz CPU)
//
//					If you are not going to use this routine as a C callable function,
//					you can reduce the number of instructions removing all stack operations. In this case
//					the total execution time can be reduced by around 50 clocks.

//============================================= Inversed FFT 1024 =======================================
  /**
	\defgroup IFFT1024 IFFT-1024
    \ingroup sFFT
	*/

/**
    \ingroup IFFT1024
	\brief
      \ru Устанавливает 6-битную точность вычислений
      \en Sets 6-bit accuracy of sin-cosine coefficients
      \~
	*/
	void FFT_Inv1024Set6bit();// Sets 6-bit accuracy of sin-cosine coefficients
/**
    \ingroup IFFT1024
	\brief
      \ru Устанавливает 7-битную точность вычислений
      \en Sets 7-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Inv1024Set7bit();// Sets 7-bit accuracy of sin-cosine coefficients

    /**
    \ingroup IFFT1024
    \brief
		\ru Обратное быстрое преобразование Фурье. ОБПФ-1024
		\en Inversed Fast Fourier Transform. IFFT-1024
		\~

		\ru Функция выполняет обратное дискретное комплексное 1024-точечное быстрое преобразование Фурье на базе алгоритма ОБПФ по онованию 2-16-16.
		\en The function computes 1024-point complex iFFT by radix 2-16-16 method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером  1024 64-р. слов
			\en Source buffer with size of 1024 64-bit words.
		\~\param [out] GDstBuffer
			\ru Результирующий массив размером 1024 64-р. слов
			\en FFT result buffer with size of 1024 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 1024*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 1024*3 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 1024*3 64-р. слов
			\en Temporary buffer on the Local Bus with size of 1024*3 64-bit words.
		\~\param [in] ShiftR1
			\ru Промежуточный сдвиг результатов на ShiftR1 бит вправо (первая нормализация). Неоходимо для предовтращения переполнения. По умолчанию равен 10
			\en Intermediate shift of results by ShiftR1 bits to the right (the first normalization). It is equal to 10 by default
		\~\param [in] ShiftR2
			\ru	Заключительный сдвиг результатов на ShiftR2 бит вправо (вторая нормализация)
				в конце вычисления обратного БПФ. По умолчанию ShiftR2 принимается равным 14 при установленной точности 7-бит с помощью функции FFT_Inv1024Set7bit()
				и 12 - при точности 6-бит, установленной с помощью функции FFT_Inv1024Set6bit().
			\en Final normalization of the result buffer.
				The default value of ShiftR2 is -1.
				It means that ShiftR2 will be reset to 14 if 7-bit precision was set by preceding call of the FFT_Inv1024Set7bit()
				or to 12 if 6-bit precision was set by preceding call of the FFT_Inv1024Set6bit()
		\~ \return void
		\note
			\ru Использование inplace параметров не допускается ( все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
		\~

    \perf
	\verbatim
    GSrcBuffer| GDstBuffer|  LBuffer  |  GBuffer  |   ShiftR1  |  ShiftR2 |   clocks
    ----------------------------------------------------------------------------------
        L     |     L     |     L     |     L     |     10    |     -1    |     28.82
        L     |     L     |     L     |     L     |     0     |     -1    |     28.82
        L     |     L     |     L     |     G     |     10    |     -1    |     23.90
        L     |     L     |     L     |     G     |     0     |     -1    |     23.90
        L     |     L     |     G     |     L     |     10    |     -1    |     26.60
        L     |     L     |     G     |     L     |     0     |     -1    |     26.60
        L     |     L     |     G     |     G     |     10    |     -1    |     25.55
        L     |     L     |     G     |     G     |     0     |     -1    |     25.55
        L     |     G     |     L     |     L     |     10    |     -1    |     27.80
        L     |     G     |     L     |     L     |     0     |     -1    |     27.80
        L     |     G     |     L     |     G     |     10    |     -1    |     22.88
        L     |     G     |     L     |     G     |     0     |     -1    |     22.88
        L     |     G     |     G     |     L     |     10    |     -1    |     27.57
        L     |     G     |     G     |     L     |     0     |     -1    |     27.57
        L     |     G     |     G     |     G     |     10    |     -1    |     26.52
        L     |     G     |     G     |     G     |     0     |     -1    |     26.52
        G     |     L     |     L     |     L     |     10    |     -1    |     27.81
        G     |     L     |     L     |     L     |     0     |     -1    |     27.81
        G     |     L     |     L     |     G     |     10    |     -1    |     22.89
        G     |     L     |     L     |     G     |     0     |     -1    |     22.89
        G     |     L     |     G     |     L     |     10    |     -1    |     27.55
        G     |     L     |     G     |     L     |     0     |     -1    |     27.55
        G     |     L     |     G     |     G     |     10    |     -1    |     26.50
        G     |     L     |     G     |     G     |     0     |     -1    |     26.50
        G     |     G     |     L     |     L     |     10    |     -1    |     26.79
        G     |     G     |     L     |     L     |     0     |     -1    |     26.79
        G     |     G     |     L     |     G     |     10    |     -1    |     21.87
        G     |     G     |     L     |     G     |     0     |     -1    |     21.87
        G     |     G     |     G     |     L     |     10    |     -1    |     28.51
        G     |     G     |     G     |     L     |     0     |     -1    |     28.51
        G     |     G     |     G     |     G     |     10    |     -1    |     27.46
        G     |     G     |     G     |     G     |     0     |     -1    |     27.46
        L     |     L     |     L     |     L     |     10    |     0     |     28.82
        L     |     L     |     L     |     L     |     0     |     0     |     28.82
        L     |     L     |     L     |     G     |     10    |     0     |     23.90
        L     |     L     |     L     |     G     |     0     |     0     |     23.90
        L     |     L     |     G     |     L     |     10    |     0     |     26.60
        L     |     L     |     G     |     L     |     0     |     0     |     26.60
        L     |     L     |     G     |     G     |     10    |     0     |     25.54
        L     |     L     |     G     |     G     |     0     |     0     |     25.54
        L     |     G     |     L     |     L     |     10    |     0     |     27.79
        L     |     G     |     L     |     L     |     0     |     0     |     27.79
        L     |     G     |     L     |     G     |     10    |     0     |     22.87
        L     |     G     |     L     |     G     |     0     |     0     |     22.87
        L     |     G     |     G     |     L     |     10    |     0     |     27.56
        L     |     G     |     G     |     L     |     0     |     0     |     27.56
        L     |     G     |     G     |     G     |     10    |     0     |     26.51
        L     |     G     |     G     |     G     |     0     |     0     |     26.51
        G     |     L     |     L     |     L     |     10    |     0     |     27.81
        G     |     L     |     L     |     L     |     0     |     0     |     27.81
        G     |     L     |     L     |     G     |     10    |     0     |     22.89
        G     |     L     |     L     |     G     |     0     |     0     |     22.89
        G     |     L     |     G     |     L     |     10    |     0     |     27.54
        G     |     L     |     G     |     L     |     0     |     0     |     27.54
        G     |     L     |     G     |     G     |     10    |     0     |     26.49
        G     |     L     |     G     |     G     |     0     |     0     |     26.49
        G     |     G     |     L     |     L     |     10    |     0     |     26.78
        G     |     G     |     L     |     L     |     0     |     0     |     26.78
        G     |     G     |     L     |     G     |     10    |     0     |     21.86
        G     |     G     |     L     |     G     |     0     |     0     |     21.86
        G     |     G     |     G     |     L     |     10    |     0     |     28.51
        G     |     G     |     G     |     L     |     0     |     0     |     28.51
        G     |     G     |     G     |     G     |     10    |     0     |     27.46
        G     |     G     |     G     |     G     |     0     |     0     |     27.46
 \endverbatim

    \xmlonly
        <testperf>
			 <init> FFT_Inv1024Set6bit(); </init>
             <param name="GSrcBuffer"> L G </param>
             <param name="GDstBuffer"> L G </param>
             <param name="LBuffer"> L G </param>
             <param name="GBuffer"> L G </param>
             <param name="ShiftR1"> 10 0</param>
             <param name="ShiftR2"> -1 0</param>
						 <size> 1024 </size>
        </testperf>
    \endxmlonly
		*/

void  FFT_Inv1024(
			nm32sc*	GSrcBuffer,	// Source buffer :long[1024]
			nm32sc*	GDstBuffer,	// Result FFT    :long[1024]
			void*		LBuffer,	// Temp buffer   :long[1024*3]
			void*		GBuffer,	// Temp buffer   :long[1024*3]
			int			ShiftR1=10,	// First Right shift normalization
			int			ShiftR2=-1	// Final Right shift normalization
			);

//			\en The performance of the FFT_Fwd2048 routine depends on memory allocation for
//					input,output and temporary buffers.
//					For the maximum speed performance it is recommended
//					to use the following configuration:
//						GSrcBuffer: Global SRAM
//						LDstBuffer: Local  SRAM
//						LBuffer   : Local  SRAM
//
//					For this configuration the following results were achieved:
//						49800 clocks - full operation (1.25ms at 40 MHz CPU)
//						47624 clocks - without normalization (1.2ms at 40 MHz CPU)
//
//					If you are not going to use this routine as a C callable function,
//					you can reduce the number of instructions removing all stack operations. In this case
//					the total execution time can be reduced by around 50 clocks.

//============================================ FFT2048 ============================================
  /**
	\defgroup FFT2048 FFT-2048
    \ingroup sFFT
	*/

	// Forward FFT 2048
    /**
    \ingroup FFT2048
	\brief
      \ru Устанавливает 6-битную точность вычислений
      \en Sets 6-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Fwd2048Set6bit();// Sets 6-bit accuracy of sin-cosine coefficients
    /**
    \ingroup FFT2048
	\brief
      \ru Устанавливает 7-битную точность вычислений
      \en Sets 7-bit accuracy of sin-cosine coefficients
      \~
	*/
void FFT_Fwd2048Set7bit();// Sets 7-bit accuracy of sin-cosine coefficients

    /**
    \ingroup FFT2048
    \brief
  		\ru Прямое быстрое преобразование Фурье-2048
		\en Forward Fast Fourier Transform - 2048
		\~

		\ru	Функция выполняет дискретное комплексное 2048-точечное преобразовние Фурье  на базе алгоритма БПФ по основанию 2-32-32
		\en	The function computes 2048-point complex Fourier transform by radix 2-32-32 FFT method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером  2048 64-р. слов
			\en Source buffer with size of 2048 64-bit words.
		\~\param [out] GDstBuffer
			\ru Результирующий массив размером 2048 64-р. слов
			\en FFT result buffer with size of 2048 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 2048*4 64-р. слов
			\en Temporary buffer on the Local Bus with size of 2048*4 64-bit words.
		\~\param [in] ShiftR
			\ru Коэффициент нормализации, выполняет арифметический сдвиг результирующего массива
				на ShiftR бит вправо для получения нормализованного массива LDstBuffer.
				При передаче значения по умолчанию (-1)
				ShiftR автоматически принимается равным 14 если ранее установленна точность 7-бит функцией FFT_Fwd2048Set7bit()
				и 12 - если ранее установлена точность 6-бит функцией FFT_Fwd2048Set6bit().
			\en Parameter for normalization of the result buffer.
				When performing normalization
				each 32-bit element is shifted right by the number of bits specified
					by the ShiftR parameter.
				The default value is -1.
					It means that ShiftR will be reset to 14 if 7-bit precision is set by preceding call of the FFT_Fwd2048Set6bit()
					or to 12 if 6-bit precision is set by preceding call of the FFT_Fwd2048Set6bit()
	    \~ \return  void
			\note
			\ru Использование inplace параметров не допускается ( все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
		\~

    \perf
	\verbatim
    GSrcBuffer| GDstBuffer|  LBuffer  |   ShiftR  |     clocks
    -----------------------------------------------------------
        L     |     L     |     L     |     -1    |     26.41
        L     |     L     |     G     |     -1    |     28.97
        L     |     G     |     L     |     -1    |     25.38
        L     |     G     |     G     |     -1    |     29.93
        G     |     L     |     L     |     -1    |     25.38
        G     |     L     |     G     |     -1    |     29.93
        G     |     G     |     L     |     -1    |     24.36
        G     |     G     |     G     |     -1    |     30.89
        L     |     L     |     L     |     0     |     26.40
        L     |     L     |     G     |     0     |     28.96
        L     |     G     |     L     |     0     |     25.38
        L     |     G     |     G     |     0     |     29.93
        G     |     L     |     L     |     0     |     25.38
        G     |     L     |     G     |     0     |     29.93
        G     |     G     |     L     |     0     |     24.35
        G     |     G     |     G     |     0     |     30.89
 \endverbatim

    \xmlonly
        <testperf>
						 <init> FFT_Fwd2048Set6bit(); </init>
             <param name="GSrcBuffer"> L G </param>
             <param name="GDstBuffer"> L G </param>
             <param name="LBuffer"> L G </param>
             <param name="ShiftR"> -1 0</param>
						 <size> 2048 </size>
        </testperf>
    \endxmlonly

		*/
void  FFT_Fwd2048(
			nm32sc*	GSrcBuffer,	// Source buffer :long[2048]
			nm32sc*	GDstBuffer,	// Result FFT    :long[2048]
			void*		LBuffer,	// Temp buffer   :long[2048*4]
			int			ShiftR=-1	// Right shift normalization
			);
//			\en The performance of the FFT_Fwd2048 routine depends on memory allocation for
//					input,output and temporary buffers.
//					For the maximum speed performance it is recommended
//					to use the following configuration:
//						GSrcBuffer: Global SRAM
//						LDstBuffer: Local  SRAM
//						LBuffer   : Local  SRAM
//
//					For this configuration the following results were achieved:
//						49800 clocks - full operation (1.25ms at 40 MHz CPU)
//						47624 clocks - without normalization (1.2ms at 40 MHz CPU)
//
//					If you are not going to use this routine as a C callable function,
//					you can reduce the number of instructions removing all stack operations. In this case
//					the total execution time can be reduced by around 50 clocks.

//=========================================== Inversed FFT 2048 ==================================
     /**
	\defgroup IFFT2048 IFFT-2048
    \ingroup sFFT
	*/

	/**
    \ingroup IFFT2048
	\brief
      \ru Устанавливает 6-битную точность вычислений
      \en Sets 6-bit accuracy of sin-cosine coefficients
      \~
	*/
	void FFT_Inv2048Set6bit();// Sets 6-bit accuracy of sin-cosine coefficients
	/**
    \ingroup IFFT2048
	\brief
      \ru Устанавливает 7-битную точность вычислений
      \en Sets 7-bit accuracy of sin-cosine coefficients
      \~
	*/
	void FFT_Inv2048Set7bit();// Sets 7-bit accuracy of sin-cosine coefficients

    /**
    \ingroup IFFT2048
    \brief
		\ru Обратное быстрое преобразование Фурье. ОБПФ-2048
		\en Inversed Fast Fourier Transform. IFFT-2048
		\~

		\ru Функция выполняет обратное дискретное комплексное 2048-точечное быстрое преобразование Фурье на базе алгоритма ОБПФ по онованию 2-32-32.
		\en The function computes 2048-point complex iFFT by radix 2-32-32 method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером  2048 64-р. слов
			\en Source buffer with size of 2048 64-bit words.
		\~\param [out] LDstBuffer
			\ru Результирующий массив размером 2048 64-р. слов
			\en FFT result buffer with size of 2048 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 2048*4 64-р. слов
			\en Temporary buffer on the Local Bus with size of 2048*4 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 2048*4 64-р. слов
			\en Temporary buffer on the Local Bus with size of 2048*4 64-bit words.
		\~\param [in] ShiftR1
			\ru Промежуточный сдвиг результатов на ShiftR1 бит вправо (первая нормализация). Неоходимо для предовтращения переполнения. По умолчанию равен 11
			\en Intermediate shift of results by ShiftR1 bits to the right (the first normalization). It is equal to 11 by default
		\~\param [in] ShiftR2
			\ru	Заключительный сдвиг результатов на ShiftR2 бит вправо (вторая нормализация)
				в конце вычисления обратного БПФ. По умолчанию ShiftR2 принимается равным 14 при установленной точности 7-бит с помощью функции FFT_Inv2048Set7bit()
				и 12 - при точности 6-бит, установленной с помощью функции FFT_Inv2048Set6bit().
			\en Final normalization of the result buffer.
				The default value of ShiftR2 is -1.
				It means that ShiftR2 will be reset to 14 if 7-bit precision was set by preceding call of the FFT_Inv2048Set7bit()
				or to 12 if 6-bit precision was set by preceding call of the FFT_Inv2048Set6bit()
		\~ \return void
		\note
			\ru Использование inplace параметров не допускается ( все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
			\~
    \perf
	\verbatim
    GSrcBuffer| LDstBuffer|  LBuffer  |  GBuffer  | ShiftR1   |  ShiftR2  |    clocks
    ---------------------------------------------------------------------------------
        L     |     L     |     L     |     L     |     11    |     -1    |     30.58
        L     |     L     |     L     |     L     |     0     |     -1    |     30.58
        L     |     L     |     L     |     G     |     11    |     -1    |     26.52
        L     |     L     |     L     |     G     |     0     |     -1    |     26.52
        L     |     L     |     G     |     L     |     11    |     -1    |     31.33
        L     |     L     |     G     |     L     |     0     |     -1    |     31.33
        L     |     L     |     G     |     G     |     11    |     -1    |     29.26
        L     |     L     |     G     |     G     |     0     |     -1    |     29.26
        L     |     G     |     L     |     L     |     11    |     -1    |     29.56
        L     |     G     |     L     |     L     |     0     |     -1    |     29.55
        L     |     G     |     L     |     G     |     11    |     -1    |     27.48
        L     |     G     |     L     |     G     |     0     |     -1    |     27.48
        L     |     G     |     G     |     L     |     11    |     -1    |     30.30
        L     |     G     |     G     |     L     |     0     |     -1    |     30.30
        L     |     G     |     G     |     G     |     11    |     -1    |     30.22
        L     |     G     |     G     |     G     |     0     |     -1    |     30.22
        G     |     L     |     L     |     L     |     11    |     -1    |     29.56
        G     |     L     |     L     |     L     |     0     |     -1    |     29.56
        G     |     L     |     L     |     G     |     11    |     -1    |     25.49
        G     |     L     |     L     |     G     |     0     |     -1    |     25.49
        G     |     L     |     G     |     L     |     11    |     -1    |     32.29
        G     |     L     |     G     |     L     |     0     |     -1    |     32.29
        G     |     L     |     G     |     G     |     11    |     -1    |     30.22
        G     |     L     |     G     |     G     |     0     |     -1    |     30.22
        G     |     G     |     L     |     L     |     11    |     -1    |     28.53
        G     |     G     |     L     |     L     |     0     |     -1    |     28.53
        G     |     G     |     L     |     G     |     11    |     -1    |     26.46
        G     |     G     |     L     |     G     |     0     |     -1    |     26.46
        G     |     G     |     G     |     L     |     11    |     -1    |     31.26
        G     |     G     |     G     |     L     |     0     |     -1    |     31.26
        G     |     G     |     G     |     G     |     11    |     -1    |     31.19
        G     |     G     |     G     |     G     |     0     |     -1    |     31.18
        L     |     L     |     L     |     L     |     11    |     0     |     30.58
        L     |     L     |     L     |     L     |     0     |     0     |     30.58
        L     |     L     |     L     |     G     |     11    |     0     |     26.51
        L     |     L     |     L     |     G     |     0     |     0     |     26.51
        L     |     L     |     G     |     L     |     11    |     0     |     31.33
        L     |     L     |     G     |     L     |     0     |     0     |     31.32
        L     |     L     |     G     |     G     |     11    |     0     |     29.25
        L     |     L     |     G     |     G     |     0     |     0     |     29.25
        L     |     G     |     L     |     L     |     11    |     0     |     29.55
        L     |     G     |     L     |     L     |     0     |     0     |     29.55
        L     |     G     |     L     |     G     |     11    |     0     |     27.48
        L     |     G     |     L     |     G     |     0     |     0     |     27.48
        L     |     G     |     G     |     L     |     11    |     0     |     30.30
        L     |     G     |     G     |     L     |     0     |     0     |     30.30
        L     |     G     |     G     |     G     |     11    |     0     |     30.22
        L     |     G     |     G     |     G     |     0     |     0     |     30.22
        G     |     L     |     L     |     L     |     11    |     0     |     29.56
        G     |     L     |     L     |     L     |     0     |     0     |     29.56
        G     |     L     |     L     |     G     |     11    |     0     |     25.49
        G     |     L     |     L     |     G     |     0     |     0     |     25.49
        G     |     L     |     G     |     L     |     11    |     0     |     32.29
        G     |     L     |     G     |     L     |     0     |     0     |     32.29
        G     |     L     |     G     |     G     |     11    |     0     |     30.22
        G     |     L     |     G     |     G     |     0     |     0     |     30.22
        G     |     G     |     L     |     L     |     11    |     0     |     28.53
        G     |     G     |     L     |     L     |     0     |     0     |     28.53
        G     |     G     |     L     |     G     |     11    |     0     |     26.46
        G     |     G     |     L     |     G     |     0     |     0     |     26.46
        G     |     G     |     G     |     L     |     11    |     0     |     31.26
        G     |     G     |     G     |     L     |     0     |     0     |     31.26
        G     |     G     |     G     |     G     |     11    |     0     |     31.18
        G     |     G     |     G     |     G     |     0     |     0     |     31.18
	\endverbatim

    \xmlonly
        <testperf>
			 <init> FFT_Inv2048Set6bit(); </init>
             <param name="GSrcBuffer"> L G </param>
             <param name="LDstBuffer"> L G </param>
             <param name="LBuffer"> L G </param>
             <param name="GBuffer"> L G </param>
             <param name="ShiftR1"> 11 0</param>
             <param name="ShiftR2"> -1 0</param>
						 <size> 2048 </size>
        </testperf>
    \endxmlonly
		*/

void  FFT_Inv2048(
			nm32sc*	GSrcBuffer,	// Source buffer :long[2048]
			nm32sc*	LDstBuffer,	// Result FFT    :long[2048]
			void*		LBuffer,	// Temp buffer   :long[2048*4]
			void*		GBuffer,	// Temp buffer   :long[2048*4]
			int			ShiftR1=11,	// First Right shift normalization
			int			ShiftR2=-1	// Final Right shift normalization
			);
//			\en The performance of the FFT_Fwd256 routine depends on memory allocation for
//					input,output and temporary buffers.
//					For the maximum speed performance it is recommended
//					to use the following configuration:
//						GSrcBuffer: Global SRAM
//						LDstBuffer: Local SRAM
//						LBuffer   : Local  SRAM
//						GBuffer   : Global SRAM
//
//					For this configuration the following results were achieved:
//						52160 clocks - full operation (1.3 ms at 40MHz CPU)
//						47780 clocks - without both normalizations (1.2ms at 40MHz CPU)
//
//					If you are not going to use this routine as a C callable function,
//					you can reduce the number of instructions removing all stack operations. In this case
//					the total execution time can be reduced by around 50 clocks.#include "nmfft.h"

//============================================ FFT4096 ============================================
  /**
	\defgroup FFT4096 FFT-4096
    \ingroup sFFT
	*/

	// Forward FFT 4096

    /**
    \ingroup FFT4096
    \brief
  		\ru Прямое быстрое преобразование Фурье-4096
		\en Forward Fast Fourier Transform - 4096
		\~

		\ru	Функция выполняет дискретное комплексное 4096-точечное преобразовние Фурье на базе алгоритма БПФ по основанию 16-16-16
		\en	The function computes 4096-point complex Fourier transform by radix 16-16-16 FFT method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером 4096 64-р. слов
			\en Source buffer with size of 4096 64-bit words.
		\~\param [out] GDstBuffer
			\ru Результирующий массив размером 4096 64-р. слов
			\en FFT result buffer with size of 4096 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 4096*2 64-р. слов
			\en Temporary buffer on the Local Bus with size of 4096*2 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 4096*3 64-р. слов
			\en Temporary buffer on the Global Bus with size of 4096*3 64-bit words.
	    \~ \return void
			\note
			\ru Использование inplace параметров не допускается (все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
 			\ru Диапазон входных данных: -4096..4096
			\en Input data range: -4096..4096
		\~
		\perf
			\verbatim
    GSrcBuffer | GDstBuffer | LBuffer | GBuffer | Clocks
    ----------------------------------------------------
         L     |     L      |    L    |    L    | 38.25
         L     |     L      |    L    |    G    | 26.82
         L     |     L      |    G    |    L    | 32.21
         L     |     L      |    G    |    G    | 30.74
         L     |     G      |    L    |    L    | 37.22
         L     |     G      |    L    |    G    | 25.79
         L     |     G      |    G    |    L    | 33.17
         L     |     G      |    G    |    G    | 31.71
         G     |     L      |    L    |    L    | 37.26
         G     |     L      |    L    |    G    | 25.83
         G     |     L      |    G    |    L    | 31.21
         G     |     L      |    G    |    G    | 29.75
         G     |     G      |    L    |    L    | 36.23
         G     |     G      |    L    |    G    | 24.80
         G     |     G      |    G    |    L    | 32.18
         G     |     G      |    G    |    G    | 30.71
			\endverbatim

		*/
void FFT_Fwd4096(
			nm32sc*	GSrcBuffer,		// Source buffer :long[4096]
			nm32sc*	GDstBuffer,		// Result FFT    :long[4096]
			void*		LBuffer,	// Temp buffer   :long[4096*2]
			void*		GBuffer		// Temp buffer   :long[4096*3]
			);

//=========================================== Inversed FFT 4096 ==================================
     /**
	\defgroup IFFT4096 IFFT-4096
    \ingroup sFFT
	*/

    /**
    \ingroup IFFT4096
    \brief
		\ru Обратное быстрое преобразование Фурье. ОБПФ-4096
		\en Inversed Fast Fourier Transform. IFFT-4096
		\~

		\ru Функция выполняет обратное дискретное комплексное 4096-точечное быстрое преобразование Фурье на базе алгоритма ОБПФ по онованию 16-16-16.
		\en The function computes 4096-point complex iFFT by radix 16-16-16 method.

		\~\param [in] GSrcBuffer
			\ru Входной массив размером 4096 64-р. слов
			\en Source buffer with size of 4096 64-bit words.
		\~\param [out] GDstBuffer
			\ru Результирующий массив размером 4096 64-р. слов
			\en FFT result buffer with size of 4096 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 4096*2 64-р. слов
			\en Temporary buffer on the Local Bus with size of 4096*2 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 4096*3 64-р. слов
			\en Temporary buffer on the Global Bus with size of 4096*3 64-bit words.
		\~ \return void
		\note
			\ru Использование inplace параметров не допускается (все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
 			\ru Диапазон входных данных: -4096..4096
			\en Input data range: -4096..4096
			\~
		\perf
		\verbatim
    GSrcBuffer | GDstBuffer | LBuffer | GBuffer | Clocks
    ----------------------------------------------------
         L     |     L      |    L    |    L    | 38.25
         L     |     L      |    L    |    G    | 26.82
         L     |     L      |    G    |    L    | 32.21
         L     |     L      |    G    |    G    | 30.74
         L     |     G      |    L    |    L    | 37.22
         L     |     G      |    L    |    G    | 25.79
         L     |     G      |    G    |    L    | 33.17
         L     |     G      |    G    |    G    | 31.71
         G     |     L      |    L    |    L    | 37.26
         G     |     L      |    L    |    G    | 25.83
         G     |     L      |    G    |    L    | 31.21
         G     |     L      |    G    |    G    | 29.75
         G     |     G      |    L    |    L    | 36.23
         G     |     G      |    L    |    G    | 24.80
         G     |     G      |    G    |    L    | 32.18
         G     |     G      |    G    |    G    | 30.71
			\endverbatim
		*/

void FFT_Inv4096(
			nm32sc*	GSrcBuffer,		// Source buffer :long[4096]
			nm32sc*	GDstBuffer,		// Result FFT    :long[4096]
			void*		LBuffer,	// Temp buffer   :long[4096*2]
			void*		GBuffer		// Temp buffer   :long[4096*3]
			);

//============================================ FFT8192 ============================================
  /**
	\defgroup FFT8192 FFT-8192
    \ingroup sFFT
	*/

	// Forward FFT 8192

    /**
    \ingroup FFT8192
    \brief
  		\ru Прямое быстрое преобразование Фурье-8192
		\en Forward Fast Fourier Transform - 8192
		\~

		\ru	Функция выполняет дискретное комплексное 8192-точечное преобразовние Фурье на базе алгоритма БПФ по основанию 2-16-16-16
		\en	The function computes 8192-point complex Fourier transform by radix 2-16-16-16 FFT method.

		\~\param [in] LSrcBuffer
			\ru Входной массив размером 8192 64-р. слов
			\en Source buffer with size of 8192 64-bit words.
		\~\param [out] GDstBuffer
			\ru Результирующий массив размером 8192 64-р. слов
			\en FFT result buffer with size of 8192 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 8192 64-р. слов
			\en Temporary buffer on the Local Bus with size of 8192 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 8192*3 64-р. слов
			\en Temporary buffer on the Global Bus with size of 8192*3 64-bit words.
	    \~ \return void
			\note
			\ru Использование inplace параметров не допускается (все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
 			\ru Диапазон входных данных: -2048..2048
			\en Input data range: -2048..2048
			\~
		\perf
			\verbatim
    LSrcBuffer | GDstBuffer | LBuffer | GBuffer | Clocks
    ----------------------------------------------------
         L     |     L      |    L    |    L    | 40.70
         L     |     L      |    L    |    G    | 28.89
         L     |     L      |    G    |    L    | 35.55
         L     |     L      |    G    |    G    | 31.88
         L     |     G      |    L    |    L    | 39.67
         L     |     G      |    L    |    G    | 27.86
         L     |     G      |    G    |    L    | 36.52
         L     |     G      |    G    |    G    | 32.85
         G     |     L      |    L    |    L    | 40.17
         G     |     L      |    L    |    G    | 29.40
         G     |     L      |    G    |    L    | 35.02
         G     |     L      |    G    |    G    | 32.39
         G     |     G      |    L    |    L    | 39.14
         G     |     G      |    L    |    G    | 28.37
         G     |     G      |    G    |    L    | 35.99
         G     |     G      |    G    |    G    | 33.36
			\endverbatim

		*/


void FFT_Fwd8192(
			nm32sc*	LSrcBuffer,		// Source buffer :long[8192]
			nm32sc*	GDstBuffer,		// Result FFT    :long[8192]
			void*		LBuffer,	// Temp buffer   :long[8192]
			void*		GBuffer		// Temp buffer   :long[8192*3]
			);

//=========================================== Inversed FFT 8192 ==================================
     /**
	\defgroup IFFT8192 IFFT-8192
    \ingroup sFFT
	*/

    /**
    \ingroup IFFT8192
    \brief
		\ru Обратное быстрое преобразование Фурье. ОБПФ-8192
		\en Inversed Fast Fourier Transform. IFFT-8192
		\~

		\ru Функция выполняет обратное дискретное комплексное 8192-точечное быстрое преобразование Фурье на базе алгоритма ОБПФ по онованию 2-16-16-16.
		\en The function computes 8192-point complex iFFT by radix 2-16-16-16 method.

		\~\param [in] LSrcBuffer
			\ru Входной массив размером 8192 64-р. слов
			\en Source buffer with size of 8192 64-bit words.
		\~\param [out] GDstBuffer
			\ru Результирующий массив размером 8192 64-р. слов
			\en FFT result buffer with size of 8192 64-bit words.
		\~\param [in] LBuffer
			\ru Временный массив на локальной шине (Local Bus) размером 8192 64-р. слов
			\en Temporary buffer on the Local Bus with size of 8192 64-bit words.
		\~\param [in] GBuffer
			\ru Временный массив на глобальной шине (Global Bus) размером 8192*3 64-р. слов
			\en Temporary buffer on the Global Bus with size of 8192*3 64-bit words.
		\~ \return void
		\note
			\ru Использование inplace параметров не допускается (все указатели должны быть разными)
			\en Using of inplace parameters is forbbiden (all The pointers can not refer to the same array)
 			\ru Диапазон входных данных: -2048..2048
			\en Input data range: -2048..2048
			\~

		\perf
			\verbatim
    GSrcBuffer | GDstBuffer | LBuffer | GBuffer | Clocks
    ----------------------------------------------------
         L     |     L      |    L    |    L    | 40.70
         L     |     L      |    L    |    G    | 28.89
         L     |     L      |    G    |    L    | 35.55
         L     |     L      |    G    |    G    | 31.88
         L     |     G      |    L    |    L    | 39.67
         L     |     G      |    L    |    G    | 27.86
         L     |     G      |    G    |    L    | 36.52
         L     |     G      |    G    |    G    | 32.85
         G     |     L      |    L    |    L    | 40.17
         G     |     L      |    L    |    G    | 29.40
         G     |     L      |    G    |    L    | 35.02
         G     |     L      |    G    |    G    | 32.39
         G     |     G      |    L    |    L    | 39.14
         G     |     G      |    L    |    G    | 28.37
         G     |     G      |    G    |    L    | 35.99
         G     |     G      |    G    |    G    | 33.36
            \endverbatim
        */

void FFT_Inv8192(
			nm32sc*	LSrcBuffer,		// Source buffer :long[8192]
			nm32sc*	GDstBuffer,		// Result FFT    :long[8192]
			void*		LBuffer,	// Temp buffer   :long[8192]
			void*		GBuffer		// Temp buffer   :long[8192*3]
			);



#ifdef __cplusplus
		};
#endif

#endif
