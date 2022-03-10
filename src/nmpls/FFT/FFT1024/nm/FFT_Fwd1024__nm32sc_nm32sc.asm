//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT1024.asm                                         */
//*   Contents:         Routine for forward FFT 1024 of complex array       */
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
    //! \fn int FFT_Fwd1024(nm32sc* GSrcBuffer, nm32sc* LDstBuffer, void*	LBuffer, void*	GBuffer, int ShiftR=-1)
	//!
	//! \perfinclude _FFT_Fwd1024__F6nm32scP6nm32scPPvPvi.html
    //--------------------------------------------------------------------
//global _FFT_Fwd1024Set	:label;
global _FFT_Fwd1024	:label;

//extern W1_1024_7bit	:long;
//extern W2_1024_7bit	:long;
//extern W1_1024_6bit	:long;
//extern W2_1024_6bit	:long;

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
	
	// Next 3 variables may be modified by FFT_Fwd1024Set for switch FFT_Fwd1024 from 7bit accuracy to 6 bit and vice versa 
global	W1_1024:word;//=W1_1024_7bit;
global	W2_1024:word;//=W2_1024_7bit;
global	DefaultShiftR_1024:word=14;		
	Rounder:long;

	struct SParam
		GSrcBuffer:word;
		LDstBuffer:word;
		LBuffer1:word;
		GBuffer1:word;
		ShiftR:word;
		
		LBuffer2:word;
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
//  Main Forward FFT-1024 procedure                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
<_FFT_Fwd1024>
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
	[Param.GSrcBuffer]=gr0;				//GSrcBuffer[1024*2]
	gr0=[--ar5];
	[Param.LDstBuffer]=gr0;				//GDstBuffer[1024*2]
	gr0=[--ar5]	with gr1=gr7<<11;
	[Param.LBuffer1]=gr0 with gr0+=gr1;	//LBuffer1[1024*2]
	[Param.LBuffer2]=gr0;				//LBuffer2[1024*2*2]
	gr0=[--ar5];
	[Param.GBuffer1]=gr0;				//GBuffer1[1024*2]
	gr0=[--ar5];
	[Param.ShiftR]=gr0					//ShiftR 
	
	////////////////////////////////////////////////////////////////////////////////////////
	// Default parameters intialization depending from 6 or 7 bit accuracy
		with gr0++;						// (gr0+1)=0 if ShiftR is stated as default
	
	if <>0 delayed skip 6;
		ar0=TableOfRounders with gr0--;
	gr0=[DefaultShiftR_1024];				// Variable Is Changed by FFT_Fwd1024Set to 14(for 7 bit) or 12(for 6bit)
	[Param.ShiftR]=gr0;
	with gr0<<=1;
	ar0,gr0=[ar0+=gr0];
	[Rounder]=ar0,gr0;
	

	//////////////////////////////////////////////////////////////
	//	The first radix-2 FFT
	//--------------------------------------
	// transforms input array X[i],where i=0..1023 (X[i]=[X[i].imag|X[i].real]), 
	// to array S[i],where i=0..2047 (S[i]=[S[i].imag|S[i].real]), 
	// array X begins from address GSrcBuffer
	// array S begins from address LBuffer
	// array S consisis two subarray S[0]..S[1023],conjg(S[0])..conjg(S[1023])
	// conjg() - complex conjugation function 
	//GENERAL REGISTERS ON INPUT
	// gr4=80000000h;
	// gr7=1
	//----------------------
	//*************** =>   ***********************
	//* GSrcBuffer  * =>   * LBuffer2  *         *
	//*************** =>   ***********************


	nb1=gr4 with gr1=gr7<<1;
	sb=gr1;
	
	ar0=LAddCmplxMask;			// Coef. for complex conjugation calculation
	rep 2 wfifo=[ar0++],ftw;

	ar4=[Param.GSrcBuffer];		// &X[0]
	ar5=ar4; ar4+=512*2;		// &X[512]
	ar6=ar4;					// &X[512]

	ar0=[Param.LBuffer2];		// &S[0]
	ar2=ar0; ar2+=1024*2;		// &conjg(S[0])

	ar1=ar0; ar1+=512*2;		// &S[512]
	ar3=ar2; ar3+=512*2;		// &conjg(S[512])
	wtw;

.repeat 16;
	rep 32 ram=[ar5++];							// X[512]  >>>
	rep 32 data=[ar4++] with ram+data;			// S[0]=X[0]+X[512] >>>
	rep 32 [ar0++]=afifo with vsum ,afifo,0;	// Conjg(S[0])
	rep 32 [ar2++]=afifo;						
	rep 32 data=[ar6++] with ram-data;			// S[512]=X[0]-X[512] >>>
	rep 32 [ar1++]=afifo with vsum ,afifo,0;	// Conjg(S[512])
	rep 32 [ar3++]=afifo;
.endrepeat;

	
	
	//////////////////////////////////////////////////////////////////
	//------- Second radix-32 FFT ----------------
	// transforms input array S[i],where i=0..2047 (S[i]=[S[i].imag|S[i].real]), 
	// to array T[i],where i=0..1023 (T[i]=[T[i].imag|T[i].real]), 
	// array S begin from address LBuffer2
	// array T begin from address LBuffer1
	// table of coef. GW1_1024=exp(-2*i*pi*512*k*n/1024) begins from address GW1_1024
	//GENERAL REGISTERS ON INPUT
	// gr4=80000000h;
	// gr7=1
	//----------------------
	//  *********************** => ***************
	//  * LBuffer2  *         * => * LBuffer1    *
	//  *********************** => ***************

	nb1=gr4;
	sb=02020202h;
	ar0=[Param.LBuffer2] with gr0=gr7<<5;	// gr0=16*2;
	
	ar5=[W1_1024];							// SinCos Table 1
	ar0=[Param.LBuffer2];					// &S[0]
	ar6=ar0;								// &S[0]
	ar1=ar0;ar1+=1024*2;					// &conjg(S[0])
	gr3=ar1;								// &conjg(S[0])
	ar3=ar5;								// SinCos Table 1


	ar2=[Param.LBuffer1];					// &T[0]
	gr5=ar2 with
		gr1=gr7<<5;							// gr1=16*2;
	gr2=gr7<<5;								// gr2=16*2

	gr7<<=1;								//	gr7=2!!!
	gr6=ar0 ;
	with gr6+=gr7;
	rep 32 wfifo=[ar0++gr0],ftw;			// S[0] >>>
	wtw;
	
//.repeat 15;
gr4=15;
<SecondLayer>
	// Multiply 1 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // SinCos Table 1
	ar1=gr3 with gr3+=gr7;
	rep 32 wfifo=[ar1++gr1];						// conjg(S[0]) >>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	// Multiply 1 - conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 wfifo=[ar0++gr0];						// S[512]>>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	ar2=gr5 with gr5+=gr7;
	rep 32 [ar2++gr2]=afifo;						// T[0]>>>
	// Multiply 2 ////////////////////////////////////////////////////////////////

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 wfifo=[ar1++gr1];						// conj(S[512]) >>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	// Multiply 2 conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	ar0=gr6 with gr6+=gr7;							// gr7=2
	rep 32 wfifo=[ar0++gr0],ftw;			// S[0] >>>
	rep 32 data=[ar5++],wtw with vsum ,data,afifo;  // GW1_1024[..]
	ar5=ar3 with gr4--;
	if <>0 delayed goto SecondLayer;
		rep 32 [ar2++gr2]=afifo;						// T[512]>>>
		nul;
//.endrepeat;

// Multiply 1 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // SinCos Table 1
	ar1=gr3 with gr3+=gr7;
	rep 32 wfifo=[ar1++gr1];						// conjg(S[0]) >>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	// Multiply 1 - conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 wfifo=[ar0++gr0];							// S[512]>>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	ar2=gr5 with gr5+=gr7;
	rep 32 [ar2++gr2]=afifo;						// T[0]>>>
	// Multiply 2 ////////////////////////////////////////////////////////////////

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 wfifo=[ar1++gr1];						// conj(S[512]) >>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	// Multiply 2 conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 data=[ar5++] with vsum ,data,afifo;  // GW1_1024[..]
	rep 32 [ar2++gr2]=afifo;						// T[512]>>>

	gr7>>=1;


	ar0=[Param.LBuffer1];							// &T[0]
	ar1=ar0;
	rep 16 wfifo=[ar0++],ftw;							// T[0]>>>
	
	//////////////////////////////////////////////////////////////////
	//------- third radix-16 FFT ----------------
	// transforms input array T[i],where i=0..1023 (S[i]=[S[i].imag|S[i].real]), 
	// at I stageе into temporary array YY[i],where i=0..2047 (YY[i]=[YY[i].imag|YY[i].real]), 
	// and then at II stageе array YY transformed into result array Y
	// Y[i],where i=0..1023 (Y[i]=[Y[i].imag|Y[i].real]), 
	// array T  begins from address	LBuffer1
	// array YY begins from address LBuffer2
	// array Y  begins from address	GDstBuffer
	// table of coef. GW2_1024=exp(-2*i*pi*k*i/1024) begin from address GW1_1024
	//------GENERAL REGISTERS ON INPUT-----
	// gr4=80000000h;
	// gr7=1
	// ar0=[Param.LBuffer1]+32;				// &T[32]
	// ar1=[Param.LBuffer1]					// &T[0]
	//----------------------
	//ar1=ar0;
	//  *************** => ***********************
	//  * LBuffer1    * => * LBuffer2  *         *
	//  *************** => ***********************

	ar5=[W2_1024]	with gr1=gr7<<10;			// gr1=512*2
	ar2=[Param.LBuffer2]					// &YY[0]
		with gr3=gr7<<11;					// gr3=1024*2
	ar3=ar2;	
	ar1+=gr1;								// &T[512] 
	ar3+=gr3;								// &YY[1024]

	wtw;
	//----------- I stage -------------------
.repeat 31;
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW2_1024
	rep 16 wfifo=[ar1++];							// T[512]>>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW2_1024
	rep 32 [ar2++]=afifo;							// YY[0]>>>

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW2_1024
	rep 16 wfifo=[ar0++];							// T[32]>>>
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW2_1024
	rep 32 [ar3++]=afifo;							// YY[1024]
.endrepeat;

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW2_1024
	rep 16 wfifo=[ar1++];							// T[527]
	rep 32 data=[ar5++],ftw,wtw with vsum ,data,afifo;  // GW2_1024
	rep 32 [ar2++]=afifo;							// YY[480]

	rep 32 data=[ar5++],ftw,wtw with vsum ,data,0;		// GW2_1024
	ar1=LAddCmplxMask with gr2=gr7<<1;
	sb=gr2;
	rep 2 wfifo=[ar1++];							// [1|0][0|-1] => wfifo
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW2_1024
	rep 32 [ar3++]=afifo;							// YY[992]



	//------------ II stage -------------------------------
	//    Summation [re*im+im*re | re*re - im*im] 
	// gr2=2
	// gr3 = 80000000h
	// WBUF =	[ 0,-1]
	//			[ 1, 0]
	// sb=2,gr3=nb=80000000h
	//   *********************** => ***************
	//   * LBuffer2  *         * => * GBuffer1    *
	//   *********************** => ***************
	wtw;
	//-------------------------
	ar4=[Param.LBuffer2]							// &YY[0]
		with gr5=gr7<<1;							// gr5=1*2
	gr2=[Param.GBuffer1];							// &Y[0]
	ar5=ar4;										
	ar5+=gr5 with									// &YY[1]
		gr0=gr7<<7;									// gr0=64*2;
	vr =[Rounder] with gr3=gr7<<2;					// gr3=2*2;
	gr4=gr7<<2;										// gr4=2*2;
	gr5=gr7<<2;										// gr5=2*2;
	
.repeat 32;
	rep 16 data=[ar5++gr5] with vsum ,data,vr;		// YY[1] >>
	rep 16 data=[ar4++gr4] with data + afifo;		// YY[0] >>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// Y[0] >>
.endrepeat;

	ar4=[Param.LBuffer2] with gr4=gr7<<11;							
	nul;
	ar4+=gr4										// &YY[1024]
		with gr6=gr7<<1;							// gr6=1*2
	ar6=ar4 
		with gr4=gr7<<2;							// gr4=2*2 
	ar5=ar6+gr6;									// &YY[1025]
	

	gr2=[Param.GBuffer1];
	gr2+=gr6;										// &Y[1]
.repeat 32;
	rep 16 data=[ar5++gr5] with vsum ,data,vr;		// &YY[1025]>>>
	rep 16 data=[ar4++gr4] with data + afifo;		// &YY[1024]>>>
	ar0=gr2 with gr2+=gr3;
	rep 16 [ar0++gr0]=afifo;						// &Y[1] >>>
.endrepeat;

	////////////////////////////////////////////////
	//  Right shift normalization
	//
	//  *************** => *************
	//  * GBuffer1    * => * LDstBuffer*
	//  *************** => *************
	ar0=[Param.GBuffer1];
	ar6=[Param.LDstBuffer];
	gr5=[Param.ShiftR];
	VEC_ARSH32_aaCG(ar0,ar6,1024*2,gr5);

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
//	gr7=t1;
return;
.wait;


end ".text_fft";