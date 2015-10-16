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




data ".data_fft_L"
	
	LAddCmplxMask:long[2]=(
			0000000100000000hl,
			00000000FFFFFFFFhl
			);
	struct SParam
		SrcBuffer	:word;
		DstBuffer	:word;
		Tmp1  		:word;
		Tmp2  		:word;
		Weights1	:word;
		Weights2	:word;
		Shift1    	:word;
		Shift2    	:word;
	end SParam;
	
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
global _FFT_Fwd256_16x16	:label;

<_FFT_Fwd256_16x16>
.branch;
	ar5=sp-2	 with gr7=false;
	push ar0,gr0 with gr7++;			// gr7=1 (CONST)
	push ar1,gr1 with gr1=gr7<<9;		// gr1=256*2;		
	push ar2,gr2 with gr2=gr7<<1;		// gr2=2(CONST)
	push ar3,gr3 with gr3=gr7<<31;		// gr3=80000000h;(CONST)				
	push ar4,gr4; 
	push ar5,gr5;
	push ar6,gr6 with gr6=gr7<<5;		// gr6=16*2
	ar0=[--ar5];						// GSrcBuffer[256*2]
	ar1=[--ar5];						// GDstBuffer[256*2]
	ar2=[--ar5];						// W0 GSrcBuffer[256*2]
	ar3=[--ar5];						// W1 GDstBuffer[256*2]
	ar4=[--ar5];						// Tmp0 LBuffer[256*3]
	ar5=[--ar5];						// Tmp1 GBuffer[256*2]
	//////////////////////////////////////////////////////////////
	// Carried out part of First radix-16 FFT 
	// Loading first 16 longs of GSrcBuffer into WBUF 
	// INPUT:
	// gr3=80000000h 
	// ar6=[Param.GSrcBuffer]
	// 
	nb1=80000000h;
	sb =02020202h;
	
	//--------------------------------------------------------
	
	////////////////////////////////////////////////////////////////////////////////////////
	// Default parameters intialization depending from 6 or 7 bit set accuracy
	// INPUT:
	// gr0=ShiftR
	
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
	rep 16 wfifo=[ar2],ftw,wtw;			// GSrcBuffer
.repeat 15;
	rep 16 data=[ar0],ftw,wtw with vsum ,data,0;		// [L]	W1_256
	rep 16 wfifo=[ar2];						// [G]	GSrcBuffer
	rep 16 data=[ar0],ftw,wtw with vsum ,data,afifo;	// [L]	LCosSin Table
	rep 16 [ar4]=afifo;							// [G]	GBuffer
	ar6+=gr6;
	ar6+=gr6;
	rep 16 data=[ar0],ftw,wtw with vsum ,data,0;		// [L]	W1_256
	rep 16 wfifo=[ar2];						// [G]	GSrcBuffer
	rep 16 data=[ar0],ftw,wtw with vsum ,data,afifo;	// [L]	LCosSin Table
	rep 16 [ar5]=afifo;							// [G]	GBuffer
	ar6+=gr6;
	ar6+=gr6;
	
.endrepeat;

	rep 16 data=[ar0],ftw,wtw with vsum ,data,0;		// [L]	W1_256
	rep 16 wfifo=[ar2];						// [G]	GSrcBuffer
	rep 16 data=[ar0],ftw,wtw with vsum ,data,afifo;	// [L]	LCosSin Table
	rep 16 [ar4]=afifo;							// [G]	GBuffer
	ar6+=gr6;
	ar6+=gr6;
	
	rep 16 data=[ar0],ftw,wtw with vsum ,data,0;		// [L]	W1_256
	sb=gr2;
	rep 2  wfifo=[ar2];							// [G]	[1|0][0|-1] => wfifo
	rep 16 data=[ar0],ftw,wtw with vsum ,data,afifo;	// [L]	LCosSin Table
	rep 16 [ar5]=afifo;							// [G]	GBuffer
	ar6+=gr6;
	ar6+=gr6;
	
	
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


	//-------------------------
.repeat 7;
	rep 32 ram =[ar4];							// [G]	GBuffer1 (Re)
	rep 32 data=[ar5] with vsum ,data,ram;		// [G]	GBuffer1 (Im)
	rep 32 [ar1]=afifo;							// [L]	LBuffer1
	ar6+=gr6;
	ar6+=gr6;
.endrepeat;
	rep 32 ram=[ar4];							// [G]	GBuffer1 (Re)
	sb =02020202h ;	
	rep 32 data=[ar5] with vsum ,data,ram;		// [G]	GBuffer1 (Im)
	rep 16 wfifo=[ar3],ftw,wtw;					// [L]	LBuffer1
	rep 32 [ar1]=afifo;						// [L]	LBuffer1
	ar6+=gr6;
	ar6+=gr6;
	
	
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

.repeat 15;
	rep 16 data =[ar1],ftw,wtw with vsum ,data,0;			// [G]	W2_256
	rep 16 wfifo=[ar3];							// [L]	LBuffer1
	rep 16 data =[ar1],ftw,wtw with vsum ,data,afifo;		// [G]	GWkn_256
	rep 16 [ar4]=afifo;								// [L]	LBuffer2
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	
	rep 16 data =[ar1],ftw,wtw with vsum ,data,0;			// [G]	W2_256
	rep 16 wfifo=[ar3];							// [L]	LBuffer1
	rep 16 data =[ar1],ftw,wtw with vsum ,data,afifo;		// [G]	GWkn_256
	rep 16 [ar5]=afifo;								// [L]	LBuffer2
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	
.endrepeat;

	rep 16 data =[ar1],ftw,wtw with vsum ,data,0;			// [G]	W2_256
	rep 16 wfifo=[ar3];							// [L]	LBuffer1
	rep 16 data =[ar1],ftw,wtw with vsum ,data,afifo;		// [G]	GWkn_256
	rep 16 [ar4]=afifo;								// [L]	LBuffer2
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	
	rep 16 data =[ar1],ftw,wtw with vsum ,data,0;			// [G]	W2_256
	sb=gr2;
	rep 2  wfifo=[ar3],ftw;								// [L]	LAddCmplxMask
	rep 16 data =[ar1],wtw with vsum ,data,afifo;		// [G]	GWkn_256
	rep 16 [ar5]=afifo;								// [L]	LBuffer2
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	ar6+=gr6;
	
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

.repeat 16;
	rep 16 ram=[ar4] ;		// [L]	LBuffer
	rep 16 data =[ar5] with vsum ,data,ram;		// [L]	LBuffer
	rep 16 [ar1]=afifo;						// [G]	GDstBuffer
	ar6+=gr6;
	ar6+=gr6;
		
.endrepeat;

	
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