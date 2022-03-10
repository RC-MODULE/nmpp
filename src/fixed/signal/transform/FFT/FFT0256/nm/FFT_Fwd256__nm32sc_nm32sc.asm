//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT256.asm                                          */
//*   Contents:         Routine for forward FFT 256 of complex array        */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Version           1.2                                                 */
//*   Start date:       03.07.2000                                          */
//*   Release  $Date: 2005/02/10 11:47:59 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/

    //--------------------------------------------------------------------
    //! \fn int FFT_Fwd256(nm32sc*	GSrcBuffer, nm32sc*	LDstBuffer, void*	LBuffer, void*	GBuffer, int ShiftR=-1)
	//!
	//! \perfinclude _FFT_Fwd256__F6nm32scP6nm32scPPvPvi.html
    //--------------------------------------------------------------------

//global _FFT_Fwd256Set	:label;
global _FFT_Fwd256	:label;

//extern W1_256_7bit	:long;
//extern W2_256_7bit	:long;

//import from regs;
//import from vecmacro;

import from rtmacro;
import from macros.mlb;


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
	global W1_256:word;//=W1_256_7bit;
	global W2_256:word;//=W2_256_7bit;
	global DefaultShiftR_256:word=14;		
	Rounder:long;
	//---------------------------------------------
	struct SParam
		GSrcBuffer:word;
		LDstBuffer:word;
		LBuffer1  :word;
		GBuffer1  :word;
		ShiftR    :word;
		//-------------
		LBuffer2  :word;
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
		00000000FFFFFFFFhl);
end ".data_fft_G";
begin ".text_fft"


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Forward FFT-256 procedure                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

<_FFT_Fwd256>
.branch;
	//pswr set 30000h;
	//t1=0;
	ar5=sp-2	 with gr7=false;
	push ar0,gr0 with gr7++;			// gr7=1 (CONST)
	push ar1,gr1 with gr1=gr7<<9;		// gr1=256*2;		
	push ar2,gr2 with gr2=gr7<<1;		// gr2=2(CONST)
	push ar3,gr3 with gr3=gr7<<31;		// gr3=80000000h;(CONST)				
	push ar4,gr4; 
	push ar5,gr5;
	push ar6,gr6 with gr6=gr7<<5;		// gr6=16*2
	ar6=[--ar5];						// GSrcBuffer[256*2]
	ar0=[--ar5];						// GDstBuffer[256*2]
	gr5=[--ar5];						// LBuffer[256*3]
	ar2=[--ar5];						// GBuffer[256*2]
	gr0=[--ar5];						// ShiftR
	//////////////////////////////////////////////////////////////
	// Carried out part of First radix-16 FFT 
	// Loading first 16 longs of GSrcBuffer into WBUF 
	// INPUT:
	// gr3=80000000h 
	// ar6=[Param.GSrcBuffer]
	// 
	nb1=gr3;
	gr4=ar6;				
	sb =02020202h;
	rep 16 wfifo=[ar6++gr6],ftw;			// GSrcBuffer
	//--------------------------------------------------------
	[Param.GSrcBuffer]= gr4;				// GSrcBuffer[256*2]
	[Param.LDstBuffer]= ar0;				// GDstBuffer[256*2]
	[Param.LBuffer1]  = gr5 with gr5+=gr1;	// LBuffer1[256*2]
	[Param.LBuffer2]  = gr5;				// LBuffer2[256*2*2]
	[Param.GBuffer1]  = ar2;				// GBuffer1[256*2]
	[Param.ShiftR]    = gr0					// ShiftR

	////////////////////////////////////////////////////////////////////////////////////////
	// Default parameters intialization depending from 6 or 7 bit set accuracy
	// INPUT:
	// gr0=ShiftR
		with gr0++;						// (gr0+1)=0 if ShiftR is stated as default
	if <>0 delayed skip 6;
		ar0=TableOfRounders with gr0--;
	gr0=[DefaultShiftR_256];				// Variable [..] Is Changed by FFT_Fwd256Set to 14(for 7 bit) or 12(for 6bit)
	[Param.ShiftR]=gr0 with gr0<<=1;
	
	ar0,gr0=[ar0+=gr0];
	[Rounder]=ar0,gr0;
	
	////////////////////////////////////////////////////////////////////
	//        First radix-16 FFT 
	//-----------------------------------------------------------------
	// INPUT:
	// gr2 = 2
	// gr3 = 80000000h
	// gr4 = [Param.GSrcBuffer]
	// gr6 = (16*2) Displacement for loading into wfifo in sequence:
	//						[X00,X16,X32,X48,X64,X80,X96,X112][X128,X144,X160...X240]
	//	in repeat(1)		[X01,X17,X33.................X113][X129,X145,.......X241]
	//						.....................................................
	//	in repeat(16)		[X15,X31,....................X127][X143,X159,.......X255]
	// sb=2,
	// WBUF =[X00,X16,X32,X48,X64,X80,X96,X112]
	// WFIFO=[X128,X144,X160..............X240]
	//*************** =>   ************************
	//* GSrcBuffer  * =>   * GBuffer1  *          *
	//*************** =>   ************************
	gr4=[Param.GSrcBuffer];
	ar1=[W1_256];	
	ar5=[Param.GBuffer1] with gr4+=gr2;
	ar6=gr4 with gr4+=gr2;
	wtw;
.repeat 15;
	rep 32 data=[ar1++],ftw,wtw with vsum ,data,0;		// [L]	W1_256
	rep 16 wfifo=[ar6++gr6];						// [G]	GSrcBuffer
	rep 32 data=[ar1++],ftw,wtw with vsum ,data,afifo;	// [L]	LCosSin Table
	ar6=gr4 with gr4+=gr2;
	rep 32 [ar5++]=afifo;							// [G]	GBuffer
.endrepeat;

	rep 32 data=[ar1++],ftw,wtw with vsum ,data,0;		// [L]	W1_256
	ar6=GAddCmplxMask;
	sb=gr2;
	rep 2 wfifo=[ar6++];							// [G]	[1|0][0|-1] => wfifo
	rep 32 data=[ar1++],ftw with vsum ,data,afifo;	// [L]	W1_256
	rep 32 [ar5++]=afifo,wtw;						// [G]	GBuffer	

	
	////////////////////////////////////////////////////////////////////////////
	//  First Summation [re*im+im*re | re*re - im*im] 
	//-----------------------------------------------------------------
	// gr2=2
	// gr3 = 80000000h
	// WBUF =  [ 0,-1]
	//		   [ 1, 0]
	// sb=2
	// ************************ => ***************   
	// * GBuffer1  *          * => * LBuffer1    *   
	// ************************ => *************** 


	ar6=[Param.GBuffer1]							// GBuffer.Real
		with gr4=gr7<<2;							// gr4=4							
	ar0=[Param.LBuffer1] 
		with gr6=gr7<<1;							// gr6=2
	ar1=ar0	with gr1=gr7<<5;						// gr1=16*2 (prepearing for 2-nd FFT16) 
	gr0=ar0;										// Push ar0=>gr0 (prepearing for 2-nd FFT16 )
	ar4=ar6+gr6										// GBuffer.Imag
		with gr6=gr4;								// gr4=4			
	//wtw;
	//-------------------------
.repeat 7;
	rep 32 ram =[ar6++gr6];							// [G]	GBuffer1 (Re)
	rep 32 data=[ar4++gr4] with vsum ,data,ram;		// [G]	GBuffer1 (Im)
	rep 32 [ar0++]=afifo;							// [L]	LBuffer1
.endrepeat;
	rep 32 ram=[ar6++gr6];							// [G]	GBuffer1 (Re)
	sb =02020202h ;	
	rep 32 data=[ar4++gr4] with vsum ,data,ram;		// [G]	GBuffer1 (Im)
	rep 14 wfifo=[ar1++gr1],ftw;					// [L]	LBuffer1
	rep 32 [ar0++]=afifo;							// [L]	LBuffer1

	///.wait;
	rep 2 wfifo=[ar1++gr1];							// [L]	LBuffer1
	///.branch;
	
	////////////////////////////////////////////////////////////////////
	// Second radix-16 FFT
	//-----------------------------------------------------------------
	//	GENERAL REGISTERS ON INPUT:
	//  gr0=LSummBuffer
	//  gr1=32
	//  gr2=2
	//  gr3=nb1=80000000
	//  sb=02020202
	//  WBUF[8] =[LSummBuffer[0][16][32]..[112]]
	//  WFIFO[8]=[LSummBuffer[128]........[240]]
	//*************** =>   ************************
	//* LBuffer1    * =>   * LBuffer2  *          *
	//*************** =>   ************************

	ar2=[Param.LBuffer2] with gr0+=gr2;					//Dst
	ar5=[W2_256];			 
	

	wtw;
	ar1=gr0	with gr0+=gr2;
	
	//vr =[Rounder];
.repeat 15;
	rep 32 data =[ar5++],ftw,wtw with vsum ,data,0;			// [G]	W2_256
	///wtw;
	rep 16 wfifo=[ar1++gr1];							// [L]	LBuffer1
	rep 32 data =[ar5++],ftw,wtw with vsum ,data,afifo;		// [G]	GWkn_256
	///wtw;
	ar1=gr0 with gr0+=gr2;
	rep 32 [ar2++]=afifo;								// [L]	LBuffer2
.endrepeat;
	rep 32 data =[ar5++],ftw,wtw with vsum ,data,0;			// [G]	W2_256
	ar1=LAddCmplxMask;
	///wtw;
	sb=gr2;
	rep 2  wfifo=[ar1++];								// [L]	LAddCmplxMask
	rep 32 data =[ar5++],ftw with vsum ,data,afifo;		// [G]	W2_256
	rep 32 [ar2++]=afifo;								// [L]	LBuffer2


	///////////////////////////////////////////////////////////
	// Second summation [re*im+im*re | re*re - im*im] 
	//----------------------------------------------------------
	// ON INPUT:
	// gr2=2
	// gr3 = 80000000h
	// WBUF =  [ 0,-1]
	//		   [ 1, 0]
	// sb=2,gr3=nb=80000000h
	// ************************ => ***************   
	// * LBuffer2  *          * => * GBuffer1    *   
	// ************************ => *************** 

	ar0=[Param.LBuffer2]	with gr1=gr7<<2;		// gr1=4
	gr5=[Param.GBuffer1]	with gr0=gr7<<1;		// gr0=2
	vr =[Rounder]			with gr6=gr7<<5;		// gr6=16*2
	nul;
	ar1=ar0+gr0				with gr0=gr1;			// gr0=4
	wtw;	
.repeat 16;
	rep 16 data =[ar1++gr1] with vsum ,data,vr;		// [L]	LBuffer
	ar6=gr5 with gr5+=gr2;
	rep 16 data =[ar0++gr0] with data+afifo;		// [L]	LBuffer
	rep 16 [ar6++gr6]=afifo;						// [G]	GDstBuffer
	//rep 16 ram =[ar0++gr0] ;		// [L]	LBuffer
	//ar6=gr5 with gr5+=gr2;
	//rep 16 data =[ar1++gr1] with vsum ,data,ram;		// [L]	LBuffer
	//rep 16 [ar6++gr6]=afifo;						// [G]	GDstBuffer
.endrepeat;

	///////////////////////////////////////////////////////////
	// Right Shift Normalization
	//----------------------------------------------------------
	// ON INPUT:
	//
	// ************ => ***************   
	// * GBuffer1 * => * LDstGBuffer *   
	// ************ => *************** 

	ar0=[Param.GBuffer1];
	gr5=[Param.ShiftR];
	ar6=[Param.LDstBuffer];
	VEC_ARSH32_aaCG(ar0,ar6,256*2,gr5);
	
	////////////
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return with gr7=false;
.wait;


end ".text_fft";