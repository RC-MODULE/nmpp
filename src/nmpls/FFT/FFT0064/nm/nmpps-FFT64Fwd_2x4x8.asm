//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640X Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             FFT3.asm                                            */
//*   Contents:         Routine for forward FFT 32 of complex array         */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

    //--------------------------------------------------------------------
    //! \fn int nmppsFFT32FwdRaw(nm32sc*	src, nm32sc*	dst, NmppsFFTSpec*	spec)
	//!
	//! \perfinclude nmppsFFT32FwdRaw.html
    //--------------------------------------------------------------------




data ".data_fft_L"

	GAddCmplxMask:long[2]=(
		0000000100000000hl,
		00000000FFFFFFFFhl);
		

	vec_tbl_sb_nb_w_int_RightShift7:long[8]=(
			1000000000000000000000001000001010000000000000000000000010000010bl,	// sb 7
			1111111110000000000000000000000011111111100000000000000000000000bl,	// nb 7
			
			0000000000000000hl,	// ShiftR 7
			0000000000000001hl,
			00000000FF000000hl,
			0000000000000000hl,
			0000000100000000hl,
		   0FF00000000000000hl);
	src	: word;
	sLo : word;
	sHi	: word;
	dRe	: word;
	dIm	: word;
	d	: word;
	n	: word;
	yRe	: word;
	yIm	: word;
	y	: word;
	dst	: word;
end ".data_fft_L";


begin ".text_fft"


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Forward FFT-32 procedure                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
// total  instructions =  ticks
// scalar instructions =  ticks
// vector instructions =  = ticks
//         
// HW TICKS: 1043                               
global _nmppsFFT64Fwd2x4x8:label;
<_nmppsFFT64Fwd2x4x8>
.branch;
	ar5=sp-2	 with gr7=false;
	push ar0,gr0 with gr7++;			
	push ar1,gr1 with gr7++;		
	push ar2,gr2;		
	push ar3,gr3;		
	push ar4,gr4; 
	push ar5,gr5;		
	push ar6,gr6 with gr6=gr7;			// gr6=2
	ar0 = [--ar5];						// src[32*2] [red]
	ar6 = [--ar5];						// dst[32*2] [red]
	ar5 = [--ar5];						// spec
	ar2 = [ar5++];						// tmp[32*2] [green]
	ar3 = [ar5++];						// tmp[32*2] [yellow]
	ar4 = [ar5++];						// weights[16*2*2]
	
	[src] = ar0;
	[dst] = ar6;
	[sLo] = ar2; ar2+= 64;
	[sHi] = ar2;
	[dRe] = ar6;
	[dIm] = ar3;
	[d]   = ar2;
	[n]   = ar3;
	[y]   = ar3;
	[yRe] = ar6;
	[yIm] = ar2;
	//-- stage 0 ------------------------------------------------------
	// [0.0] 
	ar0 = [src];
	ar1 = ar0;
	ar1+= 64;
	ar2 = ar1;
	nb1 = 80000000h;
	ar5 = [sLo];	
	ar6 = [sHi];
	rep 32 ram =[ar0++],wtw;							 
	rep 32 data=[ar1++] with ram+data;					 
	rep 32 [ar5++]=afifo;								 
	rep 32 data=[ar2++] with ram-data;					 
	rep 32 [ar6++]=afifo; 								 
	//-------- stage 1 ------------------------------------------------
	// [1.0.0.]
	sb  = 00020002h;
	ar0 = [sLo];
	ar5 = [dRe];
	ar6 = [dIm];
	gr7 = 8;
	gr0 = 8*2;
	gr5 = 8*2*2;
	gr6 = gr5;
	with gr7--;
	<NextStage100>
		ar0 = ar2+gr2 with gr2+=gr4;
		// [1.0.0.re]  	[dRe]=[W.re]*[sLo]
		rep 4  wfifo=[ar0++gr0] ,ftw,wtw;				// sLo[8*p+m].re;
		rep 4  data =[ar4++] 	 	with vsum ,data,vr;	// afifo+=w.re * sLo[8*p+m];
		rep 4  [ar5++gr5]=afifo;						// dRe[8*k+m]=afifo;
		
		// [1.0.0.im]	[dIm]=[W.im]*[sLo]
		rep 4 data =[ar4++]        		with vsum ,data,0;		// stage[5]
		rep 4 [ar6++gr6]=afifo;							// stage[6] W.Re*X[0..15]
	if <>0 goto NextStage100 with gr7--;
	
	// [1.0.1.]
	ar0 = [sHi];
	ar5 = [dRe];
	ar6 = [dIm];
	gr7 = 8;
	with gr7--;
	<NextStage101>
		// [1.0.1.re]  	[dRe]=[W.re]*[sHi]
		rep 4  wfifo=[ar0] ,ftw,wtw;							// stage[2]
		rep 4  data =[ar4] 		 	with vsum ,data,vr;		// stage[3]
		rep 4  [ar5]=afifo;									// stage[4] W.Re*X[0..15]
		
		// [1.0.1.im]	[dIm]=[W.im]*[sLo]
		rep 4 data =[ar4++]        		with vsum ,data,0;		// stage[5]
		rep 4 [ar6]=afifo;									// stage[6] W.Re*X[0..15]
			
	if <>0 goto NextStage101 with gr7--;
	
	
		
	//---- complex conjugation sum --------------------------------------------------------
	// [1.1]
	sb  = gr6; 							// sb=00000002h;
	ar0 = GAddCmplxMask;
	rep 2 wfifo=[ar0++],ftw,wtw;							// stage[10]
	ar0 = [dRe];
	ar1 = [dIm];
	ar6 = [d];

	rep 32 ram =[ar0];									// stage[11]
	rep 32 data=[ar1] 		with vsum ,data,ram;			// stage[11]
	rep 32 [ar6]=afifo;								// stage[11]
	rep 32 ram =[ar0];									// stage[12]
	rep 32 data=[ar1] 	 	with vsum ,data,ram;			// stage[12]
	rep 32 [ar6]=afifo;								// stage[12]
	
	//----------- normalization (right shift 7)---------------------
	// [1.2]
	ar6 = gr7;
	ar5 = vec_tbl_sb_nb_w_int_RightShift7;
	sb  = [ar5++];
	nb1 = [ar5++];	
	ar1 = [d];
	ar6 = [n];
	rep 6  wfifo=[ar5++],ftw,wtw;
	rep 32 data=[ar0++] with vsum ,shift data,0;			// stage[13]
	rep 32 [ar6++]=afifo;
	rep 32 data=[ar0++] with vsum ,shift data,0;			// stage[13]
	rep 32 [ar6++]=afifo;
	
	// ------------------------------------
	// [2.0]
	ar0 = [n];
	ar5 = [yRe];
	ar6 = [yIm];
	gr7 = 8;
	sb  = 02020202h;
	nb1 = 80000000h;
	with gr7--;
	<NextStage200>
		rep 8 wfifo= [ar0], ftw, wtw;
		rep 8 data = [ar4] with vsum ,data,0;
		rep 8 [ar5]=afifo;
		
		rep 8 data = [ar4] with vsum ,data,0;
		rep 8 [ar6]=afifo;
	if <>0 goto NextStage200 with gr7--;
	
	// [2.1]
	sb  = gr6; 							// sb=00000002h;
	ar0 = [yRe];
	ar1 = [yIm];
	ar2 = ar1;
	ar6 = [y];
	ar5 = GAddCmplxMask;
	rep 2  wfifo=[ar5++],ftw,wtw;							// stage[10]
	rep 32 ram =[ar0++];									// stage[11]
	rep 32 data=[ar1++] ,wtw with vsum ,data,ram;			// stage[11]
	rep 32 [ar6++]=afifo;								// stage[11]
	rep 32 ram =[ar0++];									// stage[12]
	rep 32 data=[ar1++]  	with vsum ,data,ram;			// stage[12]
	rep 32 [ar6++]=afifo;								// stage[12]
	
	// [2.2]
	ar0 = [y];
	ar6 = [dst];
	ar5 = vec_tbl_sb_nb_w_int_RightShift7;
	sb  = [ar5++];
	nb1 = [ar5++];	
	rep 6  wfifo=[ar5++],ftw,wtw;
	rep 32 data=[ar0++] with vsum ,shift data,0;			// stage[13]
	rep 32 [ar6++]=afifo;
	rep 32 data=[ar0++] with vsum ,shift data,0;			// stage[13]
	rep 32 [ar6++]=afifo;
		
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