//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6405 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*   (C-callable functions)                                                */
//*                                                                         */
//*   File:             iFFT4096.asm                                        */
//*   Contents:         Routine for inverse iFFT 4096 of complex array      */
//*                     with 32 bit elements                                */
//*                                                                         */
//*   Software design:  D. Spesivtsev                                       */
//*                                                                         */
//*   Version           1.0                                                 */
//*   Start date:       08.04.2009                                          */
//*   Release   $Date: 2009/04/08 14:19:56 $                                */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

global _FFT_Inv4096: label;

import from rtmacro;
import from macros;

data ".data_fft_L"

	extern IW1_4096: word;
	extern IW2_4096: word;
	extern IW3_4096: word;
	
	struct SParam
		GSrcBuffer: word;
		GDstBuffer: word;
		LBuffer1: word;
		GBuffer2: word;
	end SParam;
	.align;	Param: SParam;
	
end ".data_fft_L";
	
data ".data_fft_G"

	GAddCmplxMask:long[2] = (
			0000000100000000hl,
			00000000FFFFFFFFhl
			);

end ".data_fft_G";

begin ".text_fft"

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//        Main Inverse FFT-4096 procedure                                   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

<_FFT_Inv4096>
.branch;
	ar5 = sp - 2 with gr7 = false;						// gr7=0
	push ar0,gr0 with gr7++;							// gr7=1 (CONST)
	push ar1,gr1;
	push ar2,gr2 with gr2 = gr7 << 1;					// gr2=2 (CONST)
	push ar3,gr3 with gr3 = gr7 << 31;					// gr3=80000000h (CONST)
	push ar4,gr4 with gr4 = gr2 << 5;					// gr4=2^6
	push ar5,gr5 with gr1 = gr7;						// gr1=1 (почти CONST)
	push ar6,gr6 with gr6 = gr7 << 8;					// gr6=256
	
//////////////////////////////////////////////////////////////////////////////
	
	ar6 = [--ar5];										// GSrcBuffer
	ar0 = [--ar5];										// GDstBuffer
	gr5 = [--ar5];										// LBuffer1
	ar2 = [--ar5];										// GBuffer2

	[Param.GSrcBuffer] = ar6;							// GSrcBuffer
	[Param.GDstBuffer] = ar0;							// GDstBuffer
	[Param.LBuffer1]  = gr5;							// LBuffer1[4096*2]
	[Param.GBuffer2]  = ar2;							// GBuffer2[4096*2]

	vr = gr4;											// vr=2^6 (добавл€етс€ дл€ нормализации)
	
	//////////////////////////////////////////////////////////////////////////
	//        First radix-16 FFT 
	//------------------------------------------------------------------------
	// gr3=80000000h
	// gr6=256
	// gr2=2
	
	nb1 = gr3;
	sb = 02020202h;
	gr4 = [Param.GSrcBuffer];							// X
	ar5 = [Param.GBuffer2];
	gr6 = gr6 << 1;										// gr6=256*2
	
	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6], ftw;						// [G] GSrcBuffer (8 + 8 т.)
	WTW_REG(gr3);												// 1-е 8 т.
.repeat 255;
	ar1 = IW1_4096;
	rep 32 data = [ar1++], ftw with vsum, data, 0;		// [L] IW1_4096
	WTW_REG(gr3);												// 2-е 8 т.
	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];							// [G] GSrcBuffer (8 + 8 т.)
	rep 32 data = [ar1++], ftw with vsum, data, afifo;	// [L] IW1_4096
	WTW_REG(gr3);												// 1-е 8 т.
	rep 32 [ar5++] = afifo;								// [G] «апись A, B, C, D в GBuffer2
.endrepeat;
	ar1 = IW1_4096;
	rep 32 data = [ar1++], ftw with vsum, data, 0;		// [L] IW1_4096
	WTW_REG(gr3);												// 2-е 8 т.
	
	sb = gr2;
	ar6 = GAddCmplxMask;
	rep 2 wfifo = [ar6++];								// [G] [1|0][0|-1] => wfifo
	
	rep 32 data = [ar1++], ftw with vsum, data, afifo;	// [L] IW1_4096
	rep 32 [ar5++] = afifo;								// [G] «апись A, B, C, D в GBuffer2
	
	//////////////////////////////////////////////////////////////////////////
	//        First Summation [re*im+im*re | re*re-im*im] 
	//------------------------------------------------------------------------
	// gr1=1

	WTW_REG(gr3);
	ar6 = [Param.GBuffer2] with gr4 = gr1 << 2;			// gr4=4
	ar0 = [Param.LBuffer1] with gr6 = gr1 << 1;
	ar4 = ar6 + gr6 with gr6 = gr4;						// gr6=4
.repeat 128;
	rep 32 data = [ar4++gr4] with vsum, data, vr;		// [G] GBuffer2 (Im)
	rep 32 data = [ar6++gr6] with data + afifo;			// [G] GBuffer2 (Re)
	rep 32 [ar0++] = afifo;								// [L] LBuffer1 (S)
.endrepeat;

	//////////////////////////////////////////////////////////////////////////
	//        First Right Shift Normalization
	//------------------------------------------------------------------------

	ar0 = [Param.LBuffer1];								// [L] LBuffer1 (не нормализованное S)
	gr5 = 7;
	ar6 = [Param.GBuffer2];								// [G] GBuffer2 (будет нормализованное S)
	VEC_ARSH32_aaCG(ar0, ar6, 4096 * 2, gr5);
	
	//////////////////////////////////////////////////////////////////////////
	//        Second radix-16 FFT 
	//------------------------------------------------------------------------
	// gr3=80000000h
	// S находитс€ в GBuffer2
	// gr1=1
	// gr2=2

	nb1 = gr3;
	sb = 02020202h;
	ar1 = IW2_4096;
	ar5 = [Param.GBuffer2];
	gr4 = ar5;											// S
	ar5 += 4096 * 2;									// GBuffer2 (2-€ половина)
	gr6 = gr1 << 9;										// gr6=256*2

	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6], ftw;						// [G] GBuffer2 (8 + 8 т.)
	WTW_REG(gr3);												// 1-е 8 т.
.repeat 255;
	rep 32 data = [ar1++], ftw with vsum, data, 0;		// [L] IW2_4096
	WTW_REG(gr3);												// 2-е 8 т.
	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];							// [G] GBuffer2 (8 + 8 т.)
	rep 32 data = [ar1++], ftw with vsum, data, afifo;	// [L] IW2_4096
	WTW_REG(gr3);												// 1-е 8 т.
	rep 32 [ar5++] = afifo;								// [G] «апись A, B, C, D в GBuffer2 (2-€ половина)
.endrepeat;
	rep 32 data = [ar1++], ftw with vsum, data, 0;		// [L] IW2_4096
	WTW_REG(gr3);												// 2-е 8 т.

	sb = gr2;
	ar6 = GAddCmplxMask;
	rep 2 wfifo = [ar6++];								// [G] [1|0][0|-1] => wfifo

	rep 32 data = [ar1++], ftw with vsum, data, afifo;	// [L] IW2_4096
	rep 32 [ar5++] = afifo;								// [G] «апись A, B, C, D в GBuffer2 (2-€ половина)
	
	//////////////////////////////////////////////////////////////////////////
	//        Second Summation [re*im+im*re | re*re-im*im] 
	//------------------------------------------------------------------------
	// gr1=1
	
	WTW_REG(gr3);
	ar6 = [Param.GBuffer2] with gr4 = gr1 << 2;			// gr4=4
	ar6 += 4096 * 2;
	ar0 = [Param.LBuffer1] with gr6 = gr1 << 1;
	ar4 = ar6 + gr6 with gr6 = gr4;						// gr6=4
.repeat 128;
	rep 32 data = [ar4++gr4] with vsum, data, vr;		// [G] GBuffer2 (2-€ половина) (Im)
	rep 32 data = [ar6++gr6] with data + afifo;			// [G] GBuffer2 (2-€ половина) (Re)
	rep 32 [ar0++] = afifo;								// [L] LBuffer1 (T)
.endrepeat;

	//////////////////////////////////////////////////////////////////////////
	//        Second Right Shift Normalization
	//------------------------------------------------------------------------

	ar0 = [Param.LBuffer1];								// [L] LBuffer1 (не нормализованное T)
	gr5 = 7;
	ar6 = [Param.GBuffer2];								// [G] GBuffer2 (будет нормализованное T)
	VEC_ARSH32_aaCG(ar0, ar6, 4096 * 2, gr5);

	//////////////////////////////////////////////////////////////////////////
	//        Third radix-16 FFT 
	//------------------------------------------------------------------------
	// gr3=80000000h
	// T находитс€ в GBuffer2
	// gr1=1
	// gr2=2

	nb1 = gr3;
	sb = 02020202h;
	ar1 = IW3_4096;
	ar5 = [Param.GBuffer2];
	gr4 = ar5;											// T
	ar5 += 4096 * 2;
	gr6 = gr1 << 9;										// gr6=256 * 2

	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6], ftw;						// [G] GBuffer2 (8 + 8 т.)
	WTW_REG(gr3);												// 1-е 8 т.
.repeat 255;
	rep 32 data = [ar1++], ftw with vsum, data, 0;		// [L] IW3_4096
	WTW_REG(gr3);												// 2-е 8 т.
	ar6 = gr4 with gr4 += gr2;
	rep 16 wfifo = [ar6++gr6];							// [G] GBuffer2 (8 + 8 т.)
	rep 32 data = [ar1++], ftw with vsum, data, afifo;	// [L] IW3_4096
	WTW_REG(gr3);												// 1-е 8 т.
	rep 32 [ar5++] = afifo;								// [G] «апись A, B, C, D в GBuffer2 (2-€ половина)
.endrepeat;
	rep 32 data = [ar1++], ftw with vsum, data, 0;		// [L] IW3_4096
	WTW_REG(gr3);												// 2-е 8 т.

	sb = gr2;
	ar6 = GAddCmplxMask;
	rep 2 wfifo = [ar6++];								// [G] [1|0][0|-1] => wfifo

	rep 32 data = [ar1++], ftw with vsum, data, afifo;	// [L] IW3_4096
	rep 32 [ar5++] = afifo;								// [G] «апись A, B, C, D в GBuffer2 (2-€ половина)

	//////////////////////////////////////////////////////////////////////////
	//        Third Summation [re*im+im*re | re*re-im*im] 
	//------------------------------------------------------------------------
	// gr1=1

	WTW_REG(gr3);
	ar6 = [Param.GBuffer2] with gr4 = gr1 << 2;			// gr4=4
	ar6 += 4096 * 2;
	gr5 = [Param.LBuffer1] with gr6 = gr1 << 1;
	ar4 = ar6 + gr6 with gr6 = gr4;						// gr6=4
	gr3 = gr1 << 5;										// gr3=16*2
	gr1 = gr1 << 9;										// gr1=256*2 (— этого момента gr1 больше != 1 (не CONST))
	gr7 = gr1 << 9;
	vr = gr7;											// vr=2^18

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;		// [G] GBuffer2 (2-€ половина) (Im)
	rep 16 data = [ar6++gr6] with data + afifo;			// [G] GBuffer2 (2-€ половина) (Re)
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;							// [L] LBuffer1
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	gr0 = gr5 with gr5 += gr2;
.repeat 16;
	rep 16 data = [ar4++gr4] with vsum, data, vr;
	rep 16 data = [ar6++gr6] with data + afifo;
	ar1 = gr0 with gr0 += gr3;
	rep 16 [ar1++gr1] = afifo;
.endrepeat;

	//////////////////////////////////////////////////////////////////////////
	//        Third Right Shift Normalization
	//------------------------------------------------------------------------

	ar0 = [Param.LBuffer1];
	gr5 = 19;											// 7+12
	ar6 = [Param.GDstBuffer];							// Y
	VEC_ARSH32_aaCG(ar0, ar6, 4096 * 2, gr5);

//////////////////////////////////////////////////////////////////////////////

	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return with gr7 = false;
.wait;
end ".text_fft";