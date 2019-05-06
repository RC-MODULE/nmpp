//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT2048.asm                                         */
//*   Contents:         Routine for forward FFT 2048 of complex array       */
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
    //! \fn int FFT_Fwd2048(nm32sc*	GSrcBuffer, nm32sc*	GDstBuffer, void*	LBuffer, int ShiftR=-1)
	//!
	//! \perfinclude _FFT_Fwd2048__F6nm32scP6nm32scPPvi.html
    //--------------------------------------------------------------------
//global _FFT_Fwd2048Set	:label;
global _FFT_Fwd2048	:label;

//extern W1_2048_7bit	:long;
//extern W2_2048_7bit	:long;
//extern W1_2048_6bit	:long;
//extern W2_2048_6bit	:long;

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
	
	// Next 3 variables may be modified by FFT_Fwd2048Set for switch FFT_Fwd2048 from 7bit accuracy to 6 bit and vice versa 
global	W1_2048:word;//=W1_2048_7bit;
global	W2_2048:word;//=W2_2048_7bit;
global	DefaultShiftR_2048:word=14;		
	Rounder:long;

	struct SParam
		GSrcBuffer:word;
		GDstBuffer:word;
		LBuffer1:word;
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
<_FFT_Fwd2048>
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
	//ar0=Param.GDstBuffer;

	gr0=[--ar5];
	[Param.GSrcBuffer]=gr0;				//GDstBuffer
	gr0=[--ar5];
	[Param.GDstBuffer]=gr0;				//GSrcBuffer
	gr0=[--ar5]	with gr1=gr7<<13;		//gr1=2048*4
	[Param.LBuffer1]=gr0 with gr0+=gr1;	//LBuffer1
	[Param.LBuffer2]=gr0;				//LBuffer2
	gr0=[--ar5];
	[Param.ShiftR]=gr0					//Right shift 

	////////////////////////////////////////////////////////////////////////////////////////
	// Default parameters intialization depending from 6 or 7 bit accuracy
		with gr0++;						// (gr0+1)=0 if ShiftR is stated as default
	
	if <>0 delayed skip 6;
		ar0=TableOfRounders with gr0--;
	gr0=[DefaultShiftR_2048];				// Variable Is Changed by FFT_Fwd2048Set to 14(for 7 bit) or 12(for 6bit)
	[Param.ShiftR]=gr0;
	with gr0<<=1;
	ar0,gr0=[ar0+=gr0];
	[Rounder]=ar0,gr0;
	


	//////////////////////////////////////////////////////////////
	//	First radix-2 FFT with attachment of FFT ouput conjugation 
	//--------------------------------------
	// transforms input array X[i],where i=0..2047 (X[i]=[X[i].imag|X[i].real]), 
	// into array S[i],where i=0..4095 (S[i]=[S[i].imag|S[i].real]), 
	// array X begins from address GSrcBuffer
	// array S begins from address LBuffer
	// array S consists two subarrays S[0]..S[2047],conjg(S[0])..conjg(S[2047])
	// conjg() - complex conjugation function 
	//GENERAL REGISTERS ON INPUT
	// gr4=80000000h;
	// gr7=1
	//----------------------
	//  *************** => ***********************
	//  * GSrcBuffer  * => * LBuffer2  *         *
	//  *************** => ***********************

	nb1=gr4 with gr1=gr7<<1;
	sb=gr1;
	
	ar0=LAddCmplxMask;			// Coef. for complex conjugation calculation
	rep 2 wfifo=[ar0++],ftw;

	ar4=[Param.GSrcBuffer];		// &X[0]
	ar5=ar4; ar4+=1024*2;		// &X[1024]
	ar6=ar4;					// &X[1024]

	ar0=[Param.LBuffer2];		// &S[0]
	ar2=ar0; ar2+=2048*2;		// &conjg(S[0])

	ar1=ar0; ar1+=1024*2;		// &S[1024]
	ar3=ar2; ar3+=1024*2;		// &conjg(S[1024])
	WTW_REG_DEPRICATED(gr4);


.repeat 32;
	rep 32 ram=[ar5++];							// X[1024]  >>>
	rep 32 data=[ar4++] with ram+data;			// S[0]=X[0]+X[1024] >>>
	rep 32 [ar0++]=afifo with vsum ,afifo,0;	// Conjg(S[0])
	rep 32 [ar2++]=afifo;						
	rep 32 data=[ar6++] with ram-data;			// S[1024]=X[0]-X[1024] >>>
	rep 32 [ar1++]=afifo with vsum ,afifo,0;	// Conjg(S[1024])
	rep 32 [ar3++]=afifo;
.endrepeat;


	//////////////////////////////////////////////////////////////////
	//------- Second radix-32 FFT ----------------
	// transforms input array S[i],where i=0..4095
	// into array T[i],where i=0..2047 (T[i]=[T[i].imag|T[i].real]), 
	// input  array S begins from address LBuffer1
	// output array T begins from address LBuffer2
	// table of coef. - GW1_2048
	//GENERAL REGISTERS ON INPUT
	// gr4=80000000h;
	// gr7=1
	//----------------------
	//*********************** =>  *************** 
	//* LBuffer2  *         * =>  * LBuffer1    * 
	//*********************** =>  *************** 

	nb1=gr4;
	sb=02020202h;


	ar5=[W1_2048];							// SinCos Table 1
	ar0=[Param.LBuffer2];
	ar2=[Param.LBuffer1];					// &T[0]
	ar1=ar0	with gr1=gr7<<12;				// 2048*2
	ar1+=gr1;
		
	ar3=ar5 with gr0=gr7<<6;				// gr0=32*2;;
	gr3=ar1 with gr1=gr7<<6;				// gr0=32*2;

	gr6=ar0 with gr2=gr7<<6;				// gr2=32*2;
	gr5=ar2 with gr7<<=1;
	
	rep 32 wfifo=[ar0++gr0],ftw;			// S[0] >>>
	gr6+=gr7;
	WTW_REG_DEPRICATED(gr4);

.repeat 31;
	// Multiply 1 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // SinCos Table 1
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar1++gr1];						// conjg(S[0]) >>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	// Multiply 1 - conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar0++gr0];						// S[512]>>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	ar2=gr5 with gr5+=gr7;
	rep 32 [ar2++gr2]=afifo;						// T[0]>>>
	// Multiply 2 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar1++gr1];						// conj(S[512]) >>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	// Multiply 2 conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	
	ar0=gr6 with gr6+=gr7;
	
	rep 32 wfifo=[ar0++gr0];						// S[1] >>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	ar5=ar3 with gr3+=gr7;							// gr6=2
	ar1=gr3 ;
	rep 32 [ar2++gr2]=afifo;						// T[1024]>>>
.endrepeat;

	// Multiply 1 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // SinCos Table 1
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar1++gr1];						// conjg(S[0]) >>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	// Multiply 1 - conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar0++gr0];						// S[512]>>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	ar2=gr5 with gr5+=gr7;
	rep 32 [ar2++gr2]=afifo;						// T[0]>>>
	// Multiply 2 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,0;		// GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar1++gr1];						// conj(S[512]) >>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	// Multiply 2 conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++] with vsum ,data,afifo;		// GW1_2048[..]
	rep 32 [ar2++gr2]=afifo;						// T[1024]>>>
	gr7>>=1;										// gr7=1
	//gr7=1
	//////////////////////////////////////////////////
	//  Calculation complex conjugation attachment
	//  ***************  => ***********************
	//  * LBuffer1    *  => * LBuffer1  * conjg   *
	//  ***************  => ***********************

	nb1=gr4 with gr1=gr7<<1;
	sb=gr1;

	ar0=LAddCmplxMask;			// Coef. for complex conjugation calculation
	rep 2 wfifo=[ar0++],ftw;
	WTW_REG_DEPRICATED(gr4);
	
	ar0=[Param.LBuffer1];
	//ar4=[Param.LBuffer2];
	ar4=ar0; ar4+=2048*2;
	.repeat 64;
		rep 32 data=[ar0++] with vsum ,data,0;
		rep 32 [ar4++]=afifo;
	.endrepeat;
	//////////////////////////////////////////////////////////////////
	//------- Third radix-32 FFT ----------------
	//GENERAL REGISTERS ON INPUT
	// gr4=80000000h;
	// gr7=1
	//----------------------
	//  ***********************  =>  ***************
	//  * LBuffer1  *         *  =>  * LBuffer2    *
	//  ***********************  =>  ***************
	nb1=gr4;
	sb=02020202h;

	ar0=[Param.LBuffer1] ;	// gr0=64*2;
	ar1=ar0;ar1+=2048*2;
	ar4=ar0;ar4+=1024*2;
	ar6=ar1;ar6+=1024*2;
	gr2=gr7<<7;								//64*2;
	gr3=gr7<<7;								//64*2;

	ar2=[Param.LBuffer2];					// &T[0]
	ar3=ar2;ar3+=2;

	ar5=[W2_2048];							// SinCos Table 1

	gr0=ar2;
	gr1=ar3 with gr6=gr7<<2; //gr6=4;
	rep 32 wfifo=[ar0++],ftw;			// S[0] >>>
	vr =[Rounder];
	WTW_REG_DEPRICATED(gr4);
.repeat 31;
	// Multiply 1 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,vr;		// GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // SinCos Table 1
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar1++];							// conjg(S[0]) >>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	// Multiply 1 - conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar4++];							// S[512]>>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	ar2=gr0 with gr0+=gr6;
	rep 32 [ar2++gr2]=afifo;						// T[0]>>>
	// Multiply 2 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,vr;		// GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar6++];							// conj(S[512]) >>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	// Multiply 2 conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar0++];							// S[1] >>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	//rep 32 data=[ar5++] with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	ar3=gr1 with gr1+=gr6;
	rep 32 [ar3++gr3]=afifo;						// T[1024]>>>
.endrepeat;

	// Multiply 1 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,vr;		// GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // SinCos Table 1
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar1++];							// conjg(S[0]) >>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	// Multiply 1 - conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar4++];							// S[512]>>>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	ar2=gr0 with gr0+=gr6;
	rep 32 [ar2++gr2]=afifo;						// T[0]>>>
	// Multiply 2 ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,vr;		// GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 wfifo=[ar6++];							// conj(S[512]) >>
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	// Multiply 2 conjg ////////////////////////////////////////////////////////////////
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	rep 32 data=[ar5++],ftw with vsum ,data,afifo;  // GW1_2048[..]
	WTW_REG_DEPRICATED(gr4);
	ar3=gr1;
	rep 32 data=[ar5++] with vsum ,data,afifo;		// GW1_2048[..]
	rep 32 [ar3++gr3]=afifo;						// T[1024]>>>
	

	///////////////////////////////////////////////
	// Normalization
	//  ***************  => **************
	//  * LBuffer2    *  => * GDstBuffer *
	//  ***************  => **************
	

	ar0=[Param.LBuffer2];
	ar6=[Param.GDstBuffer];
	gr5=[Param.ShiftR];
	VEC_ARSH32_aaCG(ar0,ar6,2048*2,gr5);
	
	


<Finish>
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

