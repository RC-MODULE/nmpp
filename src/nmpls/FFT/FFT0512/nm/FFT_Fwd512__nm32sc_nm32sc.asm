//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT512.asm                                          */
//*   Contents:         Routine for forward FFT 512 of complex array        */
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
    //! \fn int FFT_Fwd512(nm32sc* GSrcBuffer, nm32sc* GDstBuffer, void*	LBuffer, void*	GBuffer, int ShiftR=-1)
	//!
	//! \perfinclude _FFT_Fwd512__F6nm32scP6nm32scPPvPvi.html
    //--------------------------------------------------------------------

global _FFT_Fwd512	:label;

//extern W1_512_7bit	:long;
//extern W2_512_7bit	:long;
//extern W1_512_6bit	:long;
//extern W2_512_6bit	:long;

//import from regs;
//import from vecmacro;
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
	
	// Next 3 variables may be modified by FFT_Fwd512Set for switch FFT_Fwd512 from 7bit accuracy to 6 bit and vice versa 
global	W1_512:word;//=W1_512_7bit;
global	W2_512:word;//=W2_512_7bit;
global	DefaultShiftR_512:word=14;		
	Rounder:long;

	struct SParam
		GSrcBuffer	:word;
		GDstBuffer	:word;
		LBuffer1	:word;
		GBuffer1	:word;
		ShiftR		:word;

		LBuffer2	:word;
		GBuffer2	:word;
	end SParam;
	.align; Param :SParam;
	LAddCmplxMask:long[2]=(
			0000000100000000hl,
			00000000FFFFFFFFhl
			);
end ".data_fft_L";
	
data ".data_fft_G"
end ".data_fft_G";

begin ".text_fft"

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Forward FFT-512 procedure                                          //                                                                       
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

<_FFT_Fwd512>
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
	[Param.GSrcBuffer]=gr0;				// GDstBuffer
	gr0=[--ar5];
	[Param.GDstBuffer]=gr0;				// GSrcBuffer
	gr0=[--ar5]	with gr1=gr7<<10;		// gr1=512*2
	[Param.LBuffer1]=gr0 with gr0+=gr1;	// LBuffer1
	[Param.LBuffer2]=gr0;				// LBuffer2
	gr0=[--ar5];
	[Param.GBuffer1]=gr0 with gr0+=gr1;
	[Param.GBuffer2]=gr0;
	gr0=[--ar5];
	[Param.ShiftR]=gr0
	
	////////////////////////////////////////////////////////////////////////////////////////
	// Default parameters intialization depending from 6 or 7 bit accuracy
		with gr0++;						// (gr0+1)=0 if ShiftR is stated as default
	
	if <>0 delayed skip 6;
		ar0=TableOfRounders with gr0--;
	gr0=[DefaultShiftR_512];				// Variable Is Changed by FFT_Fwd256Set to 14(for 7 bit) or 12(for 6bit)
	[Param.ShiftR]=gr0;
	gr0<<=1;
	ar0,gr0=[ar0+=gr0];
	[Rounder]=ar0,gr0;
	
	////////////////////////////////////////////////////////////////////
	//        First radix-2 FFT 
	//-----------------------------------------------------------------
	// INPUT:
	// GENERAL REGISTRES ON INPUT:
	// gr4=80000000h;
	// gr7=1
	//----------------------
	// Transforms input array X[i] to array S[j]
	//			,where i=0..511 (X[i]=[X[i].imag|X[i].real]), 
	//			,where j=0..1023 (S[i]=[S[i].imag|S[i].real]), 
	// array X begins from address GSrcBuffer
	// array S begins from address LBuffer1
	// array S consists two subarray S[0],...,S[511],S[512]=conjg(S[0]),...,S[1023]=conjg(S[511])
	// conjg() - complex conjugation function 
	//*************** =>   *************
	//* GSrcBuffer  * =>   * LBuffer1  *
	//*************** =>   *************

	ar5=[Param.GSrcBuffer];		// &X[0..255]		(IN)
	ar4=ar5; ar4+=256*2;		// &X[256..511]		(IN)
	ar6=ar4;					// &X[256..511]		(IN)

	ar2=[Param.LBuffer1];		// &S[0..255]		(OUT)
	ar3=ar2; ar3+=256*2;			// &S[512..768]		(OUT)

	nb1=gr4;
	wtw;
	
.repeat 8;
	rep 32 ram=[ar5++];							// X[0..255]  
	rep 32 data=[ar4++] with ram+data;			// S[0..255]=X[0..255]+X[256..511]
	//rep 32 [ar0++]=afifo with vsum ,afifo,0;	// S[512..767]=Conjg(S[0..255])
	rep 32 [ar2++]=afifo;						
	rep 32 data=[ar6++] with ram-data;			// S[256..511]=X[0..255]-X[256..511] 
	//rep 32 [ar1++]=afifo with vsum ,afifo,0;	// S[768..1023]=Conjg(S[256..511])
	rep 32 [ar3++]=afifo;
.endrepeat;

	//////////////////////////////////////////////////////////////////
	//------- Second radix-16 FFT ----------------
	// Transforms input array     S[i] to array T[j]
	//		,where i=0..511 ,j=0..511
	// At first, at the I stage S[] transforms into intermediate array SS[i],where i=0..1023 (SS[i]=[SS[i].imag|SS[i].real]), 
	// And then, at the II stage , array SS transforms into array T
	//
	// Array T  begin from address 	LBuffer1
	//
	// GENERAL REGISTRES ON INPUT:
	// gr4=80000000h;
	// gr7=1
	//----------------------
	//ar1=ar0;
	//*************** =>   ************************
	//* LBuffer1    * =>   * LBuffer2  *          *
	//*************** =>   ************************

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

	ar5=[W1_512] with gr1=gr7<<9;			// gr1=256*2
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
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW1_512
	//wtw;
	rep 16 wfifo=[ar1++gr1];						// T[256]>>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_512
	//wtw;
	ar4+=2;
	ar1=ar4;
	ar4=ar0;
	rep 32 [ar2++]=afifo;							// YY[0]>>>

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW1_512
	//wtw;
	rep 16 wfifo=[ar0++gr0];						// T[32]>>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_512
	//wtw;
	ar4+=2;
	ar0=ar4;
	ar5=gr5;
	ar4=ar1;
	rep 32 [ar3++]=afifo;							// YY[512]
.endrepeat;
	
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW1_512
	//wtw;
	rep 16 wfifo=[ar1++gr1];						// T[256+16]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_512
	//wtw;
	rep 32 [ar2++]=afifo;							// YY[256-32]

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW1_512
	//wtw;
	ar1=LAddCmplxMask with gr2=gr7<<1;
	sb=gr2;
	rep 2 wfifo=[ar1++];							// [1|0][0|-1] => wfifo
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_512
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
	gr3=gr7<<1;										// gr3=2*2;
	gr4=gr7<<2;										// gr4=2*2;
	gr5=gr7<<2;										// gr5=2*2;
	
.repeat 16;
	rep 16 ram=[ar4++gr4] ;							// YY[0] >>
	rep 16 data=[ar5++gr5] with vsum ,data,ram;   // YY[1] >>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// Y[0] >>
.endrepeat;

	//gr2=[Param.LBuffer1];
	gr2=[Param.GBuffer1];							// &Y[0]
	gr6=256*2;
	gr2+=gr6;
.repeat 16;
	rep 16 ram=[ar4++gr4] ;							// YY[0] >>
	rep 16 data=[ar5++gr5] with vsum ,data,ram;   // YY[1] >>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// Y[0] >>
.endrepeat;
	// ==>GBuffer1

	//////////////////////////////////////////////////////////////////
	//------- The third radix-16  FFT ----------------
	// Transorms input array T[i],where i=0..1023 (S[i]=[S[i].imag|S[i].real]), 
	// at first (at I stage) int0 intermediate array YY[i],where i=0..2047 (YY[i]=[YY[i].imag|YY[i].real]), 
	// and then (at II stage) array YY transforms into result array Y
	// Y[i],where i=0..1023 (Y[i]=[Y[i].imag|Y[i].real]), 
	// array T  begin from address LBuffer1
	// array YY begin from address  LBuffer2
	// array Y  begin from address	GDstBuffer
	// Table of cos sin coeff GW2_1024=exp(-2*i*pi*k*i/1024) begin from GW1_1024
	//
	// GENERAL REGISTRES ON INPUT:
	// gr4=80000000h;
	// gr7=1
	// ar0=[Param.LBuffer1]+32;				// &T[32]
	// ar1=[Param.LBuffer1]					// &T[0]
	//----------------------
	//*************** =>   ************************
	//* GBuffer1    * =>   * GBuffer2  *          *
	//*************** =>   ************************
	//ar1=ar0;
	sb=02020202h;
	gr4=gr7<<31;							// gr4=80000000h;(CONST)
	ar0=[Param.GBuffer1];							// &T[0]
	//ar0=[Param.LBuffer1];							// &T[0]
	ar1=ar0;
	rep 16 wfifo=[ar0++],ftw;							// T[0]>>>
	ar5=[W2_512]	with gr1=gr7<<9;			// gr1=256*2
	ar2=[Param.GBuffer2]					// &YY[0]
		with gr3=gr7<<10;					// gr3=512*2
	ar3=ar2;	
	ar1+=gr1;								// &T[256] 
	ar3+=gr3;								// &YY[512]

	wtw;
	//----------- I stage -------------------
.repeat 15;
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// LW2_512
	//wtw;
	rep 16 wfifo=[ar1++];							// T[256]>>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // LW2_512
	//wtw;
	rep 32 [ar2++]=afifo;							// YY[0]>>>

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// LW2_512
	//wtw;
	rep 16 wfifo=[ar0++];							// T[32]>>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // LW2_512
	//wtw;
	rep 32 [ar3++]=afifo;							// YY[512]
.endrepeat;

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// LW2_512
	//wtw;
	rep 16 wfifo=[ar1++];							// T[256+16]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // LW2_512
	//wtw;
	rep 32 [ar2++]=afifo;							// YY[256-32]

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// LW2_512
	//wtw;
	ar1=LAddCmplxMask with gr2=gr7<<1;
	sb=gr2;
	rep 2 wfifo=[ar1++];							// [1|0][0|-1] => wfifo
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // LW2_512
	rep 32 [ar3++]=afifo;							// YY[992]

	///////////////////////////////////////////////////////////////
	//------------ II second -------------------------------
	//    Summation [re*im+im*re | re*re - im*im] 
	// GENERAL REGISTRES ON INPUT:
	// gr2=2
	// gr3 = 80000000h
	// WBUF =	[ 0,-1]
	//			[ 1, 0]
	// sb=2,gr3=nb=80000000h
	//************************ =>   ***************
	//* GBuffer2  *          * =>   * LBuffer1    *
	//************************ =>   ***************
	wtw;
	//-------------------------
	ar4=[Param.GBuffer2]							// &YY[0]
		with gr5=gr7<<1;							// gr5=1*2
	gr2=[Param.LBuffer1];							// &Y[0]
	ar5=ar4;										
	ar5+=gr5 with									// &YY[1]
		gr0=gr7<<6;									// gr0=32*2;
	gr3=gr7<<2;										// gr3=2*2;
	gr4=gr7<<2;										// gr4=2*2;
	vr =[Rounder] with gr5=gr7<<2;										// gr5=2*2;
	
.repeat 16;
	rep 16 data=[ar5++gr5] with vsum ,data,vr;		// YY[1] >>
	rep 16 data=[ar4++gr4] with data + afifo;		// YY[0] >>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// Y[0] >>
.endrepeat;

	ar4=[Param.GBuffer2] with gr4=gr7<<10;							
	nul;
	ar4+=gr4										// &YY[512]
		with gr6=gr7<<1;							// gr6=1*2
	ar6=ar4 
		with gr4=gr7<<2;							// gr4=2*2 
	ar5=ar6+gr6;									// &YY[1025]
	

	gr2=[Param.LBuffer1];
	gr2+=gr6;					// &Y[1]
.repeat 16;
	rep 16 data=[ar5++gr5] with vsum ,data,vr;	// &YY[1025]>>>
	rep 16 data=[ar4++gr4] with data + afifo;	// &YY[1024]>>>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;					// &Y[1] >>>
.endrepeat;

	ar0=[Param.LBuffer1];
	ar6=[Param.GDstBuffer];
	gr0=[Param.ShiftR];
	VEC_ARSH32_aaCG(ar0,ar6,512*2,gr0);

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