//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             iFFT256.asm                                         */
//*   Contents:         Routine for inverse iFFT 256 of complex array       */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Version           1.2                                                 */
//*   Start date:       03.07.2000                                          */
//*   Release   $Date: 2005/07/13 14:19:56 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/
    //--------------------------------------------------------------------
    //! \fn int FFT_Inv256(nm32sc*	GSrcBuffer, nm32sc*	GDstBuffer, void*	LBuffer, void*	GBuffer, int ShiftR1=8, int ShiftR2=-1)
	//!
	//! \perfinclude _FFT_Inv256__F6nm32scP6nm32scPPvPvii.html
    //--------------------------------------------------------------------

//
//global _FFT_Inv256Set:label;
global _FFT_Inv256	:label;

//extern IW1_256_7bit	:long;
//extern IW2_256_7bit	:long;
//extern IW1_256_6bit	:long;
//extern IW2_256_6bit	:long;

//import from vecmacro;
//import from regs;
import from rtmacro;
import from macros;

data ".data_fft_L"
	
	TableOfRounders:long[32]=(
		0000000000000000hl,0000000100000001hl,0000000200000002hl,0000000400000004hl,
		0000000800000008hl,0000001000000010hl,0000002000000020hl,0000004000000040hl,
		0000008000000080hl,0000010000000100hl,0000020000000200hl,0000040000000400hl,
		0000080000000800hl,0000100000001000hl,0000200000002000hl,0000400000004000hl,
		0000800000008000hl,0001000000010000hl,0002000000020000hl,0004000000040000hl,
		0008000000080000hl,0010000000100000hl,0020000000200000hl,0040000000400000hl,
		0080000000800000hl,0100000001000000hl,0200000002000000hl,0400000004000000hl,
		0800000008000000hl,1000000010000000hl,2000000020000000hl,4000000040000000hl);
	
	// Next 3 variables may be modified by FFT_Fwd256Set for switch FFT_Fwd256 from 7bit accuracy to 6 bit and vice versa 
global	IW1_256:word;//=IW1_256_7bit;
global	IW2_256:word;//=IW2_256_7bit;
global	IDefaultShiftR2_256:word=14;		
	Rounder1:long;
	Rounder2:long;
	
	struct SParam
		GDstBuffer	:word;	//[256*2]
		GSrcBuffer	:word;	//[256*2]
		LBuffer1	:word;	//[256*2*2]
		GBuffer1	:word;	//[256*2*2]
		ShiftR1		:word;
		ShiftR2		:word;
		LBuffer2	:word;	//[256*2]
		GBuffer2	:word;
		
	end SParam;
	.align;	Param :SParam;
	LAddCmplxMask:long[2]=(
			0000000100000000hl,
			00000000FFFFFFFFhl
			);


end ".data_fft_L";




data ".data_fft_G"
	GAddCmplxMask:long[2]=(
			0000000100000000hl,
			00000000FFFFFFFFhl
			);
end ".data_fft_G";





begin ".text_fft"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  This routine  switches function FFT_Inv256 from 7bit accuracy to         //
//    6 bit accuracy and vice versa  (for more information see "nmfft.h")   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//<_FFT_Inv256Set>
//.branch;
//	ar5=sp-2;
//	gr7=[--ar5];	//gr7=1 for using 7bit accuracy, otherwise  FFT_Inv256 will be switched to 6bit accuracy 
//	with gr7--;
//	if =0 delayed goto Set7Bit;
//			   gr7 = IW1_256_6bit;
//	[IW1_256] = gr7;
//			   gr7 = IW2_256_6bit;
//	[IW2_256] = gr7;
//			   gr7 = 12;			
//	delayed return;
//		[IDefaultShiftR2_256] = gr7;		
//		nul;
//	
//	<Set7Bit>
//			  gr7=IW1_256_7bit;
//	[IW1_256]=gr7;
//			  gr7=IW2_256_7bit;
//	[IW2_256]=gr7;
//			  gr7=14;
//	delayed return;
//		[IDefaultShiftR2_256]=gr7;		
//		nul;
//.wait;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Inverse FFT-256 procedure                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


<_FFT_Inv256>
.branch;
//pswr set 30000h;
//t1=0;
	ar5=sp-2	 with gr7=false;
	push ar0,gr0 with gr7++;			// gr7=1 (CONST)
	push ar1,gr1;
	push ar2,gr2 with gr2=gr7<<10;		// gr2=256*2*2
	push ar3,gr3 with gr3=gr7<<31;		// gr3=80000000h;(CONST)				
	push ar4,gr4; 
	push ar5,gr5;
	push ar6,gr6 with gr6=gr7<<5;		// gr6=16*2
	ar6=[--ar5];						// GSrcBuffer[256*2]
	ar0=[--ar5];						// GDstBuffer[256*2]
	gr5=[--ar5];						// LBuffer[256*3]
	gr7=[--ar5];						// GBuffer[256*3]
	gr1=[--ar5];						// ShiftR1
	gr0=[--ar5];						// ShiftR2

	//////////////////////////////////////////////////////////////
	// Carried out part of First radix-16 FFT 
	// Loading first 16 longs of GSrcBuffer into WBUF 
	// INPUT:
	// gr3=80000000h 
	// ar6=[Param.GSrcBuffer]
	// 
	gr4=ar6;
	nb1=gr3;
	sb=02020202h;
	rep 16 wfifo=[ar6++gr6],ftw;		// GSrcBuffer
	//-------------------------------------------------------
	[Param.GSrcBuffer]=gr4;					// GSrcBuffer
	[Param.GDstBuffer]=ar0;					// GDstBuffer
	[Param.LBuffer1]  =gr5 with gr5+=gr2;	// LBuffer1
	[Param.LBuffer2]  =gr5;					// LBuffer2
	[Param.GBuffer1]  =gr7 with gr7+=gr2;	// GBuffer1
	[Param.GBuffer2]  =gr7 with gr7=false;	// GBuffer2
	[Param.ShiftR1]   =gr1 with gr7++;		// ShiftR1
	[Param.ShiftR2]   =gr0					// ShiftR2
	//-------------------------------------------------------
	////////////////////////////////////////////////////////////////////////////////////////
	// Default parameters intialization depending from 6 or 7 bit accuracy
		with gr0++;						// (gr0+1)=0 if ShiftR is stated as default
	if <>0 delayed skip 6;
		ar0=TableOfRounders with gr0--;
	gr0=[IDefaultShiftR2_256];					// Variable Is Changed by FFT_Fwd256Set to 14(for 7 bit) or 12(for 6bit)
	[Param.ShiftR2]=gr0;
	
	ar1=ar0 with gr1<<=1;
	ar1,gr1=[ar1+=gr1] with gr0<<=1;
	ar0,gr0=[ar0+=gr0];
	[Rounder1]=ar1,gr1;
	[Rounder2]=ar0,gr0	with gr2=gr7<<1;	// gr2=2(CONST)

	//////////////////////////////////////////////////////////////
	//        First radix-16 FFT 
	//-------------------------------------- 
	// gr2 = 2
	// gr3 = 80000000h
	// gr6 = 32 (16*2) Displacement for loading into wfifo in sequence:
	//						[X00,X16,X32,X48,X64,X80,X96,X112][X128,X144,X160...X240]
	//	in repeat(1)		[X01,X17,X33.................X113][X129,X145,.......X241]
	//						.....................................................
	//	in repeat(16)		[X15,X31,....................X127][X143,X159,.......X255]
	// sb=2,gr3=nb=80000000h
	// WBUF =[X00,X16,X32,X48,X64,X80,X96,X112]
	// WFIFO=[X128,X144,X160..............X240]
	
	//*************** =>   ************************
	//* GSrcBuffer  * =>   * GBuffer1  *          *
	//*************** =>   ************************
	
	ar1=[IW1_256]; 		
	ar5=[Param.GBuffer1] with gr4+=gr2;				// SS
	ar6=gr4 with gr4+=gr2;
	wtw;
.repeat 15;
	rep 32 data=[ar1++],ftw with vsum ,data,0;		// [L]	IW1_256
	wtw;
	rep 16 wfifo=[ar6++gr6];						// [G]	GSrcBuffer
	rep 32 data=[ar1++],ftw with vsum ,data,afifo;	// [L]	LCosSin Table
	wtw;
	ar6=gr4 with gr4+=gr2;
	rep 32 [ar5++]=afifo;							// [G]	GBuffer
.endrepeat;

	rep 32 data=[ar1++],ftw with vsum ,data,0;		// [L]	IW1_256
	ar6=GAddCmplxMask;
	wtw;
	sb=gr2;
	rep 2 wfifo=[ar6++];							// [G]	[1|0][0|-1] => wfifo
	rep 32 data=[ar1++],ftw with vsum ,data,afifo;	// [L]	IW1_256
	rep 32 [ar5++]=afifo;							// [G]	GBuffer	

	//////////////////////////////////////////////////////////////////////////
	// Summation [re*im+im*re | re*re - im*im]
	// gr2=2
	// gr3 = 80000000h
	// WBUF =  [ 0,-1]
	//		   [ 1, 0]
	// sb=2,gr3=nb=80000000h

	// ************************ => ***************   
	// * GBuffer1  *          * => * LBuffer2    *   
	// ************************ => *************** 
	
	ar6=[Param.GBuffer1]							// SS GBuffer.Real
		with gr4=gr7<<2;							// gr4=4							
	ar0=[Param.LBuffer2]							// S
		with gr6=gr7<<1;							// gr6=2
	nul;
	ar4=ar6+gr6										// GBuffer.Imag
		with gr6=gr4;								// gr4=4			
	vr=[Rounder1]
		with gr1=gr7<<5;							// gr1=16*2 (for 2-nd FFT16) 
	wtw;
	//-------------------------
.repeat 7;
	rep 32 data=[ar4++gr4] with vsum ,data,vr;		// [G]	GBuffer (Im)
	rep 32 data=[ar6++gr6] with data+afifo;			// [G]	GBuffer (Re)
	rep 32 [ar0++]=afifo;							// [L]	LSummBuffer
.endrepeat;
	rep 32 data=[ar4++gr4] with vsum ,data,vr;		// [G]	GBuffer (Im)
	rep 32 data=[ar6++gr6] with data+afifo;			// [G]	GBuffer (Re)
	rep 32 [ar0++]=afifo;							// [L]	LSummBuffer
	//////////////////////////////////////////////////////////////
	// Intermediate normalization
	// LBuffer2 is scaled down by factor of ShiftR1
	
	ar0=[Param.LBuffer2] with gr6=gr7;
	ar6=[Param.GBuffer1];
	gr5=[Param.ShiftR1];
	gr0=ar6;
	VEC_ARSH32_aaCG(ar0,ar6,256*2,gr5);
	
	
	///////////////////////////////////////////////////////////// 
	//  Second radix-16 FFT 
	//  gr0=GBuffer1
	//  gr1=32
	//  gr2=2
	//  gr3=80000000
	//  WBUF[8] =[LSummBuffer[0][16][32]..[112]]
	//  WFIFO[8]=[LSummBuffer[128]........[240]]

	//*************** =>   ************************
	//* GBuffer1    * =>   * GBuffer2  *          *
	//*************** =>   ************************
	sb =02020202h with gr7=gr6;	
	nb1=gr3 ;
	ar1=gr0	;
	rep 16 wfifo=[ar1++gr1],ftw;					// [L]	GBuffer1
	
	ar2=[Param.GBuffer2] with gr0+=gr2;				//Dst
	ar5=[IW2_256];			 
	

	wtw;
	ar1=gr0	with gr0+=gr2;
.repeat 15;
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// [G]	IW2_256
	wtw;
	rep 16 wfifo=[ar1++gr1];						// [L]	LSummBuffer
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;	// [G]	IW2_256
	wtw;
	ar1=gr0 with gr0+=gr2;
	rep 32 [ar2++]=afifo;							// [L]	LBuffer
.endrepeat;
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// [G]	IW2_256
	ar1=LAddCmplxMask;
	wtw;
	sb=gr2;
	rep 2  wfifo=[ar1++];							// [L]	LAddCmplxMask
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;	// [G]	IW2_256
	rep 32 [ar2++]=afifo;							// [L]	LBuffer


	////////////////////////////////////////////////////////////////////
	// Summation [re*im+im*re | re*re - im*im] 
	// gr2=2
	// gr3=80000000h
	// gr7=1
	// WBUF =  [ 0,-1]
	//		   [ 1, 0]
	// sb=2,gr3=nb=80000000h
	//
	// ************************ => ***************   
	// * GBuffer2  *          * => * LBuffer1    *   
	// ************************ => *************** 
	
	ar0=[Param.GBuffer2]	with gr1=gr7<<2;		// gr1=4
	gr5=[Param.LBuffer1]	with gr0=gr7<<1;		// gr0=2
	vr =[Rounder2]			with gr6=gr7<<5;		// gr6=16*2
	nul;
	ar1=ar0+gr0				with gr0=gr1;			// gr0=4
	
	wtw;	
.repeat 16;
	rep 16 data=[ar1++gr1] with vsum ,data,vr;		// [L]	LBuffer
	ar6=gr5 with gr5+=gr2;
	rep 16 data=[ar0++gr0] with data + afifo;				// [L]	LBuffer
	rep 16 [ar6++gr6]=afifo ;						// [G]	GDstBuffer
.endrepeat;
	//////////////////////////////////////////////////////////////
	// Final normalization
	//
	ar0=[Param.LBuffer1];
	ar6=[Param.GDstBuffer];
	gr5=[Param.ShiftR2];
	VEC_ARSH32_aaCG(ar0,ar6,256*2,gr5);

	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	//gr7=t1;
return;
.wait;


end ".text_fft";

