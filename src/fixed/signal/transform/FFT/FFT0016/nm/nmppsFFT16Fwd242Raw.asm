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
//import from printx.mlb;
    //==================================
    //! \fn int nmppsFFT32FwdRaw(nm32sc*	src, nm32sc*	dst, NmppsFFTSpec*	spec)
	//!
	//! \perfinclude nmppsFFT32FwdRaw.html
    //==================================

macro START_TIMER()
	//call _clock;
	//[t]=gr7;
end  START_TIMER;

macro STOP_TIMER()
	//extern _clock:label;
	//call _clock; 
	//gr0 =[t]; 	
	//gr7-=gr0; 
end STOP_TIMER;

macro CRC32(adr,size)
	//extern vec_crc32:label;
	//ar0 = [adr];
	//gr5 = size;
	//call vec_crc32;
end CRC32;


extern vec_RShift32s:label;

data ".data_fft_L"
	t: word;
	GAddCmplxMask:long[2]=(
		0000000100000000hl,
		00000000FFFFFFFFhl);
		
	
	tmp00: word;
	tmp01: word;
	tmp10: word;
	tmp11: word;
	dst0:  word;
	dst1:  word;
	
end ".data_fft_L";




begin ".text_nmplv"
	

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Core Forward FFT-16 procedure                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// FFT16Core242 call    = 214 ticks (Real performance)
// Peak performance= 8*3+4*2*4+8*2+8*2 = 88 ticks
// Real/Peak performance (reg call)= 41%
// 16:04 14.05.2019

const pY   = dst0;
const pAIm = dst0;
const pBRe = dst1;


const pARe = tmp00;
const pB   = tmp01;
const pD   = tmp01;

const pC   = tmp10;
const pA   = tmp10;
const pBIm = tmp11;
	

global FFT16Core242	:label;
      <FFT16Core242	>
.branch;
	//-----------------------------
	// Register intrerface:
	// ar0 - source array
	// ar2 - cosTbl array        ! permananent purpose register
	// ar3 - sinTbl array        ! permananent purpose register
	// ar4 - {round,shift} array ! permananent purpose register
	// 
	// [tmp00] = buffer0;
	// [tmp01] = buffer0 + 8*2;
	// [tmp10] = buffer1;
	// [tmp11] = buffer1 + 8*2;
	// [dst0]  = output ;
	// [dst1]  = output +8*2;
	//-----------------------------
	
	//------------- 0 ---------------
	//for (int j = 0; j < 8; j++) {
	//	C[j].re = X[j].re + X[j + 8].re;
	//	C[j].im = X[j].im + X[j + 8].im;
	//	D[j].re = X[j].re - X[j + 8].re;
	//	D[j].im = X[j].im - X[j + 8].im;
	//}
	nb1 = 080000000h with gr7=false;
	sb  = 020002h	 with gr7++; 
	wtw;
	//ar0=[pX];
	ar5=[pC];
	ar6=[pD];
	rep 8 ram,data  =[ar0++] with data;
	ar1 = ar0		with gr7++;	// gr7=2;
	rep 8 data=[ar0++] with data+afifo;
	rep 8 [ar5++]=afifo;
	
	rep 8 data=[ar1++] with ram-data;
	rep 8 [ar6++]=afifo;
	
	//PRINT_MATRIX_32S("[pC]",[pC],8,2);
	//PRINT_MATRIX_32S("[pD]",[pD],8,2);
	//------------- 1 ---------------
	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++) {
	//		A[2 * i] += C[2 * j]	 * expFFT<8>(2 * i*j, amplitude);
	//		B[2 * i] += C[2 * j + 1] * expFFT<8>(2 * i*j + i, amplitude);
	//	}
    // 
	// load_wfifo(C, 2, 4);
	// for (int i = 0; i < 4; i++) {
	// 	vsum_data(pwRe, ARe + 2 * i, round);
	// 	vsum_data(pwIm, AIm + 2 * i, 0);
	// 	pwRe += 4;
	// 	pwIm += 4;
	// }
	//PRINT_MATRIX_16S("[pWRe]", [pWRe], 4, 4);
	//PRINT_MATRIX_16S("[pWIm]", [pWIm], 4, 4);
	
	
	//ar0 = [pWRe];
	//ar1 = [pWIm];
	ar0 = [pC] 	 with gr0=gr7<<1;
	ar5 = [pARe] with gr5=gr7<<1;
	ar6 = [pAIm] with gr6=gr7<<1; // gr0=4
	
	rep 4 wfifo=[ar0++gr0],ftw,wtw;
	
	gr4 = [ar4++];// [round0];
	vr = gr4;
	rep 4 data=[ar2++] with vsum ,data,vr;
	rep 4 [ar5++gr5]=afifo;
	rep 4 data=[ar3++] with vsum ,data,0;
	rep 4 [ar6++gr6]=afifo;
	
		
	
	//PRINT_MATRIX_32X("[pARe]",[pARe],8,2);
	//PRINT_MATRIX_32X("[pAIm]",[pAIm],8,2);
	

	//------------- 1.1 ---------------
    //
	//	load_wfifo(C + 1, 2, 4);
	//	for (int i = 0; i < 4; i++) {
	//		vsum_data(pwRe, BRe + 2 * i, 0);
	//		vsum_data(pwIm, BIm + 2 * i, 0);
	//		pwRe += 4;
	//		pwIm += 4;
	//	}
	
	//ar0 = [pWRe];
	//ar1 = [pWIm];
	ar0 = [pC] with gr0=gr7; 	// gr0=2
	ar5 = [pBRe];
	ar6 = [pBIm];
	ar0+=gr0   with gr0=gr7<<1;   // gr0=2*2
	//gr5 = 2*2;
	//gr6 = 2*2;
	//gr0 = 2*2;
	
	rep 4 wfifo=[ar0++gr0],ftw,wtw;
	rep 4 data=[ar2++] with vsum ,data,0;
	rep 4 [ar5++gr5]=afifo;
	rep 4 data=[ar3++] with vsum ,data,0;
	rep 4 [ar6++gr6]=afifo;
	
	//PRINT_MATRIX_32X("[pBRe]",[pBRe],8,2);
	//PRINT_MATRIX_32X("[pBIm]",[pBIm],8,2);
	
	//	------------- 1.2 ---------------
	//	for (int i = 0; i < 4; i++)
	//		for (int j = 0; j < 4; j++) {
	//			A[2 * i + 1] += D[2 * j] * expFFT<8>(2 * i*j + j, amplitude);
	//			B[2 * i + 1] += D[2 * j + 1] * expFFT<16>(2 * (2 * i*j + j + i) + 1, amplitude);
	//		}
    //
	//	load_wfifo(D, 2, 4);
	//	for (int i = 0; i < 4; i++) {
	//		vsum_data(pwRe, ARe + 2 * i + 1, round);
	//		vsum_data(pwIm, AIm + 2 * i + 1, 0);
	//		pwRe += 4;
	//		pwIm += 4;
	//	}
	ar0 = [pD];
	ar5 = [pARe] with gr5 = gr7;
	ar6 = [pAIm] with gr6 = gr7;
	ar5+= gr5    with gr5 = gr7<<1;
	ar6+= gr6    with gr6 = gr7<<1;
	//gr5 = 2*2;
	//gr6 = 2*2;
	//gr0 = 2*2;
	
	rep 4 wfifo=[ar0++gr0],ftw,wtw;
	rep 4 data=[ar2++] with vsum ,data,vr;
	rep 4 [ar5++gr5]=afifo;
	rep 4 data=[ar3++] with vsum ,data,0;
	rep 4 [ar6++gr6]=afifo;
	
	//PRINT_MATRIX_32X("[pARe]",[pARe],8,2);
	//PRINT_MATRIX_32X("[pAIm]",[pAIm],8,2);

	//------------- 1.3 ---------------
	//	load_wfifo(D + 1, 2, 4);
	//	for (int i = 0; i < 4; i++) {
	//		vsum_data(pwRe, BRe + 2 * i + 1, 0);
	//		vsum_data(pwIm, BIm + 2 * i + 1, 0);
	//		pwRe += 4;
	//		pwIm += 4;
	//	}
	ar0 = [pD]   with gr0 = gr7;
	ar5 = [pBRe] with gr5 = gr7;
	ar6 = [pBIm] with gr6 = gr7;
	ar0+= gr0    with gr0 = gr7<<1;
	ar5+= gr5    with gr5 = gr7<<1;
	ar6+= gr6    with gr6 = gr7<<1;
	//gr5 = 2*2;
	//gr6 = 2*2;
	//gr0 = 2*2;
	
	rep 4 wfifo=[ar0++gr0],ftw,wtw;
	rep 4 data=[ar2++] with vsum ,data,0;
	rep 4 [ar5++gr5]=afifo;
	rep 4 data=[ar3++] with vsum ,data,0;
	rep 4 [ar6++gr6]=afifo;
	
	//PRINT_MATRIX_32X("[pBRe]",[pBRe],8,2);
	//PRINT_MATRIX_32X("[pBIm]",[pBIm],8,2);

	//------------2.0
	//	for (int i = 0; i < 8; i++) {
	//		A[i].re = ARe[i].re - AIm[i].im;
	//		A[i].im = ARe[i].im + AIm[i].re;
	//		B[i].re = BRe[i].re - BIm[i].im;
	//		B[i].im = BRe[i].im + BIm[i].re;
	//	}
	sb  = gr7; //=2
	ar6 = GAddCmplxMask;
	ar0 = [pARe];
	ar1 = [pAIm];
	ar5 = [pA];
	
	rep 2 wfifo = [ar6++],ftw,wtw;
	rep 8 ram = [ar0++];
	rep 8 data=[ar1++] with vsum ,data,ram;
	rep 8 [ar5++]=afifo;
	
	ar0 = [pBRe];
	ar1 = [pBIm];
	ar5 = [pB];
	
	rep 8 ram = [ar0++];
	rep 8 data =[ar1++] with vsum ,data,ram;
	rep 8 [ar5++]=afifo;
	
	//PRINT_MATRIX_32X("[pA]",[pA],8,2);
	//PRINT_MATRIX_32X("[pB]",[pB],8,2);

	//	//------------3.0
	//	for (int i = 0; i < 8; i++) {
	//		Y[i].re = A[i].re + B[i].re;
	//		Y[i].im = A[i].im + B[i].im;
	//		Y[i + 8].re = A[i].re - B[i].re;
	//		Y[i + 8].im = A[i].im - B[i].im;
	//	}
	
	ar0 = [pA];
	ar1 = [pB];
	ar5 = [pY];
	rep 8 ram = [ar0++];
	rep 8 data = [ar1++] with ram+data;
	rep 8 [ar5++] = afifo;
	
	ar1 = [pB];
	rep 8 data = [ar1++] with ram-data;
	rep 8 [ar5++] = afifo;
		
	//PRINT_MATRIX_32X("[pY]",[pY],16,2);
	
return ;	
	
	
//global _nmppsFFT16FwdRaw	:label;
//      <_nmppsFFT16FwdRaw>

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Forward FFT-16 procedure   without final normalization             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// C++ call 			= 381 ticks
// Peak performance= 8*3+4*2*4+8*2+8*2 = 88 ticks
// Real/Peak performance (C++ call)= 23%
// 16:04 14.05.2019	  
global _nmppsFFT16Fwd242Raw	:label;
      <_nmppsFFT16Fwd242Raw>

	ar5=sp-2		with gr7 =false;
	push ar0,gr0	with gr7++;			
	push ar1,gr1	with gr7<<=4;		// gr7=8*2
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;	
	push ar6,gr6;
	
	ar0 = [--ar5];						// src[16*2]
	gr6 = [--ar5];						// dst[16*2]
	ar4 = [--ar5];						// spec
	gr2 = [ar4++];						// tmp0[16*2]
	gr1 = [ar4++];						// tmp1[16*2]
	
	
	[tmp00] = gr2 with gr2+=gr7;
	[tmp01] = gr2;
	[tmp10] = gr1 with gr1+=gr7;
	[tmp11] = gr1;
	[dst0]  = gr6 with gr6+=gr7;
	[dst1]  = gr6;
	
	//START_TIMER();
	//gr7 =2;
	delayed call FFT16Core242;
		ar2 = [ar4++];						// weights[]
		ar3 = [ar4++];						// weights[]
	
	
		
	
	
	
	
	//STOP_TIMER();
	//PRINT_32X("dt=",gr7);
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
return;

	

//global _nmppsFFT16Fwd	:label;
//     <_nmppsFFT16Fwd>
	
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Main Forward FFT-16 procedure                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// C++ call 			= 442 ticks
// Peak performance= 8*3+4*2*4+8*2+8*2+16 = 104 ticks
// Real/Peak performance (C++ call)= 23.5%
// 16:04 14.05.2019
	
global _nmppsFFT16Fwd242	:label;
      <_nmppsFFT16Fwd242>
.branch;
	ar5=sp-2		with gr7 =false;
	push ar0,gr0	with gr7++;			
	push ar1,gr1	with gr7<<=4;		// gr7=8*2
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;	
	push ar6,gr6;
	
	ar0 = [--ar5];						// src[16*2]
	gr6 = [--ar5];						// dst[16*2]
	ar4 = [--ar5];						// spec
	gr2 = [ar4++];						// tmp0[16*2]
	gr1 = [ar4++];						// tmp1[16*2]
	
	
	[tmp00] = gr2 with gr2+=gr7;
	[tmp01] = gr2;
	[dst0]  = gr1 with gr1+=gr7;
	[dst1]  = gr1;
	[tmp10] = gr6 with gr6+=gr7;
	[tmp11] = gr6;
	
	delayed call FFT16Core242;
		ar2 = [ar4++];						// weights[]
		ar3 = [ar4++];						// weights[]
	
	ar0 = [dst0]  with gr0=gr7;
	ar6 = [tmp10] with gr6=gr7;
	delayed call vec_RShift32s	with gr5 = gr7<<4;// 16*2
		gr4 = [ar4++];	
		nul;					
		
	
	
	//START_TIMER();
	
	//STOP_TIMER();
	
	//PRINT_32X("dt=",gr7);
		
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

	

return ;
.wait;

end ".text_nmplv";