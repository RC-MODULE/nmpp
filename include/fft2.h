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


/*! \mainpage Введение 
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
    * \endif
    * \if English
    *     \defgroup sFFT Fast Fourier Transform
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

	
#include "time.h"
#include "malloc32.h"
	


	typedef struct {
		
		int shift[4];
		int round[4];
		void* fftTable[2];
		void* buffer[4];
		Free32Func* free;
		//NmppsAllocation allocOrder;
	} NmppsFFTSpec;

	

	int  nmppsFFT256FwdInitAlloc(Malloc32Func* allocate,  Free32Func* free, NmppsFFTSpec* spec);
	void nmppsFFT256FwdOptimize(void* src, void* dst, uint64* allocOrder);
	void nmppsFFT256Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec);
	
	void nmppsFFTFree(NmppsFFTSpec* spec );



#ifdef __cplusplus
		};
#endif

#endif 
		