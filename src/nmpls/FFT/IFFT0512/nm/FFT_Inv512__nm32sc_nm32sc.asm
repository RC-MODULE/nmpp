//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             iFFT512.asm                                         */
//*   Contents:         Routine for inverse iFFT 512 of complex array       */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Version           1.2                                                 */
//*   Start date:       03.07.2000                                          */
//*   Release   $Date: 2005/02/10 11:47:59 $*/
//*                                                                         */
//*                                                                         */
//***************************************************************************/
    //--------------------------------------------------------------------
    //! \fn int FFT_Inv512(nm32sc* GSrcBuffer, nm32sc* LDstBuffer, void*	LBuffer, void*	GBuffer, int ShiftR1=9, int ShiftR2=-1)
	//!
	//! \perfinclude _FFT_Inv512__F6nm32scP6nm32scPPvPvii.html
    //--------------------------------------------------------------------

//global _FFT_Inv512Set:label;
global _FFT_Inv512	:label;

//extern IW1_512_7bit	:long;
//extern IW2_512_7bit	:long;
//extern IW1_512_6bit	:long;
//extern IW2_512_6bit	:long;

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

	// Next 3 variables may be modified by FFT_Inv512Set for switch FFT_Inv512 from 7bit accuracy to 6 bit and vice versa 
global 	IW1_512:word;//=IW1_512_7bit;
global	IW2_512:word;//=IW2_512_7bit;
global 	IDefaultShiftR2_512:word=14;		
	Rounder1:long;
	Rounder2:long;
	
	struct SParam
		GDstBuffer:word;
		GSrcBuffer:word;
		LBuffer1:word;
		GBuffer1:word;
		ShiftR1:word;
		ShiftR2:word;

		LBuffer2:word;
		GBuffer2:word;

		LDstBuffer:word;
		//GBuffer2:word;
		LBuffer:word;
	end SParam;
	.align; Param :SParam;
	LAddCmplxMask:long[2]=(
			0000000100000000hl,
			00000000FFFFFFFFhl
			);
	CRC:word;
end ".data_fft_L";
	
data ".data_fft_G"
end ".data_fft_G";


begin ".text_fft"
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  This routine  switches function FFT_Inv512 from 7bit accuracy to         //
//    6 bit accuracy and vice versa  (for more information see "nmfft.h")   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//<_FFT_Inv512Set>
//.branch;
//	ar5=sp-2;
//	gr7=[--ar5];	//gr7=1 for using 7bit accuracy, otherwise FFT_Inv512 will be switched to 6bit accuracy 
//	with gr7--;
//	if =0 delayed goto Set7Bit;
//			   gr7 = IW1_512_6bit;
//	[IW1_512] = gr7;
//			   gr7 = IW2_512_6bit;
//	[IW2_512] = gr7;
//			   gr7 = 12;			
//	delayed return;
//		[IDefaultShiftR2_512] = gr7;		
//		nul;
//	
//	<Set7Bit>
//			  gr7=IW1_512_7bit;
//	[IW1_512]=gr7;
//			  gr7=IW2_512_7bit;
//	[IW2_512]=gr7;
//	gr7=14;
//	delayed return;
//		[IDefaultShiftR2_512]=gr7;		
//		nul;
//.wait;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Inverse FFT-512 procedure                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

<_FFT_Inv512>
.branch;
//pswr set 30000h;
//t1=0;
	ar5=sp-2 with gr7=false;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2; 
	push ar3,gr3 with gr7++;		// gr7=1 (CONST)
	push ar4,gr4 with gr4=gr7<<31;  // gr4=80000000h;(CONST)
	push ar5,gr5;
	push ar6,gr6 ; 
	//-------------------------------------------------------
 
	gr0=[--ar5];
	[Param.GSrcBuffer]=gr0;				// GDstBuffer[512*2]
	gr0=[--ar5];
	[Param.LDstBuffer]=gr0;				// GSrcBuffer[512*2]
	gr0=[--ar5]	with gr1=gr7<<10;		// gr1=512*2
	[Param.LBuffer1]=gr0 with gr0+=gr1;	// LBuffer1[512*2]
	[Param.LBuffer2]=gr0;				// LBuffer2[512*2]
	gr0=[--ar5];
	[Param.GBuffer1]=gr0 with gr0+=gr1;
	[Param.GBuffer2]=gr0;
	gr1=[--ar5];
	[Param.ShiftR1]=gr1;
	gr0=[--ar5];
	[Param.ShiftR2]=gr0

	////////////////////////////////////////////////////////////////////////////////////////
	// Default parameters intialization depending from 6 or 7 bit accuracy
		with gr0++;						// (gr0+1)=0 if ShiftR is stated as default
	
	if <>0 delayed skip 6;
		ar0=TableOfRounders with gr0--;
	gr0=[IDefaultShiftR2_512];				// Variable Is Changed by FFT_Fwd512Set to 14(for 7 bit) or 12(for 6bit)
	[Param.ShiftR2]=gr0;
	
	ar1=ar0 with gr0<<=1;
	ar0,gr0=[ar0+=gr0] with gr1<<=1;
	ar1,gr1=[ar1+=gr1];
	[Rounder1]=ar1,gr1;
	[Rounder2]=ar0,gr0;


	//////////////////////////////////////////////////////////////
	//	First radix-2 FFT
	//--------------------------------------
	// transforms input array X[i] в array S[j]
	//			,where i=0..511 (X[i]=[X[i].imag|X[i].real]), 
	//			,where j=0..1023 (S[i]=[S[i].imag|S[i].real]), 
	// array X begins from address GSrcBuffer
	// array S begins from address LBuffer1
	// array S consists two subarray S[0],...,S[511],S[512]=conjg(S[0]),...,S[1023]=conjg(S[511])
	// conjg() - complex conjugation function 
	//GENERAL REGISTERS ON INPUT
	// gr4=80000000h;
	// gr7=1
	//----------------------
	ar5=[Param.GSrcBuffer];		// &X[0..255]		(IN)
	ar4=ar5; ar4+=256*2;		// &X[256..511]		(IN)
	ar6=ar4;					// &X[256..511]		(IN)

	ar2=[Param.LBuffer1];		// &S[0..255]		(OUT)
	ar3=ar2; ar3+=256*2;		// &S[512..768]		(OUT)

	//ar1=ar0; ar1+=256*2;		// &S[256..511]		(OUT)
	//ar3=ar2; ar3+=256*2;		// &S[768..1023]	(OUT)
	//*************** =>   *************
	//* GSrcBuffer  * =>   * LBuffer1  *
	//*************** =>   *************
	nb1=gr4;
	wtw;
	.repeat 8;
		rep 32 ram=[ar5++];							// X[0..255]  
		rep 32 data=[ar4++] with ram+data;			// S[0..255]=X[0..255]+X[256..511]
		
		rep 32 [ar2++]=afifo;						
		rep 32 data=[ar6++] with ram-data;			// S[256..511]=X[0..255]-X[256..511] 
		
		rep 32 [ar3++]=afifo;
	.endrepeat;


	//////////////////////////////////////////////////////////////////
	//------- Second radix-16 FFT ----------------
	// transforms input array S[i] into array T[j] by 2 stagees
	//		,where i=0..511 ,j=0..511
	// at I stageе into intermediate array SS[i],where i=0..1023 (SS[i]=[SS[i].imag|SS[i].real]), 
	// and then at II stageе array SS is transformed into array T
	// array T  begin from address	LBuffer1
	//------GENERAL REGISTERS ON INPUT-----
	// gr4=80000000h;
	// gr7=1
	//---------------------- 
	//ar1=ar0;
	//*************** =>   ************************
	//* LBuffer1    * =>   * LBuffer2  *          *
	//*************** =>   ************************
gr7=1;
	sb=02020202h;
	gr4=gr7<<31;							// gr4=80000000h;(CONST)
	nb1=gr4;
	ar0=[Param.LBuffer1];					// &S[0]       (IN)
	ar1=ar0;								//             (IN)
	gr0=16*2;
	ar4=ar0;
	rep 16 wfifo=[ar0++gr0],ftw;			// S[0]>>>
	ar4+=2;
	ar0=ar4;

	ar5=[IW1_512] with gr1=gr7<<9;			// gr1=256*2
	ar2=[Param.LBuffer2]					// &SS[0]      (OUT)
		with gr3=gr7<<10;					// gr3=512*2
	ar3=ar2;	
	ar1+=gr1;								// &S[256] 
	ar3+=gr3;								// &SS[512]    (OUT)
	gr1=gr0;
	wtw;
	//----------- I stage -------------------
	gr5=ar5;
	ar4=ar1;
	
.repeat 15;
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// iGW1_512
	wtw;
	rep 16 wfifo=[ar1++gr1];						// T[256]>>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // iGW1_512
	wtw;
	ar4+=2;
	ar1=ar4;
	ar4=ar0;
	rep 32 [ar2++]=afifo;							// YY[0]>>>

	rep 32 data=[ar5++],ftw with vsum ,data,0;		// iGW1_512
	wtw;
	rep 16 wfifo=[ar0++gr0];						// T[32]>>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // iGW1_512
	wtw;
	ar4+=2;
	ar0=ar4;
	ar5=gr5;
	ar4=ar1;
	rep 32 [ar3++]=afifo;							// YY[512]
.endrepeat;
	
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// iGW1_512
	wtw;
	rep 16 wfifo=[ar1++gr1];						// T[256+16]
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // iGW1_512
	wtw;
	rep 32 [ar2++]=afifo;							// YY[256-32]

	rep 32 data=[ar5++],ftw with vsum ,data,0;		// iGW1_512
	wtw;
	ar1=LAddCmplxMask with gr2=gr7<<1;
	sb=gr2;
	rep 2 wfifo=[ar1++];							// [1|0][0|-1] => wfifo
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // iGW1_512
	rep 32 [ar3++]=afifo;							// YY[512-32]

	

	//------------ II stage -------------------------------
	//    Summation [re*im+im*re | re*re - im*im] 
	// gr2=2
	// gr3 = 80000000h
	// WBUF =	[ 0,-1]
	//			[ 1, 0]
	// sb=2,gr3=nb=80000000h
	//************************ =>   ***************
	//* LBuffer2  *          * =>   * GBuffer1    *
	//************************ =>   ***************

	wtw;
	//-------------------------
	ar4=[Param.LBuffer2]							// &YY[0]
		with gr5=gr7<<1;							// gr5=1*2
	//gr2=[Param.LBuffer1];//LBuffer1];//GDstBuffer];							// &Y[0]
	gr2=[Param.GBuffer1];							// &Y[0]
	ar5=ar4;										
	ar5+=gr5 with									// &YY[1]
		gr0=gr7<<5;									// gr0=16*2;
	vr=[Rounder1] with gr3=gr7<<1;					// gr3=2*2;
	gr4=gr7<<2;										// gr4=2*2;
	gr5=gr7<<2;										// gr5=2*2;
	
.repeat 16;
	rep 16 data=[ar5++gr5] with vsum ,data,vr;	   // YY[1] >>
	rep 16 data=[ar4++gr4] with data + afifo;	// YY[0] >>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// Y[0] >>
.endrepeat;

	//gr2=[Param.LBuffer1];
	gr2=[Param.GBuffer1];							// &Y[0]
	
	gr6=256*2;
	gr2+=gr6;
.repeat 16;
	rep 16 data=[ar5++gr5] with vsum ,data,vr;		// YY[1] >>
	rep 16 data=[ar4++gr4] with data + afifo;		// YY[0] >>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// Y[0] >>
.endrepeat;
	

	//////////////////////////////////////////////////////////////
	// Intermediate normalization
	//

	ar2=[Param.GBuffer1];
	ar6=[Param.LBuffer1];
	gr5=[Param.ShiftR1] with gr0=gr7;
	VEC_ARSH32_aaCG(ar2,ar6,512*2,gr5);
	gr7=gr0;
	

	//////////////////////////////////////////////////////////////////
	//------- Third radix-16  FFT ----------------
	//
	//------GENERAL REGISTERS ON INPUT-----
	// gr4=80000000h;
	// gr7=1
	// ar0=[Param.LBuffer1]+32;				// &T[32]
	// ar1=[Param.LBuffer1]					// &T[0]
	//----------------------
	//*************** =>   ************************
	//* LBuffer1    * =>   * LBuffer2  *          *
	//*************** =>   ************************
	//ar1=ar0;
	gr7=1;
	sb=02020202h;
	gr4=gr7<<31;							// gr4=80000000h;(CONST)
	nb1=gr4;
	ar0=[Param.LBuffer1];					// &T[0]
	ar1=ar0;
	rep 16 wfifo=[ar0++],ftw;				// T[0]>>>
	ar5=[IW2_512] with gr1=gr7<<9;			// gr1=256*2
	ar2=[Param.LBuffer2]					// &YY[0]
		with gr3=gr7<<10;					// gr3=512*2
	ar3=ar2;	
	ar1+=gr1;								// &T[256] 
	ar3+=gr3;								// &YY[512]

	wtw;
	//----------- I stage -------------------
.repeat 15;
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// iGW2_512
	wtw;
	rep 16 wfifo=[ar1++];							// T[256]>>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // iGW2_512
	wtw;
	rep 32 [ar2++]=afifo;							// YY[0]>>>

	rep 32 data=[ar5++],ftw with vsum ,data,0;		// iGW2_512
	wtw;
	rep 16 wfifo=[ar0++];							// T[32]>>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // iGW2_512
	wtw;
	rep 32 [ar3++]=afifo;							// YY[512]
.endrepeat;

	rep 32 data=[ar5++],ftw with vsum ,data,0;		// iGW2_512
	wtw;
	rep 16 wfifo=[ar1++];							// T[256+16]
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // iGW2_512
	wtw;
	rep 32 [ar2++]=afifo;							// YY[256-32]

	rep 32 data=[ar5++],ftw with vsum ,data,0;		// iGW2_512
	wtw;
	ar1=LAddCmplxMask with gr2=gr7<<1;
	sb=gr2;
	rep 2 wfifo=[ar1++];							// [1|0][0|-1] => wfifo
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // iGW2_512
	rep 32 [ar3++]=afifo;							// YY[992]
	//------------ II stage -------------------------------
	//    Summation [re*im+im*re | re*re - im*im] 
	// gr2=2
	// gr3 = 80000000h
	// WBUF =	[ 0,-1]
	//			[ 1, 0]
	// sb=2,gr3=nb=80000000h
	//************************ =>   ***************
	//* LBuffer2  *          * =>   * GBuffer1    *
	//************************ =>   ***************
	wtw;
	//-------------------------
	ar4=[Param.LBuffer2]							// &YY[0]
		with gr5=gr7<<1;							// gr5=1*2
	gr2=[Param.GBuffer1];							// &Y[0]
	ar5=ar4;										
	ar5+=gr5 with									// &YY[1]
		gr0=gr7<<6;									// gr0=32*2;
	vr=[Rounder2] with gr3=gr7<<2;					// gr3=2*2;
	gr4=gr7<<2;										// gr4=2*2;
	gr5=gr7<<2;										// gr5=2*2;
	
.repeat 16;
	rep 16 data=[ar5++gr5] with vsum ,data,vr;		// YY[1] >>
	rep 16 data=[ar4++gr4] with data + afifo;		// YY[0] >>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// Y[0] >>
.endrepeat;

	ar4=[Param.LBuffer2] with gr4=gr7<<10;							
	nul;
	ar4+=gr4										// &YY[512]
		with gr6=gr7<<1;							// gr6=1*2
	ar6=ar4 
		with gr4=gr7<<2;							// gr4=2*2 
	ar5=ar6+gr6;									// &YY[1025]
	

	gr2=[Param.GBuffer1];
	gr2+=gr6;										// &Y[1]
.repeat 16;
	rep 16 data=[ar5++gr5] with vsum ,data,vr;		// &YY[1025]>>>
	rep 16 data=[ar4++gr4] with data + afifo;		// &YY[1024]>>>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// &Y[1] >>>
.endrepeat;


	//////////////////////////////////////////////////////////////
	// Final normalization
	//
	ar0=[Param.GBuffer1];
	ar6=[Param.LDstBuffer];
	gr5=[Param.ShiftR2];
	VEC_ARSH32_aaCG(ar0,ar6,512*2,gr5);
	<Finish>

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