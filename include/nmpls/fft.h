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



#ifndef _SFFT2_H_INCLUDED_
#define _SFFT2_H_INCLUDED_


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
	


	#define FFT_SPEC_NUM_BUFFERS 2
	#define FFT_SPEC_NUM_TABLES  4
	#define FFT_SPEC_NUM_SHIFTS  8
	#define FFT_SPEC_NUM_AMPLITUDES  8
	typedef struct {
		

		nm32sc* buffer[FFT_SPEC_NUM_BUFFERS];
		void* fftTable[FFT_SPEC_NUM_TABLES];
		int shift[FFT_SPEC_NUM_SHIFTS];
		int amp[FFT_SPEC_NUM_AMPLITUDES];
		//int round[8];
		//void* coreOut;
		
		Free32Func* free;
		//NmppsAllocation allocOrder;
	} NmppsFFTSpec;

	
	
	
//	int  nmppsFFT256FwdInitAlloc(Malloc32Func* allocate,  Free32Func* free, NmppsFFTSpec* spec);
//	void nmppsFFT256Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec);
//	void nmppsFFTFree(NmppsFFTSpec* spec );
//	
//	int  nmppsFFT256FwdInitCustomAlloc(Malloc32Func* allocate,  Free32Func* free, NmppsFFTSpec* spec);
//	void nmppsFFT256FwdOptimize(void* src, void* dst, uint64* allocOrder);
	
	

//#ifdef __NM__
//#define sizeof32(t) sizeof(t)
//#else
//#define sizeof32(t) (sizeof(t)*4)
//#endif
	
	#define NMPP_OPTIMIZE_DISABLE  1 
	#define NMPP_NORMALIZE_DISABLE 2
	#define NMPP_FFT_6BIT 4
	#define NMPP_FFT_7BIT 0
	#define NMPP_OK 0
	#define NMPP_ERROR -1

	void nmppsFFTFree(NmppsFFTSpec* spec );
	
	void nmppsFFT32FwdRaw(const nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec);
	void nmppsFFT32Fwd   (const nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec);
	int  nmppsFFT32FwdInitAlloc( NmppsFFTSpec* spec, int settings);
	void nmppsFFT32Free( NmppsFFTSpec* spec);
	//void nmppsFFT32FwdRawRef2x16( nm32sc* src, nm32sc* dst);
	
//#define  nmppsFFT64FwdRaw8x8 nmppsFFT64Fwd
	void nmppsFFT64Fwd8x8Raw(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	void nmppsFFT64Fwd   	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	void nmppsFFT64Fwd2x4x8	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT64FwdInitAlloc( NmppsFFTSpec* spec, int settings);
	void nmppsFFT64Free( NmppsFFTSpec* spec);
	//void nmppsFFT64FwdRawRef2x4x8( nm32sc* src, nm32sc* dst);
	
	void nmppsFFT256Fwd (const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT256FwdOptimize(void* src, void* dst, fseq64* allocOrder) ;
	int  nmppsFFT256FwdInitAlloc( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT256FwdInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings);
	
	void nmppsFFT256Inv(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT256InvOptimize  (const void* src, const void* dst, fseq64* allocOrder) ;
	int  nmppsFFT256InvInitAlloc (NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT256InvInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free,  int settings);
	
	void nmppsFFT512FwdRaw     		(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	void nmppsFFT512Fwd				(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT512FwdOptimize		(const void* src, const void* dst, fseq64* allocOrder) ;
	int  nmppsFFT512FwdInitAlloc	( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT512FwdInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings);

	void nmppsFFT512Inv				(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	void nmppsFFT512InvRaw     		(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	int  nmppsFFT512InvOptimize  	(const void* src, const void* dst, fseq64* allocOrder) ;
	int  nmppsFFT512InvInitAlloc 	(NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT512InvInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free,  int settings);
	
	void nmppsFFT1024Fwd			(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT1024FwdOptimize	(const void* src, const void* dst, fseq64* allocOrder) ;
	int  nmppsFFT1024FwdInitAlloc	( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT1024FwdInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings);

	void nmppsFFT1024Inv			(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT1024InvOptimize  	(const void* src, const void* dst, fseq64* allocOrder) ;
	int  nmppsFFT1024InvInitAlloc 	(NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT1024InvInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free,  int settings);
	
	void nmppsFFT2048Fwd        	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	void nmppsFFT2048FwdInit		(NmppsFFTSpec* specFFT, void* datbuf0, void* datbuf1, void* tblbuf0, void* tblbuf1, int settings );
	void nmppsFFT2048Fwd4888    	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	void nmppsFFT2048Fwd4888Raw 	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	void nmppsFFT2048FwdRaw     	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
//	int  nmppsFFT2048Fwd4888_ (nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	int  nmppsFFT2048FwdOptimize	(const void* src, const void* dst, fseq64* allocOrder) ;
	int  nmppsFFT2048FwdInitAlloc	(NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT2048FwdInitAlloc4888( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT2048FwdInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings);

	
	void nmppsFFT2048Inv 			(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	void nmppsFFT2048InvRaw 		(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	int  nmppsFFT2048InvInit   		( NmppsFFTSpec* spec,  int settings, nm64s *buf0, nm64s* buf1, nm64s* tbl0, nm64s* tbl1);
	int  nmppsFFT2048InvInitAlloc	( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT2048InvInitSinCos	( NmppsFFTSpec* spec,  int settings);
	
	//int  nmppsFFT2048Inv4888RawRef (const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	//int  nmppsDFT2048InvRef_f 		(const nm32sc* src, nm32sc* dst);	
	//int  nmppsFFT2048Inv28888Ref_f	(const nm32sc* src, nm32sc* dst);
	//int  nmppsDFT2048Inv_i 			(const nm32sc* src, nm32sc* dst, int bits);		//int  nmppsFFT2048InvInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free,  int settings);
	

	#define nmppsFFT8192Fwd				nmppsFFT8192Fwd28888
	#define nmppsFFT8192FwdRaw			nmppsFFT8192Fwd28888Raw
	#define nmppsFFT8192FwdInit			nmppsFFT8192Fwd28888Init	
	#define nmppsFFT8192FwdInitAlloc	nmppsFFT8192Fwd28888InitAlloc

	#define nmppsFFT8192Inv				nmppsFFT8192Inv28888
	#define nmppsFFT8192InvRaw			nmppsFFT8192Inv28888Raw
	#define nmppsFFT8192InvInit			nmppsFFT8192Inv28888Init	
	#define nmppsFFT8192InvInitAlloc	nmppsFFT8192Inv28888InitAlloc

	#define FFT2048_TBL0_SIZE64 2048
	#define FFT2048_TBL1_SIZE64 2048
	#define FFT2048_TBL2_SIZE64 (4*4*2+4*8*8+32*8*8+256*8*8)/8
	#define FFT2048_TBL3_SIZE64 (4*4*2+4*8*8+32*8*8+256*8*8)/8
	
	#define FFT8192_TBL0_SIZE64 9344/8
	#define FFT8192_TBL1_SIZE64 65536/8
	#define FFT8192_TBL2_SIZE64 9344/8
	#define FFT8192_TBL3_SIZE64 65536/8

	//void nmppsFFT8192Fwd        	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT8192Fwd28888 		(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	int  nmppsFFT8192Fwd28888Raw 	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	int  nmppsFFT8192Fwd28888RawRef (const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT8192Fwd28888Init   ( NmppsFFTSpec* spec,  int settings, nm64s *buf0, nm64s* buf1, nm64s* tbl0, nm64s* tbl1, nm64s* tbl2, nm64s* tbl3);
	int  nmppsFFT8192Fwd28888InitAlloc( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT8192Fwd28888InitSinCos( NmppsFFTSpec* spec,  int settings);
	int  nmppsDFT8192FwdRef_f 		(const nm32sc* src, nm32sc* dst);	
	int  nmppsFFT8192Fwd28888Ref_f	(const nm32sc* src, nm32sc* dst);
	int  nmppsDFT8192Fwd_i 			(const nm32sc* src, nm32sc* dst, int bits);	

	int  nmppsFFT8192Inv28888 		(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	int  nmppsFFT8192Inv28888Raw 	(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);	
	int  nmppsFFT8192Inv28888RawRef (const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
	int  nmppsFFT8192Inv28888Init   ( NmppsFFTSpec* spec,  int settings, nm64s *buf0, nm64s* buf1, nm64s* tbl0, nm64s* tbl1, nm64s* tbl2, nm64s* tbl3);
	int  nmppsFFT8192Inv28888InitAlloc( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings);
	int  nmppsFFT8192Inv28888InitSinCos( NmppsFFTSpec* spec,  int settings);
	int  nmppsDFT8192InvRef_f 		(const nm32sc* src, nm32sc* dst);	
	int  nmppsFFT8192Inv28888Ref_f	(const nm32sc* src, nm32sc* dst);
	int  nmppsDFT8192Inv_i 			(const nm32sc* src, nm32sc* dst, int bits);	

	void nmppsFFTResetSpec(NmppsFFTSpec* spec);
#ifdef __cplusplus
		};
#endif

//#include "nmtl/tcmplx.h"
void nmppsFFT32FwdRef2x16  ( nm32sc* src, nm32sc* dst); // C++
void nmppsFFT32FwdRef2x16_f( nm32sc* src, nm32sc* dst);	// C++



void nmppsFFT64FwdRef_f     ( nm32sc* src, nm32sc* dst);
void nmppsFFT64FwdRef2x32_f ( nm32sc* src, nm32sc* dst);
void nmppsFFT64FwdRef2x4x8_f( nm32sc* src, nm32sc* dst);
void nmppsFFT64FwdRef2x4x8  ( nm32sc* src, nm32sc* dst);
void nmppsFFT64FwdRef4x4x4_f( nm32sc* src, nm32sc* dst);
void nmppsFFT64FwdRef8x8_f  ( nm32sc* src, nm32sc* dst);
void nmppsFFT64FwdRef8x8    ( nm32sc* src, nm32sc* dst);

void nmppsDFT512Fwd_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT512Fwd_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsDFT512Inv_RefFloat(const nm32sc* src, nm32sc* dst);

//id nmppsFFT2048Fwd_f      (const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec);
void nmppsDFT2048Fwd_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsDFT2048Inv_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT2048Fwd4888_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT2048Inv4888_RefFloat(const nm32sc* src, nm32sc* dst);
void nmppsFFT2048Fwd4888_RefInt(const nm32sc* src, nm32sc* dst);
void nmppsFFT2048Inv4888_RefInt(const nm32sc* src, nm32sc* dst);
//void nmppsFFT2048Fwd4888(const nm32sc* src, nm32sc* dst);

//void nmppsFFT64FwdRef2x2x16_f( nm32sc* src, nm32sc* dst);



#define SKIP_SINCOS 4

#endif 
		